#pragma once

#include "sc-memory/sc_memory.hpp"
#include "sc-memory/sc_module.hpp"

//подключаем все файлы которые используются для работы модуля
#include "keynodes/keynodes.hpp"
#include "agents/TrashByRegion.hpp"
#include "agents/TrashByPest.hpp"
#include "agents/TrashByCount.hpp"

#include "TrashModule.generated.hpp" // заменяем тут назавние файла т.е. заменить ExampleModule на свое название

namespace TrashModule {

class TrashModule : public ScModule // название модуля может быть любым (модуль может содержать несколько агентов)
{
  SC_CLASS(LoadOrder(100))
  SC_GENERATED_BODY()

  virtual sc_result InitializeImpl() override;

  virtual sc_result ShutdownImpl() override;
};
}
