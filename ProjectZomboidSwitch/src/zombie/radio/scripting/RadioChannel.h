#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameTime.h"
#include "zombie/core/Rand.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugType.h"
#include "zombie/radio/ChannelCategory.h"
#include "zombie/radio/RadioData.h"
#include "zombie/radio/ZomboidRadio.h"
#include "zombie/radio/scripting/RadioScript/ExitOption.h"
#include <algorithm>

namespace zombie {
namespace radio {
namespace scripting {


class RadioChannel {
public:
    std::string GUID;
    RadioData radioData;
    bool isTimeSynced = false;
   private Map<std::string, RadioScript> scripts = std::make_unique<std::unordered_map<>>();
    int frequency = -1;
    std::string name = "Unnamed channel";
    bool isTv = false;
    ChannelCategory category = ChannelCategory.Undefined;
    bool playerIsListening = false;
    RadioScript currentScript = nullptr;
    int currentScriptLoop = 1;
    int currentScriptMaxLoops = 1;
    RadioBroadCast airingBroadcast = nullptr;
    float airCounter = 0.0F;
    std::string lastAiredLine = "";
    std::string lastBroadcastID = nullptr;
    float airCounterMultiplier = 1.0F;
    bool louisvilleObfuscate = false;
    float minmod = 1.5F;
    float maxmod = 5.0F;

    public RadioChannel(const std::string& var1, int var2, ChannelCategory var3) {
      this(var1, var2, var3, UUID.randomUUID());
   }

    public RadioChannel(const std::string& var1, int var2, ChannelCategory var3, const std::string& var4) {
      this.name = var1;
      this.frequency = var2;
      this.category = var3;
      this.isTv = this.category == ChannelCategory.Television;
      this.GUID = var4;
   }

    std::string getGUID() {
      return this.GUID;
   }

    int GetFrequency() {
      return this.frequency;
   }

    std::string GetName() {
      return this.name;
   }

    bool IsTv() {
      return this.isTv;
   }

    ChannelCategory GetCategory() {
      return this.category;
   }

    RadioScript getCurrentScript() {
      return this.currentScript;
   }

    RadioBroadCast getAiringBroadcast() {
      return this.airingBroadcast;
   }

    std::string getLastAiredLine() {
      return this.lastAiredLine;
   }

    int getCurrentScriptLoop() {
      return this.currentScriptLoop;
   }

    int getCurrentScriptMaxLoops() {
      return this.currentScriptMaxLoops;
   }

    std::string getLastBroadcastID() {
      return this.lastBroadcastID;
   }

    RadioData getRadioData() {
      return this.radioData;
   }

    void setRadioData(RadioData var1) {
      this.radioData = var1;
   }

    bool isTimeSynced() {
      return this.isTimeSynced;
   }

    void setTimeSynced(bool var1) {
      this.isTimeSynced = var1;
   }

    bool isVanilla() {
      return this.radioData == nullptr || this.radioData.isVanilla();
   }

    void setLouisvilleObfuscate(bool var1) {
      this.louisvilleObfuscate = var1;
   }

    void LoadAiringBroadcast(const std::string& var1, int var2) {
      if (this.currentScript != nullptr) {
         this.airingBroadcast = this.currentScript.getBroadcastWithID(var1);
         if (var2 < 0) {
            this.airingBroadcast = nullptr;
         }

         if (this.airingBroadcast != nullptr && var2 >= 0) {
            this.airingBroadcast.resetLineCounter();
            this.airingBroadcast.setCurrentLineNumber(var2);
            this.airCounter = 120.0F;
            this.playerIsListening = true;
         }
      }
   }

    void SetPlayerIsListening(bool var1) {
      this.playerIsListening = var1;
      if (this.playerIsListening && this.airingBroadcast == nullptr && this.currentScript != nullptr) {
         this.airingBroadcast = this.currentScript.getValidAirBroadcast();
         if (this.airingBroadcast != nullptr) {
            this.airingBroadcast.resetLineCounter();
         }

         this.airCounter = 0.0F;
      }
   }

    bool GetPlayerIsListening() {
      return this.playerIsListening;
   }

    void setActiveScriptNull() {
      this.currentScript = nullptr;
      this.airingBroadcast = nullptr;
   }

    void setActiveScript(const std::string& var1, int var2) {
      this.setActiveScript(var1, var2, 1, -1);
   }

