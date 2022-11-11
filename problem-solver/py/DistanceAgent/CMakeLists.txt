file(GLOB_RECURSE SOURCES "*.cpp" "*.hpp")

add_library (DistanceModule SHARED ${SOURCES})

target_include_directories(DistanceModule PRIVATE ${SC_MEMORY_SRC})
target_link_libraries(DistanceModule sc-memory)

add_dependencies(DistanceModule sc-memory)

sc_codegen(DistanceModule ${CMAKE_CURRENT_LIST_DIR})
