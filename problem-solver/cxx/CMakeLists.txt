set(SC_COMMON_MODULE_SRC "${CMAKE_CURRENT_LIST_DIR}/commonModule")
set(CATCH_DIR "${SC_MACHINE_PATH}/generated/lib/Catch2")

if (EXISTS ${CATCH_DIR})
	include_directories(${CATCH_DIR})
endif ()

include_directories(${SC_MACHINE_PATH}/sc-memory/sc-test-framework)
