#ifndef DATARECEIVER_H
#define DATARECEIVER_H

#include "icardata.h"

class DataReceiver {
 public:
  DataReceiver(){};
  virtual CanData askForNewData() = 0;
  virtual ~DataReceiver();
};

#endif  // DATARECEIVER_H
