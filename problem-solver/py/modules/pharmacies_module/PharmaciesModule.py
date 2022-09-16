from common import ScModule, ScKeynodes, ScPythonEventType
from GetPharmaciesByTypeAgent import GetPharmaciesByTypeAgent
from GetPharmaciesByLocationHouseNumberAgent import GetPharmaciesByLocationHouseNumberAgent
from GetPharmaciesByCityAgent import GetPharmaciesByCityAgent
from GetPharmaciesByPhoneNumberAgent import GetPharmaciesByPhoneNumberAgent
from GetPharmaciesByDistrictAgent import GetPharmaciesByDistrictAgent
from GetPharmaciesByStreetAgent import GetPharmaciesByStreetAgent
from GetPharmaciesByRegionAgent import GetPharmaciesByRegionAgent
from GetPharmaciesByOpenTimeAgent import GetPharmaciesByOpenTimeAgent
from GetPharmaciesByCloseTimeAgent import GetPharmaciesByCloseTimeAgent

from sc import *


class PharmaciesModule(ScModule):

    def __init__(self):
        ScModule.__init__(
            self,
            ctx=__ctx__,
            cpp_bridge=__cpp_bridge__,
            keynodes=[],
        )
        self.keynodes = ScKeynodes(self.ctx)

    def OnInitialize(self, params):
        print('Initialize Pharmacies module')
        question_initiated = self.keynodes['question_initiated']

        agent1 = GetPharmaciesByTypeAgent(self)
        agent2 = GetPharmaciesByLocationHouseNumberAgent(self)
        agent3 = GetPharmaciesByCityAgent(self)

        agent4 = GetPharmaciesByPhoneNumberAgent(self)
        agent5 = GetPharmaciesByDistrictAgent(self)
        agent6 = GetPharmaciesByStreetAgent(self)

        agent7 = GetPharmaciesByRegionAgent(self)
        agent8 = GetPharmaciesByOpenTimeAgent(self)
        agent9 = GetPharmaciesByCloseTimeAgent(self)


        agent1.Register(question_initiated, ScPythonEventType.AddOutputEdge)
        agent2.Register(question_initiated, ScPythonEventType.AddOutputEdge)
        agent3.Register(question_initiated, ScPythonEventType.AddOutputEdge)
        agent4.Register(question_initiated, ScPythonEventType.AddOutputEdge)
        agent5.Register(question_initiated, ScPythonEventType.AddOutputEdge)
        agent6.Register(question_initiated, ScPythonEventType.AddOutputEdge)
        agent7.Register(question_initiated, ScPythonEventType.AddOutputEdge)
        agent8.Register(question_initiated, ScPythonEventType.AddOutputEdge)
        agent9.Register(question_initiated, ScPythonEventType.AddOutputEdge)


    def OnShutdown(self):
        print('Shutting down Pharmacies module')


service = PharmaciesModule()
service.Run()
