#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/BoxedStaticValues.h"

namespace zombie {
namespace scripting {
namespace objects {


class VehicleScript {
public:
    std::string id;
    float x;
    float y;
    float w;
    float h;

    std::string getId() {
      return this.id;
   }

    double getX() {
      return BoxedStaticValues.toDouble(this.x);
   }

    double getY() {
      return BoxedStaticValues.toDouble(this.y);
   }

    double getW() {
      return BoxedStaticValues.toDouble(this.w);
   }

    double getH() {
      return BoxedStaticValues.toDouble(this.h);
   }

    void setX(double var1) {
      this.x = var1.floatValue();
   }

    void setY(double var1) {
      this.y = var1.floatValue();
   }

    void setW(double var1) {
      this.w = var1.floatValue();
   }

    void setH(double var1) {
      this.h = var1.floatValue();
   }

   private VehicleScript$Area makeCopy() {
      VehicleScript$Area var1 = new VehicleScript$Area();
      var1.id = this.id;
      var1.x = this.x;
      var1.y = this.y;
      var1.w = this.w;
      var1.h = this.h;
    return var1;
   }
}
} // namespace objects
} // namespace scripting
} // namespace zombie
