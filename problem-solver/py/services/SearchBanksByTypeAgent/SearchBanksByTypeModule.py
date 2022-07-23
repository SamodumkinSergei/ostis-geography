from common import ScModule, ScKeynodes, ScPythonEventType
from SearchBanksByTypeAgent import SearchBanksByTypeAgent # импорт агента

from sc import *


class SearchBanksByTypeModule(ScModule):

    def __init__(self):
        ScModule.__init__(
            self,
            ctx=__ctx__,
            cpp_bridge=__cpp_bridge__,
            keynodes=[],
        )
        self.keynodes = ScKeynodes(self.ctx)

    def OnInitialize(self, params):
        print('Initialize SearchBanksByType module') # меняем название модуля для логов
        question_initiated = self.keynodes['question_initiated']

        agent = SearchBanksByTypeAgent(self) # меняем SearchBanksByTypeAgent на свой, по аналогии можно добавлять больше агентов
        agent.Register(question_initiated, ScPythonEventType.AddOutputEdge)

    def OnShutdown(self):
        print('Shutting down SearchBanksByType module') # меняем название модуля для логов


service = SearchBanksByTypeModule()
service.Run()
