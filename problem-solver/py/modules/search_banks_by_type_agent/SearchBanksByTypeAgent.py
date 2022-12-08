from termcolor import colored
from typing import List

from sc_client import client

from sc_client.models import ScAddr, ScTemplate, ScLinkContent
from sc_client.constants import sc_types

from sc_kpm import ScAgentClassic, ScResult, ScKeynodes

from sc_kpm.utils.action_utils import get_action_arguments
from sc_kpm.utils import create_edge
from sc_kpm.utils.creation_utils import create_node, create_structure, wrap_in_set
from sc_kpm.utils.common_utils import get_system_idtf
from sc_kpm.logging import get_kpm_logger


_logger = get_kpm_logger()


class SearchBanksByTypeAgent(ScAgentClassic):
    def __init__(self):
        super().__init__("action_search_banks_by_type")
        self._keynodes = ScKeynodes()

    def on_event(self, class_node: ScAddr, edge: ScAddr, action_node: ScAddr) -> ScResult:
        if not self._confirm_action_class(action_node):
            return ScResult.SKIP

        status = ScResult.OK
        _logger.debug("SearchBanksByTypeAgent starts")

        try:
            _logger.debug("SearchBanksByTypeAgent get arguments")

            if action_node is None or not action_node.is_valid():
                raise Exception("The question node isn't valid")

            node, = get_action_arguments(action_node, 1)
            answer_node = create_structure(node)

            self.find_banks(node, answer_node)

            self.finish_agent(action_node, answer_node)
            _logger.debug("SearchBanksByTypeAgent ends")
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

    # Find objects of the specified bank type if they are map objects
    def find_banks(self, bank_type: ScAddr, answer_node: ScAddr) -> None:
        if not self.is_bank_type(bank_type):
            _logger.debug("The question node isn't a bank_type")
            return

        bank_template = ScTemplate()
        bank_template.triple(
            bank_type,
            sc_types.EDGE_ACCESS_VAR_POS_PERM,
            [sc_types.UNKNOWN, "_bank"]
        )
        bank_template.triple(
            self._keynodes['concept_map_object'],
            [sc_types.EDGE_ACCESS_VAR_POS_PERM, "_edge_to_bank"],
            "_bank"
        )
        result = client.template_search(bank_template)

        wrap_in_set(answer_node, self._keynodes['concept_map_object'])

        for item in result:
            _logger.debug("SearchBanksByTypeAgent get answer: " +
                          get_system_idtf(item.get(2)))

            wrap_in_set(
                answer_node, item.get(2), item.get(1))

    # Check if the node is a bank type
    def is_bank_type(self, node: ScAddr) -> bool:
        bank_check_template = ScTemplate()
        bank_check_template.triple(
            self._keynodes['concept_banking_institution'],
            sc_types.EDGE_ACCESS_VAR_POS_PERM,
            node
        )
        bank_search_results = client.template_search(bank_check_template)

        return len(bank_search_results) > 0

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
