from common import ScModule, ScKeynodes, ScPythonEventType
from GetKindergartensByTypeAgent import GetKindergartensByTypeAgent

from sc import *


class ExampleModule(ScModule):

    def __init__(self):
        ScModule.__init__(
            self,
            ctx=__ctx__,
            cpp_bridge=__cpp_bridge__,
            keynodes=[],
        )
        self.keynodes = ScKeynodes(self.ctx)

    def OnInitialize(self, params):
        print('Initialize Kindergartens module')
        question_initiated = self.keynodes['question_initiated']
        agent7 = GetKindergartensByTypeAgent(self)
        agent7.Register(question_initiated, ScPythonEventType.AddOutputEdge)


    def OnShutdown(self):
        print('Shutting down Example module')


service = ExampleModule()
service.Run()
