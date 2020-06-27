#include "datarowfetcherthread.h"

#include <QDebug>

void DataRowFetcherThread::run() {
  while (true) {
    // wait for a new portion of data
    QThread::msleep(this->latency);

    int rpm = this->car->currentRPM();
    double speed = this->car->currentSpeed();
    int temp = this->car->currentEngineTemp();

    qDebug() << "speed: " << speed << " rpm: " << rpm << " temp: " << temp
             << "\n";
  }
}
