#ifndef ICARDATA_H
#define ICARDATA_H

#include <deque>
#include <functional>
#include <map>
#include <mutex>
#include <vector>

// function (int [], bool) -> void
typedef std::function<bool(std::vector<int>)> ProcessFunctor;
typedef std::vector<int> CanData;
typedef std::deque<CanData> CanQueue;
typedef struct {
  unsigned long timestamp;
  int rpm;
  double speed;
  double temp;
} CarState;

class ICarData {
 public:
  ICarData();

  virtual ~ICarData();
  virtual int currentRPM() = 0;
  virtual double currentSpeed() = 0;
  virtual double currentEngineTemp() = 0;

  // for register CAN handlers
  void processData(CanQueue& data);
  void registerProcessor(ProcessFunctor, int canId);

 private:
  std::multimap<int, ProcessFunctor> multiMap;
};

#endif  // ICARDATA_H
