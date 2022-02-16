file(GLOB_RECURSE SOURCES "*.cpp" "*.hpp")

add_library (SearchBanksByBrandModule SHARED ${SOURCES})

target_include_directories(SearchBanksByBrandModule PRIVATE ${SC_MEMORY_SRC})
target_link_libraries(SearchBanksByBrandModule sc-memory)

add_dependencies(SearchBanksByBrandModule sc-memory)

sc_codegen(SearchBanksByBrandModule ${CMAKE_CURRENT_LIST_DIR})
