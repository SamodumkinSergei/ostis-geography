set(SOURCES
        "SearchShortestPathAgentModule.cpp"
        "keynodes/keynodes.cpp"
        "agents/SearchShortestPathAgent.cpp"
        )

set(HEADERS
        "SearchShortestPathAgentModule.hpp"
        "keynodes/keynodes.hpp"
        "agents/SearchShortestPathAgent.hpp"
        )

include_directories(
		${CMAKE_CURRENT_LIST_DIR}
		${SC_MEMORY_SRC}
		${SC_KPM_SRC}
		${SC_TOOLS_SRC}
		${SC_COMMON_MODULE_SRC})

add_library(SearchShortestPathAgentModule SHARED ${SOURCES} ${HEADERS})
target_link_libraries(SearchShortestPathAgentModule sc-memory sc-agents-common)

sc_codegen_ex(SearchShortestPathAgentModule ${CMAKE_CURRENT_LIST_DIR} ${CMAKE_CURRENT_LIST_DIR}/generated)

if(${SC_CLANG_FORMAT_CODE})
	target_clangformat_setup(SearchShortestPathAgentModule)
endif()
