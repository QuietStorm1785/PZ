#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>

namespace zombie {
namespace spnetwork {


class ZomboidNetDataPool {
:
    static ZomboidNetDataPool instance = new ZomboidNetDataPool();
   private ArrayDeque<ZomboidNetData> Pool = std::make_unique<ArrayDeque<>>();

    ZomboidNetData get() {
      synchronized (this.Pool) {
         return this.Pool.isEmpty() ? std::make_unique<ZomboidNetData>() : this.Pool.pop();
      }
   }

    void discard(ZomboidNetData var1) {
      var1.reset();
      if (var1.buffer.capacity() == 2048) {
         synchronized (this.Pool) {
            this.Pool.add(var1);
         }
      }
   }

    ZomboidNetData getLong(int var1) {
      return new ZomboidNetData(var1);
   }
}
} // namespace spnetwork
} // namespace zombie
