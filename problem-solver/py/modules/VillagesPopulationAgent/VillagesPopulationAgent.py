from termcolor import colored
import requests
from bs4 import BeautifulSoup
from lxml import etree
import re

from common import ScAgent, ScEventParams, ScKeynodes
from sc import *



class VillagesPopulationAgent(ScAgent):
    def __init__(self, module):
        super().__init__(module)
        self.ctx = module.ctx
        self.keynodes = ScKeynodes(self.ctx)
        self.main_node = None

    def RunImpl(self, evt: ScEventParams) -> ScResult:
        self.main_node = evt.other_addr
        status = ScResult.Ok

        if self.module.ctx.HelperCheckEdge(
                self.keynodes['action_find_population'],
                self.main_node,
                ScType.EdgeAccessConstPosPerm,
        ):
            try:
                if self.main_node is None or not self.main_node.IsValid():
                    raise Exception("The question node isn't valid.")

                village1 = self.get_action_argument(self.main_node, 'rrel_1')
                answerNode = self.ctx.CreateNode(ScType.NodeConstStruct)
                defIter = self.ctx.Iterator5(
                    village1,
                    ScType.EdgeDCommon,
                    ScType.Unknown,
                    ScType.EdgeAccessConstPosPerm,
                    self.keynodes['nrel_selsoviet']
                )
                if defIter.Next():
                    distinct1 = defIter.Get(2)
                    population = self.getPopullation([self.get_main_idtf(village1), self.get_main_idtf(distinct1)])
                    population = str(population) + " people"
                    answer = self.ctx.CreateLink()
                    if self.ctx.SetLinkContent(answer, population):
                        query_edge_1 = self.ctx.CreateEdge(
                            ScType.EdgeDCommonConst,
                            village1,
                            answer
                        )

                        query_edge2 = self.ctx.CreateEdge(
                            ScType.EdgeAccessConstPosPerm,
                            self.keynodes['nrel_population'],
                            query_edge_1
                        )
                    self.add_nodes_to_answer(answerNode, [answer, village1, self.keynodes['nrel_population'], query_edge_1, query_edge2])
                else:
                    defIter = self.ctx.Iterator5(
                        village1,
                        ScType.EdgeDCommon,
                        ScType.Unknown,
                        ScType.EdgeAccessConstPosPerm,
                        self.keynodes['nrel_region']
                    )
                    if defIter.Next():
                        region = defIter.Get(2)
                        population = self.getPopullationwithRegion([self.get_main_idtf(village1), self.get_main_idtf(region)])
                        population = str(population) + " people"
                        answer = self.ctx.CreateLink()
                        if self.ctx.SetLinkContent(answer, population):
                            query_edge_1 = self.ctx.CreateEdge(
                                ScType.EdgeDCommonConst,
                                village1,
                                answer
                            )

                            query_edge2 = self.ctx.CreateEdge(
                                ScType.EdgeAccessConstPosPerm,
                                self.keynodes['nrel_population'],
                                query_edge_1
                            )
                        self.add_nodes_to_answer(answerNode,
                                             [answer, village1, self.keynodes['nrel_population'], query_edge_1,
                                              query_edge2])
                    else:
                        raise Exception("Invalid content: " + village1 + " cannot find selsoviet or region")
                self.finish_agent(self.main_node, answerNode)  # завершаем работу агента
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

    def getPopullation(self, village1):
        word = village1[1]
        word = re.sub("\s", "+", word.strip())
        url = "https://ru.wikipedia.org/w/index.php?search=" + word
        page = requests.get(url)
        soup = BeautifulSoup(page.text, 'html.parser')
        dom = etree.HTML(str(soup))
        part = dom.xpath('(//div[@class="mw-search-result-heading"]/a/@href)[1]')
        if len(part) > 0:
            url = "https://ru.wikipedia.org" + part[0]
            page = requests.get(url)
            soup = BeautifulSoup(page.text, 'html.parser')
            dom = etree.HTML(str(soup))
        village = dom.xpath('//div[@class="columns"]/ul/li/a[text()[contains(., "{}")]]/@href'.format(village1[0]))
        if len(village) == 0:
            village = dom.xpath('//div[@class="mw-parser-output"]/ul/li/a[text()[contains(., "{}")]]/@href'.format(village1[0]))
        if len(village) == 0:
            return "0"
        url = "https://ru.wikipedia.org" + village[0]
        page = requests.get(url)
        soup = BeautifulSoup(page.text, 'html.parser')
        dom = etree.HTML(str(soup))
        population = dom.xpath('//span[@data-wikidata-property-id="P1082"]/span/text()')
        if len(population) == 0:
            return "0"
        return re.sub("[^0-9]", "", population[0].strip())

    def getPopullationwithRegion(self, village1):
        word = village1[1] + " " + village1[0]
        word = re.sub("\s", "+", word.strip())
        url = "https://ru.wikipedia.org/w/index.php?search=" + word
        page = requests.get(url)
        soup = BeautifulSoup(page.text, 'html.parser')
        dom = etree.HTML(str(soup))
        village = dom.xpath('(//div[@class="mw-search-result-heading"]/a/@href)[1]')
        url = "https://ru.wikipedia.org" + village[0]
        page = requests.get(url)
        soup = BeautifulSoup(page.text, 'html.parser')
        dom = etree.HTML(str(soup))
        population = dom.xpath('//span[@data-wikidata-property-id="P1082"]/span/text()')
        if len(population) == 0:
            return "0"
        return re.sub("[^0-9]", "", population[0].strip())

    def get_main_idtf(self, node):
        template = ScTemplate()
        template.TripleWithRelation(
            node,
            ScType.EdgeDCommonVar,
            ScType.LinkVar >> 'value',
            ScType.EdgeAccessVarPosPerm,
            self.keynodes['nrel_main_idtf']
        )
        template.Triple(
            self.keynodes['name'],
            ScType.EdgeAccessVarPosPerm,
            "value"
        )
        template_result = self.ctx.HelperSearchTemplate(template)
        value = ''
        if template_result.Size():
            value = self.ctx.GetLinkContent(template_result[0]['value']).AsString()

        return value