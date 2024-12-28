/*
 * This source file is part of an OSTIS project. For the latest info, see http:
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http:
 */

#include "DanceStudiosModule.hpp"

#include "agent/SearchDanceStudiosByTypeAgent.hpp"
#include "agent/SearchDanceStudiosByCityAgent.hpp"
#include "agent/SearchDanceStudiosByFoundingYearAgent.hpp"
#include "keynodes/DanceStudiosKeynodes.hpp"

using namespace dance_studios;

// Регистрация агентов
SC_MODULE_REGISTER(DanceStudiosModule)
  ->Agent<SearchDanceStudiosByTypeAgent>()
  ->Agent<SearchDanceStudiosByCityAgent>()
  ->Agent<SearchDanceStudiosByFoundingYearAgent>();
























