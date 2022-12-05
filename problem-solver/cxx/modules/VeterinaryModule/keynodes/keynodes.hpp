
 #pragma once

 #include "sc-memory/sc_addr.hpp"
 #include "sc-memory/sc_object.hpp"

 #include "keynodes.generated.hpp"

 namespace VeterinaryModule
 {

   class Keynodes : public ScObject
   {
     SC_CLASS()
     SC_GENERATED_BODY()

   public:
     SC_PROPERTY(Keynode("question_vitebskVeterinary"), ForceCreate)
     static ScAddr question_vitebskVeterinary;

     SC_PROPERTY(Keynode("nrel_length"), ForceCreate)
     static ScAddr nrel_length;

     SC_PROPERTY(Keynode("nrel_main_idtf"), ForceCreate)
     static ScAddr nrel_main_idtf;
   };

 }