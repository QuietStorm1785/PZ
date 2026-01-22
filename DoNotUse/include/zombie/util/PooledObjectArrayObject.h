#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace util {

class PooledObjectArrayObject {
public:
    void onReleased() {
    int var1 = 0;

      for (int var2 = this.length(); var1 < var2; var1++) {
         ((IPooledObject)this.get(var1)).release();
      }
   }
}
} // namespace util
} // namespace zombie
