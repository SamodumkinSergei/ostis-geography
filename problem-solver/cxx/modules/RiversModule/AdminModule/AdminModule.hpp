#pragma once

#include "sc-memory/sc_memory.hpp"
#include "sc-memory/sc_module.hpp"

//подключаем все файлы которые используются для работы модуля
#include "keynodes/AdminKeynodes.hpp"
#include "agent/GetAdminBuildingRegion.hpp"
#include "agent/GetAdminBuildingDistrict.hpp"

class AdminModule : public ScModule  // название модуля может быть любым (модуль может содержать несколько агентов)
{
  // void Initialize(ScMemoryContext * context) ;
  // void Shutdown(ScMemoryContext * context) ;
};