    void setActiveScript(const std::string& var1, int var2, int var3, int var4) {
      if (var1 != nullptr && this.scripts.containsKey(var1)) {
         this.currentScript = this.scripts.get(var1);
         if (this.currentScript != nullptr) {
            this.currentScript.Reset();
            this.currentScript.setStartDayStamp(var2);
            this.currentScriptLoop = var3;
            if (var4 == -1) {
    int var5 = this.currentScript.getLoopMin();
    int var6 = this.currentScript.getLoopMax();
               if (var5 != var6 && var5 <= var6) {
                  var4 = Rand.Next(var5, var6);
               } else {
                  var4 = var5;
               }
            }

            this.currentScriptMaxLoops = var4;
            if (DebugLog.isEnabled(DebugType.Radio)) {
               DebugLog.Radio
                  .println(
                     "Script: " + var1 + ", day = " + var2 + ", minloops = " + this.currentScript.getLoopMin() + ", maxloops = " + this.currentScriptMaxLoops
                  );
            }
         }
      }
   }

    void getNextScript(int var1) {
      if (this.currentScript != nullptr) {
         if (this.currentScriptLoop < this.currentScriptMaxLoops) {
            this.currentScriptLoop++;
            this.currentScript.Reset();
            this.currentScript.setStartDayStamp(var1);
         } else {
    ExitOption var2 = this.currentScript.getNextScript();
            this.currentScript = nullptr;
            if (var2 != nullptr) {
               this.setActiveScript(var2.getScriptname(), var1 + var2.getStartDelay());
            }
         }
      }
   }

    void UpdateScripts(int var1, int var2) {
      this.playerIsListening = false;
      if (this.currentScript != nullptr && !this.currentScript.UpdateScript(var1)) {
         this.getNextScript(var2 + 1);
      }
   }

    void update() {
      if (this.airingBroadcast != nullptr) {
         this.airCounter = this.airCounter - 1.25F * GameTime.getInstance().getMultiplier();
         if (this.airCounter < 0.0F) {
    RadioLine var1 = this.airingBroadcast.getNextLine();
            if (var1 == nullptr) {
               this.lastBroadcastID = this.airingBroadcast.getID();
               this.airingBroadcast = nullptr;
               this.playerIsListening = false;
            } else {
               this.lastAiredLine = var1.getText();
               if (!ZomboidRadio.DISABLE_BROADCASTING) {
    std::string var2 = var1.getText();
                  if (this.louisvilleObfuscate && ZomboidRadio.LOUISVILLE_OBFUSCATION) {
                     var2 = ZomboidRadio.getInstance().scrambleString(var2, 85, true, nullptr);
                     ZomboidRadio.getInstance().SendTransmission(0, 0, this.frequency, var2, nullptr, "", 0.7F, 0.5F, 0.5F, -1, this.isTv);
                  } else {
                     ZomboidRadio.getInstance()
                        .SendTransmission(0, 0, this.frequency, var2, nullptr, var1.getEffectsString(), var1.getR(), var1.getG(), var1.getB(), -1, this.isTv);
                  }
               }

               if (var1.isCustomAirTime()) {
                  this.airCounter = var1.getAirTime() * 60.0F;
               } else {
                  this.airCounter = var1.getText().length() / 10.0F * 60.0F;
                  if (this.airCounter < 60.0F * this.minmod) {
                     this.airCounter = 60.0F * this.minmod;
                  } else if (this.airCounter > 60.0F * this.maxmod) {
                     this.airCounter = 60.0F * this.maxmod;
                  }

                  this.airCounter = this.airCounter * this.airCounterMultiplier;
               }
            }
         }
      }
   }

    void AddRadioScript(RadioScript var1) {
      if (var1 != nullptr && !this.scripts.containsKey(var1.GetName())) {
         this.scripts.put(var1.GetName(), var1);
      } else {
    std::string var2 = var1 != nullptr ? var1.GetName() : "nullptr";
         DebugLog.log(DebugType.Radio, "Error while attempting to add script (" + var2 + "), nullptr or name already exists.");
      }
   }

    RadioScript getRadioScript(const std::string& var1) {
      return var1 != nullptr && this.scripts.containsKey(var1) ? this.scripts.get(var1) : nullptr;
   }

    void setAiringBroadcast(RadioBroadCast var1) {
      this.airingBroadcast = var1;
   }

    float getAirCounterMultiplier() {
      return this.airCounterMultiplier;
   }

    void setAirCounterMultiplier(float var1) {
      this.airCounterMultiplier = PZMath.clamp(var1, 0.1F, 10.0F);
   }
}
} // namespace scripting
} // namespace radio
} // namespace zombie
