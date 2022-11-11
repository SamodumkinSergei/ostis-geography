set(SOURCES
        "LibrariesTownSearchModule.cpp"
        "keynodes/keynodes.cpp"
        "agents/LibrariesTownSearch.cpp"
        )

set(HEADERS
        "LibrariesTownSearchModule.hpp"
        "keynodes/keynodes.hpp"
        "agents/LibrariesTownSearch.hpp"
        )

include_directories(
		${CMAKE_CURRENT_LIST_DIR}
		${SC_MEMORY_SRC}
		${SC_KPM_SRC}
		${SC_TOOLS_SRC}
		${SC_COMMON_MODULE_SRC})

add_library(LibrariesTownSearchModule SHARED ${SOURCES} ${HEADERS})
target_link_libraries(LibrariesTownSearchModule sc-memory sc-agents-common)

sc_codegen_ex(LibrariesTownSearchModule ${CMAKE_CURRENT_LIST_DIR} ${CMAKE_CURRENT_LIST_DIR}/generated)
