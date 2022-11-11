set(SOURCES
    "VilagesModule.cpp"
    "keynodes/keynodes.cpp"
    "agents/VillageSearchAgent.cpp"
    )

set(HEADERS
    "VilagesModule.hpp"
    "keynodes/keynodes.hpp"
    "agents/VillageSearchAgent.hpp"
    )

include_directories(
    ${CMAKE_CURRENT_LIST_DIR}
    ${SC_MEMORY_SRC}
    ${SC_KPM_SRC}
    ${SC_TOOLS_SRC}
    ${SC_COMMON_MODULE_SRC})

add_library(VilagesModule SHARED ${SOURCES} ${HEADERS})
target_link_libraries(VillagesModule sc-memory sc-agents-common)

sc_codegen_ex(VilagesModule ${CMAKE_CURRENT_LIST_DIR} ${CMAKE_CURRENT_LIST_DIR}/generated)