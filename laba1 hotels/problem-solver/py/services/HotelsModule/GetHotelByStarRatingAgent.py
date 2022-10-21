from termcolor import colored

from common import ScAgent, ScEventParams, ScKeynodes
from sc import *
from common.sc_log import Log


class GetHotelByStarRatingAgent(ScAgent):
    def __init__(self, module):
        super().__init__(module)
        self.ctx = module.ctx
        self.keynodes = ScKeynodes(self.ctx)
        self.main_node = None

    def RunImpl(self, evt: ScEventParams) -> ScResult:
        self.main_node = evt.other_addr  # получаем узел который отвечает за вызов агента с определенными параметрами
        status = ScResult.Ok

        # проверяем что был вызван действительно наш агент
        if self.module.ctx.HelperCheckEdge(
                self.keynodes['action_get_hotel_by_star_rating'],
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

                # тут пишите свой агент
                # в данном примере агент получает как аргумент узел и находит описание этого узла, т.е. конструкцию: node <- rrel_key_sc_element: ...(* <-definition;; <= nrel_sc_text_translation: ...(* ->rrel_example: [Определение];; *);; *);;
                # ниже получение определения через итераторы
                # пятиэлементный итератор для поиска конструкции firstParameter <- rrel_key_sc_element: ...;;
                definitionIterator = self.ctx.Iterator5(
                    ScType.Unknown,
                    ScType.EdgeAccessConstPosPerm,
                    node,
                    ScType.EdgeAccessConstPosPerm,
                    self.keynodes['rrel_key_sc_element']
                )
                hotelIterator = self.ctx.Iterator5(
                    ScType.Unknown,
                    ScType.EdgeDCommon,
                    node,
                    ScType.EdgeAccessConstPosPerm,
                    self.keynodes['nrel_star_rating']
                )
                while hotelIterator.Next():
                    hotel = hotelIterator.Get(0)
                    # проверка на принадлежность к отелям
                    hotelcheck = False
                    checkIterator = self.ctx.Iterator3(
                        self.keynodes['concept_hotel'],
                        ScType.EdgeAccessConstPosPerm,
                        hotel
                    )
                    if checkIterator.Next():
                        hotelcheck = True
                    
                    if hotelcheck == True:
                        # проверка на принадлежность к объектам карты
                        checkIterator = self.ctx.Iterator3(
                            self.keynodes['concept_map_object'],
                            ScType.EdgeAccessConstPosPerm,
                            hotel
                        )
                        if checkIterator.Next():
                            self.add_nodes_to_answer(answerNode, [hotel, hotelIterator.Get(1), hotelIterator.Get(3), hotelIterator.Get(4)])
                        else:
                            print("It's not a hotel")
                    # пятиэлементный итератор для поиска конструкции ... <= nrel_sc_text_translation: ...;;
                    translationIterator = self.ctx.Iterator5(
                        ScType.Unknown,
                        ScType.EdgeDCommon,
                        definition,
                        ScType.EdgeAccessConstPosPerm,
                        self.keynodes['nrel_sc_text_translation']
                    )
                    if translationIterator.Next():
                        translation = translationIterator.Get(0)
                        # пятиэлементный итератор для поиска конструкции .. -> rrel_example: [Определение];;
                        linkIterator = self.ctx.Iterator5(
                            translation,
                            ScType.EdgeAccessConstPosPerm,
                            ScType.Unknown,
                            ScType.EdgeAccessConstPosPerm,
                            self.keynodes['rrel_example']
                        )
                        if linkIterator.Next():
                            print(self.ctx.GetLinkContent(linkIterator.Get(2)).AsString()) # получение содержимого из sc-ссылки
                            # добавим все что хотим отобразить на странице остиса в контур ответа
                            for i in range(5):
                                self.add_nodes_to_answer(answerNode, [definitionIterator.Get(i), translationIterator.Get(i), linkIterator.Get(i)])
                
                print(self.get_definition(node)) # получение определение через шаблон

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

    # ниже ваши функции
    def get_definition(self, node: ScAddr) -> str:
        template = ScTemplate()
        template.TripleWithRelation(
            ScType.NodeVar >> '_definition',     # src
            ScType.EdgeAccessVarPosPerm,         # arcType
            node,                                # trg
            ScType.EdgeAccessVarPosPerm,         # relArcType
            self.keynodes['rrel_key_sc_element'] # relation
        )
        template.Triple(
            self.keynodes['definition'], # src
            ScType.EdgeAccessVarPosPerm, # arcType
            "_definition"                # trg
        )
        template.TripleWithRelation(
            ScType.NodeVar >> "_translation",
            ScType.EdgeDCommonVar,
            "_definition",
            ScType.EdgeAccessVarPosPerm,
            self.keynodes['nrel_sc_text_translation'],
        )
        template.TripleWithRelation(
            ScType.NodeVar >> '_translation',
            ScType.EdgeAccessVarPosPerm,
            ScType.LinkVar >> "_link",
            ScType.EdgeAccessVarPosPerm,
            self.keynodes['rrel_example']
        )
        result = ''
        first = True
        template_result = self.ctx.HelperSearchTemplate(template) 
        if template_result.Size():
            for i in range(template_result.Size()):
                if not first:
                    result += "\n"
                first = False
                result += self.ctx.GetLinkContent(template_result[i]['_link']).AsString()
        return result
