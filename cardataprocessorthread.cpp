#include "cardataprocessorthread.h"

#include <condition_variable>
#include <mutex>
#include <thread>
#include "lockers.h"

void carDataProcessorThread::run() {
  std::mutex mut;
  std::unique_lock<std::mutex> lock(mut);
  while (true) {
    while (!Lockers::notifier) {
      Lockers::cond_var.wait(lock);
    }
    car->processData(*dataToProcess);
    Lockers::notifier = false;
  }
}
