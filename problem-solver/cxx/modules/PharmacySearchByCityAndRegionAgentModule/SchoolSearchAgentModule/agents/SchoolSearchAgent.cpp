#include "sc-agents-common/utils/CommonUtils.hpp"
#include "sc-agents-common/utils/IteratorUtils.hpp"
#include <string>
#include <iostream>
#include <vector>

#include "SchoolSearchAgent.hpp"
#include "keynodes/SchoolKeynodes.hpp"

using namespace std;
using namespace utils;

namespace SchoolSearchAgentModule
{

ScAddr SchoolSearchAgent::GetActionClass() const
{
//todo(codegen-removal): replace action with your action class
  return SchoolKeynodes::action_schoolByNumberSearch;
}

// ScResult SchoolSearchAgent::DoProgram(ScEventAfterGenerateOutgoingArc<ScType::ConstPermPosArc> const & event, ScAction & action)
ScResult SchoolSearchAgent::DoProgram(ScAction & action)
{
  // if (!event.GetArc().IsValid())
  //   return action.FinishUnsuccessfully();

  
  auto const & [school] = action.GetArguments<1>();

  if (!m_context.IsElement(school))
  {
    SC_AGENT_LOG_ERROR("Action does not have argument.");

    return action.FinishWithError();
  }

  if (!school.IsValid())
  {
    SC_AGENT_LOG_ERROR("First parameter isn't valid.");
    return action.FinishUnsuccessfully();
  }

  ScAddr answer = m_context.GenerateNode(ScType::ConstNodeStructure);

  ScIterator5Ptr it1 = m_context.CreateIterator5(
      ScType::Unknown, ScType::ConstCommonArc, school, ScType::ConstPermPosArc, SchoolKeynodes::nrel_school_number);
  ScAddr school1;
  ScAddr schoolResult;
  if (it1->Next())
  {
    school1 = it1->Get(0);
    ScIterator5Ptr it2 = m_context.CreateIterator5(
        school1, ScType::ConstCommonArc, ScType::Unknown, ScType::ConstPermPosArc, SchoolKeynodes::nrel_search_area);
    if (it2->Next())
    {
      m_context.GenerateConnector(ScType::ConstPermPosArc, answer, schoolResult);
    }
    else
    {
      SC_AGENT_LOG_ERROR("There is no such school");
    }
  }

//todo(codegen-removal): replace AgentUtils:: usage
  // AgentUtils::usage(&m_context, actionNode);
  
  action.SetResult(answer);
  return action.FinishSuccessfully();
}

}  // namespace SchoolSearchAgentModule
