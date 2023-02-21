#include "SoatoClassifier.hpp"
#include <iostream>
#include <vector>

const std::map<int, std::string> SoatoClassifier::firstDigitMap = {
    {1, "Брестская область"},
    {2, "Витебская область"},
    {3, "Гомельская область"},
    {4, "Гродненская область"},
    {5, "г. Минск"},
    {6, "Минская область"},
    {7, "Могилевская область"},
};


SoatoClassifier::SoatoClassifier(){};

std::vector<AdministrativeFacility> SoatoClassifier::classify(const std::vector<std::pair<std::string, std::string>> &soatoCodes) const {
  std::vector<AdministrativeFacility> result;

  for (int i = 0; i < soatoCodes.size(); i++) {
    result.push_back(classify(soatoCodes[i]));
  }

  return result;
};

AdministrativeFacility SoatoClassifier::classify(const std::pair<std::string, std::string> &soatoCode) const {
  AdministrativeFacility facility = AdministrativeFacility(soatoCode.second, soatoCode.first);

  std::string code = facility.getCode();

  int firstDigit = std::stoi(code.substr(0, 1));
  int secondDigit = std::stoi(code.substr(1, 1));
  int thirdAndFourthDigits = std::stoi(code.substr(2, 2));
  int fifthDigit = std::stoi(code.substr(4, 1));
  int sixthAndSeventhDigits = std::stoi(code.substr(5, 2));
  int eighthAndNinthAndTenthDigits = std::stoi(code.substr(7, 3));

  facility.addCategory(getFirstDigitCategory(firstDigit));

  std::string secondCategory = getSecondDigitCategory(firstDigit, secondDigit);
  if (!secondCategory.empty()) {
    facility.addCategory(secondCategory);
  }

  std::string fifthSixthSeventhCategory = getFifthSixthSeventhDigitsCategory(secondDigit, fifthDigit, sixthAndSeventhDigits);
  if (!fifthSixthSeventhCategory.empty()) {
    facility.addCategory(fifthSixthSeventhCategory);
  }

  return facility;
};

std::string SoatoClassifier::getFirstDigitCategory(const int & code) const{
  
  std::string result;

  if (firstDigitMap.count(code) == 0) {
    result = "undefined";
  }
  else {
    result = firstDigitMap.at(code);
  }

  return result;
}

std::string SoatoClassifier::getSecondDigitCategory(const int & firstDigitCode, const int & secondDigitCode) const{
  
  std::string result;

  if (secondDigitCode == 2) {
    if (firstDigitCode == 5) {
      result = "район г. Минска";
    }
    else {
      result = "район области";
    }
  }
  else if (secondDigitCode == 4){
    result = "город областного подчинения";
  }

  return result;
}

std::string SoatoClassifier::getFifthSixthSeventhDigitsCategory(const int & secondDigitCode, const int & fifthDigitCode, const int & sixthAndSeventhDigitCode) const{
 
 std::string result;

  if (fifthDigitCode == 3) {
    result = "район города областного подчинения";
  }
  else if (fifthDigitCode == 5) {
    if (sixthAndSeventhDigitCode >= 1 && sixthAndSeventhDigitCode <= 49) {
      result = "город районного подчинения";
    }
    else if (sixthAndSeventhDigitCode >= 50 && sixthAndSeventhDigitCode <= 99) {
      if (secondDigitCode == 2) {
        result = "поселок городского типа районного подчинения";
      }
      else if (secondDigitCode == 4) {
        result = "поселок городскоготипа, подчиненный городу областного подчинения";
      }
    }
  }
  else if (fifthDigitCode == 7) {
    if (sixthAndSeventhDigitCode == 0) {
      result = "сельский населенный пункт районного подчинения";
    }
    else if (sixthAndSeventhDigitCode >= 1 && sixthAndSeventhDigitCode <= 49) {
      if (secondDigitCode == 2) {
        result = "сельский населенный пункт, подчиненный городу районного подчинения";
      }
      else if (secondDigitCode == 4) {
        result = "сельский населенный пункт, подчиненный городу областного подчинения";
      }
    }
  }
  else if (fifthDigitCode == 8){
    result = "сельсовет";
  }

  return result;
}