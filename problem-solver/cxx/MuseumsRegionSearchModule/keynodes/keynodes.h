/*
* This source file is part of an OSTIS project. For the latest info, see http://ostis.net
* Distributed under the MIT License
* (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
*/

#pragma once
#include "sc-memory/sc_addr.hpp"
#include "sc-memory/sc_object.hpp"

#include "keynodes.generated.hpp"

namespace MuseumsRegionSearchModule
{

	class Keynodes : public ScObject
	{
		SC_CLASS()
			SC_GENERATED_BODY()

	public:
		SC_PROPERTY(Keynode("action_museumsRegionSearch"), ForceCreate)
			static ScAddr action_museumsRegionSearch;

		SC_PROPERTY(Keynode("nrel_region"), ForceCreate)
			static ScAddr nrel_region;

		SC_PROPERTY(Keynode("nrel_main_idtf"), ForceCreate)
			static ScAddr nrel_main_idtf;
		
		SC_PROPERTY(Keynode("concept_museum"), ForceCreate)
			static ScAddr concept_museum;
	};

} 

