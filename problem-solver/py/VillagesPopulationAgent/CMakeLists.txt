file(GLOB_RECURSE SOURCES "*.cpp" "*.hpp")

add_library (VillagesPopulationModule SHARED ${SOURCES})

target_include_directories(VillagesPopulationModule PRIVATE ${SC_MEMORY_SRC})
target_link_libraries(VillagesPopulationModule sc-memory)

add_dependencies(VillagesPopulationModule sc-memory)

sc_codegen(VillagesPopulationModule ${CMAKE_CURRENT_LIST_DIR})
