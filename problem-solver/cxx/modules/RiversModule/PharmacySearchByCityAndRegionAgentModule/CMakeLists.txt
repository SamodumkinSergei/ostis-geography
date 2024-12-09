set(SOURCES
        "PharmacySearchByCityAndRegionAgentModule.cpp"
        # "keynodes/PharmacyKeynodes.cpp"
        "agents/PharmacySearchByCityAndRegionAgent.cpp"
        )

set(HEADERS
        "PharmacySearchByCityAndRegionAgentModule.hpp"
        "keynodes/PharmacyKeynodes.hpp"
        "agents/PharmacySearchByCityAndRegionAgent.hpp"
        )

include_directories(
		${CMAKE_CURRENT_LIST_DIR}
		${SC_MEMORY_SRC}
		${SC_KPM_SRC}
		${SC_TOOLS_SRC}
		${SC_COMMON_MODULE_SRC})

add_library(PharmacySearchByCityAndRegionAgentModule SHARED ${SOURCES} ${HEADERS})
target_link_libraries(PharmacySearchByCityAndRegionAgentModule sc-memory sc-agents-common)

if(${SC_CLANG_FORMAT_CODE})
	target_clangformat_setup(PharmacySearchByCityAndRegionAgentModule)
endif()
