from common import ScModule, ScKeynodes, ScPythonEventType
from GetUniverisitiesByEmailAgent import GetUniverisitiesByEmailAgent # импорт агента
from GetUniversitiesByAdressAgent import GetUniversitiesByAdressAgent
from GetUniversitiesByFacultiesAgent import GetUniversitiesByFacultiesAgent
from GetUniversitiesByPassingGradeAgent import GetUniversitiesByPassingGradeAgent
from GetUniversitiesByPhoneNumberAgent import GetUniversitiesByPhoneNumberAgent
from GetUniversitiesByRegionAgent import GetUniversitiesByRegionAgent
from GetUniversitiesByStudentAmountGreaterAgent import GetUniversitiesByStudentAmountGreaterAgent
from GetUniversitiesByStudentAmountLessAgent import GetUniversitiesByStudentAmountLessAgent

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
        print('Initialize Universities module')
        question_initiated = self.keynodes['question_initiated']

        agent1 = GetUniverisitiesByEmailAgent(self)
        agent2 = GetUniversitiesByAdressAgent (self)
        agent3 = GetUniversitiesByFacultiesAgent(self)

        agent4 = GetUniversitiesByPassingGradeAgent(self)
        agent5 = GetUniversitiesByPhoneNumberAgent(self)
        agent6 = GetUniversitiesByRegionAgent(self)

        agent7 = GetUniversitiesByStudentAmountGreaterAgent(self)
        agent8 = GetUniversitiesByStudentAmountLessAgent(self)


        agent1.Register(question_initiated, ScPythonEventType.AddOutputEdge)
        agent2.Register(question_initiated, ScPythonEventType.AddOutputEdge)
        agent3.Register(question_initiated, ScPythonEventType.AddOutputEdge)
        agent4.Register(question_initiated, ScPythonEventType.AddOutputEdge)
        agent5.Register(question_initiated, ScPythonEventType.AddOutputEdge)
        agent6.Register(question_initiated, ScPythonEventType.AddOutputEdge)
        agent7.Register(question_initiated, ScPythonEventType.AddOutputEdge)
        agent8.Register(question_initiated, ScPythonEventType.AddOutputEdge)


    def OnShutdown(self):
        print('Shutting down Example module')


service = ExampleModule()
service.Run()