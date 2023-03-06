#include <memory>

#include "sc-memory/sc_memory.hpp"


#include "sc-memory/sc_event.hpp"




#define addInfoReviewAgent_hpp_20_init  bool _InitInternal() override \
{ \
    ScMemoryContext ctx(sc_access_lvl_make_min, "addInfoReviewAgent::_InitInternal"); \
    bool result = true; \
    return result; \
}


#define addInfoReviewAgent_hpp_20_initStatic static bool _InitStaticInternal()  \
{ \
    ScMemoryContext ctx(sc_access_lvl_make_min, "addInfoReviewAgent::_InitStaticInternal"); \
    bool result = true; \
    return result; \
}


#define addInfoReviewAgent_hpp_20_decl \
private:\
	typedef ScAgent Super;\
protected: \
	addInfoReviewAgent(char const * name, sc_uint8 accessLvl) : Super(name, accessLvl) {}\
	virtual sc_result Run(ScAddr const & listenAddr, ScAddr const & edgeAddr, ScAddr const & otherAddr) override; \
private:\
	static std::unique_ptr<ScEvent> ms_event;\
    static std::unique_ptr<ScMemoryContext> ms_context;\
public: \
	static bool handler_emit(ScAddr const & addr, ScAddr const & edgeAddr, ScAddr const & otherAddr)\
	{\
		addInfoReviewAgent Instance("addInfoReviewAgent", sc_access_lvl_make_min);\
		return Instance.Run(addr, edgeAddr, otherAddr) == SC_RESULT_OK;\
	}\
	static void RegisterHandler()\
	{\
		SC_ASSERT(!ms_event.get(), ());\
		SC_ASSERT(!ms_context.get(), ());\
		ms_context.reset(new ScMemoryContext(sc_access_lvl_make_min, "handler_addInfoReviewAgent"));\
		ms_event.reset(new ScEvent(*ms_context, Keynodes::question_add_info_review, ScEvent::Type::AddOutputEdge, &addInfoReviewAgent::handler_emit));\
        if (ms_event.get())\
        {\
            SC_LOG_INFO("Register agent addInfoReviewAgent");\
        }\
        else\
        {\
            SC_LOG_ERROR("Can't register agent addInfoReviewAgent");\
        }\
	}\
	static void UnregisterHandler()\
	{\
		ms_event.reset();\
		ms_context.reset();\
	}

#define addInfoReviewAgent_hpp_addInfoReviewAgent_impl \
std::unique_ptr<ScEvent> addInfoReviewAgent::ms_event;\
std::unique_ptr<ScMemoryContext> addInfoReviewAgent::ms_context;

#undef ScFileID
#define ScFileID addInfoReviewAgent_hpp

