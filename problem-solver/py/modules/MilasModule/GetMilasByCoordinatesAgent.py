from termcolor import colored
from sc_client import client
from sc_client.models import ScAddr
from sc_kpm import ScAgentClassic, ScResult, ScKeynodes


class GetMilasByCoordinatesAgent(ScAgentClassic):
    def __init__(self):
        super().__init__("GetMilasByCoordinatesAgent") # your agent name
        self._keynodes = ScKeynodes()

    def on_event(self, class_node: ScAddr, edge: ScAddr, action_node: ScAddr) -> ScResult:
        if not self._confirm_action_class(action_node):
            return ScResult.SKIP
        status = ScResult.OK
    def RunImpl(self, evt: ScResult) -> ScResult:
        self.main_node = evt.other_addr 
        status = ScResult.Ok
        self.log.debug("GetMilasByCoordinatesAgent starts")
        if self.module.ctx.HelperCheckEdge(
                self.keynodes['action_get_milas_by_coordinates'],
                self.main_node,
                ScType.EdgeAccessConstPosPerm,
        ):
            try:
                if self.main_node is None or not self.main_node.IsValid():
                    raise Exception("The question node isn't valid.")

                self.log.debug("GetMilasByCoordinatesAgent get arguments")

                firstCoordinateNode = self.get_action_argument(self.main_node, 'rrel_1')
                secondCoordinateNode = self.get_action_argument(self.main_node, 'rrel_2')
                
                answerNode = self.ctx.CreateNode(ScType.NodeConstStruct)
                self.add_nodes_to_answer(answerNode, [firstCoordinateNode, secondCoordinateNode])

                milasWithCoordinates = self.get_milas_with_time()
                firstCoordinate = float(self.get_main_idtf(firstCoordinateNode))
                secondCoordinate = float(self.get_main_idtf(secondCoordinateNode))
                
                results = []
                for mila, milaCoordinate in milasWithCoordinates.items():
                    if firstCoordinate <= milaCoordinate <= secondCoordinate:
                        results.append(mila)

                for mila in results:
                    self.log.debug("GetMilasByCoordinatesAgent get answer")
                    self.add_mila_to_answer(mila, answerNode)

                self.finish_agent(self.main_node, answerNode)
                self.log.debug("GetMilasByCoordinatesAgent ends")
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

    def add_mila_to_answer(self, mila, answer):
        template = ScTemplate()
        template.TripleWithRelation(
            mila,
            ScType.EdgeDCommonVar >> "_arc_1",
            ScType.LinkVar >> '_coord',
            ScType.EdgeAccessVarPosPerm >> "_arc_2",
            self.keynodes['nrel_latitude'],
        )
        search_result = self.ctx.HelperSearchTemplate(template)

        if search_result.Size():
            self.add_nodes_to_answer(answer,
             [
                mila,
                self.keynodes['nrel_latitude'],
                search_result[0]['_arc_1'],
                search_result[0]['_arc_2'],
                search_result[0]['_coord']
            ]
            )

    def get_milas_with_coordinates(self):
        template = ScTemplate()
        template.Triple(
            self.keynodes['concept_shop'],
            ScType.EdgeAccessVarPosPerm,
            ScType.NodeVar >> '_shop'
        )
        template.TripleWithRelation(
            '_shop',
            ScType.EdgeDCommonVar,
            ScType.LinkVar >> '_coord',
            ScType.EdgeAccessVarPosPerm,
            self.keynodes['nrel_latitude'],
        )

        search_result = self.ctx.HelperSearchTemplate(template)
        shops_with_coordinates = {}
        if search_result.Size():
            for i in range(search_result.Size()):
                shops_with_coordinates[search_result[i]['_shop']] = float(self.ctx.GetLinkContent(search_result[i]['_coord']).AsString())
        return shops_with_coordinates

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
        return status