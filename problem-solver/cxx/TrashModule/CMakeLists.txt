set(SOURCES
		"TrashModule.cpp"
		"keynodes/keynodes.cpp"
		"agents/TrashByRegion.cpp"
		"agents/TrashByPest.cpp"
		"agents/TrashByCount.cpp"
		)

set(HEADERS
		"TrashModule.hpp"
		"keynodes/keynodes.hpp"
		"agents/TrashByRegion.hpp"
		"agents/TrashByPest.hpp"
		"agents/TrashByCount.hpp"
		)

include_directories(
		${CMAKE_CURRENT_LIST_DIR}
		${SC_MEMORY_SRC}
		${SC_KPM_SRC}
		${SC_TOOLS_SRC}
		${SC_COMMON_MODULE_SRC})

add_library(TrashModule SHARED ${SOURCES} ${HEADERS})
target_link_libraries(TrashModule sc-memory sc-agents-common)

sc_codegen_ex(TrashModule ${CMAKE_CURRENT_LIST_DIR} ${CMAKE_CURRENT_LIST_DIR}/generated)


