/*
 * Author Artsiom Salauyou
 */

#include "sc-agents-common/utils/CommonUtils.hpp"
#include "sc-builder/src/scs_loader.hpp"
#include "sc-memory/kpm/sc_agent.hpp"
#include "sc-memory/sc_wait.hpp"
#include "sc_test.hpp"

#include "keynodes/HotelKeynodes.hpp"

#include "agent/GetHotelByMinPricePerNightAgent.hpp"

namespace testGetHotelByMinPricePerNightAgent {
    ScsLoader loader;
    const std::string TEST_FILES_DIR_PATH = HOTEL_CONTROL_MODULE_TEST_SRC_PATH "/TestStructures/HotelSearch/";
    const int WAIT_TIME = 5000;

    using SerchHotelTest = ScMemoryTest;

    void initializedClasses() {
        scAgentsCommon::CoreKeynodes::InitGlobal();
        hotelModule::HotelKeynodes::InitGlobal();
    }

    TEST_F(SerchHotelTest, Test) {
        ScMemoryContext &context = *m_ctx;

        loader.loadScsFile(context, TEST_FILES_DIR_PATH + "SuccessfulExecution.scs");
        ScAddr test_question_node = context.HelperFindBySystemIdtf("test_question_node");
        EXPECT_TRUE(test_question_node.IsValid());

        ScAgentInit(true);
        initializedClasses();

        SC_AGENT_REGISTER(hotelModule::GetHotelByMinPricePerNightAgent)

        context.CreateEdge(
                ScType::EdgeAccessConstPosPerm, scAgentsCommon::CoreKeynodes::question_initiated, test_question_node);

        EXPECT_TRUE(
                ScWaitEvent<ScEventAddOutputEdge>(context, scAgentsCommon::CoreKeynodes::question_finished_successfully)
                        .Wait(WAIT_TIME));

        SC_AGENT_UNREGISTER(hotelModule::GetHotelByMinPricePerNightAgent);
    }
}
