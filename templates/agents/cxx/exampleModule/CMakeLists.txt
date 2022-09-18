set(SOURCES
		"ExampleModule.cpp"
		"keynodes/ExampleKeynodes.cpp"
		"agent/GetDefinitionAgent.cpp"
		)

set(HEADERS
		"ExampleModule.hpp"
		"keynodes/ExampleKeynodes.hpp"
		"agent/GetDefinitionAgent.hpp"
		)

include_directories(
		${CMAKE_CURRENT_LIST_DIR}
		${SC_MEMORY_SRC}
		${SC_KPM_SRC}
		${SC_TOOLS_SRC}
		${SC_COMMON_MODULE_SRC})

add_library(exampleModule SHARED ${SOURCES} ${HEADERS})
target_link_libraries(exampleModule sc-memory sc-agents-common)

sc_codegen_ex(exampleModule ${CMAKE_CURRENT_LIST_DIR} ${CMAKE_CURRENT_LIST_DIR}/generated)

#if (${SC_BUILD_TESTS})
#	add_subdirectory(test)
#endif ()
