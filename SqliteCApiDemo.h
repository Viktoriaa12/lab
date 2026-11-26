#pragma once
#include "model/Category.h"
#include <optional>
#include <string>

int addCategoryCApi(const std::string& dbPath, const Category& category);
std::optional<Category> getCategoryCApi(const std::string& dbPath, int id);