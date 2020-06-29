#include "filereceiver.h"
#include <QDir>
#include <QTextStream>

void FileReceiver::setup() { file.setFileName(this->path); }

CanData FileReceiver::askForNewData() {
  CanData can;

  if (file.open(QIODevice::ReadOnly)) {
    QTextStream in(&file);
    while (!in.atEnd()) {
      QString line = in.readLine();
    }
    file.close();
  }

  return can;
}

FileReceiver::~FileReceiver() = default;
