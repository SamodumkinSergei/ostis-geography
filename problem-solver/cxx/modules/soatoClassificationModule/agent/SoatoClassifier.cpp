#include "sc-agents-common/utils/CommonUtils.hpp"  // Общие утилиты
#include "sc-agents-common/utils/GenerationUtils.hpp"  // Утилиты генерации
#include "sc-agents-common/utils/IteratorUtils.hpp"  // Утилиты итерации
#include "sc-memory/sc_memory.hpp"  // Работа с SC-памятью
#include "agent/AdministrativeFacility.hpp"  // Административные объекты
#include "agent/SoatoClassifier.hpp"  // Классификатор СОАТО
#include "keynodes/Keynodes.hpp"  // Узлы ключевых элементов

#include "lib/csv.h"  // Чтение CSV

#include "SoatoClassificationAgent.hpp"  // Интерфейс агента

namespace soatoClassificationModule  // Пространство имен для модуля
{

// Основной метод агента, выполняющий логику программы
ScResult SoatoClassificationAgent::DoProgram(ScActionInitiatedEvent const & event, ScAction & action)
{
  ScAddr actionAddr = event.GetOtherElement();
  if (!checkActionClass(actionAddr))  // Проверяем, принадлежит ли действие к классу агента
  {
    return action.FinishSuccessfully();  // Если нет, завершаем действие успешно
  }

  SC_AGENT_LOG_DEBUG("started");  // Логируем начало работы агента

  ScAddrVector answerElements;

  try
  {
    convertSoatoCodes();  // Выполняем конвертацию кодов СОАТО
  }
  catch (utils::ScException & exception)
  {
    SC_AGENT_LOG_ERROR(exception.Description());  // Логируем ошибку
    SC_AGENT_LOG_DEBUG("finished with an error");
    return action.FinishUnsuccessfully();
  }

  action.SetResult(answerElements[0]);  // Устанавливаем результат действия
  SC_AGENT_LOG_DEBUG("finished");
  return action.FinishSuccessfully();
}

// Возвращает SC-адрес действия, связанного с агентом
ScAddr SoatoClassificationAgent::GetActionClass() const
{
  return Keynodes::action_soato_classification;  // Возвращаем узел действия
}

// Проверяет, принадлежит ли заданное действие классу агента
bool SoatoClassificationAgent::checkActionClass(ScAddr const & actionAddr)
{
  return m_context.CheckConnector(Keynodes::action_soato_classification, actionAddr, ScType::ConstPermPosArc);
}

// Конвертирует коды СОАТО в SC-память
void SoatoClassificationAgent::convertSoatoCodes()
{
  SoatoClassifier classifier;

  io::CSVReader<2> inTable(SOATO_CODES);  // Чтение CSV с двумя столбцами
  inTable.read_header(io::ignore_extra_column, "СОАТО", "Наименование объекта");

  std::string code;
  std::string name;

  while (inTable.read_row(code, name))  // Построчно читаем коды и имена
  {
    const AdministrativeFacility facility = classifier.classify(std::make_pair(code, name));  // Классифицируем объект
    sew(facility);  // Связываем объект с SC-памятью
  }
}

// Метод связывания объекта в SC-памяти
void SoatoClassificationAgent::sew(const AdministrativeFacility & facility)
{
  ScAddr node = initializeFacility(facility);  // Инициализируем объект
  const std::vector<std::string> & categories = facility.getCategories();

  for (const auto & category : categories)  // Добавляем категории объекта
  {
    addToClassIfNotPresent(node, category);
  }
}

// Инициализирует узел объекта в SC-памяти
ScAddr SoatoClassificationAgent::initializeFacility(const AdministrativeFacility & facility)
{
  ScAgentContext ms_context;
  const auto & name = facility.getName();
  auto facilityNode = ms_context.ResolveElementSystemIdentifier(name, ScType::ConstNode);  // Узел объекта

  addToClassIfNotPresent(facilityNode, "АТЕ");  // Добавляем объект в класс "АТЕ"

  const auto & code = facility.getCode();
  auto codeNode = ms_context.ResolveElementSystemIdentifier(code, ScType::ConstNode);  // Узел кода

  addToClassIfNotPresent(codeNode, "код СОАТО");  // Добавляем код в класс "код СОАТО"

  auto facilityToCodeEdge = createEdgeIfNotPresent(facilityNode, codeNode, ScType::ConstCommonArc);  // Связываем объект и код

  auto codeNoRole = ms_context.ResolveElementSystemIdentifier("код СОАТО*", ScType::ConstNodeNonRole);  // Узел отношения

  createEdgeIfNotPresent(codeNoRole, facilityToCodeEdge, ScType::ConstPermPosArc);  // Связываем отношение с узлом

  return facilityNode;
}

// Добавляет узел в класс, если он еще не принадлежит ему
void SoatoClassificationAgent::addToClassIfNotPresent(ScAddr node, const std::string & className)
{
  ScAgentContext ms_context;
  auto scClass = ms_context.ResolveElementSystemIdentifier(className, ScType::ConstNodeClass);
  createEdgeIfNotPresent(scClass, node, ScType::ConstPermPosArc);
}

// Создает дугу, если она еще не существует
ScAddr SoatoClassificationAgent::createEdgeIfNotPresent(const ScAddr & begin, const ScAddr & end, const ScType & type)
{
  ScAgentContext ms_context;
  auto edgeIsPresent = m_context.CheckConnector(begin, end, type);
  if (!edgeIsPresent)
  {
    return ms_context.GenerateConnector(type, begin, end);  // Генерируем новую дугу
  }
}

}  // namespace soatoClassificationModule
