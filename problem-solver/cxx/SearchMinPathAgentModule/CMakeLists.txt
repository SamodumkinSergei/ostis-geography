set(SOURCES
        "SearchMinPathAgentModule.cpp"
        "keynodes/keynodes.cpp"
        "agents/SearchMinPathAgent.cpp"
        )

set(HEADERS
        "SearchMinPathAgentModule.hpp"
        "keynodes/keynodes.hpp"
        "agents/SearchMinPathAgent.hpp"
        )

include_directories(
		${CMAKE_CURRENT_LIST_DIR}
		${SC_MEMORY_SRC}
		${SC_KPM_SRC}
		${SC_TOOLS_SRC}
		${SC_COMMON_MODULE_SRC})

add_library(SearchMinPathAgentModule SHARED ${SOURCES} ${HEADERS})
target_link_libraries(SearchMinPathAgentModule sc-memory sc-agents-common)

sc_codegen_ex(SearchMinPathAgentModule ${CMAKE_CURRENT_LIST_DIR} ${CMAKE_CURRENT_LIST_DIR}/generated)

if(${SC_CLANG_FORMAT_CODE})
	target_clangformat_setup(SearchMinPathAgentModule)
endif()
