set(SOURCES
        "SearchFastestWayToBerestovitsaBorderCrossingAgentModule.cpp"
        "keynodes/keynodes.cpp"
        "agents/SearchFastestWayToBerestovitsaBorderCrossingAgent.cpp"
        )

set(HEADERS
        "SearchFastestWayToBerestovitsaBorderCrossingAgentModule.hpp"
        "keynodes/keynodes.hpp"
        "agents/SearchFastestWayToBerestovitsaBorderCrossingAgent.hpp"
        )

include_directories(
		${CMAKE_CURRENT_LIST_DIR}
		${SC_MEMORY_SRC}
		${SC_KPM_SRC}
		${SC_TOOLS_SRC}
		${SC_COMMON_MODULE_SRC})

add_library(SearchFastestWayToBerestovitsaBorderCrossingAgentModule SHARED ${SOURCES} ${HEADERS})
target_link_libraries(SearchFastestWayToBerestovitsaBorderCrossingAgentModule sc-memory sc-agents-common)

sc_codegen_ex(SearchFastestWayToBerestovitsaBorderCrossingAgentModule ${CMAKE_CURRENT_LIST_DIR} ${CMAKE_CURRENT_LIST_DIR}/generated)

if(${SC_CLANG_FORMAT_CODE})
	target_clangformat_setup(SearchFastestWayToBerestovitsaBorderCrossingAgentModule)
endif()