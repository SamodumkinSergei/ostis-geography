file(GLOB_RECURSE SOURCES "*.cpp" "*.hpp")

add_library (ExampleModule SHARED ${SOURCES})

target_include_directories(ExampleModule PRIVATE ${SC_MEMORY_SRC})
target_link_libraries(ExampleModule sc-memory)

add_dependencies(ExampleModule sc-memory)

sc_codegen(ExampleModule ${CMAKE_CURRENT_LIST_DIR})
