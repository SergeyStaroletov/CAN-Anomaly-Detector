#ifndef DATAROWFETCHERTHREAD_H
#define DATAROWFETCHERTHREAD_H

#include <QThread>
#include "icardata.h"

class DataRowFetcherThread : public QThread {
 public:
  DataRowFetcherThread(unsigned short latency, ICarData *car) {
    this->car = car;
    this->latency = latency;
  }
  void run();

 private:
  unsigned short latency;
  ICarData *car;
};

#endif  // DATAROWFETCHERTHREAD_H
