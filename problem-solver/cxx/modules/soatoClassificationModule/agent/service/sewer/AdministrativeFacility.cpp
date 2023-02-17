#include "AdministrativeFacility.hpp"

AdministrativeFacility::AdministrativeFacility(const string &name, int code, const vector<string> &classes) {
    this->name = name;
    this->code = code;
    this->classes = classes;
}

const string &AdministrativeFacility::getName() const {
    return name;
}

int AdministrativeFacility::getCode() const {
    return code;
}

const vector<string> &AdministrativeFacility::getClasses() const {
    return classes;
}
