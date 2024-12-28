set(SOURCES
        "MuseumsRegionSearchModule.cpp"
        # "keynodes/MuseumKeynodes.cpp"
        "agents/MuseumsRegionSearch.cpp"
        )

set(HEADERS
        "MuseumsRegionSearchModule.hpp"
        "keynodes/MuseumKeynodes.hpp"
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

if(${SC_CLANG_FORMAT_CODE})
	target_clangformat_setup(MuseumsRegionSearchModule)
endif()
