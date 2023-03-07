set(SOURCES
        "SearchPathAgentModule.cpp"
        "keynodes/keynodes.cpp"
        "agents/SearchPathAgent.cpp"
        )

set(HEADERS
        "SearchPathAgentModule.hpp"
        "keynodes/keynodes.hpp"
        "agents/SearchPathAgentModule.hpp"
        )

include_directories(
		${CMAKE_CURRENT_LIST_DIR}
		${SC_MEMORY_SRC}
		${SC_KPM_SRC}
		${SC_TOOLS_SRC}
		${SC_COMMON_MODULE_SRC})

add_library(SearchPathAgentModule SHARED ${SOURCES} ${HEADERS})
target_link_libraries(SearchPathAgentModule sc-memory sc-agents-common)

sc_codegen_ex(SearchPathAgentModule ${CMAKE_CURRENT_LIST_DIR} ${CMAKE_CURRENT_LIST_DIR}/generated)

if(${SC_CLANG_FORMAT_CODE})
	target_clangformat_setup(SearchPathAgentModule)
endif()
