#include <iostream>
#include "db/Database.h"
#include "seed/SeedData.h"
#include "repository/CategoryRepository.h"
#include "service/NotificationManager.h"
#include "queries/Queries.h"
#include "transaction/TransactionDemo.h"
#include "comparison/SqliteCApiDemo.h"
#include "comparison/OrmDemo.h"

int main() {
    auto storage = makeStorage("notifications.db");
    storage.sync_schema();
    std::cout << "Schema synced OK\n";

    if (storage.count<Category>() == 0) {
        seedData(storage);
        std::cout << "Seed data inserted\n";
    }
    else {
        std::cout << "DB already has " << storage.count<Category>()
            << " categories, skipping seed\n";
    }

    std::cout << "Categories in DB: " << storage.count<Category>() << "\n";
    std::cout << "Notifications in DB: " << storage.count<Notification>() << "\n\n";

    CategoryRepository<decltype(storage)> repo(storage);
    ICategoryRepository& iface = repo;

    std::cout << "--- Repository demo ---\n";

    auto found = iface.getById(1);
    if (found) std::cout << "getById(1): " << found->name << "\n";

    std::cout << "getAll() size: " << iface.getAll().size() << "\n";

    Category newCat{ 0, "Test Category", "For demo", 3 };
    int newId = iface.add(newCat);
    std::cout << "add() -> id: " << newId << "\n";

    auto added = iface.getById(newId);
    if (added) {
        added->priority = 4;
        iface.update(*added);
        std::cout << "update() done\n";
    }

    iface.remove(newId);
    std::cout << "remove() done\n";
    std::cout << "getById after remove: "
        << (iface.getById(newId) ? "FOUND (bad)" : "NOT FOUND (ok)") << "\n";

    std::cout << "\n=== NotificationManager demo ===\n";
    NotificationManager<decltype(storage)> mgr(storage);
    std::cout << "Notifications for category 1: " << mgr.getByCategoryId(1).size() << "\n";
    std::cout << "Read ratio for category 2: " << mgr.getReadRatio(2) << "\n";

    queryFilter(storage);
    querySortLimit(storage);
    queryAggregate(storage);
    queryJoin(storage);
    transactionSuccess(storage);
    transactionRollback(storage);
    std::cout << "\n=== Comparison: SQLite C API vs sqlite_orm ===\n";
    Category cmp{ 0, "Comparison Cat", "cmp", 2 };

    int idC = addCategoryCApi("notifications.db", cmp);
    int idOrm = addCategoryOrm(storage, cmp);
    std::cout << "C API insert -> id = " << idC << "\n";
    std::cout << "ORM   insert -> id = " << idOrm << "\n";

    auto c1 = getCategoryCApi("notifications.db", idC);
    auto c2 = getCategoryOrm(storage, idOrm);
    std::cout << "C API getById(" << idC << "): "
        << (c1 ? c1->name : "NOT FOUND") << "\n";
    std::cout << "ORM   getById(" << idOrm << "): "
        << (c2 ? c2->name : "NOT FOUND") << "\n";

    storage.remove<Category>(idC);
    storage.remove<Category>(idOrm);
    std::cout << "Cleanup done\n";
    return 0;
}