set(SOURCES
		"PotteryModule.cpp"
		"keynodes/keynodes.cpp"
		"agents/PotteryDate.cpp"
		)

set(HEADERS
		"PotteryModule.hpp"
		"keynodes/keynodes.hpp"
		"agents/PotteryDate.hpp"
		)

include_directories(
		${CMAKE_CURRENT_LIST_DIR}
		${SC_MEMORY_SRC}
		${SC_KPM_SRC}
		${SC_TOOLS_SRC}
		${SC_COMMON_MODULE_SRC})

add_library(PotteryModule SHARED ${SOURCES} ${HEADERS})
target_link_libraries(PotteryModule sc-memory sc-agents-common)

sc_codegen_ex(PotteryModule ${CMAKE_CURRENT_LIST_DIR} ${CMAKE_CURRENT_LIST_DIR}/generated)

if(${SC_CLANG_FORMAT_CODE})
	target_clangformat_setup(PotteryModule)
endif()
