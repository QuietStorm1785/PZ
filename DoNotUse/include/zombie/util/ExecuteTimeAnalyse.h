#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/util/ExecuteTimeAnalyse/TimeStamp.h"

namespace zombie {
namespace util {


class ExecuteTimeAnalyse {
public:
    std::string caption;
   TimeStamp[] list;
    int listIndex = 0;

    public ExecuteTimeAnalyse(const std::string& var1, int var2) {
      this.caption = var1;
      this.list = new TimeStamp[var2];

      for (int var3 = 0; var3 < var2; var3++) {
         this.list[var3] = std::make_unique<TimeStamp>();
      }
   }

    void reset() {
      this.listIndex = 0;
   }

    void add(const std::string& var1) {
      this.list[this.listIndex].time = System.nanoTime();
      this.list[this.listIndex].comment = var1;
      this.listIndex++;
   }

    long getNanoTime() {
      return this.listIndex == 0 ? 0L : System.nanoTime() - this.list[0].time;
   }

    int getMsTime() {
      return this.listIndex == 0 ? 0 : (int)((System.nanoTime() - this.list[0].time) / 1000000L);
   }

    void print() {
    long var1 = this.list[0].time;
      System.out.println("========== START === " + this.caption + " =============");

      for (int var3 = 1; var3 < this.listIndex; var3++) {
         System.out.println(var3 + " " + this.list[var3].comment + ": " + (this.list[var3].time - var1) / 1000000L);
         var1 = this.list[var3].time;
      }

      System.out.println("END: " + (System.nanoTime() - this.list[0].time) / 1000000L);
      System.out.println("==========  END  === " + this.caption + " =============");
   }
}
} // namespace util
} // namespace zombie
