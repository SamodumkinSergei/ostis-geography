from common import ScModule, ScKeynodes, ScPythonEventType
from OpenStreetMapAgent import OpenStreetMapAgent

from sc import *


class OpenStreetMapModule(ScModule):

    def __init__(self):
        ScModule.__init__(
            self,
            ctx=__ctx__,
            cpp_bridge=__cpp_bridge__,
            keynodes=[],
        )
        self.keynodes = ScKeynodes(self.ctx)

    def OnInitialize(self, params):
        print('Initialize OpenStreetMap module')
        question_initiated = self.keynodes['question_initiated']

        agent = OpenStreetMapAgent(self)
        agent.Register(question_initiated, ScPythonEventType.AddOutputEdge)

    def OnShutdown(self):
        print('Shutting down OpenStreetMap module')


service = OpenStreetMapModule()
service.Run()
