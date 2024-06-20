from common import ScModule, ScKeynodes, ScPythonEventType
from GetMilasByAddressAgent import GetMilasByAddressAgent
from GetMilasByTimeAgent import GetMilasByTimeAgent
from GetMilasByCoordinatesAgent import GetMilasByCoordinatesAgent

from sc import *


class MilasModule(ScModule):

    def __init__(self):
        ScModule.__init__(
            self,
            ctx=__ctx__,
            cpp_bridge=__cpp_bridge__,
            keynodes=[],
        )
        self.keynodes = ScKeynodes(self.ctx)

    def OnInitialize(self, params):
        print('Initialize Milas module')
        question_initiated = self.keynodes['question_initiated']

        getMilasByAddressAgent = GetMilasByAddressAgent(self)
        getMilasByAddressAgent.Register(question_initiated, ScPythonEventType.AddOutputEdge)

        getMilasByTimeAgent = GetMilasByTimeAgent(self)
        getMilasByTimeAgent.Register(question_initiated, ScPythonEventType.AddOutputEdge)

        getMilasByCoordinatesAgent = GetMilasByCoordinatesAgent(self)
        getMilasByCoordinatesAgent.Register(question_initiated, ScPythonEventType.AddOutputEdge)

    def OnShutdown(self):
        print('Shutting down Milas module')


service = MilasModule()
service.Run()