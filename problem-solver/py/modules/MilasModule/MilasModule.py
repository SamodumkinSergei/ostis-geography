from sc_kpm import ScModule
from .GetMilasByAddressAgent import GetMilasByAddressAgent
from .GetMilasByTimeAgent import GetMilasByTimeAgent
from .GetMilasByCoordinatesAgent import GetMilasByCoordinatesAgent


class MilasModule(ScModule):
    def __init__(self):
        super().__init__(
          # your agents
          GetMilasByAddressAgent(), 
          GetMilasByTimeAgent(),
	  GetMilasByCoordinatesAgent(),
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