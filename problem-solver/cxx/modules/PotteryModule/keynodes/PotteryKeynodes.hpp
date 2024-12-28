/*
 * This source file is part of an OSTIS project. For the latest info, see http:
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http:
 */

#pragma once

#include <sc-memory/sc_keynodes.hpp>

#include "sc-memory/sc_addr.hpp"
#include "sc-memory/sc_object.hpp"

namespace PotteryModule
{

class PotteryKeynodes : public ScKeynodes
{
  public:
  static inline ScKeynode const question_potteryType{"question_potteryType"};

  static inline ScKeynode const question_potteryTech{"question_potteryTech"};

  static inline ScKeynode const question_potteryDate{"question_potteryDate"};

  static inline ScKeynode const action_get_pottery{"action_get_pottery"};

  static inline ScKeynode const nrel_technologies_used{"nrel_technologies_used"};

  static inline ScKeynode const nrel_type_of_production{"nrel_type_of_production"};

  static inline ScKeynode const nrel_main_idtf{"nrel_main_idtf"};

  static inline ScKeynode const nrel_date{"nrel_date"};

  static inline ScKeynode const pottery_centre{"pottery_centre"};

  

  

  

  
};

}  
