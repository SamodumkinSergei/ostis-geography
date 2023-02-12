set(SC_SOATO_CLASSIFICATION_MODULE_SRC ${CMAKE_CURRENT_LIST_DIR})

file(GLOB_RECURSE SOURCES "*.cpp" "*.hpp")

include_directories(
  ${SC_SOATO_CLASSIFICATION_MODULE_SRC} 
  ${SC_MEMORY_SRC} 
  ${SC_KPM_SRC}
  ${SC_TOOLS_SRC}
  ${SC_COMMON_MODULE_SRC}
)

add_library(soatoClassificationModule SHARED ${SOURCES})

add_dependencies(
  soatoClassificationModule
  sc-memory
  sc-agents-common
)

target_link_libraries(
  soatoClassificationModule
  sc-memory
  sc-agents-common
)

sc_codegen_ex(soatoClassificationModule ${CMAKE_CURRENT_LIST_DIR} ${CMAKE_CURRENT_LIST_DIR}/generated)
