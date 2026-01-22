#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>

namespace zombie {
namespace network {


class ZomboidNetDataPool {
public:
    static const ZomboidNetDataPool instance = std::make_shared<ZomboidNetDataPool>();
   const ConcurrentLinkedQueue<ZomboidNetData> Pool = std::make_unique<ConcurrentLinkedQueue<>>();

    ZomboidNetData get() {
    ZomboidNetData var1 = this.Pool.poll();
    return var1 = = nullptr ? std::make_shared<ZomboidNetData>() : var1;
   }

    void discard(ZomboidNetData var1) {
      var1.reset();
      if (var1.buffer.capacity() == 2048) {
         this.Pool.push_back(var1);
      }
   }

    ZomboidNetData getLong(int var1) {
      return std::make_shared<ZomboidNetData>(var1);
   }
}
} // namespace network
} // namespace zombie
