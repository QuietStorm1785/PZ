#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/vehicles/CircleLineIntersect/Vector.h"

namespace zombie {
namespace vehicles {


class CircleLineIntersect {
public:
    void* collideobj;
    int collideindex;
    Vector collideforce;

   public CircleLineIntersect$Collider(Vector var1, int var2) {
      this.collideobj = var1;
      this.collideindex = var2;
      this.collideforce = var1;
   }

   public CircleLineIntersect$Collider(Object var1, int var2, Vector var3) {
      this.collideobj = var1;
      this.collideindex = var2;
      this.collideforce = var3;
   }

    void* getCollideobj() {
      return this.collideobj;
   }

    int getCollidewith() {
      return this.collideindex;
   }

    Vector getCollideforce() {
      return this.collideforce;
   }

    void setCollideforce(Vector var1) {
      this.collideforce = var1;
   }

    std::string toString() {
      return this.collideobj.getClass().getSimpleName() + " @ " + this.collideindex + " hit with " + this.collideforce;
   }
}
} // namespace vehicles
} // namespace zombie
