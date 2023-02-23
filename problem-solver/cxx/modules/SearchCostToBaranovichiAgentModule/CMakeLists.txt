set(SOURCES
        "SearchCostToBaranovichiAgentModule.cpp"
        "keynodes/keynodes.cpp"
        "agents/SearchCostToBaranovichiAgent.cpp"
        )

set(HEADERS
        "SearchCostToBaranovichiAgentModule.hpp"
        "keynodes/keynodes.hpp"
        "agents/SearchCostToBaranovichiAgent.hpp"
        )

include_directories(
		${CMAKE_CURRENT_LIST_DIR}
		${SC_MEMORY_SRC}
		${SC_KPM_SRC}
		${SC_TOOLS_SRC}
		${SC_COMMON_MODULE_SRC})

add_library(SearchCostToBaranovichiAgentModule SHARED ${SOURCES} ${HEADERS})
target_link_libraries(SearchCostToBaranovichiAgentModule sc-memory sc-agents-common)

sc_codegen_ex(SearchCostToBaranovichiAgentModule ${CMAKE_CURRENT_LIST_DIR} ${CMAKE_CURRENT_LIST_DIR}/generated)

if(${SC_CLANG_FORMAT_CODE})
	target_clangformat_setup(SearchCostToBaranovichiAgentModule)
endif()
