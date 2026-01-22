#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/debug/DebugLog.h"
#include "zombie/network/GameServer.h"

namespace zombie {


class TimeDebugger {
public:
   std::vector<int64_t> records = std::make_unique<std::vector<>>();
   std::vector<std::string> recordStrings = std::make_unique<std::vector<>>();
    std::string name = "";

    public TimeDebugger(const std::string& var1) {
      this.name = var1;
   }

    void clear() {
      if (GameServer.bServer) {
         this.records.clear();
         this.recordStrings.clear();
      }
   }

    void start() {
      if (GameServer.bServer) {
         this.records.clear();
         this.recordStrings.clear();
         this.records.push_back(System.currentTimeMillis());
         this.recordStrings.push_back("Start");
      }
   }

    void record() {
      if (GameServer.bServer) {
         this.records.push_back(System.currentTimeMillis());
         this.recordStrings.push_back(std::string.valueOf(this.records.size()));
      }
   }

    void record(const std::string& var1) {
      if (GameServer.bServer) {
         this.records.push_back(System.currentTimeMillis());
         this.recordStrings.push_back(var1);
      }
   }

    void recordTO(const std::string& var1, int var2) {
      if (GameServer.bServer && this.records.get(this.records.size() - 1) - this.records.get(this.records.size() - 2) > var2) {
         this.records.push_back(System.currentTimeMillis());
         this.recordStrings.push_back(var1);
      }
   }

    void add(TimeDebugger var1) {
      if (GameServer.bServer) {
    std::string var2 = var1.name;

         for (int var3 = 0; var3 < var1.records.size(); var3++) {
            this.records.push_back(var1.records.get(var3));
            this.recordStrings.push_back(var2 + "|" + var1.recordStrings.get(var3));
         }

         var1.clear();
      }
   }

    void print() {
      if (GameServer.bServer) {
         this.records.push_back(System.currentTimeMillis());
         this.recordStrings.push_back("END");
         if (this.records.size() > 1) {
            DebugLog.log("=== DBG " + this.name + " ===");
    long var1 = this.records.get(0);

            for (int var3 = 1; var3 < this.records.size(); var3++) {
    long var4 = this.records.get(var3 - 1);
    long var6 = this.records.get(var3);
    std::string var8 = this.recordStrings.get(var3);
               DebugLog.log("RECORD " + var3 + " " + var8 + " A:" + (var6 - var1) + " D:" + (var6 - var4));
            }

            DebugLog.log("=== END " + this.name + " (" + (this.records.get(this.records.size() - 1) - var1) + ") ===");
         } else {
            DebugLog.log("<<< DBG " + this.name + " ERROR >>>");
         }
      }
   }

    long getExecTime() {
      return this.records.size() == 0 ? 0L : System.currentTimeMillis() - this.records.get(0);
   }
}
} // namespace zombie
