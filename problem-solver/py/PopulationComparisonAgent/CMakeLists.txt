file(GLOB_RECURSE SOURCES "*.cpp" "*.hpp")

add_library (PopulationComparisonModule SHARED ${SOURCES})

target_include_directories(PopulationComparisonModule PRIVATE ${SC_MEMORY_SRC})
target_link_libraries(PopulationComparisonModule sc-memory)

add_dependencies(PopulationComparisonModule sc-memory)

sc_codegen(PopulationComparisonModule ${CMAKE_CURRENT_LIST_DIR})
