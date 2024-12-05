set(SOURCES
        "SchoolSearchAgentModule.cpp"
        # "keynodes/SchoolKeynodes.cpp"
        "agents/SchoolSearchAgent.cpp"
        )

set(HEADERS
        "SchoolSearchAgentModule.hpp"
        "keynodes/SchoolKeynodes.hpp"
        "agents/SchoolSearchAgent.hpp"
        )

include_directories(
		${CMAKE_CURRENT_LIST_DIR}
		${SC_MEMORY_SRC}
		${SC_KPM_SRC}
		${SC_TOOLS_SRC}
		${SC_COMMON_MODULE_SRC})

add_library(SchoolSearchAgentModule SHARED ${SOURCES} ${HEADERS})
target_link_libraries(SchoolSearchAgentModule sc-memory sc-agents-common)

if(${SC_CLANG_FORMAT_CODE})
	target_clangformat_setup(SchoolSearchAgentModule)
endif()

