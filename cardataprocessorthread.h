#ifndef CARDATAPROCESSORTHREAD_H
#define CARDATAPROCESSORTHREAD_H

#include <icardata.h>
#include <QThread>

class carDataProcessorThread : public QThread {
 public:
  carDataProcessorThread(ICarData *car, CanQueue *dataToProcess) {
    this->car = car;
    this->dataToProcess = dataToProcess;
  }
  void run();

 private:
  ICarData *car;
  CanQueue *dataToProcess;
};

#endif  // CARDATAPROCESSORTHREAD_H
