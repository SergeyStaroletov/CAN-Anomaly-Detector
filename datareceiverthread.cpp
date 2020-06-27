#include "datareceiverthread.h"
#include "icardata.h"
#include "lockers.h"

void DataReceiverThread::runLoop() {
  while (true) {
    CanData can = receiver->askForNewData();
    Lockers::monitor.lock();
    this->dataToProcess->push_back(can);
    Lockers::monitor.unlock();
    // notify
    Lockers::notifier = true;
    Lockers::cond_var.notify_one();
  }
}

DataReceiverThread::DataReceiverThread(DataReceiver *receiver) {
  impl = new std::thread(&DataReceiverThread::runLoop, this);
}
