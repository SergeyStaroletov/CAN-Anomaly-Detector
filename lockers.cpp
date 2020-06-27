#include "lockers.h"

Lockers::Lockers() {}
std::mutex Lockers::monitor;
std::condition_variable Lockers::cond_var;
bool Lockers::notifier;
