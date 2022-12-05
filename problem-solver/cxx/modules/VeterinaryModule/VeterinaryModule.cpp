#include "VeterinaryModule.hpp"

 namespace VeterinaryModule
 {
   SC_IMPLEMENT_MODULE(VeterinaryModule)

   sc_result VeterinaryModule::InitializeImpl()
   {
     if (!Keynodes::InitGlobal())
     {
       return SC_RESULT_ERROR;
     }

     ScMemoryContext ctx(sc_access_lvl_make_min, "VeterinaryModule");

     SC_AGENT_REGISTER(VeterinarySearchAgent)

     return SC_RESULT_OK;
   }

   sc_result VeterinaryModule::ShutdownImpl()
   {
     SC_AGENT_UNREGISTER(VeterinarySearchAgent)

     return SC_RESULT_OK;
   }
 }