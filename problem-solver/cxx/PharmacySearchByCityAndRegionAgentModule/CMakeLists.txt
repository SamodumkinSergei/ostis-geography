set(SOURCES
        "PharmacySearchByCityAndRegionAgentModule.cpp"
        "keynodes/keynodes.cpp"
        "agents/PharmacySearchByCityAndRegionAgent.cpp"
        )

set(HEADERS
        "PharmacySearchByCityAndRegionAgentModule.hpp"
        "keynodes/keynodes.hpp"
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

sc_codegen_ex(PharmacySearchByCityAndRegionAgentModule ${CMAKE_CURRENT_LIST_DIR} ${CMAKE_CURRENT_LIST_DIR}/generated)

if(${SC_CLANG_FORMAT_CODE})
	target_clangformat_setup(PharmacySearchByCityAndRegionAgentModule)
endif()
