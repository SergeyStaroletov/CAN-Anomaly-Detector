#include "datareceiverthread.h"
#include <QThread>
#include <QtConcurrent>
#include "icardata.h"
#include "lockers.h"

void DataReceiverThread::run() {
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
  this->receiver = receiver;
  qDebug() << "creating a thread to handle data...\n";
  // impl = new std::thread(&DataReceiverThread::runLoop, this);

  // QThread *t = QThread::create(std::bind(&DataReceiverThread::runLoop,
  // this)); t->start(); QtConcurrent::run(this, &DataReceiverThread::runLoop);

  // t->wait();
  // impl->join();
}
