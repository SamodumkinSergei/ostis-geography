#include <algorithm>
#include "sc-agents-common/utils/AgentUtils.hpp"
#include "SoatoSewer.hpp"

using namespace std;

// VillageSearchAgent is cool to check examples
void SoatoSewer::sew(ScMemoryContext & ms_context, const vector<AdministrativeFacility> & facilities)
{
  for_each(facilities.cbegin(), facilities.cend(), [&ms_context](AdministrativeFacility & facility) {
    auto node = SoatoSewer::initializeFacility(ms_context, facility);
    const auto & classes = facility.getClasses();
    for_each(classes.cbegin(), classes.cend(), [&ms_context, &node](string & class_name) {
      SoatoSewer::addToClassIfNotPresent(ms_context, node, class_name);
    });
  });
}

ScAddr SoatoSewer::initializeFacility(ScMemoryContext & ms_context, const AdministrativeFacility & facility)
{
  const auto & name = facility.getName();
  auto node = SoatoSewer::resolveNodeByIdtf(ms_context, ScType::Node, name);

  auto code = resolveNodeByIdtf(ms_context, ScType::Node, to_string(facility.getCode()));
  SoatoSewer::addToClassIfNotPresent(ms_context, node, "код СОАТО");
  ms_context.CreateEdge(ScType::EdgeUCommon, node, code);

  return node;
}

ScAddr SoatoSewer::resolveNodeByIdtf(ScMemoryContext & ms_context, const ScType & type, const string & idtf)
{
  auto node = ms_context.HelperFindBySystemIdtf(idtf);
  if (node.IsValid())
  {
    return node;
  }
  else
  {
    return ms_context.CreateNode(type);
  }
}

void SoatoSewer::addToClassIfNotPresent(ScMemoryContext & ms_context, ScAddr node, const string & class_name)
{
  auto _class = SoatoSewer::resolveNodeByIdtf(ms_context, ScType::NodeClass, class_name);
  auto iterator = ms_context.Iterator3(_class, ScType::EdgeAccess, node);
  if (!iterator->Next())
  {
    ms_context.CreateEdge(ScType::EdgeAccess, _class, node);
  }
}
