#pragma once

#include "sc-memory/sc_addr.hpp"
#include "sc-memory/sc_object.hpp"

#include "ExampleKeynodes.generated.hpp"

namespace exampleModule // название пространства
{

class ExampleKeynodes : public ScObject // класс для узлов из памяти остиса, чтобы не искать их в агенте, а использовать адреса узлов
{
  SC_CLASS()
  SC_GENERATED_BODY()

public:

  // чтобы добавить новый узел копируем эти две строчки и заменяем action_get_definition на СИСТЕМНЫЙ идентификатор узла который нам нужен
  SC_PROPERTY(Keynode("action_get_definition"), ForceCreate)
  static ScAddr action_get_definition;

  SC_PROPERTY(Keynode("rrel_key_sc_element"), ForceCreate)
  static ScAddr rrel_key_sc_element;

  SC_PROPERTY(Keynode("definition"), ForceCreate)
  static ScAddr definition;

  SC_PROPERTY(Keynode("nrel_sc_text_translation"), ForceCreate)
  static ScAddr nrel_sc_text_translation;

  SC_PROPERTY(Keynode("rrel_example"), ForceCreate)
  static ScAddr rrel_example;
};

}
