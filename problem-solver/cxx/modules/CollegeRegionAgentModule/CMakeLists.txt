set(SOURCES
        "CollegeRegionAgentModule.cpp"
        "keynodes/keynodes.cpp"
        "agents/CollegeRegionAgent.cpp"
        )

set(HEADERS
        "CollegeRegionAgentModule.hpp"
        "keynodes/keynodes.hpp"
        "agents/CollegeRegionAgent.hpp"
        )

include_directories(
		${CMAKE_CURRENT_LIST_DIR}
		${SC_MEMORY_SRC}
		${SC_KPM_SRC}
		${SC_TOOLS_SRC}
		${SC_COMMON_MODULE_SRC})

add_library(CollegeRegionAgentModule SHARED ${SOURCES} ${HEADERS})
target_link_libraries(CollegeRegionAgentModule sc-memory sc-agents-common)

sc_codegen_ex(CollegeRegionAgentModule ${CMAKE_CURRENT_LIST_DIR} ${CMAKE_CURRENT_LIST_DIR}/generated)

if(${SC_CLANG_FORMAT_CODE})
	target_clangformat_setup(CollegeRegionAgentModule)
endif()