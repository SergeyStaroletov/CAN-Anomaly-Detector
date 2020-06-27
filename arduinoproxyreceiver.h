#ifndef ARDUNOPROXYRECEIVER_H
#define ARDUNOPROXYRECEIVER_H

#include <QSerialPort>
#include <QString>

#include "streamingreceiver.h"

class ArduinoProxyReceiver : public StreamingReceiver {
 public:
  ArduinoProxyReceiver(const QString &port, CanQueue *dataToProcess) {
    this->port = port;
    this->dataToProcess = dataToProcess;
    setup();
  }
  void setup();
  CanData askForNewData();
  virtual ~ArduinoProxyReceiver();

 private:
  QString port;
  QSerialPort *serial;
  CanQueue *dataToProcess;
};

#endif  // ARDUNOPROXYRECEIVER_H
