#ifndef ANOMALYPREDICATORLSTM_H
#define ANOMALYPREDICATORLSTM_H
#include <Python.h>
#include <QFile>
#include <QTextStream>
#include "anomalypredictor.h"
#include "icardata.h"

class AnomalyPredictorLSTM : public AnomalyPredictor {
 public:
  AnomalyPredictorLSTM();
  void createCSVFile();
  virtual void getNewDataToPredict(CarState carstate);
  ~AnomalyPredictorLSTM();

 private:
  PyObject *pName, *pModule, *pDict, *pClass, *pInstance, *pValue;
  unsigned currentPoints;
  unsigned numPointsToPredict;
  QTextStream streamOut;
  QFile fileOut;
};

#endif  // ANOMALYPREDICATORLSTM_H
