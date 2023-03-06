#include <memory>

#include "sc-memory/sc_memory.hpp"


#include "sc-memory/sc_event.hpp"




#define keynodes_hpp_20_init  bool _InitInternal() override \
{ \
    ScMemoryContext ctx(sc_access_lvl_make_min, "Keynodes::_InitInternal"); \
    bool result = true; \
    return result; \
}


#define keynodes_hpp_20_initStatic static bool _InitStaticInternal()  \
{ \
    ScMemoryContext ctx(sc_access_lvl_make_min, "Keynodes::_InitStaticInternal"); \
    bool result = true; \
	nrel_area = ctx.HelperResolveSystemIdtf("nrel_area", ScType::Node); result = result && nrel_area.IsValid(); \
	nrel_area_classification = ctx.HelperResolveSystemIdtf("nrel_area_classification", ScType::Node); result = result && nrel_area_classification.IsValid(); \
	large = ctx.HelperResolveSystemIdtf("large", ScType::Node); result = result && large.IsValid(); \
	shallow = ctx.HelperResolveSystemIdtf("shallow", ScType::Node); result = result && shallow.IsValid(); \
	question_classify_lake = ctx.HelperResolveSystemIdtf("question_classify_lake", ScType::Node); result = result && question_classify_lake.IsValid(); \
    return result; \
}


#define keynodes_hpp_20_decl 

#define keynodes_hpp_Keynodes_impl 

#undef ScFileID
#define ScFileID keynodes_hpp

