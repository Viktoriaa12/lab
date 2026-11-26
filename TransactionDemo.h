#pragma once
#include "db/Database.h"

void transactionSuccess(decltype(makeStorage(""))& storage);
void transactionRollback(decltype(makeStorage(""))& storage);