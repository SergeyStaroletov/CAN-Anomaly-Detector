#include "arduinoproxyreceiver.h"

void ArduinoProxyReceiver::setup() {
  serial = new QSerialPort();
  serial->setPortName(port);

  serial->setBaudRate(115200);
  serial->setDataBits(QSerialPort::Data8);
  serial->setParity(QSerialPort::NoParity);
  serial->setStopBits(QSerialPort::OneStop);
  serial->setFlowControl(QSerialPort::NoFlowControl);

  serial->open(QIODevice::ReadWrite);
}

CanData ArduinoProxyReceiver::askForNewData() {
  //
  CanData d;
  return d;
}

ArduinoProxyReceiver::~ArduinoProxyReceiver() = default;
