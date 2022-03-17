from termcolor import colored

from common import ScAgent, ScEventParams, ScKeynodes
from sc import *


class SearchPostOfficeByBrandAgent(ScAgent):
    def __init__(self, module):
        super().__init__(module)
        self.ctx = module.ctx
        self.keynodes = ScKeynodes(self.ctx)
        self.main_node = None

    def RunImpl(self, evt: ScEventParams) -> ScResult:
        self.main_node = evt.other_addr # получаем узел который отвечает за вызов агента с определенными параметрами
        status = ScResult.Ok

        # проверяем что был вызван действительно наш агент
        if self.module.ctx.HelperCheckEdge(
                self.keynodes['action_search_post_offices_by_brand'],
                self.main_node,
                ScType.EdgeAccessConstPosPerm,
        ):
            try:
                if self.main_node is None or not self.main_node.IsValid():
                    raise Exception("The question node isn't valid.")
                # получаем наши аргументы агента
                node = self.get_action_argument(self.main_node, 'rrel_1') 
                answerNode = self.ctx.CreateNode(ScType.NodeConstStruct) # создаем узел ответа
                self.add_nodes_to_answer(answerNode, [node]) # добавляем входные аргументы в ответ

                print("start")
                # пятиэлементный итератор для поиска конструкции firstParameter <= nrel_operator: ...;;
                post_officeIterator = self.ctx.Iterator5(
                    ScType.Unknown,
                    ScType.EdgeDCommon,
                    node,
                    ScType.EdgeAccessConstPosPerm,
                    self.keynodes['nrel_operator']
                )
				# while post_officeIterator.Next():
					# post_office = post_officeIterator.Get(2)
					# self.add_nodes_to_answer(answerNode, [post_office])     
                while post_officeIterator.Next():
                    post_office = post_officeIterator.Get(0)
                    checkIterator = self.ctx.Iterator3(
                        self.keynodes['concept_post_office'],
						ScType.EdgeAccessConstPosPerm,
                        post_office
					)
                    if checkIterator.Next():
                        self.add_nodes_to_answer(answerNode, [post_office, post_officeIterator.Get(1), post_officeIterator.Get(3), post_officeIterator.Get(4)])
                    else:
                        checkIterator = self.ctx.Iterator3(
                            self.keynodes['concept_business_post'],
                            ScType.EdgeAccessConstPosPerm,
                            post_office
                        )
                        if checkIterator.Next():
                            self.add_nodes_to_answer(answerNode, [post_office, post_officeIterator.Get(1), post_officeIterator.Get(3), post_officeIterator.Get(4)])
                        else:
                            checkIterator = self.ctx.Iterator3(
                                self.keynodes['concept_international_post_office'],
                                ScType.EdgeAccessConstPosPerm,
                                post_office
                            )
                            if checkIterator.Next():
                                self.add_nodes_to_answer(answerNode, [post_office, post_officeIterator.Get(1), post_officeIterator.Get(3), post_officeIterator.Get(4)])
								
				# print(self.get_definition(node)) # получение определение через шаблон
                self.finish_agent(self.main_node, answerNode) # завершаем работу агента
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