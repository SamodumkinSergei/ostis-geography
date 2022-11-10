set(SOURCES
        "StatusAndDistrictSearchModule.cpp"
        "keynodes/keynodes.cpp"
        "agents/StatusAndDistrictSearch.cpp"
        )

set(HEADERS
        "StatusAndDistrictSearchModule.hpp"
        "keynodes/keynodes.hpp"
        "agents/StatusAndDistrictSearch.hpp"
        )

include_directories(
		${CMAKE_CURRENT_LIST_DIR}
		${SC_MEMORY_SRC}
		${SC_KPM_SRC}
		${SC_TOOLS_SRC}
		${SC_COMMON_MODULE_SRC})

add_library(statusAndDistrictSearchModule SHARED ${SOURCES} ${HEADERS})
target_link_libraries(statusAndDistrictSearchModule sc-memory sc-agents-common)

sc_codegen_ex(statusAndDistrictSearchModule ${CMAKE_CURRENT_LIST_DIR} ${CMAKE_CURRENT_LIST_DIR}/generated)