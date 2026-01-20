#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/vehicles/CircleLineIntersect/Collider.h"
#include "zombie/vehicles/CircleLineIntersect/ForceCircle.h"
#include "zombie/vehicles/CircleLineIntersect/Vector.h"

namespace zombie {
namespace vehicles {


class CircleLineIntersect {
public:
   private std::vector<Collider> colliders = new std::vector<>(1);
    int numforcecircles;

   public CircleLineIntersect$Collideclassindex() {
      this.numforcecircles = 0;
   }

   public CircleLineIntersect$Collideclassindex(Object var1, int var2, Vector var3) {
      this.colliders.push_back(std::make_shared<Collider>(var1, var2, var3));
   }

    bool collided() {
      return this.size() > 0;
   }

    void reset() {
      this.colliders.trimToSize();
      this.colliders.clear();
      this.numforcecircles = 0;
   }

    void setCollided(void* var1, int var2, Vector var3) {
      if (this.size() > 0) {
         this.reset();
      }

      if (dynamic_cast<ForceCircle*>(var1) != nullptr && !((ForceCircle)var1).isFrozen()) {
         this.numforcecircles++;
      }

      this.colliders.push_back(std::make_shared<Collider>(var1, var2, var3));
   }

    void addCollided(void* var1, int var2, Vector var3) {
      if (dynamic_cast<ForceCircle*>(var1) != nullptr && !((ForceCircle)var1).isFrozen()) {
         this.numforcecircles++;
      }

      this.colliders.push_back(std::make_shared<Collider>(var1, var2, var3));
   }

   public std::vector<Collider> getColliders() {
      return this.colliders;
   }

    int getNumforcecircles() {
      return this.numforcecircles;
   }

    Collider contains(void* var1) {
      for (Collider var3 : this.colliders) {
         if (var3.getCollideobj() == var1)) {
    return var3;
         }
      }

    return nullptr;
   }

    int size() {
      return this.colliders.size();
   }

    std::string toString() {
    std::string var1 = "";

      for (Collider var3 : this.colliders) {
         var1 = var1 + var3 + "\n";
      }

    return var1;
   }
}
} // namespace vehicles
} // namespace zombie
