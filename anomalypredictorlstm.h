#ifndef ANOMALYPREDICATORLSTM_H
#define ANOMALYPREDICATORLSTM_H
#ifdef _WIN64
#define _hypot hypot
#include <cmath>
#endif
#include <Python.h>
#include <QFile>
#include <QTextStream>
#include <QBuffer>
#include <QMutex>
#include "anomalypredictor.h"
#include "icardata.h"



class AnomalyPredictorLSTM : public AnomalyPredictor {
 public:
  AnomalyPredictorLSTM();
  void createCSVFile();
  virtual void getNewDataToPredict(CarState carstate);
  ~AnomalyPredictorLSTM();

 private:
     PyObject *pName, *pModule, *pDict, *pClass, *pInstance;
  unsigned currentPoints;
  unsigned numPointsToPredict;
  QTextStream streamOut;
  QBuffer buffer;
  QFile fileOut;
  QMutex mut;
  bool busy;
};

#endif  // ANOMALYPREDICATORLSTM_H
