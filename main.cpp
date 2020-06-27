#include <QCoreApplication>
#include <QString>
#include <iostream>
#include "arduinoproxyreceiver.h"
#include "candumpreceiver.h"
#include "datareceiverthread.h"

int main(int argc, char *argv[]) {
  QCoreApplication app(argc, argv);

  DataReceiver *d =
      new ArduinoProxyReceiver(QString("/dev/cu.wchusbserial1410"));

  DataReceiverThread drth(d);

  app.exec();

  // int ok;
  // std::cin >> ok;
}
