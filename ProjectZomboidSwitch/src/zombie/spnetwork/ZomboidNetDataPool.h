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
public:
    static ZomboidNetDataPool instance = std::make_shared<ZomboidNetDataPool>();
   private const ArrayDeque<ZomboidNetData> Pool = std::make_unique<ArrayDeque<>>();

    ZomboidNetData get() {
      /* synchronized - TODO: add std::mutex */ (this.Pool) {
         return this.Pool.empty() ? std::make_unique<ZomboidNetData>() : this.Pool.pop();
      }
   }

    void discard(ZomboidNetData var1) {
      var1.reset();
      if (var1.buffer.capacity() == 2048) {
         /* synchronized - TODO: add std::mutex */ (this.Pool) {
            this.Pool.push_back(var1);
         }
      }
   }

    ZomboidNetData getLong(int var1) {
      return std::make_shared<ZomboidNetData>(var1);
   }
}
} // namespace spnetwork
} // namespace zombie
