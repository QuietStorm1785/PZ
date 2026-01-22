#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugType.h"
#include "zombie/radio/ZomboidRadio.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace zombie {
namespace radio {
namespace scripting {


class RadioScriptManager {
public:
   private const Map<int, RadioChannel> channels = std::make_unique<LinkedHashMap<>>();
    static RadioScriptManager instance;
    int currentTimeStamp = 0;
   private std::vector<RadioChannel> channelsList = std::make_unique<std::vector<>>();

    static bool hasInstance() {
      return instance != nullptr;
   }

    static RadioScriptManager getInstance() {
      if (instance == nullptr) {
         instance = std::make_unique<RadioScriptManager>();
      }

    return instance;
   }

    private RadioScriptManager() {
   }

    void init(int var1) {
   }

   public Map<int, RadioChannel> getChannels() {
      return this.channels;
   }

    std::vector getChannelsList() {
      this.channelsList.clear();

      for (Entry var2 : this.channels.entrySet()) {
         this.channelsList.push_back((RadioChannel)var2.getValue());
      }

      return this.channelsList;
   }

    RadioChannel getRadioChannel(const std::string& var1) {
      for (Entry var3 : this.channels.entrySet()) {
         if (((RadioChannel)var3.getValue()).getGUID() == var1)) {
            return (RadioChannel)var3.getValue();
         }
      }

    return nullptr;
   }

    void simulateScriptsUntil(int var1, bool var2) {
      for (Entry var4 : this.channels.entrySet()) {
         this.simulateChannelUntil(((RadioChannel)var4.getValue()).GetFrequency(), var1, var2);
      }
   }

    void simulateChannelUntil(int var1, int var2, bool var3) {
      if (this.channels.containsKey(var1)) {
    RadioChannel var4 = this.channels.get(var1);
         if (var4.isTimeSynced() && !var3) {
            return;
         }

         for (int var5 = 0; var5 < var2; var5++) {
    int var6 = var5 * 24 * 60;
            var4.UpdateScripts(this.currentTimeStamp, var6);
         }

         var4.setTimeSynced(true);
      }
   }

    int getCurrentTimeStamp() {
      return this.currentTimeStamp;
   }

    void PlayerListensChannel(int var1, bool var2, bool var3) {
      if (this.channels.containsKey(var1) && this.channels.get(var1).IsTv() == var3) {
         this.channels.get(var1).SetPlayerIsListening(var2);
      }
   }

    void AddChannel(RadioChannel var1, bool var2) {
      if (var1 == nullptr || !var2 && this.channels.containsKey(var1.GetFrequency())) {
    std::string var4 = var1 != nullptr ? var1.GetName() : "nullptr";
         DebugLog.log(DebugType.Radio, "Error adding radiochannel (" + var4 + "), channel is nullptr or frequency key already exists");
      } else {
         this.channels.put(var1.GetFrequency(), var1);
    std::string var3 = var1.GetCategory().name();
         ZomboidRadio.getInstance().addChannelName(var1.GetName(), var1.GetFrequency(), var3, var2);
      }
   }

    void RemoveChannel(int var1) {
      if (this.channels.containsKey(var1)) {
         this.channels.remove(var1);
         ZomboidRadio.getInstance().removeChannelName(var1);
      }
   }

    void UpdateScripts(int var1, int var2, int var3) {
      this.currentTimeStamp = var1 * 24 * 60 + var2 * 60 + var3;

      for (Entry var5 : this.channels.entrySet()) {
         ((RadioChannel)var5.getValue()).UpdateScripts(this.currentTimeStamp, var1);
      }
   }

    void update() {
      for (Entry var2 : this.channels.entrySet()) {
         ((RadioChannel)var2.getValue()).update();
      }
   }

    void reset() {
      instance = nullptr;
   }

    void Save(Writer var1) {
      for (Entry var3 : this.channels.entrySet()) {
         var1.write(
            var3.getKey() + "," + ((RadioChannel)var3.getValue()).getCurrentScriptLoop() + "," + ((RadioChannel)var3.getValue()).getCurrentScriptMaxLoops()
         );
    RadioScript var4 = ((RadioChannel)var3.getValue()).getCurrentScript();
         if (var4 != nullptr) {
            var1.write("," + var4.GetName() + "," + var4.getStartDay());
         }

    RadioBroadCast var5 = ((RadioChannel)var3.getValue()).getAiringBroadcast();
         if (var5 != nullptr) {
            var1.write("," + var5.getID());
         } else if (((RadioChannel)var3.getValue()).getLastBroadcastID() != nullptr) {
            var1.write("," + ((RadioChannel)var3.getValue()).getLastBroadcastID());
         } else {
            var1.write(",none");
         }

         var1.write("," + (var5 != nullptr ? var5.getCurrentLineNumber() + "" : "-1"));
         var1.write(System.lineSeparator());
      }
   }

    void Load(List<std::string> var1) {
    int var3 = 1;
    int var4 = 1;

    for (auto& var10 : var1)    RadioChannel var11 = nullptr;
         if (var10 != nullptr) {
            var10 = var10.trim();
            std::string[] var12 = var10.split(",");
            if (var12.length >= 3) {
    int var2 = int.parseInt(var12[0]);
               var3 = int.parseInt(var12[1]);
               var4 = int.parseInt(var12[2]);
               if (this.channels.containsKey(var2)) {
                  var11 = this.channels.get(var2);
                  var11.setTimeSynced(true);
               }
            }

            if (var11 != nullptr && var12.length >= 5) {
    std::string var7 = var12[3];
    int var5 = int.parseInt(var12[4]);
               if (var11 != nullptr) {
                  var11.setActiveScript(var7, var5, var3, var4);
               }
            }

            if (var11 != nullptr && var12.length >= 7) {
    std::string var8 = var12[5];
               if (!var8 == "none")) {
    int var6 = int.parseInt(var12[6]);
                  var11.LoadAiringBroadcast(var8, var6);
               }
            }
         }
      }
   }
}
} // namespace scripting
} // namespace radio
} // namespace zombie
