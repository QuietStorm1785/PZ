#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace popman {


class ObjectPool {
public:
   ObjectPool$1(ObjectPool var1) {
      this.this$0 = var1;
   }

    bool contains(void* var1) {
      for (int var2 = 0; var2 < this.this$0.pool.size(); var2++) {
         if (this.this$0.pool.get(var2) == var1) {
    return true;
         }
      }

    return false;
   }
}
} // namespace popman
} // namespace zombie
