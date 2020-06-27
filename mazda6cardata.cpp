#include "mazda6cardata.h"

using namespace std::placeholders;

Mazda6CarData::Mazda6CarData() {
  registerProcessor(std::bind(&Mazda6CarData::motorRpmProcessor, this, _1),
                    0x201);
  registerProcessor(std::bind(&Mazda6CarData::speedProcessor, this, _1), 0x201);

  registerProcessor(std::bind(&Mazda6CarData::tempProcessor, this, _1), 0x420);
}
