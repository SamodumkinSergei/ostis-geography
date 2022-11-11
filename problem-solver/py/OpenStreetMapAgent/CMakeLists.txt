file(GLOB_RECURSE SOURCES "*.cpp" "*.hpp")

add_library (OpenStreetMapModule SHARED ${SOURCES})

target_include_directories(OpenStreetMapModule PRIVATE ${SC_MEMORY_SRC})
target_link_libraries(OpenStreetMapModule sc-memory)

add_dependencies(OpenStreetMapModule sc-memory)

sc_codegen(OpenStreetMapModule ${CMAKE_CURRENT_LIST_DIR})
