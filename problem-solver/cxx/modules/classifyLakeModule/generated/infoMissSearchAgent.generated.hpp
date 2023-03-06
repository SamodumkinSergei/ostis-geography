#include <memory>

#include "sc-memory/sc_memory.hpp"


#include "sc-memory/sc_event.hpp"




#define infoMissSearchAgent_hpp_20_init  bool _InitInternal() override \
{ \
    ScMemoryContext ctx(sc_access_lvl_make_min, "AinfoMissSearchAgent::_InitInternal"); \
    bool result = true; \
    return result; \
}


#define infoMissSearchAgent_hpp_20_initStatic static bool _InitStaticInternal()  \
{ \
    ScMemoryContext ctx(sc_access_lvl_make_min, "AinfoMissSearchAgent::_InitStaticInternal"); \
    bool result = true; \
    return result; \
}


#define infoMissSearchAgent_hpp_20_decl \
private:\
	typedef ScAgent Super;\
protected: \
	AinfoMissSearchAgent(char const * name, sc_uint8 accessLvl) : Super(name, accessLvl) {}\
	virtual sc_result Run(ScAddr const & listenAddr, ScAddr const & edgeAddr, ScAddr const & otherAddr) override; \
private:\
	static std::unique_ptr<ScEvent> ms_event;\
    static std::unique_ptr<ScMemoryContext> ms_context;\
public: \
	static bool handler_emit(ScAddr const & addr, ScAddr const & edgeAddr, ScAddr const & otherAddr)\
	{\
		AinfoMissSearchAgent Instance("AinfoMissSearchAgent", sc_access_lvl_make_min);\
		return Instance.Run(addr, edgeAddr, otherAddr) == SC_RESULT_OK;\
	}\
	static void RegisterHandler()\
	{\
		SC_ASSERT(!ms_event.get(), ());\
		SC_ASSERT(!ms_context.get(), ());\
		ms_context.reset(new ScMemoryContext(sc_access_lvl_make_min, "handler_AinfoMissSearchAgent"));\
		ms_event.reset(new ScEvent(*ms_context, Keynodes::question_add_game_info, ScEvent::Type::AddOutputEdge, &AinfoMissSearchAgent::handler_emit));\
        if (ms_event.get())\
        {\
            SC_LOG_INFO("Register agent AinfoMissSearchAgent");\
        }\
        else\
        {\
            SC_LOG_ERROR("Can't register agent AinfoMissSearchAgent");\
        }\
	}\
	static void UnregisterHandler()\
	{\
		ms_event.reset();\
		ms_context.reset();\
	}

#define infoMissSearchAgent_hpp_AinfoMissSearchAgent_impl \
std::unique_ptr<ScEvent> AinfoMissSearchAgent::ms_event;\
std::unique_ptr<ScMemoryContext> AinfoMissSearchAgent::ms_context;

#undef ScFileID
#define ScFileID infoMissSearchAgent_hpp

