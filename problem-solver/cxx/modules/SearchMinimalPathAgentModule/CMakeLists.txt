set(SOURCES
        "SearchMinimalPathAgentModule.cpp"
        "keynodes/keynodes.cpp"
        "agents/SearchMinimalPathAgent.cpp"
        )

set(HEADERS
        "SearchMinimalPathAgentModule.hpp"
        "keynodes/keynodes.hpp"
        "agents/SearchMinimalPathAgent.hpp"
        )

include_directories(
		${CMAKE_CURRENT_LIST_DIR}
		${SC_MEMORY_SRC}
		${SC_KPM_SRC}
		${SC_TOOLS_SRC}
		${SC_COMMON_MODULE_SRC})

add_library(SearchMinimalPathAgentModule SHARED ${SOURCES} ${HEADERS})
target_link_libraries(SearchMinimalPathAgentModule sc-memory sc-agents-common)

sc_codegen_ex(SearchMinimalPathAgentModule ${CMAKE_CURRENT_LIST_DIR} ${CMAKE_CURRENT_LIST_DIR}/generated)

if(${SC_CLANG_FORMAT_CODE})
	target_clangformat_setup(SearchMinimalPathAgentModule)
endif()
