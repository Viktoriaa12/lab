cmake_minimum_required(VERSION 3.20)
project(NotificationSystemLab CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SqliteOrm CONFIG REQUIRED)
find_package(unofficial-sqlite3 CONFIG REQUIRED)

add_executable(NotificationSystemLab
    src/main.cpp
    src/queries/Queries.cpp
    src/transaction/TransactionDemo.cpp
    src/comparison/SqliteCApiDemo.cpp
    src/comparison/OrmDemo.cpp
)

target_include_directories(NotificationSystemLab PRIVATE src)

target_link_libraries(NotificationSystemLab PRIVATE
    sqlite_orm::sqlite_orm
    unofficial::sqlite3::sqlite3
)