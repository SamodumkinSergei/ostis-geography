/*
* This source file is part of an OSTIS project. For the latest info, see http://ostis.net
* Distributed under the MIT License
* (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
*/

#pragma once
#include "sc-memory/sc_addr.hpp"
#include "sc-memory/sc_object.hpp"

#include "keynodes.generated.hpp"

namespace StatusAndDistrictSearchModule
{

	class Keynodes : public ScObject
	{
		SC_CLASS()
			SC_GENERATED_BODY()

	public:
		SC_PROPERTY(Keynode("action_statusAndDistrictSearch"), ForceCreate)
			static ScAddr action_statusAndDistrictSearch;

		SC_PROPERTY(Keynode("nrel_district"), ForceCreate)
			static ScAddr nrel_district;

		SC_PROPERTY(Keynode("nrel_search_area"), ForceCreate)
			static ScAddr nrel_search_area;

		SC_PROPERTY(Keynode("nrel_city"), ForceCreate)
			static ScAddr nrel_city;

		SC_PROPERTY(Keynode("nrel_main_idtf"), ForceCreate)
			static ScAddr nrel_main_idtf;
		
		SC_PROPERTY(Keynode("nrel_status"), ForceCreate)
			static ScAddr nrel_status;
	};

} 

