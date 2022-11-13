#include "TrashModule.hpp"
namespace TrashModule {
SC_IMPLEMENT_MODULE(TrashModule)

sc_result TrashModule::InitializeImpl()
{
  if (!Keynodes::InitGlobal()) // exampleModule это название пространства в котором находятся агенты и другие классы которые используются для работы агентов
  {
    return SC_RESULT_ERROR;
  }

  ScMemoryContext ctx(sc_access_lvl_make_min, "TrashModule"); // тут exampleModule может быть любой строкой, но для простоты исползуется название пространства

  SC_AGENT_REGISTER(TrashByRegion)
  SC_AGENT_REGISTER(TrashByPest)
  SC_AGENT_REGISTER(TrashByCount) // регистрируем свои агенты, можно сколько угодно агентов зарегистрировать, если этого не сдлеать агент работать не будет, так как не загружен в память.

  return SC_RESULT_OK;
}

sc_result TrashModule::ShutdownImpl()
{
  SC_AGENT_UNREGISTER(TrashByRegion)
  SC_AGENT_UNREGISTER(TrashByPest)
  SC_AGENT_UNREGISTER(TrashByCount) // по аналогии с регистрацией агентов в памяти, убираем их из памяти, прописать для каждого агента в модуле

  return SC_RESULT_OK;
}
}
