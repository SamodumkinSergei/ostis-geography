set(SOURCES
        "MuseumsRegionSearchModule.cpp"
        "keynodes/keynodes.cpp"
        "agents/MuseumsRegionSearch.cpp"
        )

set(HEADERS
        "MuseumsRegionSearchModule.hpp"
        "keynodes/keynodes.hpp"
        "agents/MuseumsRegionSearch.hpp"
        )

include_directories(
		${CMAKE_CURRENT_LIST_DIR}
		${SC_MEMORY_SRC}
		${SC_KPM_SRC}
		${SC_TOOLS_SRC}
		${SC_COMMON_MODULE_SRC})

add_library(MuseumsRegionSearchModule SHARED ${SOURCES} ${HEADERS})
target_link_libraries(MuseumsRegionSearchModule sc-memory sc-agents-common)

sc_codegen_ex(MuseumsRegionSearchModule ${CMAKE_CURRENT_LIST_DIR} ${CMAKE_CURRENT_LIST_DIR}/generated)