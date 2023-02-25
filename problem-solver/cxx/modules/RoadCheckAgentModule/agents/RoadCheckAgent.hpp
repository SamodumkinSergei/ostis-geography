#pragma once
#include <sc-memory/kpm/sc_agent.hpp>

#include "keynodes/keynodes.hpp"
#include "RoadCheckAgent.generated.hpp"

namespace RoadCheckAgentModule
{

    class RoadCheckAgent : public ScAgent
    {
        SC_CLASS(Agent, Event(Keynodes::action_search_road_pass, ScEvent::Type::AddOutputEdge))
            SC_GENERATED_BODY()

        static std::list<ScAddr> getIdentifierMeta(const ScAddr& addr);

        static ScAddr getStatusNode(const ScAddr& edge);

        static ScAddr getEdgeBetween(const ScAddr& from, const ScAddr& to, ScType type, bool findReverse);
    };

}  
