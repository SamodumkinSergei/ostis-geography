## Receiving arguments by the agent

The agent receives arguments through the otherAddr node. This node is a field of the ScAgent class and the arguments used in the agent's work are attached to it.

Example: 

<img src="../../images/receiveAgentArgument.png"></img>

## ScMemoryContext

`ScMemoryContext` -- is a class that provides utility methods for working with the knowledge base, the most used of them are:

 - `EraseElement`
 - `CreateNode`
 - `CreateLink`
 - `CreateEdge`
 - `GetEdgeSource/GetEdgeTarget`
 - `GetLinkContent/SetLinkContent`
 - `HelperFindBySystemIdtf`
 - `HelperCheckEdge`
 - `HelperSetSystemIdtf`
 - `Iterator3/Iterator5`
 
For more information about node types and other features of the C++ API, see [sc-machine documentation](https://ostis-ai.github.io/sc-machine/)

