#pragma once

#include <string>
#include <vector>

namespace soatoClassificationModule
{

class AdministrativeFacility
{
public:
  AdministrativeFacility() = default;

  AdministrativeFacility(const std::string & name, const std::string & code);

  const std::string & getName() const;

  const std::string & getCode() const;

  const std::vector<std::string> & getCategories() const;

  void addCategory(const std::string & category);

  void removeCategory(const std::string & category);

private:
  std::string name;
  std::string code;
  std::vector<std::string> categories;
};

}
