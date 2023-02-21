#include <algorithm>
#include "AdministrativeFacility.hpp"

AdministrativeFacility::AdministrativeFacility(){};

AdministrativeFacility::AdministrativeFacility(const std::string & name, const std::string & code)
{
  this->name = name;
  this->code = code;
};

std::string AdministrativeFacility::getName() const
{
  return name;
};

void AdministrativeFacility::setName(const std::string & name)
{
  this->name = name;
};

std::string AdministrativeFacility::getCode() const
{
  return code;
};

void AdministrativeFacility::setCode(std::string code)
{
  this->code = code;
};

std::vector<std::string> AdministrativeFacility::getCategories() const
{
  return categories;
}

void AdministrativeFacility::addCategory(const std::string & category)
{
  categories.push_back(category);
};

void AdministrativeFacility::removeCategory(const std::string & category)
{
  categories.erase(std::find(categories.begin(), categories.end(), category));
};
