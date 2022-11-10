file(GLOB_RECURSE SOURCES "*.cpp" "*.hpp")

add_library (kindergartensModule SHARED ${SOURCES})

target_include_directories(kindergartensModule PRIVATE ${SC_MEMORY_SRC})
target_link_libraries(kindergartensModule sc-memory)

add_dependencies(kindergartensModule sc-memory)

sc_codegen(kindergartensModule ${CMAKE_CURRENT_LIST_DIR})