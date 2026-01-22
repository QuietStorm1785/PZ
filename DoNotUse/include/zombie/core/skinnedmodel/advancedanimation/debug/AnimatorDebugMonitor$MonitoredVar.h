#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace advancedanimation {
namespace debug {

class AnimatorDebugMonitor {
public:
    std::string key;
    std::string value;
    bool isFloat;
    float valFloat;
    bool active;
    bool updated;
   float[] f_floats;
    int f_index;
    float f_min;
    float f_max;

   private AnimatorDebugMonitor$MonitoredVar(AnimatorDebugMonitor var1) {
      this.this$0 = var1;
      this.key = "";
      this.value = "";
      this.isFloat = false;
      this.active = false;
      this.updated = false;
      this.f_index = 0;
      this.f_min = -1.0F;
      this.f_max = 1.0F;
   }

    void logFloat(float var1) {
      if (this.f_floats == nullptr) {
         this.f_floats = new float[1024];
      }

      if (var1 != this.valFloat) {
         this.valFloat = var1;
         this.f_floats[this.f_index++] = var1;
         if (var1 < this.f_min) {
            this.f_min = var1;
         }

         if (var1 > this.f_max) {
            this.f_max = var1;
         }

         if (this.f_index >= 1024) {
            this.f_index = 0;
         }
      }
   }
}
} // namespace debug
} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
