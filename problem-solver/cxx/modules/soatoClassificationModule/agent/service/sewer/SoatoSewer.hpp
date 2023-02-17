#ifndef SC_MACHINE_SOATOSEWER_H
#define SC_MACHINE_SOATOSEWER_H

#include "AdministrativeFacility.hpp"
#include "sc-memory/kpm/sc_agent.hpp"

using namespace std;

class SoatoSewer {
    static void sew(ScMemoryContext &ms_context, const vector<AdministrativeFacility> &facilities);

    static ScAddr initializeFacility(ScMemoryContext &ms_context, const AdministrativeFacility& facility);

    static void addToClassIfNotPresent(ScMemoryContext &ms_context, ScAddr node, const string& class_name);

    static ScAddr resolveNodeByIdtf(ScMemoryContext &ms_context, const ScType &type, const string &idtf);
};

#endif  // SC_MACHINE_SOATOSEWER_H
