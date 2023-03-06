#include <memory>

#include "sc-memory/sc_memory.hpp"


#include "sc-memory/sc_event.hpp"




#define addGameRatingAgent_hpp_20_init  bool _InitInternal() override \
{ \
    ScMemoryContext ctx(sc_access_lvl_make_min, "addGameRatingAgent::_InitInternal"); \
    bool result = true; \
    return result; \
}


#define addGameRatingAgent_hpp_20_initStatic static bool _InitStaticInternal()  \
{ \
    ScMemoryContext ctx(sc_access_lvl_make_min, "addGameRatingAgent::_InitStaticInternal"); \
    bool result = true; \
    return result; \
}


#define addGameRatingAgent_hpp_20_decl \
private:\
	typedef ScAgent Super;\
protected: \
	addGameRatingAgent(char const * name, sc_uint8 accessLvl) : Super(name, accessLvl) {}\
	virtual sc_result Run(ScAddr const & listenAddr, ScAddr const & edgeAddr, ScAddr const & otherAddr) override; \
private:\
	static std::unique_ptr<ScEvent> ms_event;\
    static std::unique_ptr<ScMemoryContext> ms_context;\
public: \
	static bool handler_emit(ScAddr const & addr, ScAddr const & edgeAddr, ScAddr const & otherAddr)\
	{\
		addGameRatingAgent Instance("addGameRatingAgent", sc_access_lvl_make_min);\
		return Instance.Run(addr, edgeAddr, otherAddr) == SC_RESULT_OK;\
	}\
	static void RegisterHandler()\
	{\
		SC_ASSERT(!ms_event.get(), ());\
		SC_ASSERT(!ms_context.get(), ());\
		ms_context.reset(new ScMemoryContext(sc_access_lvl_make_min, "handler_addGameRatingAgent"));\
		ms_event.reset(new ScEvent(*ms_context, Keynodes::question_add_game_rating, ScEvent::Type::AddOutputEdge, &addGameRatingAgent::handler_emit));\
        if (ms_event.get())\
        {\
            SC_LOG_INFO("Register agent addGameRatingAgent");\
        }\
        else\
        {\
            SC_LOG_ERROR("Can't register agent addGameRatingAgent");\
        }\
	}\
	static void UnregisterHandler()\
	{\
		ms_event.reset();\
		ms_context.reset();\
	}

#define addGameRatingAgent_hpp_addGameRatingAgent_impl \
std::unique_ptr<ScEvent> addGameRatingAgent::ms_event;\
std::unique_ptr<ScMemoryContext> addGameRatingAgent::ms_context;

#undef ScFileID
#define ScFileID addGameRatingAgent_hpp

