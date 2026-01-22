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
    long processed = 0L;

    void Clear() {
      this.added = 0L;
      this.processed = 0L;
   }

    std::string PrintTitle(const std::string& var1) {
      return var1 + "Added; " + var1 + "Processed; ";
   }

    std::string Print() {
      return this.added + "; " + this.processed + "; ";
   }

    void Added() {
      this.added++;
   }

    void Processed() {
      this.processed++;
   }
}
} // namespace network
} // namespace zombie
