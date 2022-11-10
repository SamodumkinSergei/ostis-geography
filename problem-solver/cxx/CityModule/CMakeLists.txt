file(GLOB_RECURSE SOURCES "*.cpp" "*.hpp")

add_library (CityModule SHARED ${SOURCES})

target_include_directories(CityModule PRIVATE ${SC_MEMORY_SRC})
target_link_libraries(CityModule sc-memory)

add_dependencies(CityModule sc-memory)

sc_codegen(CityModule ${CMAKE_CURRENT_LIST_DIR})