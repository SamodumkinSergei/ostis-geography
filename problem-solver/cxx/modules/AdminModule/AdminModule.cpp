#include "AdminModule.hpp"

// Регистрация агентов
SC_MODULE_REGISTER(AdminModule)
  ->Agent<adminModule::GetAdminBuildingRegion>()
  ->Agent<adminModule::GetAdminBuildingDistrict>();


