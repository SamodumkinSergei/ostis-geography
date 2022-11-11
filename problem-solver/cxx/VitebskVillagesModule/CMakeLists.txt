set(SOURCES
		"VitebskVillagesModule.cpp"
		"keynodes/keynodes.cpp"
		"agents/LargerVillageByPopulationInTheDistrict.cpp"
		"agents/LargerVillageByPopulation.cpp"
		"agents/GreatestDistanceToTheRegionalCenter.cpp"
		)

set(HEADERS
		"VitebskVillagesModule.hpp"
		"keynodes/keynodes.hpp"
		"agents/LargerVillageByPopulationInTheDistrict.hpp"
		"agents/LargerVillageByPopulation.hpp"
		"agents/GreatestDistanceToTheRegionalCenter.hpp"
		)

include_directories(
		${CMAKE_CURRENT_LIST_DIR}
		${SC_MEMORY_SRC}
		${SC_KPM_SRC}
		${SC_TOOLS_SRC}
		${SC_COMMON_MODULE_SRC})

add_library(VitebskVillagesModule SHARED ${SOURCES} ${HEADERS})
target_link_libraries(VitebskVillagesModule sc-memory sc-agents-common)

sc_codegen_ex(VitebskVillagesModule ${CMAKE_CURRENT_LIST_DIR} ${CMAKE_CURRENT_LIST_DIR}/generated)

if(${SC_CLANG_FORMAT_CODE})
	target_clangformat_setup(VitebskVillagesModule)
endif()
