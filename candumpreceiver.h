#ifndef CANDUMPRECEIVER_H
#define CANDUMPRECEIVER_H

#include "streamingreceiver.h"

class CanDumpReceiver : public StreamingReceiver {
 public:
  CanDumpReceiver(int a){};
  void setup();
  virtual CanData askForNewData();
  virtual ~CanDumpReceiver();
};

#endif  // CANDUMPRECEIVER_H
