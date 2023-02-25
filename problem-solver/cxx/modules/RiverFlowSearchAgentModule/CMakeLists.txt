set(SOURCES
        "RiverFlowSearchAgentModule.cpp"
        "keynodes/keynodes.cpp"
        "agents/RiverFlowSearchAgent.cpp"
        )

set(HEADERS
        "RiverFlowSearchAgentModule.hpp"
        "keynodes/keynodes.hpp"
        "agents/RiverFlowSearchAgent.hpp"
        )

include_directories(
		${CMAKE_CURRENT_LIST_DIR}
		${SC_MEMORY_SRC}
		${SC_KPM_SRC}
		${SC_TOOLS_SRC}
		${SC_COMMON_MODULE_SRC})

add_library(RiverFlowSearchAgentModule SHARED ${SOURCES} ${HEADERS})
target_link_libraries(RiverFlowSearchAgentModule sc-memory sc-agents-common)

sc_codegen_ex(RiverFlowSearchAgentModule ${CMAKE_CURRENT_LIST_DIR} ${CMAKE_CURRENT_LIST_DIR}/generated)

if(${SC_CLANG_FORMAT_CODE})
	target_clangformat_setup(RiverFlowSearchAgentModule)
endif()
