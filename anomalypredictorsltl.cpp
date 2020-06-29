#include "anomalypredictorsltl.h"
#include <QDateTime>
#include <QDebug>
#include "icardata.h"

enum state { start, rpm_greater_1000, rpm_dot_greater_0, speed_dotg_greater_0 };

state currentState;
unsigned t;
unsigned tRpmDot;
bool once = false;

AnomalyPredictorSLTL::AnomalyPredictorSLTL() {
  currentState = start;
  t = 0;
}

void AnomalyPredictorSLTL::getNewDataToPredict(CarState carstate) {
  bool RPMOk = (carstate.rpm > 1000) && (carstate.temp > 60);

  if (currentState == start) {
    if (RPMOk) {
      t = carstate.timestamp;
      once = false;
      currentState = rpm_greater_1000;
      return;
    }
    if (currentState == rpm_greater_1000) {
      if (!RPMOk) {
        currentState = start;
        return;
      }
      if (carstate.rpmDot >= 0 && (carstate.timestamp - t) > 1000) {
        currentState = rpm_dot_greater_0;
        return;
      }
      if (carstate.rpmDot < 0) {
        currentState = start;
        return;
      }
    }
    if (currentState == rpm_dot_greater_0) {
      if (!RPMOk) {
        currentState = start;
        return;
      }
      if (carstate.speedDot >= 0 && once && (carstate.timestamp - t) > 2000) {
        qDebug() << "Property holds!\n";
      }
      if (carstate.speedDot > 0) once = true;
      if (carstate.speedDot < 0) {
        qDebug() << "!!!Property violation at "
                 << QDateTime::fromTime_t(carstate.timestamp).toString();
      }
    }
  }
}

AnomalyPredictorSLTL::~AnomalyPredictorSLTL() = default;
