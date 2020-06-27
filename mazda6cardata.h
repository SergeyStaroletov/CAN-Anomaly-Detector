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
    motorRPM = (data[4] + (data[5] << 8)) - (512 * (data[5] & 0x80));
    return true;
  }

  bool speedProcessor(CanData data) {
    speed = 0.1 * (data[2] + ((data[3] & 0x0F) << 8));
    return true;
  }

  bool tempProcessor(CanData data) {
    // Negative terminal temperature degrees C
    if ((data[6] > 0)) engineTemp = ((data[6] + ((data[7] & 0x07) << 8))) * 0.1;
    return (data[6] > 0);
  }

 protected:
  int motorRPM;
  double speed;
  double engineTemp;
};

#endif  // MAZDA6CARDATA_H
