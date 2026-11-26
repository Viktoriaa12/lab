#pragma once
#include <string>

struct Notification {
    int id = 0;
    int category_id = 0;
    std::string title;
    std::string message;
    std::string created_at;
    int read_flag = 0;
};