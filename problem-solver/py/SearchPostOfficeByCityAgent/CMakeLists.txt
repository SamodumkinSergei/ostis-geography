file(GLOB_RECURSE SOURCES "*.cpp" "*.hpp")

add_library (SearchPostOfficeByCityModule SHARED ${SOURCES})

target_include_directories(SearchPostOfficeByCityModule PRIVATE ${SC_MEMORY_SRC})
target_link_libraries(SearchPostOfficeByCityModule sc-memory)

add_dependencies(SearchPostOfficeByCityModule sc-memory)

sc_codegen(SearchPostOfficeByCityModule ${CMAKE_CURRENT_LIST_DIR})
