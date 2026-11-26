#pragma once
#include "db/Database.h"

int addCategoryOrm(decltype(makeStorage(""))& storage, const Category& category);
std::optional<Category> getCategoryOrm(decltype(makeStorage(""))& storage, int id);