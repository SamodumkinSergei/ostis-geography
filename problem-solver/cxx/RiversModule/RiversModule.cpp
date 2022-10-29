#include "RiversModule.hpp"
namespace RiversModule {
SC_IMPLEMENT_MODULE(RiversModule)

sc_result RiversModule::InitializeImpl()
{
  if (!Keynodes::InitGlobal()) // exampleModule это название пространства в котором находятся агенты и другие классы которые используются для работы агентов
  {
    return SC_RESULT_ERROR;
  }

  ScMemoryContext ctx(sc_access_lvl_make_min, "RiversModule"); // тут exampleModule может быть любой строкой, но для простоты исползуется название пространства

  SC_AGENT_REGISTER(LongestInRegion) // регистрируем свои агенты, можно сколько угодно агентов зарегистрировать, если этого не сдлеать агент работать не будет, так как не загружен в память.

  return SC_RESULT_OK;
}

sc_result RiversModule::ShutdownImpl()
{
  SC_AGENT_UNREGISTER(LongestInRegion) // по аналогии с регистрацией агентов в памяти, убираем их из памяти, прописать для каждого агента в модуле

  return SC_RESULT_OK;
}
}
