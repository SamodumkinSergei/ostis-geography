from common import ScModule, ScKeynodes, ScPythonEventType
from SearchPostOfficeByBrandAgent import SearchPostOfficeByBrandAgent # импорт агента

from sc import *


class SearchPostOfficeByBrandModule(ScModule):

    def __init__(self):
        ScModule.__init__(
            self,
            ctx=__ctx__,
            cpp_bridge=__cpp_bridge__,
            keynodes=[],
        )
        self.keynodes = ScKeynodes(self.ctx)

    def OnInitialize(self, params):
        print('Initialize SearchPostOfficeByBrand module') # меняем название модуля для логов
        question_initiated = self.keynodes['question_initiated']

        agent = SearchPostOfficeByBrandAgent(self) # меняем SearchPostOfficeByBrandAgent на свой, по аналогии можно добавлять больше агентов
        agent.Register(question_initiated, ScPythonEventType.AddOutputEdge)

    def OnShutdown(self):
        print('Shutting down SearchPostOfficeByBrand module') # меняем название модуля для логов


service = SearchPostOfficeByBrandModule()
service.Run()