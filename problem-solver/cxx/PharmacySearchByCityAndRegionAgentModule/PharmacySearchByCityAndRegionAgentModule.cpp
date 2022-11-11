#include "PharmacySearchByCityAndRegionAgentModule.hpp"
namespace PharmacySearchByCityAndRegionAgentModule {
    SC_IMPLEMENT_MODULE(PharmacySearchByCityAndRegionAgentModule)

        sc_result PharmacySearchByCityAndRegionAgentModule::InitializeImpl()
        {
            if (!Keynodes::InitGlobal()) 
            {
            return SC_RESULT_ERROR;
            }

            ScMemoryContext ctx(sc_access_lvl_make_min, "PharmacySearchByCityAndRegionAgentModule");

            SC_AGENT_REGISTER(PharmacySearchByCityAndRegionAgent)

            return SC_RESULT_OK;
        }

    sc_result PharmacySearchByCityAndRegionAgentModule::ShutdownImpl()
    {
        SC_AGENT_UNREGISTER(PharmacySearchByCityAndRegionAgent)

            return SC_RESULT_OK;
    }
}
