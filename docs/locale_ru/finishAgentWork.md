## Завершение работы агента

Агент завершает работу с помощью метода 

    utils::AgentUtils::finishAgentWork(&m_memoryCtx, actionAddr, answerVector, true)
	
Аргументы: 

 - `&m_memoryCtx` -- ScMemoryContext агента
 - `actionAddr` -- узел принимаемых аргументов
 - `answerVector` -- ScAddrVector содержащий все элементы результирующей конструкции
 - `bool` -- результат работы агента

После завершения работы агента методом, из необходимо вернуть результат работы в виде одной из констант:

 - `SC_RESULT_ERROR` -- ошибка
 - `SC_RESULT_OK` -- успешное завершение

