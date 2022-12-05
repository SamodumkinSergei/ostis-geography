#pragma once

 #include "sc-memory/kpm/sc_agent.hpp"

 #include "keynodes/keynodes.hpp"
 #include "VeterinaryModule.generated.hpp"

 namespace VeterinaryModule
 {

   class VeterinaryModule : public ScAgent
   {
     SC_CLASS(Agent, Event(Keynodes::question_vitebskVeterinary, ScEvent::Type::AddOutputEdge))
     SC_GENERATED_BODY()
   };

 }