#include "anomalypredictorlstm.h"
#include <Python.h>
#include <pythonrun.h>
#include <QDateTime>
#include <QDebug>
#include <QFile>

void AnomalyPredictorLSTM::createCSVFile() {
  fileOut.setFileName("input.csv");
  fileOut.open(QFile::WriteOnly);
  streamOut.setDevice(&fileOut);
  streamOut << "timestamp,vehicle_speed,vehicle_rpm,engine_temp\n";
}

AnomalyPredictorLSTM::AnomalyPredictorLSTM() {
  currentPoints = 11000;

  // initialize python embedding

  Py_Initialize();

  qDebug() << "python init ok";

  pName = NULL;
  pModule = NULL;
  pDict = NULL;
  pClass = NULL;
  pInstance = NULL;
  pValue = NULL;

  // Build the name object
  pName = PyUnicode_FromString("LSTMAnomaly");

  if (!pName) {
    qDebug() << "wrong python file";
    exit(1);
  }

  // Load the module object
  pModule = PyImport_Import(pName);

  if (!pModule) {
    qDebug() << "wrong python module";
    exit(1);
  }

  qDebug() << "python import ok";

  // pDict is a borrowed reference
  pDict = PyModule_GetDict(pModule);

  pClass = PyDict_GetItemString(pDict, "LSTMAnomaly");

  if (PyCallable_Check(pClass)) {
    pInstance = PyObject_CallObject(pClass, NULL);
  }

  // Call a method of the class to setup
  pValue = PyObject_CallMethod(pInstance, "setup", NULL);

  createCSVFile();
}

void AnomalyPredictorLSTM::getNewDataToPredict(CarState carstate) {
  // store all needed data into an input csv file
  currentPoints++;

  QString timestamp = QDateTime::fromMSecsSinceEpoch(carstate.timestamp)
                          .toString("yyyy-MM-dd HH:mm:ss.zzz");

  streamOut << timestamp << "," << carstate.speed << "," << carstate.rpm << ","
            << carstate.temp << "\n";

  // we got a sufficient number of points to run the detector
  if (currentPoints >= numPointsToPredict) {
    fileOut.close();

    // todo: run in a mulithreaded task

    // Call a method of the  python class to predict
    pValue = PyObject_CallMethod(pInstance, "predict", NULL);
    if (pValue != NULL) {
      int ret = PyLong_AsLong(pValue);  // get the result
      Py_DECREF(pValue);
      if (ret > 0) {
        qDebug()
            << "LSTM anomaly for last " << numPointsToPredict
            << " points detected at "
            << QDateTime::fromMSecsSinceEpoch(carstate.timestamp).toString();
      }
    }

    // next iteration
    createCSVFile();
    currentPoints = 0;
  }
}

AnomalyPredictorLSTM::~AnomalyPredictorLSTM() = default;
