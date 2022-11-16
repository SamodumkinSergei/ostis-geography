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
  ScAddr rangeTop;

  SC_LOG_INFO("search start");

  ScIterator3Ptr arguments = ms_context->Iterator3(questionNode, ScType::EdgeAccessConstPosPerm, ScType::NodeConst);

  while (arguments->Next())
  {
    ScAddr value = arguments->Get(2);
    if (ms_context->HelperCheckEdge(valueConcept, value, ScType::EdgeAccessConstPosPerm))
    {
      rangeTop = value;
    }
  }

  if (!rangeTop.IsValid())
  {
    return {};
  }

  std::string top = ms_context->HelperGetSystemIdtf(rangeTop);
  SC_LOG_INFO("search value \"" + top + "\"");

  ScIterator3Ptr danceStudios = ms_context->Iterator3(
      DanceStudiosKeynodes::concept_dance_studio, ScType::EdgeAccessConstPosPerm, ScType::NodeConst);

  ScAddr solution = ms_context->CreateNode(ScType::NodeConst);
  ScAddr set = ms_context->CreateNode(ScType::NodeConst);
  ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, solution, set);

  while (danceStudios->Next())
  {
    ScAddr danceStudio = danceStudios->Get(2);

    ScIterator5Ptr property = ms_context->Iterator5(
        danceStudio, ScType::EdgeDCommon, ScType::NodeConst, ScType::EdgeAccessConstPosPerm, propertyNrel);

    if (property->Next())
    {
      ScAddr propertyValue = property->Get(2);

      std::string value = ms_context->HelperGetSystemIdtf(propertyValue);

      if (value == top)
      {
        SC_LOG_INFO(value + " == " + top);

        ScAddr edge = ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, set, danceStudio);
        ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, solution, edge);
        ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, solution, danceStudio);
      }
    }
  }

  ms_context->CreateEdge(ScType::EdgeAccessConstPosPerm, DanceStudiosKeynodes::concept_success_solution, solution);

  return solution;
}
}  // namespace dance_studios
