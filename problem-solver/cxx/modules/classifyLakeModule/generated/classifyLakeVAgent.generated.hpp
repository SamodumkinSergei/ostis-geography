#include <memory>

#include "sc-memory/sc_memory.hpp"


#include "sc-memory/sc_event.hpp"




#define classifyLakeVAgent_hpp_19_init  bool _InitInternal() override \
{ \
    ScMemoryContext ctx(sc_access_lvl_make_min, "classifyLakeVAgent::_InitInternal"); \
    bool result = true; \
    return result; \
}


#define classifyLakeVAgent_hpp_19_initStatic static bool _InitStaticInternal()  \
{ \
    ScMemoryContext ctx(sc_access_lvl_make_min, "classifyLakeVAgent::_InitStaticInternal"); \
    bool result = true; \
    return result; \
}


#define classifyLakeVAgent_hpp_19_decl \
private:\
	typedef ScAgent Super;\
protected: \
	classifyLakeVAgent(char const * name, sc_uint8 accessLvl) : Super(name, accessLvl) {}\
	virtual sc_result Run(ScAddr const & listenAddr, ScAddr const & edgeAddr, ScAddr const & otherAddr) override; \
private:\
	static std::unique_ptr<ScEvent> ms_event;\
    static std::unique_ptr<ScMemoryContext> ms_context;\
public: \
	static bool handler_emit(ScAddr const & addr, ScAddr const & edgeAddr, ScAddr const & otherAddr)\
	{\
		classifyLakeVAgent Instance("classifyLakeVAgent", sc_access_lvl_make_min);\
		return Instance.Run(addr, edgeAddr, otherAddr) == SC_RESULT_OK;\
	}\
	static void RegisterHandler()\
	{\
		SC_ASSERT(!ms_event.get(), ());\
		SC_ASSERT(!ms_context.get(), ());\
		ms_context.reset(new ScMemoryContext(sc_access_lvl_make_min, "handler_classifyLakeVAgent"));\
		ms_event.reset(new ScEvent(*ms_context, Keynodes::question_classify_lake_v, ScEvent::Type::AddOutputEdge, &classifyLakeVAgent::handler_emit));\
        if (ms_event.get())\
        {\
            SC_LOG_INFO("Register agent classifyLakeVAgent");\
        }\
        else\
        {\
            SC_LOG_ERROR("Can't register agent classifyLakeVAgent");\
        }\
	}\
	static void UnregisterHandler()\
	{\
		ms_event.reset();\
		ms_context.reset();\
	}

#define classifyLakeVAgent_hpp_classifyLakeVAgent_impl \
std::unique_ptr<ScEvent> classifyLakeVAgent::ms_event;\
std::unique_ptr<ScMemoryContext> classifyLakeVAgent::ms_context;

#undef ScFileID
#define ScFileID classifyLakeVAgent_hpp

