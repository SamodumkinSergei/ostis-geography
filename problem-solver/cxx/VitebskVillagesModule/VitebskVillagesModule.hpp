#pragma once

#include "sc-memory/sc_memory.hpp"
#include "sc-memory/sc_module.hpp"

//подключаем все файлы которые используются для работы модуля
#include "keynodes/keynodes.hpp"
#include "agents/LargerVillageByPopulationInTheDistrict.hpp"
#include "agents/LargerVillageByPopulation.hpp"
#include "agents/GreatestDistanceToTheRegionalCenter.hpp"

#include "VitebskVillagesModule.generated.hpp" // заменяем тут назавние файла т.е. заменить ExampleModule на свое название

namespace VitebskVillagesModule {

class VitebskVillagesModule : public ScModule // название модуля может быть любым (модуль может содержать несколько агентов)
{
  SC_CLASS(LoadOrder(100))
  SC_GENERATED_BODY()

  virtual sc_result InitializeImpl() override;

  virtual sc_result ShutdownImpl() override;
};
}
