#ifndef ARDUNOPROXYRECEIVER_H
#define ARDUNOPROXYRECEIVER_H

#include <QSerialPort>
#include <QString>

#include "streamingreceiver.h"

class ArduinoProxyReceiver : public StreamingReceiver {
 public:
  ArduinoProxyReceiver(const QString &port) {
    this->port = port;
    setup();
  }
  void setup();
  CanData askForNewData();
  virtual ~ArduinoProxyReceiver();

 private:
  QString port;
  QSerialPort *serial;
};

#endif  // ARDUNOPROXYRECEIVER_H
