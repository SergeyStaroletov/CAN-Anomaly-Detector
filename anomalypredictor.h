#ifndef ANOMALYPREDICTOR_H
#define ANOMALYPREDICTOR_H

#include "icardata.h"

class AnomalyPredictor {
 public:
  AnomalyPredictor(){};
  virtual void getNewDataToPredict(CarState carstate) = 0;
  virtual ~AnomalyPredictor();
};

#endif  // ANOMALYPREDICTOR_H
