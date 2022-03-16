from common import ScModule, ScKeynodes, ScPythonEventType
from SearchPostOfficeByTypeAgent import SearchPostOfficeByTypeAgent # импорт агента

from sc import *


class SearchPostOfficeByTypeModule(ScModule):

    def __init__(self):
        ScModule.__init__(
            self,
            ctx=__ctx__,
            cpp_bridge=__cpp_bridge__,
            keynodes=[],
        )
        self.keynodes = ScKeynodes(self.ctx)

    def OnInitialize(self, params):
        print('Initialize SearchPostOfficesByType module') # меняем название модуля для логов
        question_initiated = self.keynodes['question_initiated']

        agent = SearchPostOfficeByTypeAgent(self) # меняем SearchPostOfficeByTypeAgent на свой, по аналогии можно добавлять больше агентов
        agent.Register(question_initiated, ScPythonEventType.AddOutputEdge)

    def OnShutdown(self):
        print('Shutting down SearchPostOfficesByType module') # меняем название модуля для логов


service = SearchPostOfficeByTypeModule()
service.Run()
