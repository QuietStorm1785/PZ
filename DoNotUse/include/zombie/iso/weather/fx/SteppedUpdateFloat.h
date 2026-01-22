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
namespace fx {

class SteppedUpdateFloat {
public:
    float current;
    float step;
    float target;
    float min;
    float max;

    public SteppedUpdateFloat(float var1, float var2, float var3, float var4) {
      this.current = var1;
      this.step = var2;
      this.target = var1;
      this.min = var3;
      this.max = var4;
   }

    float value() {
      return this.current;
   }

    void setTarget(float var1) {
      this.target = this.clamp(this.min, this.max, var1);
   }

    float getTarget() {
      return this.target;
   }

    void overrideCurrentValue(float var1) {
      this.current = var1;
   }

    float clamp(float var1, float var2, float var3) {
      var3 = Math.min(var2, var3);
      return Math.max(var1, var3);
   }

    void update(float var1) {
      if (this.current != this.target) {
         if (this.target > this.current) {
            this.current = this.current + this.step * var1;
            if (this.current > this.target) {
               this.current = this.target;
            }
         } else if (this.target < this.current) {
            this.current = this.current - this.step * var1;
            if (this.current < this.target) {
               this.current = this.target;
            }
         }
      }
   }
}
} // namespace fx
} // namespace weather
} // namespace iso
} // namespace zombie
