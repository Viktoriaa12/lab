#pragma once
#include <vector>
#include "model/Category.h"
#include "model/Notification.h"

template<class Storage>
void seedData(Storage& storage) {
    std::vector<Category> categories = {
        {0, "System",     "System notifications",      1},
        {0, "Security",   "Security alerts",           5},
        {0, "Marketing",  "Promotional messages",      2},
        {0, "Support",    "User support messages",     3},
        {0, "Billing",    "Payment and invoices",      4}
    };
    for (auto& c : categories) storage.insert(c);

    std::vector<Notification> notifications = {
        {0, 1, "Server started",      "Server is up",            "2026-11-10T08:00:00", 1},
        {0, 1, "Server restart",      "Scheduled restart",       "2026-11-10T12:00:00", 0},
        {0, 1, "Disk space low",      "Only 10% left",           "2026-11-10T18:00:00", 0},
        {0, 2, "Login failed",        "3 failed attempts",       "2026-11-10T08:15:00", 0},
        {0, 2, "Password changed",    "Password updated",        "2026-11-10T11:00:00", 1},
        {0, 2, "Suspicious activity", "Unusual login location",  "2026-11-10T19:00:00", 0},
        {0, 3, "New promo",           "50% discount",            "2026-11-10T09:00:00", 1},
        {0, 3, "Newsletter",          "Monthly newsletter",      "2026-11-10T10:00:00", 1},
        {0, 3, "Black Friday",        "Huge sale",               "2026-11-10T17:00:00", 0},
        {0, 4, "Ticket created",      "New support ticket",      "2026-11-10T07:30:00", 1},
        {0, 4, "Ticket resolved",     "Ticket #123 resolved",    "2026-11-10T13:00:00", 1},
        {0, 4, "Feedback request",    "Please rate us",          "2026-11-10T16:00:00", 0},
        {0, 5, "Invoice paid",        "Invoice #456 paid",       "2026-11-10T09:45:00", 1},
        {0, 5, "Payment failed",      "Card declined",           "2026-11-10T14:00:00", 0},
        {0, 5, "Subscription renewed","Auto-renewal done",       "2026-11-10T20:00:00", 0}
    };
    for (auto& n : notifications) storage.insert(n);
}