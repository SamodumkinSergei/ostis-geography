#pragma once

#include <string>
#include <vector>
#include "AdministrativeFacility.hpp"
#include <map>

class SoatoClassifier {
  public:
  SoatoClassifier();
  std::vector<AdministrativeFacility> classify(const std::vector<std::pair<std::string, std::string>> & soatoCodes) const;
  AdministrativeFacility classify(const std::pair<std::string, std::string> & soatoCode) const;
  
  private:
  static const std::map<int, std::string> firstDigitMap;
  std::string getFirstDigitCategory(const int & code) const;
  std::string getSecondDigitCategory(const int & firstDigitCode, const int & secondDigitCode) const;
  std::string getFifthSixthSeventhDigitsCategory(const int & secondDigitCode, const int & fifthDigitCode, const int & sixthAndSeventhDigitCode) const;
};