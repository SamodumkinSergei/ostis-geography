file(GLOB_RECURSE SOURCES "*.cpp" "*.hpp")

add_library (SearchBanksByCityModule SHARED ${SOURCES})

target_include_directories(SearchBanksByCityModule PRIVATE ${SC_MEMORY_SRC})
target_link_libraries(SearchBanksByCityModule sc-memory)

add_dependencies(SearchBanksByCityModule sc-memory)

sc_codegen(SearchBanksByCityModule ${CMAKE_CURRENT_LIST_DIR})
