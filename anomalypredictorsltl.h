#ifndef ANOMALYPREDICTORSLTL_H
#define ANOMALYPREDICTORSLTL_H

#include "anomalypredictor.h"
#include "icardata.h"

enum state { start, rpm_greater_1000, rpm_dot_greater_0, speed_dotg_greater_0 };

class AnomalyPredictorSLTL : public AnomalyPredictor {
 public:
  AnomalyPredictorSLTL();
  virtual void getNewDataToPredict(CarState carstate);
  virtual ~AnomalyPredictorSLTL();

 private:
  state currentState;
  unsigned long t;
  bool once = false;
};

#endif  // ANOMALYPREDICTORSLTL_H
