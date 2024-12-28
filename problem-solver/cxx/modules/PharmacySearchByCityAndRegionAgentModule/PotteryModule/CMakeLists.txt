set(SOURCES
		"PotteryModule.cpp"
		# "keynodes/PotteryKeynodes.cpp"
		"agents/PotteryDate.cpp"
		)

set(HEADERS
		"PotteryModule.hpp"
		"keynodes/PotteryKeynodes.hpp"
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

if(${SC_CLANG_FORMAT_CODE})
	target_clangformat_setup(PotteryModule)
endif()
