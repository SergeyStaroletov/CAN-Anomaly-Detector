#include "filereceiver.h"
#include <QDir>

void FileReceiver::setup() {}

CanData FileReceiver::askForNewData() {
  CanData can;

  while (true) {
    // tbd
  }

  return can;
}

FileReceiver::~FileReceiver() = default;
