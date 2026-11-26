#pragma once
#include <string>
#include <sqlite_orm/sqlite_orm.h>
#include "model/Category.h"
#include "model/Notification.h"

inline auto makeStorage(const std::string& dbPath) {
    using namespace sqlite_orm;
    return make_storage(dbPath,
        make_table("categories",
            make_column("id", &Category::id, primary_key().autoincrement()),
            make_column("name", &Category::name),
            make_column("description", &Category::description),
            make_column("priority", &Category::priority)
        ),
        make_table("notifications",
            make_column("id", &Notification::id, primary_key().autoincrement()),
            make_column("category_id", &Notification::category_id),
            make_column("title", &Notification::title),
            make_column("message", &Notification::message),
            make_column("created_at", &Notification::created_at),
            make_column("read_flag", &Notification::read_flag),
            foreign_key(&Notification::category_id).references(&Category::id)
        )
    );
}