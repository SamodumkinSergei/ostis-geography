from termcolor import colored
from typing import List
import logging

from sc_client import client

from sc_client.models import ScAddr, ScTemplate, ScLinkContent
from sc_client.constants import sc_type

from sc_kpm import ScAgentClassic, ScResult, ScKeynodes

from sc_kpm.utils.action_utils import get_action_arguments
from sc_kpm.utils import generate_connector
from sc_kpm.utils.common_utils import generate_node
from sc_kpm.utils.common_utils import get_element_system_identifier
from sc_kpm.sc_sets.sc_set import ScSet
from sc_kpm.sc_sets.sc_structure import ScStructure
# from sc_kpm.logging import get_kpm_logger


# _logger = get_kpm_logger()

logging.basicConfig(
    level=logging.DEBUG, format="%(asctime)s | %(name)s | %(message)s", datefmt="[%d-%b-%y %H:%M:%S]"
)

class SearchKindergartensByRegionAgent(ScAgentClassic):
    def __init__(self):
        super().__init__("action_get_kindergartens_by_region")
        # self._keynodes = ScKeynodes()

    def on_event(self, class_node: ScAddr, edge: ScAddr, action_node: ScAddr) -> ScResult:
        if not self._confirm_action_class(action_node):
            return ScResult.SKIP

        status = ScResult.OK
        self.logger.debug("SearchKindergartensByRegionAgent starts")

        try:
            self.logger.debug("SearchKindergartensByRegionAgent get arguments")

            if action_node is None or not action_node.is_valid():
                self.logger.debug("Not Valid node")
                raise Exception("The question node isn't valid")

            node, = get_action_arguments(action_node, 1)
            answer_node = ScStructure(node)

            self.find_kindergarten(node, answer_node)
            self.finish_agent(action_node, answer_node)

            self.logger.debug("SearchKindergartensByRegionAgent ends")
        except Exception as ex:
            self.set_unsuccessful_status(action_node)
            status = ScResult.ERROR
        finally:
            generate_connector(
                sc_type.MEMBERSHIP_ARC_CONST_POS_PERM,
                ScKeynodes['question_finished'],
                action_node,
            )
        return status

    # Find objects of the specified region if they are map objects and kindergartens
    def find_kindergarten(self, kindergarten_region: ScAddr, answer_node: ScAddr) -> None:
        kindergarten_template = ScTemplate()
        kindergarten_template.quintuple(
            [sc_types.UNKNOWN, "_kindergarten"],
            sc_type.COMMON_ARC_VAR,
            [kindergarten_region, "_region_node"],
            sc_type.MEMBERSHIP_ARC_VAR_POS_PERM,
            ScKeynodes["nrel_region"]
        )
        self.logger.debug("1st passed")

        kindergarten_template.triple(
            ScKeynodes['concept_preschool_education_institution'],
            [sc_type.MEMBERSHIP_ARC_VAR_POS_PERM, "_edge_to_kindergarten"],
            "_kindergarten"
        )
        self.logger.debug("2st passed")
        result = client.search_by_template(kindergarten_template)

        ScSet(answer_node, ScKeynodes['concept_preschool_education_institution'])

        for item in result:
            self.logger.debug("SearchKindergartensByRegionAgent get answer: " +
                          get_element_system_identifier(item.get(0)))

            ScSet(answer_node, item.get(1), item.get(0))

    def set_unsuccessful_status(self, action_node: ScAddr) -> None:
        generate_connector(
            sc_type.MEMBERSHIP_ARC_CONST_POS_PERM,
            ScKeynodes['question_finished_unsuccessfully'],
            action_node,
        )

    def finish_agent(self, action_node: ScAddr, answer: ScAddr) -> None:
        contour_edge = generate_connector(
            sc_type.COMMON_ARC_CONST,
            action_node,
            answer,
        )
        generate_connector(
            sc_type.MEMBERSHIP_ARC_CONST_POS_PERM,
            ScKeynodes['nrel_answer'],
            contour_edge,
        )
        generate_connector(
            sc_type.MEMBERSHIP_ARC_CONST_POS_PERM,
            ScKeynodes['question_finished_successfully'],
            action_node,
        )
