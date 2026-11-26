#include "transaction/TransactionDemo.h"
#include <iostream>
#include <sqlite_orm/sqlite_orm.h>

using namespace sqlite_orm;

// Сценарій 1: успішне додавання категорії + першого сповіщення
void transactionSuccess(decltype(makeStorage(""))& storage) {
    std::cout << "\n--- Transaction 1: SUCCESS scenario ---\n";
    auto before = storage.count<Category>();
    std::cout << "Categories before: " << before << "\n";

    try {
        storage.transaction([&]() {
            Category c{ 0, "Alerts", "Critical alerts", 5 };
            int newId = storage.insert(c);
            std::cout << "  Inserted category id=" << newId << "\n";

            Notification n{ 0, newId, "First alert", "Critical event",
                           "2026-11-10T21:00:00", 0 };
            storage.insert(n);
            std::cout << "  Inserted first notification\n";
            return true;
            });
        std::cout << "  Transaction committed\n";
    }
    catch (const std::exception& e) {
        std::cerr << "  Transaction failed: " << e.what() << "\n";
    }

    auto after = storage.count<Category>();
    std::cout << "Categories after: " << after
        << (after == before + 1 ? " (ok, +1)" : " (unexpected)") << "\n";
}

// Сценарій 2: навмисна помилка другої операції → відкат
void transactionRollback(decltype(makeStorage(""))& storage) {
    std::cout << "\n--- Transaction 2: ROLLBACK scenario ---\n";
    auto before = storage.count<Category>();
    std::cout << "Categories before: " << before << "\n";

    try {
        storage.transaction([&]() {
            Category c{ 0, "Rollback Cat", "Will be rolled back", 1 };
            int newId = storage.insert(c);
            std::cout << "  Inserted category id=" << newId << "\n";

            // station_id = 999999 не існує → порушення FK
            Notification bad{ 0, 999999, "Bad", "Bad",
                             "2026-11-10T21:00:00", 0 };
            storage.insert(bad);
            std::cout << "  This line should not be reached\n";
            return true;
            });
    }
    catch (const std::exception& e) {
        std::cout << "  Exception caught (expected): " << e.what() << "\n";
    }

    auto after = storage.count<Category>();
    std::cout << "Categories after: " << after
        << (after == before ? " (rollback OK)" : " (rollback FAILED)") << "\n";

    auto found = storage.get_all<Category>(
        where(c(&Category::name) == "Rollback Cat"));
    std::cout << "  'Rollback Cat' in DB: " << found.size()
        << (found.empty() ? " (ok, rolled back)" : " (bad, committed)") << "\n";
}