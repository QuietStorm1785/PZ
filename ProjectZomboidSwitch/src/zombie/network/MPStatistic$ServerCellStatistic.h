#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace network {

class MPStatistic {
public:
    long added = 0L;
    long canceled = 0L;

    void Clear() {
      this.added = 0L;
      this.canceled = 0L;
   }

    std::string PrintTitle(const std::string& var1) {
      return var1 + "Added; " + var1 + "Canceled; ";
   }

    std::string Print() {
      return this.added + "; " + this.canceled + "; ";
   }

    void Added() {
      this.added++;
   }

    void Added(int var1) {
      this.added += var1;
   }

    void Canceled() {
      this.canceled++;
   }
}
} // namespace network
} // namespace zombie
