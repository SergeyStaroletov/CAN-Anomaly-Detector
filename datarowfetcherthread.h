#ifndef DATAROWFETCHERTHREAD_H
#define DATAROWFETCHERTHREAD_H

#include <QThread>
#include <deque>
#include "icardata.h"

class DataRowFetcherThread : public QThread {
 public:
  DataRowFetcherThread(unsigned latency, unsigned capacity, ICarData *car) {
    this->car = car;
    this->latency = latency;
    this->capacity = capacity;
  }
  void run();

 private:
  unsigned latency;
  unsigned capacity;
  std::deque<CarState> dataRows;

  ICarData *car;
};

#endif  // DATAROWFETCHERTHREAD_H
