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
    bool started = false;
    long timeStart = 0L;
    long timeWork = 0L;
    long timeMax = 0L;
    long timeCount = 0L;

    void Clear() {
      this.timeWork = 0L;
      this.timeMax = 0L;
      this.timeCount = 0L;
   }

    std::string PrintTitle(const std::string& var1) {
      return var1 + "Work; " + var1 + "Max; " + var1 + "Count;";
   }

    std::string Print() {
      return this.timeWork / 1000000L + "; " + this.timeMax / 1000000L + "; " + this.timeCount + "; ";
   }

    void Start() {
      this.timeStart = System.nanoTime();
      this.timeCount++;
      this.started = true;
   }

    void End() {
      if (this.started) {
    long var1 = System.nanoTime() - this.timeStart;
         this.timeWork += var1;
         if (this.timeMax < var1) {
            this.timeMax = var1;
         }

         this.started = false;
      }
   }
}
} // namespace network
} // namespace zombie
