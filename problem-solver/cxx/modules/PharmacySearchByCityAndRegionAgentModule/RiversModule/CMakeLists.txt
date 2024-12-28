set(SOURCES
		"RiversModule.cpp"
		# "keynodes/RiverKeynodes.cpp"
		"agents/TheBiggestBasinInRegion.cpp"
		"agents/LongerRiver.cpp"
		"agents/LongestInRegion.cpp"
		"agents/BiggerBasin.cpp"
		"agents/ShorterRiver.cpp"
		)

set(HEADERS
		"RiversModule.hpp"
		"keynodes/RiverKeynodes.hpp"
		"agents/TheBiggestBasinInRegion.hpp"
		"agents/LongerRiver.hpp"
		"agents/LongestInRegion.hpp"
		"agents/BiggerBasin.hpp"
		"agents/ShorterRiver.hpp"
		)

include_directories(
		${CMAKE_CURRENT_LIST_DIR}
		${SC_MEMORY_SRC}
		${SC_KPM_SRC}
		${SC_TOOLS_SRC}
		${SC_COMMON_MODULE_SRC})

add_library(RiversModule SHARED ${SOURCES} ${HEADERS})
target_link_libraries(RiversModule sc-memory sc-agents-common)

if(${SC_CLANG_FORMAT_CODE})
	target_clangformat_setup(RiversModule)
endif()
