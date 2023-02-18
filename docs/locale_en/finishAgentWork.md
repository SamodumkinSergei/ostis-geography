## Agent shutdown

The agent shutdown is performed with a method:

    utils::AgentUtils::finishAgentWork(&m_memoryCtx, actionAddr, answerVector, true)
	
Arguments: 

 - `&m_memoryCtx` -- ScMemoryContext агента
 - `actionAddr` -- accepted arguments node
 - `answerVector` -- ScAddrVector containing all elements of the resulting structure
 - `bool` -- the result of the agent's work

After the agent was shutdown with the method, it is necessary to return the result with one of the following constants:

 - `SC_RESULT_ERROR` -- error
 - `SC_RESULT_OK` -- successfully finished

