from common import ScModule, ScKeynodes, ScPythonEventType
from SearchBanksByCityAgent import SearchBanksByCityAgent # импорт агента

from sc import *


class SearchBanksByCityModule(ScModule):

    def __init__(self):
        ScModule.__init__(
            self,
            ctx=__ctx__,
            cpp_bridge=__cpp_bridge__,
            keynodes=[],
        )
        self.keynodes = ScKeynodes(self.ctx)

    def OnInitialize(self, params):
        print('Initialize SearchBanksByCity module') # меняем название модуля для логов
        question_initiated = self.keynodes['question_initiated']

        agent = SearchBanksByCityAgent(self) # меняем search_banks_by_city_agent на свой, по аналогии можно добавлять больше агентов
        agent.Register(question_initiated, ScPythonEventType.AddOutputEdge)

    def OnShutdown(self):
        print('Shutting down SearchBanksByCity module') # меняем название модуля для логов


service = SearchBanksByCityModule()
service.Run()
