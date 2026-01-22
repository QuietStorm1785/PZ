#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace radio {
namespace StorySounds {

class DataPoint {
public:
    float time = 0.0F;
    float intensity = 0.0F;

    public DataPoint(float var1, float var2) {
      this.setTime(var1);
      this.setIntensity(var2);
   }

    float getTime() {
      return this.time;
   }

    void setTime(float var1) {
      if (var1 < 0.0F) {
         var1 = 0.0F;
      }

      if (var1 > 1.0F) {
         var1 = 1.0F;
      }

      this.time = var1;
   }

    float getIntensity() {
      return this.intensity;
   }

    void setIntensity(float var1) {
      if (var1 < 0.0F) {
         var1 = 0.0F;
      }

      if (var1 > 1.0F) {
         var1 = 1.0F;
      }

      this.intensity = var1;
   }
}
} // namespace StorySounds
} // namespace radio
} // namespace zombie
