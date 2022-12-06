set(SOURCES
     "VeterinaryModule.cpp"
     "keynodes/keynodes.cpp"
     "agents/VeterinarySearchAgent.cpp"
     )

 set(HEADERS
     "VeterinaryModule.hpp"
     "keynodes/keynodes.hpp"
     "agents/VeterinarySearchAgent.hpp"
     )

 include_directories(
     ${CMAKE_CURRENT_LIST_DIR}
     ${SC_MEMORY_SRC}
     ${SC_KPM_SRC}
     ${SC_TOOLS_SRC}
     ${SC_COMMON_MODULE_SRC})

 add_library(VeterinaryModule SHARED ${SOURCES} ${HEADERS})
 target_link_libraries(VeterinarysModule sc-memory sc-agents-common)

 sc_codegen_ex(VeterinaryModule ${CMAKE_CURRENT_LIST_DIR} ${CMAKE_CURRENT_LIST_DIR}/generated)