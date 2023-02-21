#include <iostream>
#include "SoatoClassifier.hpp"
#include "AdministrativeFacility.hpp"

int main(int argc, char ** argv)
{
  SoatoClassifier classifier = SoatoClassifier();

  AdministrativeFacility facility = classifier.classify(std::make_pair("2238808061", "Сельцо-Белое"));

  std::cout << "name - " << facility.getName() << "\ncode - " << facility.getCode() << "\ncategories: \n";
  std::vector<std::string> test = facility.getCategories();
  for (int i = 0; i < test.size(); i++)
  {
    std::cout << test[i] << "\n";
  }
  return 0;
}
