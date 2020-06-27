#include <QCoreApplication>
#include <QString>
#include <iostream>
#include "arduinoproxyreceiver.h"
#include "candumpreceiver.h"
#include "datareceiverthread.h"

int main(int argc, char *argv[]) {
  QCoreApplication app(argc, argv);

  DataReceiver *d = new ArduinoProxyReceiver(QString("/dev/ttyUSB0"));

  DataReceiverThread drth(d);
  drth.start();

  app.exec();

  // int ok;
  // std::cin >> ok;
}
