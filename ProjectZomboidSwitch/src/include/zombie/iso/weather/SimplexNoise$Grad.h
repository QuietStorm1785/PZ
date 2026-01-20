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

class SimplexNoise {
public:
    double x;
    double y;
    double z;
    double w;

   SimplexNoise$Grad(double var1, double var3, double var5) {
      this.x = var1;
      this.y = var3;
      this.z = var5;
   }

   SimplexNoise$Grad(double var1, double var3, double var5, double var7) {
      this.x = var1;
      this.y = var3;
      this.z = var5;
      this.w = var7;
   }
}
} // namespace weather
} // namespace iso
} // namespace zombie
