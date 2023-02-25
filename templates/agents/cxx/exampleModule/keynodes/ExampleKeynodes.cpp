#include "ExampleKeynodes.hpp"

namespace exampleModule
{
  // чтобы добавить новый узел копируем эту строчку и заменяем action_get_definition на СИСТЕМНЫЙ идентификатор узла который нам нужен
  ScAddr ExampleKeynodes::action_get_definition;
  ScAddr ExampleKeynodes::rrel_key_sc_element;
  ScAddr ExampleKeynodes::definition;
  ScAddr ExampleKeynodes::nrel_sc_text_translation;
  ScAddr ExampleKeynodes::rrel_example;
}
