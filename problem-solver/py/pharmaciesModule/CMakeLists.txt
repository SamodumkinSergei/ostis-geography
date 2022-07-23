file(GLOB_RECURSE SOURCES "*.cpp" "*.hpp")

add_library (pharmaciesModule SHARED ${SOURCES})

target_include_directories(pharmaciesModule PRIVATE ${SC_MEMORY_SRC})
target_link_libraries(pharmaciesModule sc-memory)

add_dependencies(pharmaciesModule sc-memory)

sc_codegen(pharmaciesModule ${CMAKE_CURRENT_LIST_DIR})
