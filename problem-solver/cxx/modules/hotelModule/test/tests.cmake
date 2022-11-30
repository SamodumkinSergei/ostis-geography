make_tests_from_folder(${CMAKE_CURRENT_LIST_DIR}/units
        NAME hotel-module-tests
        DEPENDS sc-agents-common hotelModule sc-builder-lib
        INCLUDES ${SC_MEMORY_SRC}/tests/sc-memory/_test ..)

add_definitions(-DHOTEL_CONTROL_MODULE_TEST_SRC_PATH="${CMAKE_CURRENT_LIST_DIR}")