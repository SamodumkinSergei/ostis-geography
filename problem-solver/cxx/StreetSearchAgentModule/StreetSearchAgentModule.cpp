#include "StreetSearchAgentModule.hpp"
namespace StreetSearchAgentModule {
    SC_IMPLEMENT_MODULE(StreetSearchAgentModule)

        sc_result StreetSearchAgentModule::InitializeImpl()
        {
            if (!Keynodes::InitGlobal()) 
            {
            return SC_RESULT_ERROR;
            }

            ScMemoryContext ctx(sc_access_lvl_make_min, "StreetSearchAgentModule");

            SC_AGENT_REGISTER(StreetSearchAgent)

            return SC_RESULT_OK;
        }

    sc_result StreetSearchAgentModule::ShutdownImpl()
    {
        SC_AGENT_UNREGISTER(StreetSearchAgent)

            return SC_RESULT_OK;
    }
}
