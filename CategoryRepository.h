#pragma once
#include "repository/ICategoryRepository.h"
#include <sqlite_orm/sqlite_orm.h>

template<class Storage>
class CategoryRepository : public ICategoryRepository {
    Storage& storage_;
public:
    explicit CategoryRepository(Storage& storage) : storage_(storage) {}

    int add(const Category& category) override {
        return storage_.insert(category);
    }

    std::optional<Category> getById(int id) override {
        auto ptr = storage_.get_pointer<Category>(id);
        if (ptr) return *ptr;
        return std::nullopt;
    }

    std::vector<Category> getAll() override {
        return storage_.get_all<Category>();
    }

    void update(const Category& category) override {
        storage_.update(category);
    }

    void remove(int id) override {
        storage_.remove<Category>(id);
    }
};