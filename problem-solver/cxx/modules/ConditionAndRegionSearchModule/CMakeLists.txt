file(GLOB_RECURSE SOURCES "*.cpp" "*.hpp")

include_directories(${CMAKE_CURRENT_LIST_DIR} ${SC_MEMORY_SRC} ${SC_KPM_SRC})

add_library(StatusAndDistrictSearchModule SHARED ${SOURCES} ${HEADERS})
target_link_libraries(StatusAndDistrictSearchModule sc-memory sc-agents-common)

sc_codegen_ex(StatusAndDistrictSearchModule ${CMAKE_CURRENT_LIST_DIR} ${CMAKE_CURRENT_LIST_DIR}/generated)
