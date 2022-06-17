#include "anomalypredictorlstm.h"
#include <Python.h>
#include <pythonrun.h>
#include <QDateTime>
#include <QDebug>
#include <QFile>
#include <QBuffer>

void AnomalyPredictorLSTM::createCSVFile() {
  buffer.open(QBuffer::ReadWrite);
  streamOut.setDevice(&buffer);
  busy = false;
}

AnomalyPredictorLSTM::AnomalyPredictorLSTM() {
 numPointsToPredict = 200;//11000;

 currentPoints = 0;
  // initialize python embedding

  Py_Initialize();
  qDebug() << "python init ok";

  pName = NULL;
  pModule = NULL;
  pDict = NULL;
  pClass = NULL;
  pInstance = NULL;

  // Build the name object
  pName = PyUnicode_FromString("LSTMAnomaly");
  Py_INCREF(pName);

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
  Py_INCREF(pModule);


  qDebug() << "python import ok";

  // pDict is a borrowed reference
  pDict = PyModule_GetDict(pModule);

  pClass = PyDict_GetItemString(pDict, "LSTMAnomaly"); //LSTMAnomaly
  Py_INCREF(pClass);


  if (PyCallable_Check(pClass)) {
    pInstance = PyObject_CallObject(pClass, NULL);
  } else {
      qDebug() << "!! no py instance";
  exit(1);
  }

  Py_INCREF(pInstance);

  //pInstance = PyInstanceMethod_New(pClass);

  if (!pInstance) {
      qDebug() << "no py new";
      exit(1);
  }

  // Call a method of the class to setup
  PyObject *pValue = PyObject_CallMethod(pInstance, "setup", NULL);

  if (!pValue) {
      qDebug() << "setup not called";
      exit(1);
  }

  Py_DECREF(pValue);


  createCSVFile();
}

void AnomalyPredictorLSTM::getNewDataToPredict(CarState carstate) {
  // store all needed data into an input csv file
  mut.lock();
  currentPoints++;

  QString timestamp = QDateTime::fromMSecsSinceEpoch(carstate.timestamp)
                          .toString("yyyy-MM-dd HH:mm:ss.zzz");



  streamOut << timestamp << "," << carstate.speed << "," << carstate.rpm << ","
            << carstate.temp << "," << carstate.gear << "\n";
  mut.unlock();


  // we got a sufficient number of points to run the detector
  if (!busy && currentPoints >= numPointsToPredict) {
      currentPoints = 0;
    //streamOut.reset();
    //fileOut.close();
    mut.lock();

    QByteArray data = buffer.buffer();
    QFile file("data/input.csv");
    file.open(QIODevice::WriteOnly);
    file.write("timestamp,vehicle_speed,vehicle_rpm,engine_temp,gear\n");
    file.write(data);
    file.close();
    buffer.close();
    buffer.open(QBuffer::WriteOnly);

    mut.unlock();

    // todo: run in a mulithreaded task

    // Call a method of the  python class to predict
    qDebug() << "!!! RUN predict  !!!";
    busy = true;

    PyObject *pValue = PyObject_CallMethod(pInstance, "predict", NULL);

    if (pValue) {
    //int ret = PyLong_AsLong(pValue);  // get the result
    int ret = 0;
    Py_DECREF(pValue);
      if (ret > 0) {
        qDebug()
            << "LSTM anomaly for last " << numPointsToPredict
            << " points detected at "
            << QDateTime::fromMSecsSinceEpoch(carstate.timestamp).toString();
      } else {
          qDebug() << "no anomalies!";
      }
    } else {
        qDebug() << "!!! NULL predict";
        //std::perror("hi");
        PyObject *ptype, *pvalue, *ptraceback;
        PyErr_Fetch(&ptype, &pvalue, &ptraceback);
        //pvalue contains error message
        //ptraceback contains stack snapshot and many other information
        //(see python traceback structure)

        //Get error message
        char *pStrErrorMessage = Py_STRINGIFY(ptraceback);

        qDebug() << pStrErrorMessage;


        exit(1);
    }
    busy = false;
    qDebug() << "!!! DONE predict  !!!";


    // next iteration
    //createCSVFile();
    currentPoints = 0;
  }
}

AnomalyPredictorLSTM::~AnomalyPredictorLSTM() = default;
