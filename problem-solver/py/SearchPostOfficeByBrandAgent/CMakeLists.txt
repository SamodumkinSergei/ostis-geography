file(GLOB_RECURSE SOURCES "*.cpp" "*.hpp")

add_library (SearchPostOfficeByBrandModule SHARED ${SOURCES})

target_include_directories(SearchPostOfficeByBrandModule PRIVATE ${SC_MEMORY_SRC})
target_link_libraries(SearchPostOfficeByBrandModule sc-memory)

add_dependencies(SearchPostOfficeByBrandModule sc-memory)

sc_codegen(SearchPostOfficeByBrandModule ${CMAKE_CURRENT_LIST_DIR})
