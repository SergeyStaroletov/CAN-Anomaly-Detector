#ifndef MAZDA6CARDATA_H
#define MAZDA6CARDATA_H

#include <deque>
#include <map>
#include <mutex>

#include "icardata.h"

class Mazda6CarData : public ICarData {
 public:
  Mazda6CarData();

  virtual int currentRPM() { return motorRPM; }
  virtual double currentSpeed() { return speed; }
  virtual double currentEngineTemp() { return engineTemp; }

  bool motorRpmProcessor(CanData data) {
    if (data.size() < 2) return false;
    motorRPM = int((data[0] * 256 + data[1]) / 3.6);
    return true;
  }

  bool speedProcessor(CanData data) {
    if (data.size() < 6) return false;

    speed = (((data[4] * 256) + data[5]) - 10000) / 100;
    return true;
  }

  bool tempProcessor(CanData data) {
    if (data.size() < 1) return false;

    engineTemp = data[0] - 15;
    return true;
  }

 protected:
  int motorRPM;
  double speed;
  double engineTemp;
  int gear;
};

#endif  // MAZDA6CARDATA_H
