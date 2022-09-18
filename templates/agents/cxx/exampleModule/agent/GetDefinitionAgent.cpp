#include "sc-agents-common/utils/AgentUtils.hpp"
#include "sc-agents-common/utils/CommonUtils.hpp"
#include "sc-agents-common/utils/IteratorUtils.hpp"
#include "sc-agents-common/keynodes/coreKeynodes.hpp"

#include "keynodes/ExampleKeynodes.hpp"

#include "GetDefinitionAgent.hpp"

using namespace exampleModule;
using namespace utils;

SC_AGENT_IMPLEMENTATION(GetDefinitionAgent)
{
  ScAddr actionNode = m_memoryCtx.GetEdgeTarget(edgeAddr); // получаем узел который отвечает за вызов агента с определенными параметрами

  if (!checkActionClass(actionNode)) // проверяем что был вызван действительно наш агент
  {
    return SC_RESULT_OK;
  }
  SC_LOG_DEBUG("GetDefinitionAgent started")

  // получаем наши аргументы агента
  ScAddr firstParameter = IteratorUtils::getFirstByOutRelation(
        &m_memoryCtx,
        actionNode,
        scAgentsCommon::CoreKeynodes::rrel_1); // чтобы получить второй аргумент агента меняем на rrel_2 вместо rrel_1, следующие аргументы по аналогии.
  if (!firstParameter.IsValid())
  {
    SC_LOG_ERROR("First parameter isn't valid.")
    AgentUtils::finishAgentWork(&m_memoryCtx, actionNode, false);
    return SC_RESULT_ERROR_INVALID_PARAMS;
  }
  // создаем узел ответа
  ScAddr answerNode = m_memoryCtx.CreateNode(ScType::NodeConstStruct);
  m_memoryCtx.CreateEdge(ScType::EdgeAccessConstPosPerm, answerNode, firstParameter); // добавляем входные аргументы агента в ответнуый контур

  // тут пишите свой агент
  // в данном примере агент получает как аргумент узел и находит описание этого узла, т.е. конструкцию: firstParameter <- rrel_key_sc_element: ...(* <-definition;; <= nrel_sc_text_translation: ...(* ->rrel_example: [Определение];; *);; *);;

  // ниже получение определения через итераторы
  ScAddr key_sc_element;
  // пятиэлементный итератор для поиска конструкции firstParameter <- rrel_key_sc_element: ...;;
  ScIterator5Ptr iterator5 = m_memoryCtx.Iterator5(ScType::Unknown, ScType::EdgeAccessConstPosPerm, firstParameter, ScType::EdgeAccessConstPosPerm, ExampleKeynodes::rrel_key_sc_element);
  if (iterator5->Next())
  {
    key_sc_element = iterator5->Get(0);
    ScAddr translation;
    // пятиэлементный итератор для поиска конструкции ... <= nrel_sc_text_translation: ...;;
    ScIterator5Ptr it5 = m_memoryCtx.Iterator5(ScType::Unknown, ScType::EdgeDCommonConst, key_sc_element, ScType::EdgeAccessConstPosPerm, ExampleKeynodes::nrel_sc_text_translation);
    if (it5->Next())
    {
      translation = it5->Get(0);
      ScAddr defLink;
      // пятиэлементный итератор для поиска конструкции .. -> rrel_example: [Определение];;
      ScIterator5Ptr i5 = m_memoryCtx.Iterator5(translation, ScType::EdgeAccessConstPosPerm, ScType::Unknown, ScType::EdgeAccessConstPosPerm, ExampleKeynodes::rrel_example);
      if (i5->Next())
      {
        defLink = i5->Get(2);
        string defString = CommonUtils::readString(&m_memoryCtx, defLink); // получение содержимого из sc-ссылки
        SC_LOG_DEBUG(defString)
        // добавим все что хотим отобразить на странице остиса в контур ответа
        for (int i=0; i < 5; i++){
          m_memoryCtx.CreateEdge(ScType::EdgeAccessConstPosPerm, answerNode, i5->Get(i));
          m_memoryCtx.CreateEdge(ScType::EdgeAccessConstPosPerm, answerNode, it5->Get(i));
          m_memoryCtx.CreateEdge(ScType::EdgeAccessConstPosPerm, answerNode, iterator5->Get(i));
        }
      }
    }
  }

  string def = getDefinition(firstParameter); // получение определения через шаблон
  SC_LOG_DEBUG(def)

  // завершаем работу агента
  AgentUtils::finishAgentWork(&m_memoryCtx, actionNode, answerNode, true);
  SC_LOG_DEBUG("GetDefinitionAgent finished")
  return SC_RESULT_OK;
}

bool GetDefinitionAgent::checkActionClass(const ScAddr & actionNode)
{
  return m_memoryCtx.HelperCheckEdge(
        ExampleKeynodes::action_get_definition,
        actionNode,
        ScType::EdgeAccessConstPosPerm);
}

string GetDefinitionAgent::getDefinition(const ScAddr & node)
{
  ScTemplate templ;

  templ.TripleWithRelation(
          ScType::NodeVar >> "_definition",    // src
          ScType::EdgeAccessVarPosPerm,        // arcType
          node,                                // trg
          ScType::EdgeAccessVarPosPerm,        // relArcType
          ExampleKeynodes::rrel_key_sc_element // relation
  );
  templ.Triple(
          ExampleKeynodes::definition,  //src
          ScType::EdgeAccessVarPosPerm, // arcType
          "_definition");               // trg
  templ.TripleWithRelation(
          ScType::NodeVar >> "_translation",
          ScType::EdgeDCommonVar,
          "_definition",
          ScType::EdgeAccessVarPosPerm,
          ExampleKeynodes::nrel_sc_text_translation
  );
  templ.TripleWithRelation(
          "_translation",
          ScType::EdgeAccessVarPosPerm,
          ScType::LinkVar >> "_link",
          ScType::EdgeAccessVarPosPerm,
          ExampleKeynodes::rrel_example
  );

  ScTemplateSearchResult results;
  m_memoryCtx.HelperSearchTemplate(templ, results);
  string result = "";
  bool first = true;
  for(size_t i=0; i < results.Size(); i++){
    if (!first){
      result += "\n";
    }
    first = false;
    result += CommonUtils::readString(&m_memoryCtx, results[i]["_link"]);
  }
  return result;
}