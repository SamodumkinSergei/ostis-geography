set(SOURCES
        "FindingTimeToGetToMinskAgentModule.cpp"
        "keynodes/keynodes.cpp"
        "agents/FindingTimeToGetToMinskAgent.cpp"
        )

set(HEADERS
        "FindingTimeToGetToMinskAgentModule.hpp"
        "keynodes/keynodes.hpp"
        "agents/FindingTimeToGetToMinskAgent.hpp"
        )

include_directories(
		${CMAKE_CURRENT_LIST_DIR}
		${SC_MEMORY_SRC}
		${SC_KPM_SRC}
		${SC_TOOLS_SRC}
		${SC_COMMON_MODULE_SRC})

add_library(FindingTimeToGetToMinskAgentModule SHARED ${SOURCES} ${HEADERS})
target_link_libraries(FindingTimeToGetToMinskAgentModule sc-memory sc-agents-common)

sc_codegen_ex(FindingTimeToGetToMinskAgentModule ${CMAKE_CURRENT_LIST_DIR} ${CMAKE_CURRENT_LIST_DIR}/generated)

if(${SC_CLANG_FORMAT_CODE})
	target_clangformat_setup(FindingTimeToGetToMinskAgentModule)
endif()
