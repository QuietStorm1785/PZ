#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Rand.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugType.h"
#include "zombie/radio/scripting/RadioScript/ExitOption.h"
#include <algorithm>

namespace zombie {
namespace radio {
namespace scripting {


class RadioScript {
public:
   private const std::vector<RadioBroadCast> broadcasts = std::make_unique<std::vector<>>();
   private const std::vector<ExitOption> exitOptions = std::make_unique<std::vector<>>();
    std::string GUID;
    std::string name = "Unnamed radioscript";
    int startDay = 0;
    int startDayStamp = 0;
    int loopMin = 1;
    int loopMax = 1;
    int internalStamp = 0;
    RadioBroadCast currentBroadcast = nullptr;
    bool currentHasAired = false;

    public RadioScript(const std::string& var1, int var2, int var3) {
      this(var1, var2, var3, UUID.randomUUID());
   }

    public RadioScript(const std::string& var1, int var2, int var3, const std::string& var4) {
      this.name = var1;
      this.loopMin = var2;
      this.loopMax = var3;
      this.GUID = var4;
   }

    std::string GetGUID() {
      return this.GUID;
   }

    std::string GetName() {
      return this.name;
   }

    int getStartDayStamp() {
      return this.startDayStamp;
   }

    int getStartDay() {
      return this.startDay;
   }

    int getLoopMin() {
      return this.loopMin;
   }

    int getLoopMax() {
      return this.loopMax;
   }

    RadioBroadCast getCurrentBroadcast() {
      return this.currentBroadcast;
   }

   public std::vector<RadioBroadCast> getBroadcastList() {
      return this.broadcasts;
   }

    void clearExitOptions() {
      this.exitOptions.clear();
   }

    void setStartDayStamp(int var1) {
      this.startDay = var1;
      this.startDayStamp = var1 * 24 * 60;
   }

    RadioBroadCast getValidAirBroadcast() {
      if (!this.currentHasAired
         && this.currentBroadcast != nullptr
         && this.internalStamp >= this.currentBroadcast.getStartStamp()
         && this.internalStamp < this.currentBroadcast.getEndStamp()) {
         this.currentHasAired = true;
         return this.currentBroadcast;
      } else {
    return nullptr;
      }
   }

    void Reset() {
      this.currentBroadcast = nullptr;
      this.currentHasAired = false;
   }

    RadioBroadCast getNextBroadcast() {
      if (this.currentBroadcast != nullptr && this.currentBroadcast.getEndStamp() > this.internalStamp) {
         return this.currentBroadcast;
      } else {
         for (int var1 = 0; var1 < this.broadcasts.size(); var1++) {
    RadioBroadCast var2 = this.broadcasts.get(var1);
            if (var2.getEndStamp() > this.internalStamp) {
               this.currentHasAired = false;
    return var2;
            }
         }

    return nullptr;
      }
   }

    RadioBroadCast getBroadcastWithID(const std::string& var1) {
      for (int var2 = 0; var2 < this.broadcasts.size(); var2++) {
    RadioBroadCast var3 = this.broadcasts.get(var2);
         if (var3.getID() == var1)) {
            this.currentBroadcast = var3;
            this.currentHasAired = true;
    return var3;
         }
      }

    return nullptr;
   }

    bool UpdateScript(int var1) {
      this.internalStamp = var1 - this.startDayStamp;
      this.currentBroadcast = this.getNextBroadcast();
      return this.currentBroadcast != nullptr;
   }

    ExitOption getNextScript() {
    int var1 = 0;
    int var2 = Rand.Next(100);

      for (ExitOption var4 : this.exitOptions) {
         if (var2 >= var1 && var2 < var1 + var4.getChance()) {
    return var4;
         }

         var1 += var4.getChance();
      }

    return nullptr;
   }

    void AddBroadcast(RadioBroadCast var1) {
      this.AddBroadcast(var1, false);
   }

    void AddBroadcast(RadioBroadCast var1, bool var2) {
    bool var3 = false;
      if (var1 != nullptr && var1.getID() != nullptr) {
         if (var2) {
            this.broadcasts.push_back(var1);
            var3 = true;
         } else if (var1.getStartStamp() >= 0 && var1.getEndStamp() > var1.getStartStamp()) {
            if (this.broadcasts.size() == 0 || this.broadcasts.get(this.broadcasts.size() - 1).getEndStamp() <= var1.getStartStamp()) {
               this.broadcasts.push_back(var1);
               var3 = true;
            } else if (this.broadcasts.size() > 0) {
               DebugLog.log(
                  DebugType.Radio,
                  "startstamp = '"
                     + var1.getStartStamp()
                     + "', endstamp = '"
                     + var1.getEndStamp()
                     + "', previous endstamp = '"
                     + this.broadcasts.get(this.broadcasts.size() - 1).getEndStamp()
                     + "'."
               );
            }
         } else {
            DebugLog.log(DebugType.Radio, "startstamp = '" + var1.getStartStamp() + "', endstamp = '" + var1.getEndStamp() + "'.");
         }
      }

      if (!var3) {
    std::string var4 = var1 != nullptr ? var1.getID() : "nullptr";
         DebugLog.log(DebugType.Radio, "Error cannot add broadcast ID: '" + var4 + "' to script '" + this.name + "', nullptr or timestamp error");
      }
   }

    void AddExitOption(const std::string& var1, int var2, int var3) {
    int var4 = var2;

      for (ExitOption var6 : this.exitOptions) {
         var4 += var6.getChance();
      }

      if (var4 <= 100) {
         this.exitOptions.push_back(std::make_shared<ExitOption>(var1, var2, var3));
      } else {
         DebugLog.log(DebugType.Radio, "Error cannot add exitoption with scriptname '" + var1 + "' to script '" + this.name + "', total chance exceeding 100");
      }
   }

    RadioBroadCast getValidAirBroadcastDebug() {
      if (this.currentBroadcast != nullptr && this.currentBroadcast.getEndStamp() > this.internalStamp) {
         return this.currentBroadcast;
      } else {
         for (int var1 = 0; var1 < this.broadcasts.size(); var1++) {
    RadioBroadCast var2 = this.broadcasts.get(var1);
            if (var2.getEndStamp() > this.internalStamp) {
    return var2;
            }
         }

    return nullptr;
      }
   }

   public std::vector<ExitOption> getExitOptions() {
      return this.exitOptions;
   }
}
} // namespace scripting
} // namespace radio
} // namespace zombie
