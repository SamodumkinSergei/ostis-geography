file(GLOB_RECURSE SOURCES "*.cpp" "*.hpp")

add_library (SearchBanksByTypeModule SHARED ${SOURCES})

target_include_directories(SearchBanksByTypeModule PRIVATE ${SC_MEMORY_SRC})
target_link_libraries(SearchBanksByTypeModule sc-memory)

add_dependencies(SearchBanksByTypeModule sc-memory)

sc_codegen(SearchBanksByTypeModule ${CMAKE_CURRENT_LIST_DIR})
