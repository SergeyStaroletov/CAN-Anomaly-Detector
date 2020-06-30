#ifndef FILERECEIVER_H
#define FILERECEIVER_H

#include <QFile>
#include <QString>
#include <deque>
#include <vector>
#include "anomalypredictor.h"
#include "datareceiver.h"

class FileReceiver : public DataReceiver {
 public:
  FileReceiver(const QString &path, std::deque<CarState> *dataRows) {
    this->path = path;
    this->dataRows = dataRows;
    setup();
  };
  void attachPredictor(AnomalyPredictor *predictor) {
    attachedPredictors.push_back(predictor);
  };
  virtual CanData askForNewData();
  ~FileReceiver();

 private:
  void setup();
  QString path;
  QFile file;
  std::deque<CarState> *dataRows;
  CarState oldState;
  std::vector<AnomalyPredictor *> attachedPredictors;
};

#endif  // FILERECEIVER_H
