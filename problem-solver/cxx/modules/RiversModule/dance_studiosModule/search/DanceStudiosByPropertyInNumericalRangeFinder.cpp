/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "DanceStudiosByPropertyInNumericalRangeFinder.hpp"
#include "keynodes/DanceStudiosKeynodes.hpp"
#include <sc-agents-common/utils/IteratorUtils.hpp>

namespace dance_studios
{
ScAddr DanceStudiosByPropertyInNumericalRangeFinder::findDanceStudiosByPropertyInNumericalRange(
    ScMemoryContext * ms_context,
    ScAddr questionNode,
    ScAddr valueConcept,
    ScAddr propertyNrel) const
{
  ScAddr rangeTop;

  

  ScIterator3Ptr arguments = ms_context->CreateIterator3(questionNode, ScType::ConstPermPosArc, ScType::ConstNode);

  while (arguments->Next())
  {
    ScAddr value = arguments->Get(2);
    if (ms_context->CheckConnector(valueConcept, value, ScType::ConstPermPosArc))
    {
      rangeTop = value;
    }
  }

  if (!rangeTop.IsValid())
  {
    return {};
  }

  long long top = std::stoll(ms_context->GetElementSystemIdentifier(rangeTop));
  

  ScIterator3Ptr danceStudios = ms_context->CreateIterator3(
      DanceStudiosKeynodes::concept_dance_studio, ScType::ConstPermPosArc, ScType::ConstNode);

  ScAddr solution = ms_context->GenerateNode(ScType::ConstNode);
  ScAddr set = ms_context->GenerateNode(ScType::ConstNode);
  ms_context->GenerateConnector(ScType::ConstPermPosArc, solution, set);

  while (danceStudios->Next())
  {
    ScAddr danceStudio = danceStudios->Get(2);

    ScIterator5Ptr property = ms_context->CreateIterator5(
        danceStudio, ScType::CommonArc, ScType::ConstNode, ScType::ConstPermPosArc, propertyNrel);

    if (property->Next())
    {
      ScAddr propertyValue = property->Get(2);

      long long value = std::stoll(ms_context->GetElementSystemIdentifier(propertyValue));

      if (value == top)
      {
        

        ScAddr edge = ms_context->GenerateConnector(ScType::ConstPermPosArc, set, danceStudio);
        ms_context->GenerateConnector(ScType::ConstPermPosArc, solution, edge);
        ms_context->GenerateConnector(ScType::ConstPermPosArc, solution, danceStudio);
      }
    }
  }

  ms_context->GenerateConnector(ScType::ConstPermPosArc, DanceStudiosKeynodes::concept_success_solution, solution);

  return solution;
}
}  // namespace dance_studios
