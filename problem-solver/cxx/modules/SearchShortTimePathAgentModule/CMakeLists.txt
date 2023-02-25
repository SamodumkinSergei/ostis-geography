set(SOURCES
        "SearchShortTimePathAgentModule.cpp"
        "keynodes/keynodes.cpp"
        "agents/SearchShortTimePathAgent.cpp"
        )

set(HEADERS
        "SearchShortTimePathAgentModule.hpp"
        "keynodes/keynodes.hpp"
        "agents/SearchShortTimePathAgent.hpp"
        )

include_directories(
		${CMAKE_CURRENT_LIST_DIR}
		${SC_MEMORY_SRC}
		${SC_KPM_SRC}
		${SC_TOOLS_SRC}
		${SC_COMMON_MODULE_SRC})

add_library(SearchShortTimePathAgentModule SHARED ${SOURCES} ${HEADERS})
target_link_libraries(SearchShortTimePathAgentModule sc-memory sc-agents-common)

sc_codegen_ex(SearchShortTimePathAgentModule ${CMAKE_CURRENT_LIST_DIR} ${CMAKE_CURRENT_LIST_DIR}/generated)

if(${SC_CLANG_FORMAT_CODE})
	target_clangformat_setup(SearchShortTimePathAgentModule)
endif()
