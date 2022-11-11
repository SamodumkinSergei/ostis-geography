from common import ScModule, ScKeynodes, ScPythonEventType
from PopulationComparisonAgent import PopulationComparisonAgent

from sc import *


class PopulationComparisonModule(ScModule):

    def __init__(self):
        ScModule.__init__(
            self,
            ctx=__ctx__,
            cpp_bridge=__cpp_bridge__,
            keynodes=[],
        )
        self.keynodes = ScKeynodes(self.ctx)

    def OnInitialize(self, params):
        print('Initialize PopulationComparison module')
        question_initiated = self.keynodes['question_initiated']

        agent = PopulationComparisonAgent(self)
        agent.Register(question_initiated, ScPythonEventType.AddOutputEdge)

    def OnShutdown(self):
        print('Shutting down PopulationComparison module')


service = PopulationComparisonModule()
service.Run()
