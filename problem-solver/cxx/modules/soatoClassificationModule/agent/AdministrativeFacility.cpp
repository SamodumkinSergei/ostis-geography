#include <algorithm>  // Для использования std::find
#include "AdministrativeFacility.hpp"

namespace soatoClassificationModule  // Определение пространства имен для модуля классификации SOATO
{

// Конструктор класса AdministrativeFacility
AdministrativeFacility::AdministrativeFacility(const std::string & inName, const std::string & inCode)
  : name(inName)  // Инициализация имени объекта
  , code(inCode)  // Инициализация кода объекта
{};

// Возвращает имя административного объекта
const std::string & AdministrativeFacility::getName() const
{
  return name;
};

// Возвращает код административного объекта
const std::string & AdministrativeFacility::getCode() const
{
  return code;
};

// Возвращает список категорий объекта
const std::vector<std::string> & AdministrativeFacility::getCategories() const
{
  return categories;
}

// Добавляет новую категорию в список категорий
void AdministrativeFacility::addCategory(const std::string & category)
{
  categories.push_back(category);  // Добавление категории в конец вектора
};

// Удаляет категорию из списка
void AdministrativeFacility::removeCategory(const std::string & category)
{
  // Ищем категорию в списке и удаляем ее
  categories.erase(std::find(categories.begin(), categories.end(), category));
};

}  // namespace soatoClassificationModule
