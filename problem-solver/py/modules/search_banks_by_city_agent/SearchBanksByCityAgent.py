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

class SearchBanksByCityAgent(ScAgentClassic):
    def __init__(self):
        super().__init__("action_search_banks_by_city")
        # self._keynodes = ScKeynodes()

    def on_event(self, class_node: ScAddr, edge: ScAddr, action_node: ScAddr) -> ScResult:
        self.logger.debug("Event for banks/city found")
        if not self._confirm_action_class(action_node):
            return ScResult.SKIP

        status = ScResult.OK
        self.logger.debug("SearchBanksByCityAgent starts")

        try:
            self.logger.debug("SearchBanksByCityAgent get arguments")

            if action_node is None or not action_node.is_valid():
                self.logger.debug("Not Valid node")
                raise Exception("The question node isn't valid")

            node, = get_action_arguments(action_node, 1)
            answer_node = ScStructure(node)

            self.find_banks(node, answer_node)
            self.finish_agent(action_node, answer_node)

            self.logger.debug("SearchBanksByCityAgent ends")
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

    # Find objects of the specified city if they are map objects and banks
    def find_banks(self, bank_city: ScAddr, answer_node: ScAddr) -> None:
        bank_template = ScTemplate()
        bank_template.quintuple(
            [sc_types.UNKNOWN, "_bank"],
            sc_type.COMMON_ARC_VAR,
            [bank_city, "_city_node"],
            sc_type.MEMBERSHIP_ARC_VAR_POS_PERM,
            ScKeynodes["nrel_city"]
        )
        self.logger.debug("1st passed")
        bank_template.triple(
            ScKeynodes['concept_map_object'],
            [sc_type.MEMBERSHIP_ARC_VAR_POS_PERM, "_edge_to_map_object"],
            "_bank"
        )
        self.logger.debug("2st passed")
        bank_template.triple(
            ScKeynodes['concept_bank'],
            [sc_type.MEMBERSHIP_ARC_VAR_POS_PERM, "_edge_to_bank"],
            "_bank"
        )
        self.logger.debug("3st passed")
        result = client.search_by_template(bank_template)
        ScSet(answer_node, ScKeynodes['concept_map_object'])

        for item in result:
            self.logger.debug("SearchBanksByCityAgent get answer: " +
                          get_element_system_identifier(item.get(0)))

            ScSet(answer_node, item.get(1), item.get(0))

        ScSet(answer_node, ScKeynodes['concept_map_object'])

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
