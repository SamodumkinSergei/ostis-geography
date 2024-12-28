/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "DanceStudiosModule.hpp"

#include "agent/SearchDanceStudiosByTypeAgent.hpp"
#include "agent/SearchDanceStudiosByCityAgent.hpp"
#include "agent/SearchDanceStudiosByFoundingYearAgent.hpp"
#include "keynodes/DanceStudiosKeynodes.hpp"

using namespace dance_studios;

SC_MODULE_REGISTER(DanceStudiosModule)
  ->Agent<SearchDanceStudiosByTypeAgent>()
  ->Agent<SearchDanceStudiosByCityAgent>()
  ->Agent<SearchDanceStudiosByFoundingYearAgent>();

//todo(codegen-removal): if needed override ScModule::Initialize and move all non-keynodes and non-agents code from previous initialization method
// void DanceStudiosModule::Initialize(ScMemoryContext * context)
// {
//   // if (!DanceStudiosKeynodes::InitGlobal())
//   //   return SC_RESULT_ERROR;

//  // context->SubscribeAgent<SearchDanceStudiosByTypeAgentt>;
//  // context->SubscribeAgent<SearchDanceStudiosByCityAgent>;
//  // context->SubscribeAgent<SearchDanceStudiosByFoundingYearAgent>;


// }

// //todo(codegen-removal): if needed override ScModule::Shutdown and move all non-agents code from previous shutdown method
// void DanceStudiosModule::Shutdown(ScMemoryContext * context)
// {
//  // context->UnsubscribeAgent<SearchDanceStudiosByTypeAgentt>;
//  // context->UnsubscribeAgent<SearchDanceStudiosByCityAgent>;
//  // context->UnsubscribeAgent<SearchDanceStudiosByFoundingYearAgent>;


// }

