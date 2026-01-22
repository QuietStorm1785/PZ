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

class RainParticle {
public:
    double origx;
    double origy;
    double x;
    double y;

   private RainParticle$Point(RainParticle var1) {
      this.this$0 = var1;
   }

    void setOrig(double var1, double var3) {
      this.origx = var1;
      this.origy = var3;
      this.x = var1;
      this.y = var3;
   }

    void set(double var1, double var3) {
      this.x = var1;
      this.y = var3;
   }
}
} // namespace fx
} // namespace weather
} // namespace iso
} // namespace zombie
