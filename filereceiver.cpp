#include "filereceiver.h"
#include <icardata.h>
#include <QDateTime>
#include <QDebug>
#include <QDir>
#include <QStringList>
#include <QTextStream>
#include <QThread>
#include <cstring>
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
      std::memset(&state, 0, sizeof(state));

      QString ts = vals[0].replace("\"", "");
      QDateTime timestamp =
          QDateTime::fromString(ts, "yyyy-MM-dd HH:mm:ss.zzz");

      state.timestamp = timestamp.toMSecsSinceEpoch();

      state.speed = vals[1].toInt();
      state.rpm = vals[6].toInt();
      state.gear = vals[7].toInt();
      state.temp = vals[9].toInt();

      if (state.speed == 0 && state.rpm == 0 && state.temp == 0) continue;

      if (!firstRun) {
        unsigned diff = old.msecsTo(timestamp);

        // calculate the derivatives
        if (diff != 0) {
          state.speedDot = 1. * (state.speed - oldState.speed) / diff;
          state.rpmDot = 1. * (state.rpm - oldState.rpm) / diff;
          state.tempDot = 1. * (state.tempDot - oldState.tempDot) / diff;
        }

        QThread::msleep(diff / 2);  // we wait...
      }

      qDebug() << "Car state vector: <speed: " << state.speed
               << " rpm: " << state.rpm << " gear: " << state.gear << " temp: " << state.temp << ">\n";

      Lockers::row_lock.lock();
      // if (this->dataRows->size() == capacity) dataRows->pop_front();
      dataRows->push_back(state);
      Lockers::row_lock.unlock();

      // notify predictors
      for (AnomalyPredictor *p : this->attachedPredictors)
        p->getNewDataToPredict(state);

      old = timestamp;
      oldState.speed = state.speed;
      oldState.rpm = state.rpm;
      oldState.temp = state.temp;
      firstRun = false;
    }
    file.close();
  }

  return can;
}

FileReceiver::~FileReceiver() = default;
