#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/network/MPStatistic/ThreadStatistic.h"

namespace zombie {
namespace network {


class MPStatistic {
public:
    long timeStartSleep;

   public MPStatistic$MainThreadStatistic(MPStatistic var1) {
      this.this$0 = var1;
      this.timeStartSleep = 0L;
   }

    void Start() {
      if (this.timeStart == 0L) {
         this.timeStart = System.currentTimeMillis();
      } else {
    long var1 = System.currentTimeMillis() - this.timeStart;
         this.timeStart = System.currentTimeMillis();
         this.timeWork += var1;
         if (this.timeMax < var1) {
            this.timeMax = var1;
         }

         this.timeCount++;
      }
   }

    void End() {
   }

    void StartSleep() {
      this.timeStartSleep = System.currentTimeMillis();
   }

    void EndSleep() {
    long var1 = System.currentTimeMillis() - this.timeStartSleep;
      this.timeSleep += var1;
      this.timeStart += var1;
   }
}
} // namespace network
} // namespace zombie
