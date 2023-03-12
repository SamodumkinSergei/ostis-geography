set(SOURCES
        "CityBelongsSearchAgentModule.cpp"
        "keynodes/keynodes.cpp"
        "agents/CityBelongsSearchAgent.cpp"
        )

set(HEADERS
        "CityBelongsSearchAgentModule.hpp"
        "keynodes/keynodes.hpp"
        "agents/CityBelongsSearchAgent.hpp"
        )

include_directories(
		${CMAKE_CURRENT_LIST_DIR}
		${SC_MEMORY_SRC}
		${SC_KPM_SRC}
		${SC_TOOLS_SRC}
		${SC_COMMON_MODULE_SRC})

add_library(CityBelongsSearchAgentModule SHARED ${SOURCES} ${HEADERS})
target_link_libraries(CityBelongsSearchAgentModule sc-memory sc-agents-common)

sc_codegen_ex(CityBelongsSearchAgentModule ${CMAKE_CURRENT_LIST_DIR} ${CMAKE_CURRENT_LIST_DIR}/generated)

if(${SC_CLANG_FORMAT_CODE})
	target_clangformat_setup(CityBelongsSearchAgentModule)
endif()