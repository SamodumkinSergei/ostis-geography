set(SOURCES
        "HotelModule.cpp"
        "agent/GetHotelByMinPricePerNightAgent.cpp"
        # "keynodes/HotelKeynodes.cpp"
        "searcher/HotelSearcher.cpp"
        "templates/HotelTemplates.cpp"
        )

set(HEADERS
        "HotelModule.hpp"
        "agent/GetHotelByMinPricePerNightAgent.hpp"
        "keynodes/HotelKeynodes.hpp"
        "searcher/HotelSearcher.hpp"
        "templates/HotelTemplates.hpp"
        )

include_directories(
        ${CMAKE_CURRENT_LIST_DIR}
        ${SC_MEMORY_SRC}
        ${SC_KPM_SRC}
        ${SC_TOOLS_SRC}
)

add_library(hotelModule SHARED ${SOURCES} ${HEADERS})

target_link_libraries(
        hotelModule
        sc-memory
        sc-agents-common
)

if (${SC_BUILD_TESTS})
    include(${CMAKE_CURRENT_LIST_DIR}/test/tests.cmake)
endif ()

if(${SC_CLANG_FORMAT_CODE})
    target_clangformat_setup(hotelModule)
endif()

