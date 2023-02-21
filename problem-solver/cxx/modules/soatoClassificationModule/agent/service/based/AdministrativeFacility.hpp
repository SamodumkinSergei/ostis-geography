#pragma once

#include <string>
#include <vector>

class AdministrativeFacility {
  public: 
  std::string getName() const;
  void setName(const std::string & name);
  
  std::string getCode() const;
  void setCode(std::string code);

  std::vector<std::string> getCategories() const;

  void addCategory(const std::string & category);
  void removeCategory(const std::string & category);

  AdministrativeFacility();
  AdministrativeFacility(const std::string & name, const std::string & code);

  private:
  std::string name;
  std::string code;
  std::vector<std::string> categories;
};