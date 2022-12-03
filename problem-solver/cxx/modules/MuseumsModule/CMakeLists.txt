set(SOURCES
        "MuseumsModule.cpp"
        "keynodes/keynodes.cpp"
        "agents/SearchMuseumsByRegion.cpp"
        )

set(HEADERS
        "MuseumsModule.hpp"
        "keynodes/keynodes.hpp"
        "agents/SearchMuseumsByRegion.hpp"
        )

include_directories(
		${CMAKE_CURRENT_LIST_DIR}
		${SC_MEMORY_SRC}
		${SC_KPM_SRC}
		${SC_TOOLS_SRC}
		${SC_COMMON_MODULE_SRC})

add_library(MuseumsModule SHARED ${SOURCES} ${HEADERS})
target_link_libraries(MuseumsModule sc-memory sc-agents-common)

sc_codegen_ex(MuseumsModule ${CMAKE_CURRENT_LIST_DIR} ${CMAKE_CURRENT_LIST_DIR}/generated)

if(${SC_CLANG_FORMAT_CODE})
	target_clangformat_setup(MuseumsModule)
endif()
