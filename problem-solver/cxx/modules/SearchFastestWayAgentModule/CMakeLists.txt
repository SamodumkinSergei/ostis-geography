set(SOURCES
        "SearchFastestWayAgentModule.cpp"
        "keynodes/keynodes.cpp"
        "agents/SearchFastestWayAgent.cpp"
        )

set(HEADERS
        "SearchFastestWayAgentModule.hpp"
        "keynodes/keynodes.hpp"
        "agents/SearchFastestWayAgent.hpp"
        )

include_directories(
		${CMAKE_CURRENT_LIST_DIR}
		${SC_MEMORY_SRC}
		${SC_KPM_SRC}
		${SC_TOOLS_SRC}
		${SC_COMMON_MODULE_SRC})

add_library(SearchFastestWayAgentModule SHARED ${SOURCES} ${HEADERS})
target_link_libraries(SearchFastestWayAgentModule sc-memory sc-agents-common)

sc_codegen_ex(SearchFastestWayAgentModule ${CMAKE_CURRENT_LIST_DIR} ${CMAKE_CURRENT_LIST_DIR}/generated)

if(${SC_CLANG_FORMAT_CODE})
	target_clangformat_setup(SearchFastestWayAgentModule)
endif()
