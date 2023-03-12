#pragma once
#include <sc-memory/kpm/sc_agent.hpp>

#include "keynodes/keynodes.hpp"
#include "CityBelongsSearchAgentModule.generated.hpp"

namespace CityBelongsSearchAgentModule
{

    class CityBelongsSearchAgent : public ScAgent
    {
        SC_CLASS(Agent, Event(Keynodes::action_search_city_belongs, ScEvent::Type::AddOutputEdge))
            SC_GENERATED_BODY()

        static std::list<ScAddr> getIdentifierMeta(const ScAddr& addr);

        static ScAddr getStatusNode(const ScAddr& edge);

        static ScAddr getEdgeBetween(const ScAddr& from, const ScAddr& to, ScType type, bool findReverse);
    };

}  