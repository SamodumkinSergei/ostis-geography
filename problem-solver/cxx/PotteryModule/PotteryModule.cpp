#include "PotteryModule.hpp"
namespace PotteryModule {
SC_IMPLEMENT_MODULE(PotteryModule)

sc_result PotteryModule::InitializeImpl()
{
  if (!Keynodes::InitGlobal()) // exampleModule это название пространства в котором находятся агенты и другие классы которые используются для работы агентов
  {
    return SC_RESULT_ERROR;
  }

  ScMemoryContext ctx(sc_access_lvl_make_min, "PotteryModule"); // тут exampleModule может быть любой строкой, но для простоты исползуется название пространства

  SC_AGENT_REGISTER(PotteryDate)
  SC_AGENT_REGISTER(PotteryTech)
  SC_AGENT_REGISTER(PotteryType) // регистрируем свои агенты, можно сколько угодно агентов зарегистрировать, если этого не сдлеать агент работать не будет, так как не загружен в память.

  return SC_RESULT_OK;
}

sc_result PotteryModule::ShutdownImpl()
{
  SC_AGENT_UNREGISTER(PotteryDate)
  SC_AGENT_UNREGISTER(PotteryTech)
  SC_AGENT_UNREGISTER(PotteryType) // по аналогии с регистрацией агентов в памяти, убираем их из памяти, прописать для каждого агента в модуле

  return SC_RESULT_OK;
}
}
