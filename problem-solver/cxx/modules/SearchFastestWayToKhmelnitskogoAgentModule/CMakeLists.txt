set(SOURCES
        "SearchFastestWayToKhmelnitskogoAgentModule.cpp"
        "keynodes/keynodes.cpp"
        "agents/SearchFastestWayToKhmelnitskogoAgent.cpp"
        )

set(HEADERS
        "SearchFastestWayToKhmelnitskogoAgentModule.hpp"
        "keynodes/keynodes.hpp"
        "agents/SearchFastestWayToKhmelnitskogoAgent.hpp"
        )

include_directories(
		${CMAKE_CURRENT_LIST_DIR}
		${SC_MEMORY_SRC}
		${SC_KPM_SRC}
		${SC_TOOLS_SRC}
		${SC_COMMON_MODULE_SRC})

add_library(SearchFastestWayToKhmelnitskogoAgentModule SHARED ${SOURCES} ${HEADERS})
target_link_libraries(SearchFastestWayToKhmelnitskogoAgentModule sc-memory sc-agents-common)

sc_codegen_ex(SearchFastestWayToKhmelnitskogoAgentModule ${CMAKE_CURRENT_LIST_DIR} ${CMAKE_CURRENT_LIST_DIR}/generated)

if(${SC_CLANG_FORMAT_CODE})
	target_clangformat_setup(SearchFastestWayToKhmelnitskogoAgentModule)
endif()