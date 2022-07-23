from termcolor import colored

from common import ScAgent, ScEventParams, ScKeynodes
from sc import *
from common.sc_log import Log


class GetLakesByAreaAgent(ScAgent):
    def __init__(self, module):
        super().__init__(module)
        self.ctx = module.ctx
        self.keynodes = ScKeynodes(self.ctx)
        self.main_node = None
        self.log = Log(self.__class__.__name__)

    def RunImpl(self, evt: ScEventParams) -> ScResult:
        self.main_node = evt.other_addr 
        status = ScResult.Ok
        self.log.debug("GetLakesByAreaAgent starts")
        if self.module.ctx.HelperCheckEdge(
                self.keynodes['action_get_lake_by_area'],
                self.main_node,
                ScType.EdgeAccessConstPosPerm,
        ):
            try:
                if self.main_node is None or not self.main_node.IsValid():
                    raise Exception("The question node isn't valid.")

                self.log.debug("GetLakesByAreaAgent get arguments")

                firstAreaNode = self.get_action_argument(self.main_node, 'rrel_1')
                secondAreaNode = self.get_action_argument(self.main_node, 'rrel_2')
                answerNode = self.ctx.CreateNode(ScType.NodeConstStruct)
                self.add_nodes_to_answer(answerNode, [firstAreaNode, secondAreaNode])

                lakeArea = self.get_lakes_with_area()
                firstArea = float(self.get_main_idtf(firstAreaNode))
                secondArea = float(self.get_main_idtf(secondAreaNode))

                results = []
                for lake, area in lakeArea.items():
                    if firstArea <= area <= secondArea:
                        print(colored(str(area), 'green'))
                        results.append(lake)

                for lake in results:
                    self.log.debug("GetLakesByAreaAgent get answer")
                    self.add_lake_to_answer(lake, answerNode)

                self.finish_agent(self.main_node, answerNode)
                self.log.debug("GetLakesByAreaAgent ends")
            except Exception as ex:
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

    def finish_agent(self, action_node, answer):
        contour_edge = self.ctx.CreateEdge(
            ScType.EdgeDCommonConst,
            action_node,
            answer
        )
        self.ctx.CreateEdge(
            ScType.EdgeAccessConstPosPerm,
            self.keynodes['nrel_answer'],
            contour_edge
        )
        self.ctx.CreateEdge(
            ScType.EdgeAccessConstPosPerm,
            self.keynodes['question_finished_successfully'],
            action_node,
        )

    def get_action_argument(self, question: ScAddr, rrel: str, argument_class=None) -> ScAddr:
        actual_argument = "_actual_argument"

        template = ScTemplate()
        template.TripleWithRelation(
            question,
            ScType.EdgeAccessVarPosPerm,
            ScType.NodeVar >> actual_argument,
            ScType.EdgeAccessVarPosPerm,
            self.keynodes[rrel],
        )
        if argument_class is not None:
            template.Triple(self.keynodes[argument_class], ScType.EdgeAccessVarPosPerm, actual_argument)

        search_result = self.ctx.HelperSearchTemplate(template)

        search_result_size = search_result.Size()
        if search_result_size > 0:
            argument_node = search_result[0][actual_argument]
        else:
            raise Exception("The argument node isn't found.")

        return argument_node

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

    def add_lake_to_answer(self, lake, answer):
        template = ScTemplate()
        template.TripleWithRelation(
            lake,
            ScType.EdgeDCommonVar >> "_arc_1",
            ScType.LinkVar >> '_area',
            ScType.EdgeAccessVarPosPerm >> "_arc_2",
            self.keynodes['nrel_area'],
        )
        search_result = self.ctx.HelperSearchTemplate(template)

        if search_result.Size():
            self.add_nodes_to_answer(answer,
             [
                lake,
                self.keynodes['nrel_area'],
                search_result[0]['_arc_1'],
                search_result[0]['_arc_2'],
                search_result[0]['_area']
            ]
            )

    def get_lakes_with_area(self):
        template = ScTemplate()
        template.Triple(
            self.keynodes['concept_lake'],
            ScType.EdgeAccessVarPosPerm,
            ScType.NodeVar >> '_lake'
        )
        template.TripleWithRelation(
            '_lake',
            ScType.EdgeDCommonVar,
            ScType.LinkVar >> '_area',
            ScType.EdgeAccessVarPosPerm,
            self.keynodes['nrel_area'],
        )

        search_result = self.ctx.HelperSearchTemplate(template)
        lakes_with_area = {}
        if search_result.Size():
            for i in range(search_result.Size()):
                lakes_with_area[search_result[i]['_lake']] = float(self.ctx.GetLinkContent(search_result[i]['_area']).AsString())
        return lakes_with_area

    def get_main_idtf(self, node):
        template = ScTemplate()
        template.TripleWithRelation(
            node,
            ScType.EdgeDCommonVar,
            ScType.LinkVar >> 'value',
            ScType.EdgeAccessVarPosPerm,
            self.keynodes['nrel_main_idtf']
        )
        template_result = self.ctx.HelperSearchTemplate(template)
        value = ''
        if template_result.Size():
            value = self.ctx.GetLinkContent(template_result[0]['value']).AsString()

        return value
