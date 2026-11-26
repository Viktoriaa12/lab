#include "comparison/OrmDemo.h"
#include <sqlite_orm/sqlite_orm.h>

int addCategoryOrm(decltype(makeStorage(""))& storage, const Category& category) {
    return storage.insert(category);
}

std::optional<Category> getCategoryOrm(decltype(makeStorage(""))& storage, int id) {
    auto ptr = storage.get_pointer<Category>(id);
    if (ptr) return *ptr;
    return std::nullopt;
}