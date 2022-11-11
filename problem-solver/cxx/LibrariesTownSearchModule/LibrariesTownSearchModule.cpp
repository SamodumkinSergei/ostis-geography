/*
* This source file is part of an OSTIS project. For the latest info, see http://ostis.net
* Distributed under the MIT License
* (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
*/

#include "LibrariesTownSearchModule.hpp"
namespace LibrariesTownSearchModule {
    SC_IMPLEMENT_MODULE(LibrariesTownSearchModule)

        sc_result LibrariesTownSearchModule::InitializeImpl()
        {
            if (!Keynodes::InitGlobal()) 
            {
            return SC_RESULT_ERROR;
            }

            ScMemoryContext ctx(sc_access_lvl_make_min, "LibrariesTownSearchModule");

            SC_AGENT_REGISTER(LibrariesTownSearch)

            return SC_RESULT_OK;
        }

    sc_result LibrariesTownSearchModule::ShutdownImpl()
    {
        SC_AGENT_UNREGISTER(LibrariesTownSearch)

            return SC_RESULT_OK;
    }
}
