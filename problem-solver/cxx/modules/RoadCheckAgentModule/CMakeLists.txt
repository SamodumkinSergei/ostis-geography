set(SOURCES
        "RoadCheckAgentModule.cpp"
        "keynodes/keynodes.cpp"
        "agents/RoadCheckAgent.cpp"
        )

set(HEADERS
        "RoadCheckAgentModule.hpp"
        "keynodes/keynodes.hpp"
        "agents/RoadCheckAgent.hpp"
        )

include_directories(
		${CMAKE_CURRENT_LIST_DIR}
		${SC_MEMORY_SRC}
		${SC_KPM_SRC}
		${SC_TOOLS_SRC}
		${SC_COMMON_MODULE_SRC})

add_library(RoadCheckAgentModule SHARED ${SOURCES} ${HEADERS})
target_link_libraries(RoadCheckAgentModule sc-memory sc-agents-common)

sc_codegen_ex(RoadCheckAgentModule ${CMAKE_CURRENT_LIST_DIR} ${CMAKE_CURRENT_LIST_DIR}/generated)

if(${SC_CLANG_FORMAT_CODE})
	target_clangformat_setup(RoadCheckAgentModule)
endif()
