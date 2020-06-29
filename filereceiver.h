#ifndef FILERECEIVER_H
#define FILERECEIVER_H

#include <QFile>
#include <QString>
#include "datareceiver.h"

class FileReceiver : public DataReceiver {
 public:
  FileReceiver(QString &path) {
    this->path = path;
    setup();
  };
  virtual CanData askForNewData();
  ~FileReceiver();

 private:
  void setup();
  QString path;
  QFile file;
};

#endif  // FILERECEIVER_H
