from common import ScModule, ScKeynodes, ScPythonEventType
from VillagesPopulationAgent import VillagesPopulationAgent

from sc import *


class VillagesPopulationModule(ScModule):

    def __init__(self):
        ScModule.__init__(
            self,
            ctx=__ctx__,
            cpp_bridge=__cpp_bridge__,
            keynodes=[],
        )
        self.keynodes = ScKeynodes(self.ctx)

    def OnInitialize(self, params):
        print('Initialize VillagesPopulation module')
        question_initiated = self.keynodes['question_initiated']

        agent = VillagesPopulationAgent(self)
        agent.Register(question_initiated, ScPythonEventType.AddOutputEdge)

    def OnShutdown(self):
        print('Shutting down VillagesPopulation module')


service = VillagesPopulationModule()
service.Run()
