#include <memory>

#include "sc-memory/sc_memory.hpp"


#include "sc-memory/sc_event.hpp"




#define addInfoSupportedLanguageAgent_hpp_20_init  bool _InitInternal() override \
{ \
    ScMemoryContext ctx(sc_access_lvl_make_min, "addInfoSupportedLanguageAgent::_InitInternal"); \
    bool result = true; \
    return result; \
}


#define addInfoSupportedLanguageAgent_hpp_20_initStatic static bool _InitStaticInternal()  \
{ \
    ScMemoryContext ctx(sc_access_lvl_make_min, "addInfoSupportedLanguageAgent::_InitStaticInternal"); \
    bool result = true; \
    return result; \
}


#define addInfoSupportedLanguageAgent_hpp_20_decl \
private:\
	typedef ScAgent Super;\
protected: \
	addInfoSupportedLanguageAgent(char const * name, sc_uint8 accessLvl) : Super(name, accessLvl) {}\
	virtual sc_result Run(ScAddr const & listenAddr, ScAddr const & edgeAddr, ScAddr const & otherAddr) override; \
private:\
	static std::unique_ptr<ScEvent> ms_event;\
    static std::unique_ptr<ScMemoryContext> ms_context;\
public: \
	static bool handler_emit(ScAddr const & addr, ScAddr const & edgeAddr, ScAddr const & otherAddr)\
	{\
		addInfoSupportedLanguageAgent Instance("addInfoSupportedLanguageAgent", sc_access_lvl_make_min);\
		return Instance.Run(addr, edgeAddr, otherAddr) == SC_RESULT_OK;\
	}\
	static void RegisterHandler()\
	{\
		SC_ASSERT(!ms_event.get(), ());\
		SC_ASSERT(!ms_context.get(), ());\
		ms_context.reset(new ScMemoryContext(sc_access_lvl_make_min, "handler_addInfoSupportedLanguageAgent"));\
		ms_event.reset(new ScEvent(*ms_context, Keynodes::question_add_info_supported_language, ScEvent::Type::AddOutputEdge, &addInfoSupportedLanguageAgent::handler_emit));\
        if (ms_event.get())\
        {\
            SC_LOG_INFO("Register agent addInfoSupportedLanguageAgent");\
        }\
        else\
        {\
            SC_LOG_ERROR("Can't register agent addInfoSupportedLanguageAgent");\
        }\
	}\
	static void UnregisterHandler()\
	{\
		ms_event.reset();\
		ms_context.reset();\
	}

#define addInfoSupportedLanguageAgent_hpp_addInfoSupportedLanguageAgent_impl \
std::unique_ptr<ScEvent> addInfoSupportedLanguageAgent::ms_event;\
std::unique_ptr<ScMemoryContext> addInfoSupportedLanguageAgent::ms_context;

#undef ScFileID
#define ScFileID addInfoSupportedLanguageAgent_hpp

