#pragma once
#include "model/Category.h"
#include <vector>
#include <optional>

class ICategoryRepository {
public:
    virtual ~ICategoryRepository() = default;

    virtual int add(const Category& category) = 0;
    virtual std::optional<Category> getById(int id) = 0;
    virtual std::vector<Category> getAll() = 0;
    virtual void update(const Category& category) = 0;
    virtual void remove(int id) = 0;
};