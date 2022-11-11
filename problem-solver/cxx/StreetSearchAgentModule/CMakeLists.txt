set(SOURCES
        "StreetSearchAgentModule.cpp"
        "keynodes/keynodes.cpp"
        "agents/StreetSearchAgent.cpp"
        )

set(HEADERS
        "StreetSearchAgentModule.hpp"
        "keynodes/keynodes.hpp"
        "agents/StreetSearchAgent.hpp"
        )

include_directories(
		${CMAKE_CURRENT_LIST_DIR}
		${SC_MEMORY_SRC}
		${SC_KPM_SRC}
		${SC_TOOLS_SRC}
		${SC_COMMON_MODULE_SRC})

add_library(StreetSearchAgentModule SHARED ${SOURCES} ${HEADERS})
target_link_libraries(StreetSearchAgentModule sc-memory sc-agents-common)

sc_codegen_ex(StreetSearchAgentModule ${CMAKE_CURRENT_LIST_DIR} ${CMAKE_CURRENT_LIST_DIR}/generated) 
