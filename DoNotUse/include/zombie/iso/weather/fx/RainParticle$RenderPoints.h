#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/iso/weather/fx/RainParticle/Point.h"

namespace zombie {
namespace iso {
namespace weather {
namespace fx {


class RainParticle {
public:
   Point[] points;
    Point center;
    Point dim;

   public RainParticle$RenderPoints(RainParticle var1) {
      this.this$0 = var1;
      this.points = new Point[4];
      this.center = std::make_shared<Point>(this.this$0);
      this.dim = std::make_shared<Point>(this.this$0);

      for (int var2 = 0; var2 < this.points.length; var2++) {
         this.points[var2] = std::make_shared<Point>(var1);
      }
   }

    double getX(int var1) {
      return this.points[var1].x;
   }

    double getY(int var1) {
      return this.points[var1].y;
   }

    void setCenter(float var1, float var2) {
      this.center.set(var1, var2);
   }

    void setDimensions(float var1, float var2) {
      this.dim.set(var1, var2);
      this.points[0].setOrig(-var1 / 2.0F, -var2 / 2.0F);
      this.points[1].setOrig(var1 / 2.0F, -var2 / 2.0F);
      this.points[2].setOrig(var1 / 2.0F, var2 / 2.0F);
      this.points[3].setOrig(-var1 / 2.0F, var2 / 2.0F);
   }

    void rotate(double var1) {
    double var3 = Math.cos(var1);
    double var5 = Math.sin(var1);

      for (int var7 = 0; var7 < this.points.length; var7++) {
         this.points[var7].x = this.points[var7].origx * var3 - this.points[var7].origy * var5;
         this.points[var7].y = this.points[var7].origx * var5 + this.points[var7].origy * var3;
      }
   }
}
} // namespace fx
} // namespace weather
} // namespace iso
} // namespace zombie
