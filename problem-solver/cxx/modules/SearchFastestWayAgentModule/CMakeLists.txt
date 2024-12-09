set(SOURCES
       "SearchFastestWayAgentModule.cpp"
        
       "agents/SearchFastestWayAgent.cpp"
       )

set(HEADERS
       "SearchFastestWayAgentModule.hpp"
       "keynodes/keynodes.hpp"
       "agents/SearchFastestWayAgent.hpp"
      )
#file(GLOB_RECURSE SOURCES "*.cpp" "*.hpp")
include_directories(
		${CMAKE_CURRENT_LIST_DIR}
		${SC_MEMORY_SRC}
		${SC_KPM_SRC}
		${SC_TOOLS_SRC}
		${SC_COMMON_MODULE_SRC})

add_library(SearchFastestWayAgentModule SHARED ${SOURCES} ${HEADERS})
target_link_libraries(SearchFastestWayAgentModule sc-memory sc-agents-common)

if(${SC_CLANG_FORMAT_CODE})
	target_clangformat_setup(SearchFastestWayAgentModule)
endif()
