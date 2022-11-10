file(GLOB_RECURSE SOURCES "*.cpp" "*.hpp")

add_library (HotelsModule SHARED ${SOURCES})

target_include_directories(HotelsModule PRIVATE ${SC_MEMORY_SRC})
target_link_libraries(HotelsModule sc-memory)

add_dependencies(HotelsModule sc-memory)

sc_codegen(HotelsModule ${CMAKE_CURRENT_LIST_DIR})
