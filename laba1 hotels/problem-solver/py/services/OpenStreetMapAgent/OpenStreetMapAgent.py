from termcolor import colored

from common import ScAgent, ScEventParams, ScKeynodes
from sc import *

osm_level_to_tag = {
    '2': ['addr:city', 'addr:district', 'addr:region'],
    '4': ['addr:city', 'addr:district', 'addr:region'],
    '6': ['addr:city', 'addr:district'],
    '8': ['addr:city'],
    '9': ['addr:country', 'addr:district', 'addr:region'],
    '10': ['addr:city'],
    None: ['addr:country', 'addr:district', 'addr:region', 'addr:city']
}


class OpenStreetMapAgent(ScAgent):
    def __init__(self, module):
        super().__init__(module)
        self.ctx = module.ctx
        self.keynodes = ScKeynodes(self.ctx)
        self.main_node = None

    def RunImpl(self, evt: ScEventParams) -> ScResult:
        self.main_node = evt.other_addr
        status = ScResult.Ok

        if self.module.ctx.HelperCheckEdge(
                self.keynodes['action_generate_osm_query'],
                self.main_node,
                ScType.EdgeAccessConstPosPerm,
        ):
            try:
                if self.main_node is None or not self.main_node.IsValid():
                    raise Exception("The question node isn't valid.")

                node = self.get_action_argument(self.main_node, 'rrel_1')
                contour = self.ctx.CreateNode(ScType.NodeConstStruct)
                self.ctx.CreateEdge(
                    ScType.EdgeAccessConstPosPerm,
                    contour,
                    node
                )

                elements = self.get_query(node)
                if elements is None:
                    elements = self.generate_osm_query(node)

                self.add_nodes_to_answer(contour, elements)

                contour_edge = self.ctx.CreateEdge(
                    ScType.EdgeDCommonConst,
                    self.main_node,
                    contour
                )
                self.ctx.CreateEdge(
                    ScType.EdgeAccessConstPosPerm,
                    self.keynodes['nrel_answer'],
                    contour_edge
                )
                self.ctx.CreateEdge(
                    ScType.EdgeAccessConstPosPerm,
                    self.keynodes['question_finished_successfully'],
                    self.main_node,
                )
            except Exception as ex:
                print(colored(str(ex), color='red'))
                self.set_unsuccessful_status()
                status = ScResult.Error
            finally:
                self.ctx.CreateEdge(
                    ScType.EdgeAccessConstPosPerm,
                    self.keynodes['question_finished'],
                    self.main_node,
                )
        return status

    def set_unsuccessful_status(self):
        self.module.ctx.CreateEdge(
            ScType.EdgeAccessConstPosPerm,
            self.keynodes['question_finished_unsuccessfully'],
            self.main_node,
        )

    def get_action_argument(self, question: ScAddr, rrel: str, argument_class=None) -> ScAddr:
        actual_argument = "_actual_argument"

        keynodes = self.keynodes

        template = ScTemplate()
        template.TripleWithRelation(
            question,
            ScType.EdgeAccessVarPosPerm,
            ScType.NodeVar >> actual_argument,
            ScType.EdgeAccessVarPosPerm,
            keynodes[rrel],
        )
        if argument_class is not None:
            template.Triple(keynodes[argument_class], ScType.EdgeAccessVarPosPerm, actual_argument)

        search_result = self.ctx.HelperSearchTemplate(template)

        search_result_size = search_result.Size()
        if search_result_size > 0:
            argument_node = search_result[0][actual_argument]
        else:
            raise Exception("The argument node isn't found.")

        return argument_node

    def get_query(self, node):
        template = ScTemplate()
        template.TripleWithRelation(
            node,
            ScType.EdgeDCommonVar >> 'dedge',
            ScType.LinkVar >> 'value',
            ScType.EdgeAccessVarPosPerm >> 'aedge',
            self.keynodes['nrel_osm_query']
        )
        template_result = self.ctx.HelperSearchTemplate(template)
        if template_result.Size():
            print(colored("Get from base: " + self.ctx.GetLinkContent(template_result[0]['value']).AsString(),
                          color='green')
                  )
            return [template_result[0]['dedge'],
                    template_result[0]['value'],
                    template_result[0]['aedge'],
                    self.keynodes['nrel_osm_query']
                    ]
        else:
            return None

    def get_main_idtf(self, node):
        template = ScTemplate()
        template.TripleWithRelation(
            node,
            ScType.EdgeDCommonVar,
            ScType.LinkVar >> 'value',
            ScType.EdgeAccessVarPosPerm,
            self.keynodes['nrel_main_idtf']
        )
        template.Triple(
            self.keynodes['name'],
            ScType.EdgeAccessVarPosPerm,
            "value"
        )
        template_result = self.ctx.HelperSearchTemplate(template)
        value = ''
        if template_result.Size():
            value = self.ctx.GetLinkContent(template_result[0]['value']).AsString()

        return value

    def get_admin_level(self, node):
        template = ScTemplate()
        template.TripleWithRelation(
            node,
            ScType.EdgeDCommonVar,
            ScType.LinkVar >> 'value',
            ScType.EdgeAccessVarPosPerm,
            self.keynodes['nrel_admin_level']
        )
        template_result = self.ctx.HelperSearchTemplate(template)
        if template_result.Size():
            return self.ctx.GetLinkContent(template_result[0]['value']).AsString()
        return None

    def get_values_links_of_tags_for_node(self, node, admin_level):
        global osm_level_to_tag
        template = ScTemplate()
        template.TripleWithRelation(
            node,
            ScType.EdgeDCommonVar,
            ScType.LinkVar >> 'value',
            ScType.EdgeAccessVarPosPerm,
            ScType.NodeVar >> "tag_relation"
        )
        template.TripleWithRelation(
            "tag_relation",
            ScType.EdgeDCommonVar,
            ScType.NodeVar >> "tag_class",
            ScType.EdgeAccessVarPosPerm,
            self.keynodes['nrel_tag'],
        )
        template.Triple(
            self.keynodes['concept_openstreetmap_tag'],
            ScType.EdgeAccessVarPosPerm,
            "tag_class"
        )
        template.TripleWithRelation(
            "tag_class",
            ScType.EdgeDCommonVar,
            ScType.LinkVar >> "tag_name",
            ScType.EdgeAccessVarPosPerm,
            self.keynodes['nrel_main_idtf']
        )
        template_result = self.ctx.HelperSearchTemplate(template)
        relations_tags = {}
        if template_result.Size():
            for i in range(template_result.Size()):
                tag = self.ctx.GetLinkContent(template_result[i]['tag_name']).AsString()
                value = self.ctx.GetLinkContent(template_result[i]['value']).AsString()
                if tag not in osm_level_to_tag.get(admin_level):
                    relations_tags[tag] = value
        return relations_tags

    def get_values_nodes_of_tags_for_node(self, node, admin_level):
        global osm_level_to_tag
        template = ScTemplate()
        template.TripleWithRelation(
            node,
            ScType.EdgeDCommonVar,
            ScType.NodeVar >> 'value',
            ScType.EdgeAccessVarPosPerm,
            ScType.NodeVar >> "tag_relation"
        )
        template.TripleWithRelation(
            "tag_relation",
            ScType.EdgeDCommonVar,
            ScType.NodeVar >> "tag_class",
            ScType.EdgeAccessVarPosPerm,
            self.keynodes['nrel_tag'],
        )
        template.Triple(
            self.keynodes['concept_openstreetmap_tag'],
            ScType.EdgeAccessVarPosPerm,
            "tag_class"
        )
        template.TripleWithRelation(
            "tag_class",
            ScType.EdgeDCommonVar,
            ScType.LinkVar >> "tag_name",
            ScType.EdgeAccessVarPosPerm,
            self.keynodes['nrel_main_idtf']
        )
        template_result = self.ctx.HelperSearchTemplate(template)
        relations_tags = {}
        if template_result.Size():
            for i in range(template_result.Size()):
                tag = self.ctx.GetLinkContent(template_result[i]['tag_name']).AsString()
                value = self.get_main_idtf(template_result[i]['value'])
                if tag not in osm_level_to_tag.get(admin_level):
                    relations_tags[tag] = value
        return relations_tags

    def get_way(self, node) -> bool:
        template = ScTemplate()
        template.Triple(
            self.keynodes['concept_way'],
            ScType.EdgeAccessVarPosPerm,
            node
        )
        template_result = self.ctx.HelperSearchTemplate(template)
        if template_result.Size() > 0:
            return True
        else:
            return False

    def get_search_area_name(self, node) -> str:
        template = ScTemplate()
        template.TripleWithRelation(
            node,
            ScType.EdgeDCommonVar,
            ScType.NodeVar >> '_search_area',
            ScType.EdgeAccessVarPosPerm,
            self.keynodes['nrel_search_area']
        )
        template_result = self.ctx.HelperSearchTemplate(template)
        if template_result.Size() > 0:
            return self.get_main_idtf(template_result[0]['_search_area'])
        else:
            return ''

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
                query = f'[out:json][timeout:25];area["name:en"="Belarus"]->.searchArea;' \
                    f'(node["name"="{self.get_main_idtf(node)}"](area.searchArea);' \
                    f'relation["name"="{self.get_main_idtf(node)}"]{relation}(area.searchArea););out center;>;out skel qt;'
            else:
                query = f'[out:json][timeout:25];area["name"="{self.get_search_area_name(node)}"]->.searchArea;' \
                    f'(way["name"="{self.get_main_idtf(node)}"]{relation}(area.searchArea););out center;>;out skel qt;'
        else:    
            query = f'[out:json][timeout:25];area["name:en"="Belarus"]->.searchArea;' \
                f'(relation["name"="{self.get_main_idtf(node)}"]{relation}(area.searchArea););out center;>;out skel qt;'
        print(colored('Generated: ' + query, color='green'))
        query_link = self.ctx.CreateLink()
        elements = []
        if self.ctx.SetLinkContent(query_link, query):
            query_edge = self.ctx.CreateEdge(
                ScType.EdgeDCommonConst,
                node,
                query_link
            )
            query_edge2 = self.ctx.CreateEdge(
                ScType.EdgeAccessConstPosPerm,
                self.keynodes['nrel_osm_query'],
                query_edge
            )
            elements += [query_edge, query_link, query_edge2, self.keynodes['nrel_osm_query']]
        else:
            raise Exception("Invalid content: " + query)
        return elements

    def add_nodes_to_answer(self, contour=None, nodes=None):
        if contour is None:
            contour = self.ctx.CreateNode()
        if nodes is None:
            nodes = []
        for node in nodes:
            self.ctx.CreateEdge(
                ScType.EdgeAccessConstPosPerm,
                contour,
                node
            )
