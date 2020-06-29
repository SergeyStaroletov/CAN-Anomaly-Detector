#include "filereceiver.h"
#include <icardata.h>
#include <QDateTime>
#include <QDebug>
#include <QDir>
#include <QStringList>
#include <QTextStream>
#include <QThread>
#include "lockers.h"

void FileReceiver::setup() { file.setFileName(this->path); }

CanData FileReceiver::askForNewData() {
  CanData can;

  if (file.open(QIODevice::ReadOnly)) {
    QTextStream in(&file);
    in.readLine();  // caption

    QDateTime old;
    bool firstRun = true;
    while (!in.atEnd()) {
      QString line = in.readLine();
      QStringList vals = line.split(",");
      if (vals.size() < 10) continue;

      CarState state;

      QString ts = vals[0].replace("\"", "");
      QDateTime timestamp =
          QDateTime::fromString(ts, "yyyy-MM-dd HH:mm:ss.zzz");

      if (!firstRun) {
        unsigned diff = old.msecsTo(timestamp);
        QThread::msleep(diff / 2);  // we wait...
      }
      state.timestamp = timestamp.toTime_t();

      state.speed = vals[1].toInt();
      state.rpm = vals[6].toInt();
      state.temp = vals[9].toInt();

      qDebug() << "Car state vector: <speed: " << state.speed
               << " rpm: " << state.rpm << " temp: " << state.temp << ">\n";

      Lockers::row_lock.lock();
      // if (this->dataRows->size() == capacity) dataRows->pop_front();
      dataRows->push_back(state);
      Lockers::row_lock.unlock();

      old = timestamp;
      firstRun = false;
    }
    file.close();
  }

  return can;
}

FileReceiver::~FileReceiver() = default;
