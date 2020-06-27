#include "arduinoproxyreceiver.h"
#include <QCoreApplication>
#include <QDateTime>
#include <QDebug>
#include <QThread>

void ArduinoProxyReceiver::setup() {
  qDebug() << "Opening serial...\n";
  serial = new QSerialPort();
  serial->setPortName(port);

  serial->setBaudRate(115200);
  serial->setDataBits(QSerialPort::Data8);
  serial->setParity(QSerialPort::NoParity);
  serial->setStopBits(QSerialPort::OneStop);
  serial->setFlowControl(QSerialPort::NoFlowControl);

  if (!serial->open(QIODevice::ReadWrite)) {
    qDebug() << "bad serial \n";
    QCoreApplication::exit();
  }

  // data to send magic configuration
  unsigned char sendData[4] = {0x19, 0x84, 0, 0};
  sendData[3] = 3;  // 500

  const char *sending = reinterpret_cast<char *>(sendData);

  QByteArray resp;

  qDebug() << "waiting Arduino to be ready...\n";

  QString outputMsg = "";
  do {
    QCoreApplication::processEvents();
    if (serial->bytesAvailable() > 30) {
      QByteArray data = serial->readAll();
      if (data.length() > 0) resp.append(data);
      outputMsg = QString::fromStdString(resp.toStdString());
    }
  } while (outputMsg.indexOf("\n") < 0);

  QThread::msleep(1000);
  serial->readAll();
  serial->flush();
  // sending setup data buffer
  serial->write(QByteArray::fromRawData(sending, sizeof(sendData)));
  serial->waitForBytesWritten(1000);
  QCoreApplication::processEvents();
  serial->flush();
  serial->waitForReadyRead(100);

  qDebug() << "waiting the reply...\n";
  // waiting the reply
  QDateTime timeStart = QDateTime::currentDateTime();
  resp.clear();
  do {
    QCoreApplication::processEvents();
    // if (serial->bytesAvailable() > 0) {
    QByteArray data = serial->readAll();

    if (data.length() > 0) {
      resp.append(data);
      qDebug() << data;
    }
    outputMsg = QString::fromStdString(resp.toStdString());

    if (timeStart.secsTo(QDateTime::currentDateTime()) > 5) {
      outputMsg = "Init fail with timeout. Try again.";
      break;
    }

  } while ((outputMsg.indexOf("init ok") < 0) &&
           (outputMsg.indexOf("init fail") < 0));

  serial->flush();

  if (outputMsg.indexOf("init ok") > 0) {
    qDebug() << "Init COM port OK \n";
  } else {
    qDebug() << "Init COM port NOT OK \n";
    QCoreApplication::exit();
  }
}

/*
 *
 */
CanData ArduinoProxyReceiver::askForNewData() {
  //

  static int nTries;

  bool isStopped = false;

  QByteArray data;
  QString dataRep;
  QString dataToProcess;

  // pass all data to /n
  int indexOf = -1;
  do {
    QByteArray data0 = serial->readAll();
    if (data0.length() > 0) data.append(data0);
    dataRep = QString::fromStdString(data.toStdString());
    // qDebug() << dataRep << "\n";
    indexOf = dataRep.indexOf("\n");
  } while (indexOf < 0);

  // we get from \n to end (start of new substring)
  dataToProcess = dataRep.mid(indexOf + 1);

  data.clear();
  data.append(dataToProcess);

  do {
    QDateTime timeStartGetting = QDateTime::currentDateTime();
    QString sendMe;
    QThread::msleep(1);

    int runn = 0;
    do {
      QCoreApplication::processEvents();

      QThread::msleep(10);

      do {
        QThread::msleep(0);

        QByteArray data0 = serial->readAll();
        if (data0.length() > 0) data.append(data0);
        dataRep = QString::fromStdString(data.toStdString());
        indexOf = dataRep.indexOf("\n");
      } while (indexOf < 0);
      QString dataToProcessNext = dataRep.mid(indexOf + 1);

      data.clear();
      data.append(dataToProcessNext);

      // process data
      sendMe += dataRep;
      runn++;
      break;
    } while (timeStartGetting.msecsTo(QDateTime::currentDateTime()) <
             100);  // collect all data for not more than 100ms

    qDebug() << dataRep << "\n";
    // send signal with data collected in 100ms period

  } while (!isStopped);

  CanData d;
  return d;
}

ArduinoProxyReceiver::~ArduinoProxyReceiver() = default;
