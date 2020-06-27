#include <QCoreApplication>
#include <QString>
#include <iostream>
#include "arduinoproxyreceiver.h"
#include "candumpreceiver.h"
#include "datareceiverthread.h"
#include "icardata.h"
#include "mazda6cardata.h"

int main(int argc, char *argv[]) {
  QCoreApplication app(argc, argv);

  // our data queue
  CanQueue dataToProcess;

  // objects
  DataReceiver *dataRcv =
      new ArduinoProxyReceiver(QString("/dev/ttyUSB0"), &dataToProcess);
  ICarData *car = new Mazda6CarData();

  // threads
  DataReceiverThread drth(dataRcv, &dataToProcess);
  drth.start();

  // loop
  app.exec();
}
