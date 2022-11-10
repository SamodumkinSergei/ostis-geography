from common import ScModule, ScKeynodes, ScPythonEventType
from CityAgent import CityAgent # импорт агента


from sc import *


class CityModule(ScModule):

    def __init__(self):
        ScModule.__init__(
            self,
            ctx=__ctx__,
            cpp_bridge=__cpp_bridge__,
            keynodes=[],
        )
        self.keynodes = ScKeynodes(self.ctx)

    def OnInitialize(self, params):
        print('Initialize CityAgent') # меняем название модуля для логов
        question_initiated = self.keynodes['question_initiated']

        agent = CityAgent(self) # меняем GetDefinitionAgent на свой, по аналогии можно добавлять больше агентов
        agent.Register(question_initiated, ScPythonEventType.AddOutputEdge)

    def OnShutdown(self):
        print('Shutting down CityAgent') # меняем название модуля для логов


service = CityModule()
service.Run()