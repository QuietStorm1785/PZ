#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace core {
namespace utils {

class UpdateTimer {
public:
    long time = 0L;

    public UpdateTimer() {
      this.time = System.currentTimeMillis() + 3800L;
   }

    void reset(long var1) {
      this.time = System.currentTimeMillis() + var1;
   }

    bool check() {
      return this.time != 0L && System.currentTimeMillis() + 200L >= this.time;
   }

    long getTime() {
      return this.time;
   }
}
} // namespace utils
} // namespace core
} // namespace zombie
