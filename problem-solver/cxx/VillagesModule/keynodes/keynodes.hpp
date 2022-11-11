/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#pragma once

#include "sc-memory/sc_addr.hpp"
#include "sc-memory/sc_object.hpp"

#include "keynodes.generated.hpp"

namespace VillagesModule
{

  class Keynodes : public ScObject
  {
    SC_CLASS()
    SC_GENERATED_BODY()

  public:
    SC_PROPERTY(Keynode("question_vitebskVillage"), ForceCreate)
    static ScAddr question_vitebskVillage;

    SC_PROPERTY(Keynode("nrel_length"), ForceCreate)
    static ScAddr nrel_length;

    SC_PROPERTY(Keynode("nrel_main_idtf"), ForceCreate)
    static ScAddr nrel_main_idtf;
  };

}