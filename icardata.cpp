#include "icardata.h"

#include <algorithm>
#include <deque>
#include <iterator>
#include "lockers.h"

ICarData::ICarData() {}
ICarData::~ICarData(){};

void ICarData::registerProcessor(ProcessFunctor fun, int canId) {
  multiMap.insert(std::pair<int, ProcessFunctor>(canId, fun));
}

void ICarData::processData(CanQueue& data) {
  while (data.size() > 0) {
    Lockers::monitor.lock();
    CanData oneCan = data.front();
    data.pop_front();
    Lockers::monitor.unlock();

    auto it = multiMap.find(oneCan[0]);

    // execute processable function
    // forall functions
    while (it != multiMap.end()) {
      auto fun = it->second;
      // remove can id
      oneCan.erase(oneCan.begin());
      // apply function
      fun(oneCan);
      it++;
    }
  }
}
