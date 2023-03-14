from sc_kpm.logging import get_kpm_logger
from termcolor import colored
from typing import List

from sc_client import client

from sc_client.models import ScAddr, ScTemplate, ScLinkContent
from sc_client.constants import sc_types

from sc_kpm import ScAgentClassic, ScResult, ScKeynodes

from sc_kpm.utils.action_utils import get_action_arguments
from sc_kpm.utils import create_edge, create_link
from sc_kpm.utils.creation_utils import create_node, create_structure, wrap_in_set


osm_level_to_tag = {
    '2': ['addr:city', 'addr:district', 'addr:region'],
    '4': ['addr:city', 'addr:district', 'addr:region'],
    '6': ['addr:city', 'addr:district'],
    '8': ['addr:city'],
    '9': ['addr:country', 'addr:district', 'addr:region'],
    '10': ['addr:city'],
    '': ['addr:country', 'addr:district', 'addr:region', 'addr:city']
}

logger = get_kpm_logger()

class OpenStreetMapAgent(ScAgentClassic):
    def __init__(self):
        super().__init__("action_generate_osm_query")
        self._keynodes = ScKeynodes()

    def on_event(self, class_node: ScAddr, edge: ScAddr, action_node: ScAddr) -> ScResult:
        if not self._confirm_action_class(action_node):
            return ScResult.SKIP

        status = ScResult.OK
        logger.debug("GetLakesByAreaAgent starts")

        try:
            if action_node is None or not action_node.is_valid():
                raise Exception("The question node isn't valid.")

            [node] = get_action_arguments(action_node, 1)
            contour = create_node(sc_types.NODE_CONST_STRUCT)
            create_edge(
                sc_types.EDGE_ACCESS_CONST_POS_PERM,
                contour,
                node
            )

            elements = self.get_query(node)
            if not elements:
                elements = self.generate_osm_query(node)

            self.add_nodes_to_answer(contour, elements)

            contour_edge = create_edge(
                sc_types.EDGE_D_COMMON_CONST,
                action_node,
                contour
            )
            create_edge(
                sc_types.EDGE_ACCESS_CONST_POS_PERM,
                self._keynodes['nrel_answer'],
                contour_edge
            )
            create_edge(
                sc_types.EDGE_ACCESS_CONST_POS_PERM,
                self._keynodes['question_finished_successfully'],
                action_node,
            )
        except Exception as ex:
            logger.debug(colored(str(ex), color='red'))
            self.set_unsuccessful_status(action_node)
            status = ScResult.ERROR
        finally:
            create_edge(
                sc_types.EDGE_ACCESS_CONST_POS_PERM,
                self._keynodes['question_finished'],
                action_node,
            )
        return status

    def set_unsuccessful_status(self, action_node: ScAddr) -> ScAddr:
        create_edge(
            sc_types.EDGE_ACCESS_CONST_POS_PERM,
            self._keynodes['question_finished_unsuccessfully'],
            action_node,
        )

    def get_query(self, node: ScAddr) -> List[ScAddr]:
        template = ScTemplate()
        template.triple_with_relation(
            node,
            [sc_types.EDGE_D_COMMON_VAR, '_dedge'],
            [sc_types.LINK_VAR, '_value'],
            [sc_types.EDGE_ACCESS_VAR_POS_PERM, '_aedge'],
            self._keynodes.resolve('nrel_osm_query', sc_types.NODE_CONST_NOROLE)
        )
        template_result = client.template_search(template)
        if template_result:
            logger.debug(colored(
                "Get from base: " + client.get_link_content(template_result[0].get('_value'))[0].data, color='green'))
            return [
                template_result[0].get('_dedge'),
                template_result[0].get('_value'),
                template_result[0].get('_aedge'),
                self._keynodes['nrel_osm_query']
            ]
        else:
            return []

    def get_main_idtf(self, node: ScAddr) -> str:
        template = ScTemplate()
        template.triple_with_relation(
            node,
            sc_types.EDGE_D_COMMON_VAR,
            [sc_types.LINK_VAR, '_value'],
            sc_types.EDGE_ACCESS_VAR_POS_PERM,
            self._keynodes['nrel_main_idtf']
        )
        template.triple(
            self._keynodes.resolve('name', sc_types.NODE_CONST_CLASS),
            sc_types.EDGE_ACCESS_VAR_POS_PERM,
            "_value"
        )
        template_result = client.template_search(template)
        if template_result:
            return client.get_link_content(template_result[0].get('_value'))[0].data

        return ""

    def get_admin_level(self, node):
        template = ScTemplate()
        template.triple_with_relation(
            node,
            sc_types.EDGE_D_COMMON_VAR,
            [sc_types.LINK_VAR, '_value'],
            sc_types.EDGE_ACCESS_VAR_POS_PERM,
            self._keynodes.resolve('nrel_admin_level', sc_types.NODE_CONST_NOROLE)
        )
        template_result = client.template_search(template)
        if template_result:
            return client.get_link_content(template_result[0].get('_value'))[0].data
        return ""

    def get_values_links_of_tags_for_node(self, node: ScAddr, admin_level):
        global osm_level_to_tag
        template = ScTemplate()
        template.triple_with_relation(
            node,
            sc_types.EDGE_D_COMMON_VAR,
            [sc_types.LINK_VAR, '_value'],
            sc_types.EDGE_ACCESS_VAR_POS_PERM,
            [sc_types.NODE_VAR, "_tag_relation"]
        )
        template.triple_with_relation(
            "_tag_relation",
            sc_types.EDGE_D_COMMON_VAR,
            [sc_types.NODE_VAR, "_tag_class"],
            sc_types.EDGE_ACCESS_VAR_POS_PERM,
            self._keynodes.resolve('nrel_tag', sc_types.NODE_CONST_NOROLE),
        )
        template.triple(
            self._keynodes.resolve('concept_openstreetmap_tag', sc_types.NODE_CONST_CLASS),
            sc_types.EDGE_ACCESS_VAR_POS_PERM,
            "_tag_class"
        )
        template.triple_with_relation(
            "_tag_class",
            sc_types.EDGE_D_COMMON_VAR,
            [sc_types.LINK_VAR, "_tag_name"],
            sc_types.EDGE_ACCESS_VAR_POS_PERM,
            self._keynodes['nrel_main_idtf']
        )
        template_result = client.template_search(template)
        relations_tags = {}
        for item in template_result:
            tag = client.get_link_content(item.get('_tag_name'))[0].data
            value = client.get_link_content(item.get('_value'))[0].data
            if tag not in osm_level_to_tag.get(admin_level):
                relations_tags[tag] = value
        return relations_tags

    def get_values_nodes_of_tags_for_node(self, node: ScAddr, admin_level):
        global osm_level_to_tag
        template = ScTemplate()
        template.triple_with_relation(
            node,
            sc_types.EDGE_D_COMMON_VAR,
            [sc_types.NODE_VAR, '_value'],
            sc_types.EDGE_ACCESS_VAR_POS_PERM,
            [sc_types.NODE_VAR, "_tag_relation"]
        )
        template.triple_with_relation(
            "_tag_relation",
            sc_types.EDGE_D_COMMON_VAR,
            [sc_types.NODE_VAR, "_tag_class"],
            sc_types.EDGE_ACCESS_VAR_POS_PERM,
            self._keynodes.resolve('nrel_tag', sc_types.NODE_CONST_NOROLE),
        )
        template.triple(
            self._keynodes.resolve('concept_openstreetmap_tag', sc_types.NODE_CONST_CLASS),
            sc_types.EDGE_ACCESS_VAR_POS_PERM,
            "_tag_class"
        )
        template.triple_with_relation(
            "_tag_class",
            sc_types.EDGE_D_COMMON_VAR,
            [sc_types.LINK_VAR, "_tag_name"],
            sc_types.EDGE_ACCESS_VAR_POS_PERM,
            self._keynodes['nrel_main_idtf']
        )
        template_result = client.template_search(template)
        relations_tags = {}
        for item in template_result:
            tag = client.get_link_content(item.get('_tag_name'))[0].data
            value = self.get_main_idtf(item.get('_value'))
            if osm_level_to_tag.get(admin_level) and tag not in osm_level_to_tag.get(admin_level):
                if tag != 'addr:region':
                    relations_tags[tag] = value
        return relations_tags

    def get_way(self, node: ScAddr) -> bool:
        template = ScTemplate()
        template.triple(
            self._keynodes.resolve('concept_way', sc_types.NODE_CONST_CLASS),
            sc_types.EDGE_ACCESS_VAR_POS_PERM,
            node
        )
        template_result = client.template_search(template)
        return bool(template_result)

    def get_search_area_name(self, node: ScAddr) -> str:
        template = ScTemplate()
        template.triple_with_relation(
            node,
            sc_types.EDGE_D_COMMON_VAR,
            [sc_types.NODE_VAR, '_search_area'],
            sc_types.EDGE_ACCESS_VAR_POS_PERM,
            self._keynodes.resolve('nrel_search_area', sc_types.NODE_CONST_NOROLE)
        )
        template_result = client.template_search(template)
        if template_result:
            return self.get_main_idtf(template_result[0].get('_search_area'))
        else:
            return 'Беларусь'

    def generate_osm_query(self, node) -> list:
        admin_level = self.get_admin_level(node)
        is_way = self.get_way(node)
        relations_tags = self.get_values_links_of_tags_for_node(node, admin_level)
        relations_tags.update(self.get_values_nodes_of_tags_for_node(node, admin_level))
        relation = ''
        for k, v in relations_tags.items():
            relation += '["' + k + '"="' + v + '"]'
        if admin_level is None:
            if not is_way:
                query = f'[out:json][timeout:25];area["name:ru"="{self.get_search_area_name(node)}"]->.searchArea;' \
                    f'(node["name:ru"="{self.get_main_idtf(node)}"]{relation}(area.searchArea);' \
                    f'way["name:ru"="{self.get_main_idtf(node)}"]{relation}(area.searchArea);' \
                    f'relation["name:ru"="{self.get_main_idtf(node)}"]{relation}(area.searchArea););out center;>;out skel qt;'
            else:
                query = f'[out:json][timeout:25];area["name:ru"="{self.get_search_area_name(node)}"]->.searchArea;' \
                    f'(way["name:ru"="{self.get_main_idtf(node)}"]{relation}(area.searchArea););out center;>;out skel qt;'
        else:    
            query = f'[out:json][timeout:25];area["name:en"="Belarus"]->.searchArea;' \
                f'(relation["name:ru"="{self.get_main_idtf(node)}"]{relation}(area.searchArea););out center;>;out skel qt;'
        logger.debug(colored('Generated: ' + query, color='green'))
        query_link = create_link(query)
        query_edge = create_edge(
            sc_types.EDGE_D_COMMON_CONST,
            node,
            query_link
        )
        query_edge2 = create_edge(
            sc_types.EDGE_ACCESS_CONST_POS_PERM,
            self._keynodes['nrel_osm_query'],
            query_edge
        )
        return [query_edge, query_link, query_edge2, self._keynodes['nrel_osm_query']]

    def add_nodes_to_answer(self, contour: ScAddr, nodes):
        if contour is None:
            contour = create_node(sc_types.NODE_CONST_STRUCT)
        if nodes is None:
            nodes = []
        for node in nodes:
            create_edge(
                sc_types.EDGE_ACCESS_CONST_POS_PERM,
                contour,
                node
            )