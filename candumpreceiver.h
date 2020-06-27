#ifndef CANDUMPRECEIVER_H
#define CANDUMPRECEIVER_H

#include "streamingreceiver.h"

class CanDumpReceiver : public StreamingReceiver {
 public:
  CanDumpReceiver(int a){};
  virtual CanData askForNewData();
  virtual ~CanDumpReceiver();
};

#endif  // CANDUMPRECEIVER_H
