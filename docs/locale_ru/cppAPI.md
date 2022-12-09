## Получение аргументов агентом

Получение аргументов агентом осуществляется через узел otherAddr. Данный узел является полем класса ScAgent и к нему присоединяются аргументы используемые в работе агента.

Пример: 

<img src="../../images/receiveAgentArgument.png"></img>

## ScMemoryContext

`ScMemoryContext` -- это класс предоставляющий утилитарные методы работы с базой знаний, наиболее используемые из них это:

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
 
Подробнее о типах узлов и других возможностях C++ API можно узнать в [документации sc-машины](https://ostis-ai.github.io/sc-machine/)

