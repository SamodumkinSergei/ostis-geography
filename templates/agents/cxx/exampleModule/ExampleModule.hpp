#pragma once

#include "sc-memory/sc_memory.hpp"
#include "sc-memory/sc_module.hpp"

//подключаем все файлы которые используются для работы модуля
#include "keynodes/ExampleKeynodes.hpp"
#include "agent/GetDefinitionAgent.hpp"

#include "ExampleModule.generated.hpp" // заменяем тут назавние файла т.е. заменить ExampleModule на свое название

class ExampleModule : public ScModule // название модуля может быть любым (модуль может содержать несколько агентов)
{
  SC_CLASS(LoadOrder(100))
  SC_GENERATED_BODY()

  virtual sc_result InitializeImpl() override;

  virtual sc_result ShutdownImpl() override;
};
