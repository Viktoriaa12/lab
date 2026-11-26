#pragma once
#include "db/Database.h"

void queryFilter(decltype(makeStorage(""))& storage);
void querySortLimit(decltype(makeStorage(""))& storage);
void queryAggregate(decltype(makeStorage(""))& storage);
void queryJoin(decltype(makeStorage(""))& storage);