#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace audio {
namespace parameters {

enum class ParameterEquippedBaggageContainer {
   None(0),
   HikingBag(1),
   DuffleBag(2),
   PlasticBag(3),
   SchoolBag(4),
   ToteBag(5),
   GarbageBag(6);

    const int label;

   private ParameterEquippedBaggageContainer$ContainerType(int var3) {
      this.label = var3;
   }
}
} // namespace parameters
} // namespace audio
} // namespace zombie
