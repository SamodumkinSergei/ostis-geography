#include <memory>

#include "sc-memory/sc_memory.hpp"


#include "sc-memory/sc_event.hpp"




#define classifyLakeDepthAgent_hpp_19_init  bool _InitInternal() override \
{ \
    ScMemoryContext ctx(sc_access_lvl_make_min, "classifyLakeDepthAgent::_InitInternal"); \
    bool result = true; \
    return result; \
}


#define classifyLakeDepthAgent_hpp_19_initStatic static bool _InitStaticInternal()  \
{ \
    ScMemoryContext ctx(sc_access_lvl_make_min, "classifyLakeDepthAgent::_InitStaticInternal"); \
    bool result = true; \
    return result; \
}


#define classifyLakeDepthAgent_hpp_19_decl \
private:\
	typedef ScAgent Super;\
protected: \
	classifyLakeDepthAgent(char const * name, sc_uint8 accessLvl) : Super(name, accessLvl) {}\
	virtual sc_result Run(ScAddr const & listenAddr, ScAddr const & edgeAddr, ScAddr const & otherAddr) override; \
private:\
	static std::unique_ptr<ScEvent> ms_event;\
    static std::unique_ptr<ScMemoryContext> ms_context;\
public: \
	static bool handler_emit(ScAddr const & addr, ScAddr const & edgeAddr, ScAddr const & otherAddr)\
	{\
		classifyLakeDepthAgent Instance("classifyLakeDepthAgent", sc_access_lvl_make_min);\
		return Instance.Run(addr, edgeAddr, otherAddr) == SC_RESULT_OK;\
	}\
	static void RegisterHandler()\
	{\
		SC_ASSERT(!ms_event.get(), ());\
		SC_ASSERT(!ms_context.get(), ());\
		ms_context.reset(new ScMemoryContext(sc_access_lvl_make_min, "handler_classifyLakeDepthAgent"));\
		ms_event.reset(new ScEvent(*ms_context, Keynodes::question_classify_lake_depth, ScEvent::Type::AddOutputEdge, &classifyLakeDepthAgent::handler_emit));\
        if (ms_event.get())\
        {\
            SC_LOG_INFO("Register agent classifyLakeDepthAgent");\
        }\
        else\
        {\
            SC_LOG_ERROR("Can't register agent classifyLakeDepthAgent");\
        }\
	}\
	static void UnregisterHandler()\
	{\
		ms_event.reset();\
		ms_context.reset();\
	}

#define classifyLakeDepthAgent_hpp_classifyLakeDepthAgent_impl \
std::unique_ptr<ScEvent> classifyLakeDepthAgent::ms_event;\
std::unique_ptr<ScMemoryContext> classifyLakeDepthAgent::ms_context;

#undef ScFileID
#define ScFileID classifyLakeDepthAgent_hpp

