from common import ScModule, ScKeynodes, ScPythonEventType
from GetKindergartensByOpenTimeAgent import GetKindergartensByOpenTimeAgent
from GetKindergartensByCloseTimeAgent import GetKindergartensByCloseTimeAgent
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
        agent3 = GetKindergartensByOpenTimeAgent(self)
        agent4 = GetKindergartensByCloseTimeAgent(self)
        agent3.Register(question_initiated, ScPythonEventType.AddOutputEdge)
        agent4.Register(question_initiated, ScPythonEventType.AddOutputEdge)


    def OnShutdown(self):
        print('Shutting down Example module')


service = ExampleModule()
service.Run()