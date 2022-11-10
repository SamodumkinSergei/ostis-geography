set(SOURCES
		"RiversModule.cpp"
		"keynodes/keynodes.cpp"
		"agents/TheBiggestBasin.cpp"
		)

set(HEADERS
		"RiversModule.hpp"
		"keynodes/keynodes.hpp"
		"agents/TheBiggestBasin.hpp"
		)

include_directories(
		${CMAKE_CURRENT_LIST_DIR}
		${SC_MEMORY_SRC}
		${SC_KPM_SRC}
		${SC_TOOLS_SRC}
		${SC_COMMON_MODULE_SRC})

add_library(RiversModule SHARED ${SOURCES} ${HEADERS})
target_link_libraries(RiversModule sc-memory sc-agents-common)

sc_codegen_ex(RiversModule ${CMAKE_CURRENT_LIST_DIR} ${CMAKE_CURRENT_LIST_DIR}/generated)

