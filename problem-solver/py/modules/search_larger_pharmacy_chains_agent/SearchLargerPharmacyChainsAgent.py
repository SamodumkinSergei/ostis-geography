from termcolor import colored
from typing import List

from sc_client import client

from sc_client.models import ScAddr, ScTemplate, ScLinkContent, ScConstruction
from sc_client.constants import sc_types

from sc_kpm import ScAgentClassic, ScResult, ScKeynodes

from sc_kpm.utils.action_utils import get_action_arguments
from sc_kpm.utils import create_edge
from sc_kpm.utils.creation_utils import create_node, create_structure, wrap_in_set
from sc_kpm.utils.common_utils import get_system_idtf
from sc_kpm.logging import get_kpm_logger


_logger = get_kpm_logger()

class SearchLargerPharmacyChainsAgent(ScAgentClassic):
    def __init__(self):
        super().__init__("action_search_larger_pharmacy_chains")
        self._keynodes = ScKeynodes()

    def on_event(self, class_node: ScAddr, edge: ScAddr, action_node: ScAddr) -> ScResult:
        if not self._confirm_action_class(action_node):
            return ScResult.SKIP

        status = ScResult.OK
        _logger.debug("SearchSmallerPharmacyChainsAgent starts")

        try:
            _logger.debug("SearchSmallerPharmacyChainsAgent get arguments")

            if action_node is None or not action_node.is_valid():
                _logger.debug("Not Valid node")
                raise Exception("The question node isn't valid")

            node, = get_action_arguments(action_node, 1)
            answer_node = create_structure()
            
            self.find_bigger_chains(node, answer_node)
            self.finish_agent(action_node, answer_node)

            _logger.debug("SearchSmallerPharmacyChainsAgent ends")
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

    def find_bigger_chains(self, main_chain: ScAddr, answer_node: ScAddr) -> None:
        # определение величины начальной сети (из запроса)
        # (величина сети = количество аптек, которые к ней относятся)
        main_chain_template = ScTemplate()
        
        main_chain_template.triple_with_relation(
            [main_chain, "_main_pharmacy_chain"],
            sc_types.EDGE_D_COMMON_VAR,
            [sc_types.UNKNOWN, "_pharmacy"],
            sc_types.EDGE_ACCESS_VAR_POS_PERM,
            self._keynodes["nrel_inclusion"]
        )
        
        main_chain_template.triple(
            self._keynodes['concept_pharmacy'],
            [sc_types.EDGE_ACCESS_VAR_POS_PERM, "_edge_to_pharmacy"],
            "_pharmacy"
        )
        
        main_chain_pharmacies_result = client.template_search(main_chain_template)
        
        main_chain_length = len(main_chain_pharmacies_result)
        _logger.debug(f"Main chain's length is {main_chain_length}")
        
        
        # поиск других сетей
        chains_template = ScTemplate()
        chains_template.triple(
            self._keynodes['concept_pharmacy_chain'],
            [sc_types.EDGE_ACCESS_VAR_POS_PERM, "_edge_to_pharmacy_chain"],
            "_pharmacy_chain"
        )
        
        chains_result = client.template_search(chains_template)
        
        # определение параметров других сетей
        for item in chains_result:
            chain = item.get(2)
            
            # т.к. начальная сеть всё равно попадётся (и в ответ она попадать не должна), лучше сразу её пропустить
            if (chain == main_chain): 
                continue
            
            _logger.debug(f"checking chain {get_system_idtf(chain)}")
            
            chain_template = ScTemplate()
            
            chain_template.triple_with_relation(
                [chain, "_pharmacy_chain"],
                sc_types.EDGE_D_COMMON_VAR,
                [sc_types.UNKNOWN, "_pharmacy"],
                sc_types.EDGE_ACCESS_VAR_POS_PERM,
                self._keynodes["nrel_inclusion"]
            )
            
            chain_template.triple(
                self._keynodes['concept_pharmacy'],
                [sc_types.EDGE_ACCESS_VAR_POS_PERM, "_edge_to_pharmacy"],
                "_pharmacy"
            )
            
            chain_pharmacies_result = client.template_search(chain_template)
            chain_length = len(chain_pharmacies_result)
            _logger.debug(f"{get_system_idtf(chain)}'s length is {chain_length}")
            
            # в ответ добавляются только те сети, которые больше начальной
            if (chain_length > main_chain_length):
                _logger.debug(f"{get_system_idtf(chain)} is larger... adding it to answer")
                create_edge(sc_types.EDGE_ACCESS_CONST_POS_PERM, answer_node, chain)
        
        
        
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
