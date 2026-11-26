#include "queries/Queries.h"
#include <iostream>
#include <sqlite_orm/sqlite_orm.h>

using namespace sqlite_orm;

// 1. Фільтрація: непрочитані сповіщення
void queryFilter(decltype(makeStorage(""))& storage) {
    std::cout << "\n--- Query 1: Filter (unread notifications) ---\n";
    auto rows = storage.get_all<Notification>(where(c(&Notification::read_flag) == 0));
    for (auto& n : rows) {
        std::cout << "  id=" << n.id
            << " category_id=" << n.category_id
            << " title=" << n.title << "\n";
    }
}

// 2. Сортування + ліміт: 5 найновіших сповіщень
void querySortLimit(decltype(makeStorage(""))& storage) {
    std::cout << "\n--- Query 2: Sort by created_at DESC, limit 5 ---\n";
    auto rows = storage.get_all<Notification>(
        order_by(&Notification::created_at).desc(),
        limit(5)
    );
    for (auto& n : rows) {
        std::cout << "  " << n.created_at << " | " << n.title << "\n";
    }
}

// 3. Агрегація: кількість прочитаних + сума пріоритетів категорій
void queryAggregate(decltype(makeStorage(""))& storage) {
    std::cout << "\n--- Query 3: Aggregate ---\n";
    auto readCount = storage.count<Notification>(where(c(&Notification::read_flag) == 1));
    std::cout << "  COUNT(read notifications) = " << readCount << "\n";

    auto sumPriority = storage.sum(&Category::priority);
    std::cout << "  SUM(category priority) = "
        << (sumPriority ? *sumPriority : 0) << "\n";
}

// 4. JOIN: назва категорії + заголовок сповіщення + час
void queryJoin(decltype(makeStorage(""))& storage) {
    std::cout << "\n--- Query 4: JOIN categories + notifications ---\n";
    auto rows = storage.select(
        columns(&Category::name, &Notification::title, &Notification::created_at),
        inner_join<Notification>(on(c(&Category::id) == &Notification::category_id))
    );
    for (auto& row : rows) {
        std::cout << "  " << std::get<0>(row)
            << " | " << std::get<1>(row)
            << " | " << std::get<2>(row) << "\n";
    }
}