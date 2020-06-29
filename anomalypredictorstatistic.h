#ifndef ANOMALYPREDICTORSTATISTIC_H
#define ANOMALYPREDICTORSTATISTIC_H
#include "anomalypredictor.h"

class AnomalyPredictorStatistic : public AnomalyPredictor {
 public:
  AnomalyPredictorStatistic();
  virtual void getNewDataToPredict(CarState carstate);
  virtual ~AnomalyPredictorStatistic();
};

#endif  // ANOMALYPREDICTORSTATISTIC_H
