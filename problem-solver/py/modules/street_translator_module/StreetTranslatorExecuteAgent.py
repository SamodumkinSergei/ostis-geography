from termcolor import colored

from sc_client import client

from sc_client.models import ScAddr, ScTemplate
from sc_client.constants import sc_type

from sc_kpm import ScAgentClassic, ScResult, ScKeynodes

from sc_kpm.utils.action_utils import get_action_arguments
from sc_kpm.utils import generate_connector, generate_node
from sc_kpm.sc_sets.sc_set import ScSet
# from sc_kpm.sc_sets.sc_sctructure import ScStructure

class StreetTranslatorExecuteAgent(ScAgentClassic):
    def __init__(self):
        super().__init__("action_street_translator")
        # self._keynodes = ScKeynodes()

    def on_event(self, class_node: ScAddr, edge: ScAddr, action_node: ScAddr) -> ScResult:
        if not self._confirm_action_class(action_node):
            return ScResult.SKIP

        status = ScResult.OK
        try:
            if action_node is None or not action_node.is_valid():
                raise Exception("The question node isn't valid.")
            print("StreetTranslatorExecuteAgent started")

            enNameNode, ruNameNode, countNode = get_action_arguments(action_node, 3)
            enName = self.get_main_idtf(enNameNode)
            ruName = self.get_main_idtf(ruNameNode)
            count = self.get_main_idtf(countNode)

            os.system(f"../../tools/street_parser/StreetTranslator hrodna Гродно 101")
            answerNode = self.ctx.CreateNode(ScType.NodeConstStruct)
            self.finish_agent(self.main_node, answerNode)
        except Exception as ex:
            print(colored(str(ex), color='red'))
            self.set_unsuccessful_status(action_node)
            status = ScResult.ERROR
        finally:
            self.ctx.CreateEdge(
                ScType.EdgeAccessConstPosPerm,
                self.keynodes['question_finished'],
                self.main_node,
            )
        return status

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

    def add_nodes_to_answer(self, contour: ScAddr, nodes: ScAddr):
        if contour is None:
            contour = generate_node(sc_type.CONST_NODE)
        if nodes is None:
            nodes = []
        for node in nodes:
            generate_connector(
                sc_type.MEMBERSHIP_ARC_CONST_POS_PERM,
                contour,
                node
            )

    def get_main_idtf(self, node: ScAddr) -> str:
        template = ScTemplate()
        template.quintuple(
            node,
            sc_type.COMMON_ARC_VAR,
            [sc_type.NODE_LINK_VAR, '_value'],
            sc_type.MEMBERSHIP_ARC_VAR_POS_PERM,
            ScKeynodes['nrel_main_idtf'],
        )
        template_result = client.search_by_template(template)
        value = ''
        if len(template_result):
            value = client.get_link_content(template_result[0].get('_value'))[0].data

        return value
