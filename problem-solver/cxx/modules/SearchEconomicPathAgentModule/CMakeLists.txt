set(SOURCES
        "SearchEconomicPathAgentModule.cpp"
        "keynodes/keynodes.cpp"
        "agents/SearchEconomicPathAgent.cpp"
        )

set(HEADERS
        "SearchEconomicPathAgentModule.hpp"
        "keynodes/keynodes.hpp"
        "agents/SearchEconomicPathAgent.hpp"
        )

include_directories(
		${CMAKE_CURRENT_LIST_DIR}
		${SC_MEMORY_SRC}
		${SC_KPM_SRC}
		${SC_TOOLS_SRC}
		${SC_COMMON_MODULE_SRC})

add_library(SearchEconomicPathAgentModule SHARED ${SOURCES} ${HEADERS})
target_link_libraries(SearchEconomicPathAgentModule sc-memory sc-agents-common)

sc_codegen_ex(SearchEconomicPathAgentModule ${CMAKE_CURRENT_LIST_DIR} ${CMAKE_CURRENT_LIST_DIR}/generated)

if(${SC_CLANG_FORMAT_CODE})
	target_clangformat_setup(SearchEconomicPathAgentModule)
endif()
