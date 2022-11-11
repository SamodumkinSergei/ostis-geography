from termcolor import colored

from common import ScAgent, ScEventParams, ScKeynodes
from sc import *

import geopy.distance
import requests
from bs4 import BeautifulSoup
from lxml import etree

class DistanceAgent(ScAgent):
    def __init__(self, module):
        super().__init__(module)
        self.ctx = module.ctx
        self.keynodes = ScKeynodes(self.ctx)
        self.main_node = None

    def RunImpl(self, evt: ScEventParams) -> ScResult:
        self.main_node = evt.other_addr
        status = ScResult.Ok

        if self.module.ctx.HelperCheckEdge(
                self.keynodes['action_find_distance'],
                self.main_node,
                ScType.EdgeAccessConstPosPerm,
        ):
            try:
                if self.main_node is None or not self.main_node.IsValid():
                    raise Exception("The question node isn't valid.")

                village1 = self.get_action_argument(self.main_node, 'rrel_1')
                village2 = self.get_action_argument(self.main_node, 'rrel_2')
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
                    defIter = self.ctx.Iterator5(
                        village2,
                        ScType.EdgeDCommon,
                        ScType.Unknown,
                        ScType.EdgeAccessConstPosPerm,
                        self.keynodes['nrel_selsoviet']
                    )
                    if defIter.Next():
                        distinct2 = defIter.Get(2)
                        distance = self.getDistance([self.get_main_idtf(village1), self.get_main_idtf(distinct1)],
                                                    [self.get_main_idtf(village2), self.get_main_idtf(distinct2)])
                        distance = str(distance) + " meters"
                        answer = self.ctx.CreateLink()
                        if self.ctx.SetLinkContent(answer, distance):
                            tuple = self.ctx.CreateNode(ScType.NodeConstTuple)
                            query_edge = self.ctx.CreateEdge(
                                ScType.EdgeAccessConstPosPerm,
                                tuple,
                                village1
                            )
                            query_edge_1 = self.ctx.CreateEdge(
                                ScType.EdgeAccessConstPosPerm,
                                tuple,
                                village2
                            )
                            query_edge_11 = self.ctx.CreateEdge(
                                ScType.EdgeDCommonConst,
                                tuple,
                                answer
                            )
                            query_edge2 = self.ctx.CreateEdge(
                                ScType.EdgeAccessConstPosPerm,
                                self.keynodes['nrel_distance'],
                                query_edge_11
                            )
                            self.add_nodes_to_answer(answerNode, [answer, village1, village2, self.keynodes['nrel_distance'], tuple, query_edge, query_edge_1, query_edge_11, query_edge2])
                else:
                    raise Exception("Invalid content: " + village1 + " or " + village2 + "cannot find selsoviet")
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

    def getLatLon(self, url):
        page = requests.get(url)
        elements_lst = []
        soup = BeautifulSoup(page.text, 'html.parser')
        dom = etree.HTML(str(soup))
        lat = dom.xpath('(//a[@class="set_position"]/@data-lat)[1]')
        lon = dom.xpath('(//a[@class="set_position"]/@data-lon)[1]')
        if len(lat) == 0 | len(lon) == 0:
            return (1.11, 1.11)
        return (float(lat[0]), float(lon[0]))

    def getDistance(self, village1, village2):
        url = "https://www.openstreetmap.org/geocoder/search_osm_nominatim?query=" + village1[0] + "%2C" + village1[1]
        coord1 = self.getLatLon(url)
        url_n = "https://www.openstreetmap.org/geocoder/search_osm_nominatim?query=" + village2[0] + "%2C" + village2[1]
        coord2 = self.getLatLon(url_n)
        return round(geopy.distance.distance(coord1, coord2).m, 2)

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
