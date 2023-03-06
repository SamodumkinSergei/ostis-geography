#include <memory>

#include "sc-memory/sc_memory.hpp"


#include "sc-memory/sc_event.hpp"




#define addInfoAgeRatingAgent_hpp_20_init  bool _InitInternal() override \
{ \
    ScMemoryContext ctx(sc_access_lvl_make_min, "addInfoAgeRatingAgent::_InitInternal"); \
    bool result = true; \
    return result; \
}


#define addInfoAgeRatingAgent_hpp_20_initStatic static bool _InitStaticInternal()  \
{ \
    ScMemoryContext ctx(sc_access_lvl_make_min, "addInfoAgeRatingAgent::_InitStaticInternal"); \
    bool result = true; \
    return result; \
}


#define addInfoAgeRatingAgent_hpp_20_decl \
private:\
	typedef ScAgent Super;\
protected: \
	addInfoAgeRatingAgent(char const * name, sc_uint8 accessLvl) : Super(name, accessLvl) {}\
	virtual sc_result Run(ScAddr const & listenAddr, ScAddr const & edgeAddr, ScAddr const & otherAddr) override; \
private:\
	static std::unique_ptr<ScEvent> ms_event;\
    static std::unique_ptr<ScMemoryContext> ms_context;\
public: \
	static bool handler_emit(ScAddr const & addr, ScAddr const & edgeAddr, ScAddr const & otherAddr)\
	{\
		addInfoAgeRatingAgent Instance("addInfoAgeRatingAgent", sc_access_lvl_make_min);\
		return Instance.Run(addr, edgeAddr, otherAddr) == SC_RESULT_OK;\
	}\
	static void RegisterHandler()\
	{\
		SC_ASSERT(!ms_event.get(), ());\
		SC_ASSERT(!ms_context.get(), ());\
		ms_context.reset(new ScMemoryContext(sc_access_lvl_make_min, "handler_addInfoAgeRatingAgent"));\
		ms_event.reset(new ScEvent(*ms_context, Keynodes::question_add_info_age_rating, ScEvent::Type::AddOutputEdge, &addInfoAgeRatingAgent::handler_emit));\
        if (ms_event.get())\
        {\
            SC_LOG_INFO("Register agent addInfoAgeRatingAgent");\
        }\
        else\
        {\
            SC_LOG_ERROR("Can't register agent addInfoAgeRatingAgent");\
        }\
	}\
	static void UnregisterHandler()\
	{\
		ms_event.reset();\
		ms_context.reset();\
	}

#define addInfoAgeRatingAgent_hpp_addInfoAgeRatingAgent_impl \
std::unique_ptr<ScEvent> addInfoAgeRatingAgent::ms_event;\
std::unique_ptr<ScMemoryContext> addInfoAgeRatingAgent::ms_context;

#undef ScFileID
#define ScFileID addInfoAgeRatingAgent_hpp

