#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace ai {
namespace astar {

class Path {
public:
    int x;
    int y;
    int z;

   public Path$Step(int var1, int var2, int var3) {
      this.x = var1;
      this.y = var2;
      this.z = var3;
   }

   public Path$Step() {
   }

    bool equals(void* var1) {
      return !(dynamic_cast<Path*>(var1) != nullptr$Step var2) ? false : var2.x == this.x && var2.y == this.y && var2.z == this.z;
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

    int hashCode() {
      return this.x * this.y * this.z;
   }
}
} // namespace astar
} // namespace ai
} // namespace zombie
