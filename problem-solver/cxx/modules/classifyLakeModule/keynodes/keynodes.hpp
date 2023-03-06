/*
* This source file is part of an OSTIS project. For the latest info, see http://ostis.net
* Distributed under the MIT License
* (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
*/

#pragma once

#include <sc-memory/sc_object.hpp>
#include <sc-memory/sc_addr.hpp>

#include "keynodes.generated.hpp"

namespace classifyLakeModule
{

class Keynodes : public ScObject
{
  SC_CLASS()
  SC_GENERATED_BODY()

public:
	SC_PROPERTY(Keynode("nrel_area"), ForceCreate)
  static ScAddr nrel_area;
  
	SC_PROPERTY(Keynode("nrel_area_classification"), ForceCreate)
  static ScAddr nrel_area_classification;
  
  	SC_PROPERTY(Keynode("large"), ForceCreate)
  static ScAddr large;
  
  	SC_PROPERTY(Keynode("shallow"), ForceCreate)
  static ScAddr shallow;	


	SC_PROPERTY(Keynode("question_classify_lake"), ForceCreate)
  static ScAddr question_classify_lake;
};

} // namespace exampleModule
