set(SOURCES
    "VillagesModule.cpp"
    "keynodes/keynodes.cpp"
    "agents/VillageSearchAgent.cpp"
    )

set(HEADERS
    "VillagesModule.hpp"
    "keynodes/keynodes.hpp"
    "agents/VillageSearchAgent.hpp"
    )

include_directories(
    ${CMAKE_CURRENT_LIST_DIR}
    ${SC_MEMORY_SRC}
    ${SC_KPM_SRC}
    ${SC_TOOLS_SRC}
    ${SC_COMMON_MODULE_SRC})

add_library(VillagesModule SHARED ${SOURCES} ${HEADERS})
target_link_libraries(VillagesModule sc-memory sc-agents-common)

sc_codegen_ex(VillagesModule ${CMAKE_CURRENT_LIST_DIR} ${CMAKE_CURRENT_LIST_DIR}/generated)