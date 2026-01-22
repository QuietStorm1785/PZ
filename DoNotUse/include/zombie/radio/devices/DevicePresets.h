#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/GameWindow.h"
#include "zombie/Lua/LuaManager.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace radio {
namespace devices {


class DevicePresets {
public:
    int maxPresets = 10;
   protected std::vector<PresetEntry> presets = std::make_unique<std::vector<>>();

    void* clone() {
      return super.clone();
   }

    KahluaTable getPresetsLua() {
    KahluaTable var1 = LuaManager.platform.newTable();

      for (int var2 = 0; var2 < this.presets.size(); var2++) {
    PresetEntry var3 = this.presets.get(var2);
    KahluaTable var4 = LuaManager.platform.newTable();
         var4.rawset("name", var3.name);
         var4.rawset("frequency", var3.frequency);
         var1.rawset(var2, var4);
      }

    return var1;
   }

   public std::vector<PresetEntry> getPresets() {
      return this.presets;
   }

    void setPresets(std::vector<PresetEntry> var1) {
      this.presets = var1;
   }

    int getMaxPresets() {
      return this.maxPresets;
   }

    void setMaxPresets(int var1) {
      this.maxPresets = var1;
   }

    void addPreset(const std::string& var1, int var2) {
      if (this.presets.size() < this.maxPresets) {
         this.presets.push_back(std::make_shared<PresetEntry>(var1, var2));
      }
   }

    void removePreset(int var1) {
      if (this.presets.size() != 0 && var1 >= 0 && var1 < this.presets.size()) {
         this.presets.remove(var1);
      }
   }

    std::string getPresetName(int var1) {
      return this.presets.size() != 0 && var1 >= 0 && var1 < this.presets.size() ? this.presets.get(var1).name : "";
   }

    int getPresetFreq(int var1) {
      return this.presets.size() != 0 && var1 >= 0 && var1 < this.presets.size() ? this.presets.get(var1).frequency : -1;
   }

    void setPresetName(int var1, const std::string& var2) {
      if (var2 == nullptr) {
         var2 = "name-is-nullptr";
      }

      if (this.presets.size() != 0 && var1 >= 0 && var1 < this.presets.size()) {
    PresetEntry var3 = this.presets.get(var1);
         var3.name = var2;
      }
   }

    void setPresetFreq(int var1, int var2) {
      if (this.presets.size() != 0 && var1 >= 0 && var1 < this.presets.size()) {
    PresetEntry var3 = this.presets.get(var1);
         var3.frequency = var2;
      }
   }

    void setPreset(int var1, const std::string& var2, int var3) {
      if (var2 == nullptr) {
         var2 = "name-is-nullptr";
      }

      if (this.presets.size() != 0 && var1 >= 0 && var1 < this.presets.size()) {
    PresetEntry var4 = this.presets.get(var1);
         var4.name = var2;
         var4.frequency = var3;
      }
   }

    void clearPresets() {
      this.presets.clear();
   }

    void save(ByteBuffer var1, bool var2) {
      var1.putInt(this.maxPresets);
      var1.putInt(this.presets.size());

      for (int var3 = 0; var3 < this.presets.size(); var3++) {
    PresetEntry var4 = this.presets.get(var3);
         GameWindow.WriteString(var1, var4.name);
         var1.putInt(var4.frequency);
      }
   }

    void load(ByteBuffer var1, int var2, bool var3) {
      if (var2 >= 69) {
         this.clearPresets();
         this.maxPresets = var1.getInt();
    int var4 = var1.getInt();

         for (int var5 = 0; var5 < var4; var5++) {
    std::string var6 = GameWindow.ReadString(var1);
    int var7 = var1.getInt();
            if (this.presets.size() < this.maxPresets) {
               this.presets.push_back(std::make_shared<PresetEntry>(var6, var7));
            }
         }
      }
   }
}
} // namespace devices
} // namespace radio
} // namespace zombie
