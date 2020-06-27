#ifndef DATARECEIVERTHREAD_H
#define DATARECEIVERTHREAD_H

#include <thread>
#include "datareceiver.h"

class DataReceiverThread {
 private:
  std::thread *impl;
  DataReceiver *receiver;
  CanQueue *dataToProcess;

  void runLoop();

 public:
  DataReceiverThread(DataReceiver *receiver);
};

#endif  // DATARECEIVERTHREAD_H
