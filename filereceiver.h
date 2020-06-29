#ifndef FILERECEIVER_H
#define FILERECEIVER_H

#include <QFile>
#include <QString>
#include <deque>
#include "datareceiver.h"

class FileReceiver : public DataReceiver {
 public:
  FileReceiver(const QString &path, std::deque<CarState> *dataRows) {
    this->path = path;
    this->dataRows = dataRows;
    setup();
  };
  virtual CanData askForNewData();
  ~FileReceiver();

 private:
  void setup();
  QString path;
  QFile file;
  std::deque<CarState> *dataRows;
};

#endif  // FILERECEIVER_H
