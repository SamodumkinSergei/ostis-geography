file(GLOB_RECURSE SOURCES "*.cpp" "*.hpp")

add_library (SearchPostOfficeByTypeModule SHARED ${SOURCES})

target_include_directories(SearchPostOfficeByTypeModule PRIVATE ${SC_MEMORY_SRC})
target_link_libraries(SearchPostOfficeByTypeModule sc-memory)

add_dependencies(SearchPostOfficeByTypeModule sc-memory)

sc_codegen(SearchPostOfficeByTypeModule ${CMAKE_CURRENT_LIST_DIR})
