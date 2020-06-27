#ifndef ARDUNOPROXYRECEIVER_H
#define ARDUNOPROXYRECEIVER_H

#include "streamingreceiver.h"

class ArduinoProxyReceiver : public StreamingReceiver {
 public:
  ArduinoProxyReceiver(){};
  CanData askForNewData();
  virtual ~ArduinoProxyReceiver();
};

#endif  // ARDUNOPROXYRECEIVER_H
