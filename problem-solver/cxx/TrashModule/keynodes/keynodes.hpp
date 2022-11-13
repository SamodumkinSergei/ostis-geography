/*
* This source file is part of an OSTIS project. For the latest info, see http://ostis.net
* Distributed under the MIT License
* (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
*/

#pragma once

#include "sc-memory/sc_addr.hpp"
#include "sc-memory/sc_object.hpp"

#include "keynodes.generated.hpp"

namespace TrashModule
{

class Keynodes : public ScObject
{
  SC_CLASS()
  SC_GENERATED_BODY()

public:



  SC_PROPERTY(Keynode("question_trashByRegion"), ForceCreate)
  static ScAddr question_trashByRegion;

  SC_PROPERTY(Keynode("question_trashByPest"), ForceCreate)
  static ScAddr question_trashByPest;

  SC_PROPERTY(Keynode("question_trashByCount"), ForceCreate)
  static ScAddr question_trashByCount;

  SC_PROPERTY(Keynode("nrel_stored_pesticides"), ForceCreate)
  static ScAddr nrel_stored_pesticides;
  SC_PROPERTY(Keynode("nrel_number_of_stocked_pesticides"), ForceCreate)
  static ScAddr nrel_number_of_stocked_pesticides;
  SC_PROPERTY(Keynode("nrel_search_area"), ForceCreate)
  static ScAddr nrel_search_area;
  SC_PROPERTY(Keynode("concept_way"), ForceCreate)
  static ScAddr concept_way;



  
};

} // namespace exampleModule
