/*
* This source file is part of an OSTIS project. For the latest info, see http://ostis.net
* Distributed under the MIT License
* (See accompanying file COPYING.MIT or copy at http://opensource.org/licenses/MIT)
*/

#pragma once

#include <sc-memory/kpm/sc_agent.hpp>
#include "keynodes/keynodes.hpp"
#include "classifyLakeAgent.generated.hpp"

namespace classifyLakeModule
{

    class classifyLakeAgent : public ScAgent
    {
        SC_CLASS(Agent, Event(Keynodes::question_classify_lake, ScEvent::Type::AddOutputEdge))
        SC_GENERATED_BODY()
    };

} // namespace exampleModule
