#include <QString>
#include <iostream>
#include "arduinoproxyreceiver.h"
#include "candumpreceiver.h"
#include "datareceiverthread.h"

int main(int argc, char *argv[]) {
  DataReceiver *d = new ArduinoProxyReceiver(QString("/dev/USBtty0"));

  DataReceiverThread drth(d);

  int ok;
  std::cin >> ok;
}
