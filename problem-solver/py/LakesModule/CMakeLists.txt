file(GLOB_RECURSE SOURCES "*.cpp" "*.hpp")

add_library (LakesModule SHARED ${SOURCES})

target_include_directories(LakesModule PRIVATE ${SC_MEMORY_SRC})
target_link_libraries(LakesModule sc-memory)

add_dependencies(LakesModule sc-memory)

sc_codegen(LakesModule ${CMAKE_CURRENT_LIST_DIR})
