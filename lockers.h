#ifndef LOCKERS_H
#define LOCKERS_H

#include <condition_variable>
class Lockers {
 public:
  Lockers();
  static std::condition_variable cond_var;
  static std::mutex monitor;
  static bool notifier;
};

#endif  // LOCKERS_H
