#pragma once
#include "model/Notification.h"
#include <vector>
#include <sqlite_orm/sqlite_orm.h>

template<class Storage>
class NotificationManager {
    Storage& storage_;
public:
    explicit NotificationManager(Storage& storage) : storage_(storage) {}

    int addNotification(const Notification& n) {
        return storage_.insert(n);
    }

    std::vector<Notification> getByCategoryId(int categoryId) {
        using namespace sqlite_orm;
        return storage_.get_all<Notification>(
            where(c(&Notification::category_id) == categoryId));
    }

    double getReadRatio(int categoryId) {
        using namespace sqlite_orm;
        auto total = storage_.count<Notification>(
            where(c(&Notification::category_id) == categoryId));
        if (total == 0) return 0.0;
        auto readCount = storage_.count<Notification>(
            where(c(&Notification::category_id) == categoryId
                and c(&Notification::read_flag) == 1));
        return static_cast<double>(readCount) / static_cast<double>(total);
    }
};