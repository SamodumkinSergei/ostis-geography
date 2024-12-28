#include "RiversModule.hpp"
namespace RiversModule
{

// Регистрация агентов
SC_MODULE_REGISTER(RiversModule)
  ->Agent<TheBiggestBasinInRegion>()
  ->Agent<LongerRiver>()
  ->Agent<LongestInRegion>()
  ->Agent<BiggerBasin>()
  ->Agent<ShorterRiver>();





























}  
