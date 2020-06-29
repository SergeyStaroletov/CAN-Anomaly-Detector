#include <QCoreApplication>
#include <QString>
#include <iostream>
#include "arduinoproxyreceiver.h"
#include "candumpreceiver.h"
#include "cardataprocessorthread.h"
#include "datareceiverthread.h"
#include "datarowfetcherthread.h"
#include "filereceiver.h"
#include "icardata.h"
#include "lockers.h"
#include "mazda6cardata.h"

int main(int argc, char *argv[]) {
  QCoreApplication app(argc, argv);

  // consts
  const QString comPort = "/dev/ttyUSB0";
  const unsigned dataCapacity = 11000;
  const unsigned dataFetchInterval = 100;

  // our data queue
  CanQueue dataToProcess;
  std::deque<CarState> dataRows;
  Lockers::notifier = false;

  // objects
  // DataReceiver *dataRcv = new ArduinoProxyReceiver(comPort, &dataToProcess);
  DataReceiver *dataRcv = new FileReceiver(
      QString("/Volumes/SD128/CAN_DATA_ARTICLE/usual_drive.csv"), &dataRows);

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
