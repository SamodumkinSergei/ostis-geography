# from sc_kpm.logging import get_kpm_logger
from termcolor import colored
import logging

from sc_client import client

from sc_client.models import ScAddr, ScTemplate
from sc_client.constants import sc_type

from sc_kpm import ScAgentClassic, ScResult, ScKeynodes

from sc_kpm.utils.action_utils import get_action_arguments
from sc_kpm.utils import generate_connector
from sc_kpm.utils.common_utils import generate_node
from sc_kpm.sc_sets import ScSet

# logger = get_kpm_logger()

logging.basicConfig(
    level=logging.DEBUG, format="%(asctime)s | %(name)s | %(message)s", datefmt="[%d-%b-%y %H:%M:%S]"
)

class GetLakesByAreaAgent(ScAgentClassic):
    def __init__(self):
        super().__init__("action_get_lake_by_area")
        # self._keynodes = ScKeynodes()

    def on_event(self, class_node: ScAddr, edge: ScAddr, action_node: ScAddr) -> ScResult:
        if not self._confirm_action_class(action_node):
            return ScResult.SKIP

        status = ScResult.OK
        self.logger.debug("GetLakesByAreaAgent starts")
        try:
            self.logger.debug("GetLakesByAreaAgent get arguments")

            first_area_node, second_area_node = get_action_arguments(action_node, 2)

            answer_node = generate_node(sc_type.CONST_NODE) #first_area_node, second_area_node

            lake_area = self.get_lakes_with_area()
            first_area = float(client.get_link_content(first_area_node)[0].data)
            second_area = float(client.get_link_content(second_area_node)[0].data)

            results = []
            for lake, area in lake_area.items():
                if first_area <= area <= second_area:
                    print(colored(str(area), 'green'))
                    results.append(lake)

            for lake in results:
                self.logger.debug("GetLakesByAreaAgent get answer")
                self.add_lake_to_answer(lake, answer_node)

            self.finish_agent(action_node, answer_node)
            self.logger.debug("GetLakesByAreaAgent ends")

        except Exception as ex:
            self.set_unsuccessful_status(action_node)
            status = ScResult.ERROR
        finally:
            generate_connector(
                sc_type.CONST_PERM_POS_ARC,
                ScKeynodes['question_finished'],
                action_node,
            )
        return status

    def set_unsuccessful_status(self, action_node: ScAddr) -> None:
        generate_connector(
            sc_type.CONST_PERM_POS_ARC,
            ScKeynodes['question_finished_unsuccessfully'],
            action_node,
        )

    def finish_agent(self, action_node: ScAddr, answer: ScAddr) -> None:
        contour_edge = generate_connector(
            sc_type.CONST_COMMON_ARC,
            action_node,
            answer,
        )
        generate_connector(
            sc_type.CONST_PERM_POS_ARC,
            ScKeynodes['nrel_answer'],
            contour_edge,
        )
        generate_connector(
            sc_type.CONST_PERM_POS_ARC,
            ScKeynodes['question_finished_successfully'],
            action_node,
        )

    def add_lake_to_answer(self, lake, answer):
        template = ScTemplate()
        template.quintuple(
            lake,
            [sc_type.VAR_COMMON_ARC, "_arc_1"],
            [sc_type.VAR_NODE_LINK, '_area'],
            [sc_type.VAR_PERM_POS_ARC, "_arc_2"],
            ScKeynodes['nrel_area'],
        )
        search_result = client.search_by_template(template)

        if len(search_result):
            ScSet(
                answer,
                lake,
                ScKeynodes['nrel_area'],
                search_result[0].get('_arc_1'),
                search_result[0].get('_arc_2'),
                search_result[0].get('_area'),
            )

    def get_lakes_with_area(self):
        template = ScTemplate()
        template.triple(
            ScKeynodes['concept_lake'],
            sc_type.VAR_PERM_POS_ARC,
            [sc_type.VAR_NODE, '_lake'],
        )
        template.quintuple(
            '_lake',
            sc_type.VAR_COMMON_ARC,
            [sc_type.VAR_NODE_LINK, '_area'],
            sc_type.VAR_PERM_POS_ARC,
            ScKeynodes['nrel_area'],
        )

        search_result = client.search_by_template(template)
        lakes_with_area = {}
        for item in search_result:
            lakes_with_area[item.get('_lake')] = float(client.get_link_content(item.get("_area"))[0].data)
        return lakes_with_area

    def get_main_idtf(self, node: ScAddr) -> str:
        template = ScTemplate()
        template.quintuple(
            node,
            sc_type.VAR_COMMON_ARC,
            [sc_type.VAR_NODE_LINK, '_value'],
            sc_type.VAR_PERM_POS_ARC,
            ScKeynodes['nrel_main_idtf'],
        )
        template_result = client.search_by_template(template)
        value = ''
        if len(template_result):
            value = client.get_link_content(template_result[0].get('_value'))[0].data

        return value
