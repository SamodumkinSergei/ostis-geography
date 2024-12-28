/*
 * This source file is part of an OSTIS project. For the latest info, see http://ostis.net
 * Distributed under the MIT License
 * (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
 */

#include "MuseumsRegionSearchModule.hpp"
namespace MuseumsRegionSearchModule
{
// SC_IMPLEMENT_MODULE(MuseumsRegionSearchModule)
SC_MODULE_REGISTER(MuseumsRegionSearchModule)
  ->Agent<MuseumsRegionSearch>();

// void MuseumsRegionSearchModule::Initialize(ScMemoryContext * context)
// {
//   // if (!Keynodes::InitGlobal())
//   // {
//   //   return SC_RESULT_ERROR;
//   // }

//   // // ScMemoryContext ctx(sc_access_lvl_make_min, "MuseumsRegionSearchModule");

//  // context->SubscribeAgent<MuseumsRegionSearch>;

// }

// void MuseumsRegionSearchModule::Shutdown(ScMemoryContext * context)
// {
//  // context->UnsubscribeAgent<MuseumsRegionSearch>;
// }
}  // namespace MuseumsRegionSearchModule
