#ifndef ANOMALYPREDICTORSLTL_H
#define ANOMALYPREDICTORSLTL_H

#include "anomalypredictor.h"
#include "icardata.h"

class AnomalyPredictorSLTL : AnomalyPredictor {
 public:
  AnomalyPredictorSLTL();
  virtual void getNewDataToPredict(CarState carstate);
  virtual ~AnomalyPredictorSLTL();
};

#endif  // ANOMALYPREDICTORSLTL_H
