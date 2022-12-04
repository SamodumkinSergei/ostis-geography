/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "DanceStudiosByString.hpp"
#include "keynodes/DanceStudiosKeynodes.hpp"
#include <sc-agents-common/utils/IteratorUtils.hpp>

namespace dance_studios
{
ScAddr DanceStudiosByString::findDanceStudiosByString(
    ScMemoryContext * ms_context,
    ScAddr questionNode,
    ScAddr valueConcept,
    ScAddr propertyNrel) const
{
  SC_LOG_INFO("DanceStudiosByString::findDanceStudiosByString begin");

  ScAddr searchNode;
  ScIterator3Ptr iterator3 = ms_context->Iterator3(questionNode, ScType::EdgeAccessConstPosPerm, ScType::NodeConst);

  while (iterator3->Next())
  {
    ScAddr node = iterator3->Get(2);
    if (ms_context->HelperCheckEdge(valueConcept, node, ScType::EdgeAccessConstPosPerm))
    {
      searchNode = node;
    }
  }

  if (!searchNode.IsValid())
  {
    SC_LOG_ERROR("Search node is invalid");
    return {};
  }

  std::string searchValue = ms_context->HelperGetSystemIdtf(searchNode);
  SC_LOG_DEBUG("Search value = " + searchValue + "");

  iterator3 = ms_context->Iterator3(
      DanceStudiosKeynodes::concept_dance_studio, ScType::EdgeAccessConstPosPerm, ScType::NodeConst);

  ScAddr answer = ms_context->CreateNode(ScType::NodeConst);

  while (iterator3->Next())
  {
    ScAddr danceStudio = iterator3->Get(2);
    std::string danceStudioIdtf = ms_context->HelperGetSystemIdtf(danceStudio);

    ScIterator5Ptr property = ms_context->Iterator5(
        danceStudio, ScType::EdgeDCommon, ScType::NodeConst, ScType::EdgeAccessConstPosPerm, propertyNrel);

    if (property->Next())
    {
      ScAddr propertyNode = property->Get(2);
      std::string propertyValue = ms_context->HelperGetSystemIdtf(propertyNode);

      if (propertyValue == searchValue)
      {
        SC_LOG_DEBUG("For dance studio = " + danceStudioIdtf + " search value equals property value = " + propertyValue);
        ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, answer, danceStudio);
      }
    }
  }

  ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, DanceStudiosKeynodes::concept_success_solution, answer);

  SC_LOG_INFO("DanceStudiosByString::findDanceStudiosByString end");
  return answer;
}
}  // namespace dance_studios
