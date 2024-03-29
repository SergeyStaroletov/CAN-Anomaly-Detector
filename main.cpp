#include "anomalypredictorlstm.h"

#include <QCoreApplication>
#include <QString>
#include <iostream>
#include "anomalypredictor.h"
#include "anomalypredictorsltl.h"
#include "arduinoproxyreceiver.h"
#include "candumpreceiver.h"
#include "cardataprocessorthread.h"
#include "datareceiverthread.h"
#include "datarowfetcherthread.h"
#include "filereceiver.h"
#include "icardata.h"
#include "isltlproperty.h"
#include "lockers.h"
#include "mazda6cardata.h"
#include "speedincreasesafterrpmincreasesproperty.h"

int main(int argc, char *argv[]) {
  QCoreApplication app(argc, argv);

  // consts
  // const QString comPort = "/dev/ttyUSB0";
  const unsigned dataCapacity = 11000;
  const unsigned dataFetchInterval = 100;

  // our data queue
  CanQueue dataToProcess;
  std::deque<CarState> dataRows;
  Lockers::notifier = false;

  // objects

  // to load data from arduino-can shield
  // DataReceiver *dataRcv = new ArduinoProxyReceiver(comPort, &dataToProcess);

  // real CAN data
  // FileReceiver *dataRcv = new FileReceiver(
  //   QString("/Volumes/SD128/CAN_DATA_ARTICLE/usual_drive.csv"), &dataRows);

  // generated file
  // FileReceiver *dataRcv = new FileReceiver(
  //    QString("/Volumes/SD128/CAN_DATA_ARTICLE/bad_rpm.csv"), &dataRows);

  FileReceiver *dataRcv = new FileReceiver(
      QString("c:/work/LSTM-Neural-Network-for-Time-Series-Prediction/data/usual_drive.csv"), &dataRows);

  /*
  AnomalyPredictorSLTL *pred = new AnomalyPredictorSLTL();
  SpeedIncreasesAfterRPMIncreasesProperty *property =
      new SpeedIncreasesAfterRPMIncreasesProperty();
  // for now just to inform
  property->setFormula(
      "G(rpm > 1000 & temp > 60) & G[0,1000](rpm’ > 0) -> (G[1000,2000](v’ > "
      "0))");
  pred->attachProperty(property);*/

  AnomalyPredictorLSTM *pred = new AnomalyPredictorLSTM();


  dataRcv->attachPredictor(pred);

  ICarData *car = new Mazda6CarData();

  // threads
  DataReceiverThread drth(dataRcv, &dataToProcess);
  drth.start();
  carDataProcessorThread cdpth(car, &dataToProcess);
  cdpth.start();
  DataRowFetcherThread drft(dataFetchInterval, dataCapacity, car, &dataRows);
  drft.start();

  // loop
  app.exec();
}
