from common import ScModule, ScKeynodes, ScPythonEventType
from GetHotelByCityCentreDistanceAgent import GetHotelByCityCentreDistanceAgent
from sc import *


class HotelsModule(ScModule):

    def __init__(self):
        ScModule.__init__(
            self,
            ctx=__ctx__,
            cpp_bridge=__cpp_bridge__,
            keynodes=[],
        )
        self.keynodes = ScKeynodes(self.ctx)

    def OnInitialize(self, params):
        print('Initialize Hotels module')
        question_initiated = self.keynodes['question_initiated']

        hotels_city_centre_agent = GetHotelByCityCentreDistanceAgent(self)

        hotels_city_centre_agent.Register(question_initiated, ScPythonEventType.AddOutputEdge)

    def OnShutdown(self):
        print('Shutting down Hotels module')


service = HotelsModule()
service.Run()
