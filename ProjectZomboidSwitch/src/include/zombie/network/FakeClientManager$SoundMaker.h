#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/utils/UpdateLimit.h"

namespace zombie {
namespace network {


class FakeClientManager {
public:
    const int radius;
    const int interval;
    const std::string message;
    const UpdateLimit soundMakerLimiter;

   public FakeClientManager$SoundMaker(int var1, int var2, std::string var3) {
      this.radius = var2;
      this.message = var3;
      this.interval = var1;
      this.soundMakerLimiter = std::make_shared<UpdateLimit>(var1);
   }
}
} // namespace network
} // namespace zombie
