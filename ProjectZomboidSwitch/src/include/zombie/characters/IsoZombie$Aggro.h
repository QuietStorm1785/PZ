#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/iso/IsoMovingObject.h"

namespace zombie {
namespace characters {


class IsoZombie {
public:
    IsoMovingObject obj;
    float damage;
    long lastDamage;

   public IsoZombie$Aggro(IsoMovingObject var1, float var2) {
      this.obj = var1;
      this.damage = var2;
      this.lastDamage = System.currentTimeMillis();
   }

    void addDamage(float var1) {
      this.damage += var1;
      this.lastDamage = System.currentTimeMillis();
   }

    float getAggro() {
    float var1 = (float)(System.currentTimeMillis() - this.lastDamage);
    float var2 = Math.min(1.0F, Math.max(0.0F, (10000.0F - var1) / 5000.0F));
      return Math.min(1.0F, Math.max(0.0F, var2 * this.damage * 0.5F));
   }
}
} // namespace characters
} // namespace zombie
