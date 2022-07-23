from common import ScModule, ScKeynodes, ScPythonEventType
from GetLakesByAreaAgent import GetLakesByAreaAgent
from GetLakesByTemperatureAgent import GetLakesByTemperatureAgent
from GetLakesBySaltIndexAgent import GetLakesBySaltIndexAgent

from sc import *


class LakesModule(ScModule):

    def __init__(self):
        ScModule.__init__(
            self,
            ctx=__ctx__,
            cpp_bridge=__cpp_bridge__,
            keynodes=[],
        )
        self.keynodes = ScKeynodes(self.ctx)

    def OnInitialize(self, params):
        print('Initialize Lakes module')
        question_initiated = self.keynodes['question_initiated']

        getLakesByAreaAgent = GetLakesByAreaAgent(self)
        getLakesByAreaAgent.Register(question_initiated, ScPythonEventType.AddOutputEdge)

        getLakesByTemperatureAgent = GetLakesByTemperatureAgent(self)
        getLakesByTemperatureAgent.Register(question_initiated, ScPythonEventType.AddOutputEdge)

        getLakesBySaltIndexAgent = GetLakesBySaltIndexAgent(self)
        getLakesBySaltIndexAgent.Register(question_initiated, ScPythonEventType.AddOutputEdge)

    def OnShutdown(self):
        print('Shutting down Lakes module')


service = LakesModule()
service.Run()
