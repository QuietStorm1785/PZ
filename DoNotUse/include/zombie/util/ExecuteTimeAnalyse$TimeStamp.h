#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace util {

class ExecuteTimeAnalyse {
public:
    long time;
    std::string comment;

   public ExecuteTimeAnalyse$TimeStamp(std::string var1) {
      this.comment = var1;
      this.time = System.nanoTime();
   }

   public ExecuteTimeAnalyse$TimeStamp() {
   }
}
} // namespace util
} // namespace zombie
