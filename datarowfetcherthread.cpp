#include "datarowfetcherthread.h"

#include <QDebug>
#include "lockers.h"

void DataRowFetcherThread::run() {
  while (true) {
    // wait for a new portion of data
    QThread::msleep(this->latency);

    CarState state;
    state.rpm = this->car->currentRPM();
    state.speed = this->car->currentSpeed();
    state.temp = this->car->currentEngineTemp();

    if (state.speed == 0 && state.rpm == 0 && state.temp == 0) continue;

    qDebug() << "Car state vector: <speed: " << state.speed
             << " rpm: " << state.rpm << " temp: " << state.temp << ">\n";

    Lockers::row_lock.lock();
    if (this->dataRows->size() == capacity) dataRows->pop_front();
    dataRows->push_back(state);
    Lockers::row_lock.unlock();
  }
}
