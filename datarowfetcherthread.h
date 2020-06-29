#ifndef DATAROWFETCHERTHREAD_H
#define DATAROWFETCHERTHREAD_H

#include <QThread>
#include <deque>
#include "icardata.h"

class DataRowFetcherThread : public QThread {
 public:
  DataRowFetcherThread(unsigned latency, unsigned capacity, ICarData *car,
                       std::deque<CarState> *dataRows) {
    this->car = car;
    this->latency = latency;
    this->capacity = capacity;
    this->dataRows = dataRows;
  }
  void run();

 private:
  unsigned latency;
  unsigned capacity;
  std::deque<CarState> *dataRows;

  ICarData *car;
};

#endif  // DATAROWFETCHERTHREAD_H
