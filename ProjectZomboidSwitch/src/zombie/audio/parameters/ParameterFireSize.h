#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/audio/OpenALParameterStub.h"

namespace zombie {
namespace audio {
namespace parameters {


class ParameterFireSize : public OpenALParameterStub {
public:
    int size = 0;

    public ParameterFireSize() {
      super("FireSize");
   }

    float calculateCurrentValue() {
      return this.size;
   }

    void setSize(int var1) {
      this.size = var1;
   }
}
} // namespace parameters
} // namespace audio
} // namespace zombie
