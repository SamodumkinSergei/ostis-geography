#pragma once
#include <sc-memory/kpm/sc_agent.hpp>

#include "keynodes/keynodes.hpp"
#include "RiverFlowSearchAgent.generated.hpp"

namespace RiverFlowSearchAgentModule
{

    class RiverFlowSearchAgent : public ScAgent
    {
        SC_CLASS(Agent, Event(Keynodes::action_search_river_flow, ScEvent::Type::AddOutputEdge))
            SC_GENERATED_BODY()

        static std::list<ScAddr> getIdentifierMeta(const ScAddr& addr);

        static ScAddr getStatusNode(const ScAddr& edge);

        static ScAddr getEdgeBetween(const ScAddr& from, const ScAddr& to, ScType type, bool findReverse);
    };

}  
