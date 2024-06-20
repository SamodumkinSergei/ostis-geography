file(GLOB_RECURSE SOURCES "*.cpp" "*.hpp")

add_library (MilasModule SHARED ${SOURCES})

target_include_directories(MilasModule PRIVATE ${SC_MEMORY_SRC})
target_link_libraries(MilasModule sc-memory)

add_dependencies(MilasModule sc-memory)

sc_codegen(MilasModule ${CMAKE_CURRENT_LIST_DIR})