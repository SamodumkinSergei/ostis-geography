SET(CMAKE_BUILD_TYPE Debug)
file(GLOB_RECURSE SOURCES "*.cpp" "*.hpp")

add_library (StreetTranslatorModule SHARED ${SOURCES})

target_include_directories(StreetTranslatorModule PRIVATE ${SC_MEMORY_SRC})
target_link_libraries(StreetTranslatorModule sc-memory)

add_dependencies(StreetTranslatorModule sc-memory)

sc_codegen(StreetTranslatorModule ${CMAKE_CURRENT_LIST_DIR})
