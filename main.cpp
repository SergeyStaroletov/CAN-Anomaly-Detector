#include <iostream>
#include "arduinoproxyreceiver.h"
#include "candumpreceiver.h"
#include "datareceiverthread.h"

int main(int argc, char *argv[]) {
  DataReceiver *d = new ArduinoProxyReceiver();

  DataReceiverThread drth(d);

  int ok;
  std::cin >> ok;
}
