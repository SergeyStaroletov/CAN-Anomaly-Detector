#include "lockers.h"

Lockers::Lockers() {}
std::mutex Lockers::monitor;
std::mutex Lockers::row_lock;
std::condition_variable Lockers::cond_var;
bool Lockers::notifier;
