#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/vehicles/CircleLineIntersect/Collideclassindex.h"
#include "zombie/vehicles/CircleLineIntersect/PointVector.h"

namespace zombie {
namespace vehicles {


class CircleLineIntersect {
public:
   protected PointVector[] resultants;
   protected std::vector<int> collidelist;
   protected Collideclassindex[] collideinto;
   protected double[] timepassed;
   protected double[] collidetime;
   protected boolean[] modified;

   public CircleLineIntersect$Collideresult(PointVector[] var1, Collideclassindex[] var2, std::vector<int> var3, double[] var4, double[] var5, boolean[] var6) {
      this.resultants = var1;
      this.collideinto = var2;
      this.collidelist = var3;
      this.timepassed = var4;
      this.collidetime = var5;
      this.modified = var6;
   }

    std::string toString() {
      return this.collidelist;
   }
}
} // namespace vehicles
} // namespace zombie
