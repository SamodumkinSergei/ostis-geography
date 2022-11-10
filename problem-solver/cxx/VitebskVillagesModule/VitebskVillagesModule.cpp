#include "VitebskVillagesModule.hpp"
namespace VitebskVillagesModule {
SC_IMPLEMENT_MODULE(VitebskVillagesModule)

sc_result VitebskVillagesModule::InitializeImpl()
{
  if (!Keynodes::InitGlobal()) // exampleModule это название пространства в котором находятся агенты и другие классы которые используются для работы агентов
  {
    return SC_RESULT_ERROR;
  }

  ScMemoryContext ctx(sc_access_lvl_make_min, "VitebskVillagesModule"); // тут exampleModule может быть любой строкой, но для простоты исползуется название пространства

  SC_AGENT_REGISTER(LargerVillageByPopulationInTheDistrict)
  SC_AGENT_REGISTER(LargerVillageByPopulation)
  SC_AGENT_REGISTER(GreatestDistanceToTheRegionalCenter) // регистрируем свои агенты, можно сколько угодно агентов зарегистрировать, если этого не сдлеать агент работать не будет, так как не загружен в память.

  return SC_RESULT_OK;
}

sc_result VitebskVillagesModule::ShutdownImpl()
{
  SC_AGENT_UNREGISTER(LargerVillageByPopulationInTheDistrict)
  SC_AGENT_UNREGISTER(LargerVillageByPopulation)
  SC_AGENT_UNREGISTER(GreatestDistanceToTheRegionalCenter) // по аналогии с регистрацией агентов в памяти, убираем их из памяти, прописать для каждого агента в модуле

  return SC_RESULT_OK;
}
}
