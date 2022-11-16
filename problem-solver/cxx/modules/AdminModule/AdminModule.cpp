#include "AdminModule.hpp"

SC_IMPLEMENT_MODULE(AdminModule)

sc_result AdminModule::InitializeImpl()
{
  if (!adminModule::AdminKeynodes::InitGlobal())  // AdminModule это название пространства в котором находятся агенты и
                                                  // другие классы которые используются для работы агентов
  {
    return SC_RESULT_ERROR;
  }

  ScMemoryContext ctx(
      sc_access_lvl_make_min,
      "adminModule");  // тут AdminModule может быть любой строкой, но для простоты исползуется название пространства
  SC_AGENT_REGISTER(adminModule::GetAdminBuildingRegion)
  SC_AGENT_REGISTER(adminModule::GetAdminBuildingDistrict)
  // регистрируем свои агенты, можно сколько угодно агентов зарегистрировать, если этого не сдлеать агент работать не
  // будет, так как не загружен в память.

  return SC_RESULT_OK;
}

sc_result AdminModule::ShutdownImpl()
{
  SC_AGENT_UNREGISTER(adminModule::GetAdminBuildingRegion)
  SC_AGENT_UNREGISTER(adminModule::GetAdminBuildingDistrict)
  // по аналогии с регистрацией агентов в памяти, убираем их из памяти, прописать для каждого агента в модуле

  return SC_RESULT_OK;
}
