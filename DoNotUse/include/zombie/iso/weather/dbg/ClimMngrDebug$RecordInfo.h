#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace iso {
namespace weather {
namespace dbg {

class ClimMngrDebug {
public:
    bool isWeather;
    float strength;
    int airType;
    double durationHours;
    int weatherType;

   private ClimMngrDebug$RecordInfo(ClimMngrDebug var1) {
      this.this$0 = var1;
      this.weatherType = 0;
   }
}
} // namespace dbg
} // namespace weather
} // namespace iso
} // namespace zombie
