#include "comparison/SqliteCApiDemo.h"
#include <sqlite3.h>
#include <iostream>

int addCategoryCApi(const std::string& dbPath, const Category& category) {
    sqlite3* db = nullptr;
    if (sqlite3_open(dbPath.c_str(), &db) != SQLITE_OK) return -1;

    const char* sql =
        "INSERT INTO categories (name, description, priority) VALUES (?, ?, ?);";
    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "prepare failed: " << sqlite3_errmsg(db) << "\n";
        sqlite3_close(db);
        return -1;
    }

    sqlite3_bind_text(stmt, 1, category.name.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, category.description.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 3, category.priority);

    int rc = sqlite3_step(stmt);
    int newId = (rc == SQLITE_DONE)
        ? static_cast<int>(sqlite3_last_insert_rowid(db))
        : -1;

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return newId;
}

std::optional<Category> getCategoryCApi(const std::string& dbPath, int id) {
    sqlite3* db = nullptr;
    if (sqlite3_open(dbPath.c_str(), &db) != SQLITE_OK) return std::nullopt;

    const char* sql =
        "SELECT id, name, description, priority FROM categories WHERE id = ?;";
    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        sqlite3_close(db);
        return std::nullopt;
    }

    sqlite3_bind_int(stmt, 1, id);

    std::optional<Category> result;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        Category c;
        c.id = sqlite3_column_int(stmt, 0);
        c.name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        c.description = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        c.priority = sqlite3_column_int(stmt, 3);
        result = c;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return result;
}