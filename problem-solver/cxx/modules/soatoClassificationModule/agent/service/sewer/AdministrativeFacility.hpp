#ifndef SC_MACHINE_ADMINISTRATIVEFACILITY_HPP
#define SC_MACHINE_ADMINISTRATIVEFACILITY_HPP

#include <string>
#include <vector>

using namespace std;

class AdministrativeFacility {
public:
    AdministrativeFacility(const string &name, int code, const vector<string> &classes);

    const string &getName() const;

    int getCode() const;

    const vector<string> &getClasses() const;

private:
    string name;
    int code;
    vector<string> classes;
};

#endif  // SC_MACHINE_ADMINISTRATIVEFACILITY_HPP
