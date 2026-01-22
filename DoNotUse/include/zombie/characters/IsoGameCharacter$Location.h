#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace characters {

class IsoGameCharacter {
public:
    int x;
    int y;
    int z;

   public IsoGameCharacter$Location() {
   }

   public IsoGameCharacter$Location(int var1, int var2, int var3) {
      this.x = var1;
      this.y = var2;
      this.z = var3;
   }

   public IsoGameCharacter$Location set(int var1, int var2, int var3) {
      this.x = var1;
      this.y = var2;
      this.z = var3;
    return this;
   }

    int getX() {
      return this.x;
   }

    int getY() {
      return this.y;
   }

    int getZ() {
      return this.z;
   }

    bool equals(void* var1) {
      return !(dynamic_cast<IsoGameCharacter*>(var1) != nullptr$Location var2) ? false : this.x == var2.x && this.y == var2.y && this.z == var2.z;
   }
}
} // namespace characters
} // namespace zombie
