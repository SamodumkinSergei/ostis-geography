from sc_kpm.logging import get_kpm_logger
from termcolor import colored

from sc_client import client

from sc_client.models import ScAddr, ScTemplate
from sc_client.constants import sc_types

from sc_kpm import ScAgentClassic, ScResult, ScKeynodes

from sc_kpm.utils.action_utils import get_action_arguments
from sc_kpm.utils import create_edge
from sc_kpm.utils.creation_utils import create_structure, wrap_in_set

logger = get_kpm_logger()


class GetLakesByAreaAgent(ScAgentClassic):
    def __init__(self):
        super().__init__("action_get_lake_by_area")
        self._keynodes = ScKeynodes()

    def on_event(self, class_node: ScAddr, edge: ScAddr, action_node: ScAddr) -> ScResult:
        if not self._confirm_action_class(action_node):
            return ScResult.SKIP

        status = ScResult.OK
        logger.debug("GetLakesByAreaAgent starts")
        try:
            logger.debug("GetLakesByAreaAgent get arguments")

            first_area_node, second_area_node = get_action_arguments(action_node, 2)

            answer_node = create_structure(first_area_node, second_area_node)

            lake_area = self.get_lakes_with_area()
            first_area = float(client.get_link_content(first_area_node)[0].data)
            second_area = float(client.get_link_content(second_area_node)[0].data)

            results = []
            for lake, area in lake_area.items():
                if first_area <= area <= second_area:
                    print(colored(str(area), 'green'))
                    results.append(lake)

            for lake in results:
                logger.debug("GetLakesByAreaAgent get answer")
                self.add_lake_to_answer(lake, answer_node)

            self.finish_agent(action_node, answer_node)
            logger.debug("GetLakesByAreaAgent ends")

        except Exception as ex:
            self.set_unsuccessful_status(action_node)
            status = ScResult.ERROR
        finally:
            create_edge(
                sc_types.EDGE_ACCESS_CONST_POS_PERM,
                self._keynodes['question_finished'],
                action_node,
            )
        return status

    def set_unsuccessful_status(self, action_node: ScAddr) -> None:
        create_edge(
            sc_types.EDGE_ACCESS_CONST_POS_PERM,
            self._keynodes['question_finished_unsuccessfully'],
            action_node,
        )

    def finish_agent(self, action_node: ScAddr, answer: ScAddr) -> None:
        contour_edge = create_edge(
            sc_types.EDGE_D_COMMON_CONST,
            action_node,
            answer,
        )
        create_edge(
            sc_types.EDGE_ACCESS_CONST_POS_PERM,
            self._keynodes['nrel_answer'],
            contour_edge,
        )
        create_edge(
            sc_types.EDGE_ACCESS_CONST_POS_PERM,
            self._keynodes['question_finished_successfully'],
            action_node,
        )

    def add_lake_to_answer(self, lake, answer):
        template = ScTemplate()
        template.triple_with_relation(
            lake,
            [sc_types.EDGE_D_COMMON_VAR, "_arc_1"],
            [sc_types.LINK_VAR, '_area'],
            [sc_types.EDGE_ACCESS_VAR_POS_PERM, "_arc_2"],
            self._keynodes['nrel_area'],
        )
        search_result = client.template_search(template)

        if len(search_result):
            wrap_in_set(
                answer,
                lake,
                self._keynodes['nrel_area'],
                search_result[0].get('_arc_1'),
                search_result[0].get('_arc_2'),
                search_result[0].get('_area'),
            )

    def get_lakes_with_area(self) -> dict[ScAddr, float]:
        template = ScTemplate()
        template.triple(
            self._keynodes['concept_lake'],
            sc_types.EDGE_ACCESS_VAR_POS_PERM,
            [sc_types.NODE_VAR, '_lake'],
        )
        template.triple_with_relation(
            '_lake',
            sc_types.EDGE_D_COMMON_VAR,
            [sc_types.LINK_VAR, '_area'],
            sc_types.EDGE_ACCESS_VAR_POS_PERM,
            self._keynodes['nrel_area'],
        )

        search_result = client.template_search(template)
        lakes_with_area = {}
        for item in search_result:
            lakes_with_area[item.get('_lake')] = float(client.get_link_content(item.get("_area"))[0].data)
        return lakes_with_area

    def get_main_idtf(self, node: ScAddr) -> str:
        template = ScTemplate()
        template.triple_with_relation(
            node,
            sc_types.EDGE_D_COMMON_VAR,
            [sc_types.LINK_VAR, '_value'],
            sc_types.EDGE_ACCESS_VAR_POS_PERM,
            self._keynodes['nrel_main_idtf'],
        )
        template_result = client.template_search(template)
        value = ''
        if len(template_result):
            value = client.get_link_content(template_result[0].get('_value'))[0].data

        return value
