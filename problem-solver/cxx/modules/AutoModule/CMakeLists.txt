set(SOURCES
        "AutoModule.cpp"
        "agent/FindSiteAgent.cpp"
        "keynodes/AutoKeynodes.cpp"
        )

set(HEADERS
        "AutoModule.hpp"
        "agent/FindSiteAgent.hpp"
        "keynodes/AutoKeynodes.hpp"
        )

include_directories(
        ${CMAKE_CURRENT_LIST_DIR}
        ${SC_MEMORY_SRC}
        ${SC_KPM_SRC}
        ${SC_TOOLS_SRC}
)

add_library(AutoModule SHARED ${SOURCES} ${HEADERS})

target_link_libraries(
        AutoModule
        sc-memory
        sc-agents-common
)

sc_codegen_ex(AutoModule ${CMAKE_CURRENT_LIST_DIR} ${CMAKE_CURRENT_LIST_DIR}/generated)



