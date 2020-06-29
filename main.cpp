#include <QCoreApplication>
#include <QString>
#include <iostream>
#include "arduinoproxyreceiver.h"
#include "candumpreceiver.h"
#include "cardataprocessorthread.h"
#include "datareceiverthread.h"
#include "datarowfetcherthread.h"
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
  Lockers::notifier = false;

  // objects
  DataReceiver *dataRcv = new ArduinoProxyReceiver(comPort, &dataToProcess);
  ICarData *car = new Mazda6CarData();

  // threads
  DataReceiverThread drth(dataRcv, &dataToProcess);
  drth.start();
  carDataProcessorThread cdpth(car, &dataToProcess);
  cdpth.start();
  DataRowFetcherThread drft(dataFetchInterval, dataCapacity, car);
  drft.start();

  // loop
  app.exec();
}
