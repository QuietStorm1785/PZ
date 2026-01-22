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
    const int count;
    const long interval;
    const UpdateLimit hordeCreatorLimiter;

   public FakeClientManager$HordeCreator(int var1, int var2, long var3) {
      this.radius = var1;
      this.count = var2;
      this.interval = var3;
      this.hordeCreatorLimiter = std::make_shared<UpdateLimit>(var3);
   }

    std::string getCommand(int var1, int var2, int var3) {
      return std::string.format(
         "/createhorde2 -x %d -y %d -z %d -count %d -radius %d -crawler false -isFallOnFront false -isFakeDead false -knockedDown false -health 1 -outfit",
         var1,
         var2,
         var3,
         this.count,
         this.radius
      );
   }
}
} // namespace network
} // namespace zombie
