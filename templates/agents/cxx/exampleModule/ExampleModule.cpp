#include "ExampleModule.hpp"

SC_IMPLEMENT_MODULE(ExampleModule)

sc_result ExampleModule::InitializeImpl()
{
  if (!exampleModule::ExampleKeynodes::InitGlobal()) // exampleModule это название пространства в котором находятся агенты и другие классы которые используются для работы агентов
  {
    return SC_RESULT_ERROR;
  }

  ScMemoryContext ctx(sc_access_lvl_make_min, "exampleModule"); // тут exampleModule может быть любой строкой, но для простоты исползуется название пространства

  SC_AGENT_REGISTER(exampleModule::GetDefinitionAgent) // регистрируем свои агенты, можно сколько угодно агентов зарегистрировать, если этого не сдлеать агент работать не будет, так как не загружен в память.

  return SC_RESULT_OK;
}

sc_result ExampleModule::ShutdownImpl()
{
  SC_AGENT_UNREGISTER(exampleModule::GetDefinitionAgent) // по аналогии с регистрацией агентов в памяти, убираем их из памяти, прописать для каждого агента в модуле

  return SC_RESULT_OK;
}
