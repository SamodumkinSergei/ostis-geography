set(SOURCES
        "SearchFastestHikingWayAgentModule.cpp"
        "keynodes/keynodes.cpp"
        "agents/SearchFastestHikingWayAgent.cpp"
        )

set(HEADERS
        "SearchFastestHikingWayAgentModule.hpp"
        "keynodes/keynodes.hpp"
        "agents/SearchFastestHikingWayAgent.hpp"
        )

include_directories(
		${CMAKE_CURRENT_LIST_DIR}
		${SC_MEMORY_SRC}
		${SC_KPM_SRC}
		${SC_TOOLS_SRC}
		${SC_COMMON_MODULE_SRC})

add_library(SearchFastestHikingWayAgentModule SHARED ${SOURCES} ${HEADERS})
target_link_libraries(SearchFastestHikingWayAgentModule sc-memory sc-agents-common)

sc_codegen_ex(SearchFastestHikingWayAgentModule ${CMAKE_CURRENT_LIST_DIR} ${CMAKE_CURRENT_LIST_DIR}/generated)

if(${SC_CLANG_FORMAT_CODE})
	target_clangformat_setup(SearchFastestHikingWayAgentModule)
endif()
