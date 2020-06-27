#ifndef CARDATAPROCESSORTHREAD_H
#define CARDATAPROCESSORTHREAD_H

#include <icardata.h>
#include <QThread>

class carDataProcessorThread : public QThread {
 public:
  carDataProcessorThread(ICarData *car) { this->car = car; }
  void run();

 private:
  ICarData *car;
};

#endif  // CARDATAPROCESSORTHREAD_H
