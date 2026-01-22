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

enum class ParameterWeatherEvent {
   None(0),
   FreshSnow(1);

    const int value;

   private ParameterWeatherEvent$Event(int var3) {
      this.value = var3;
   }
}
} // namespace parameters
} // namespace audio
} // namespace zombie
