#include <algorithm>
#include "AdministrativeFacility.hpp"

namespace soatoClassificationModule
{

AdministrativeFacility::AdministrativeFacility(const std::string & inName, const std::string & inCode)
  : name(inName)
  , code(inCode){};

const std::string & AdministrativeFacility::getName() const
{
  return name;
};

const std::string & AdministrativeFacility::getCode() const
{
  return code;
};

const std::vector<std::string> & AdministrativeFacility::getCategories() const
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

}  // namespace soatoClassificationModule
