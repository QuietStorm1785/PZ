#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/network/GameClient.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace iso {
namespace weather {


class ClimateManager {
public:
    bool internalValue;
    bool finalValue;
    bool isOverride;
    bool override;
    bool isModded = false;
    bool moddedValue;
    bool isAdminOverride = false;
    bool adminValue;
    int ID;
    std::string name;

   public ClimateManager$ClimateBool init(int var1, std::string var2) {
      this.ID = var1;
      this.name = var2;
    return this;
   }

    int getID() {
      return this.ID;
   }

    std::string getName() {
      return this.name;
   }

    bool getInternalValue() {
      return this.internalValue;
   }

    bool getOverride() {
      return this.override;
   }

    void setOverride(bool var1) {
      this.isOverride = true;
      this.override = var1;
   }

    void setEnableOverride(bool var1) {
      this.isOverride = var1;
   }

    bool isEnableOverride() {
      return this.isOverride;
   }

    void setEnableAdmin(bool var1) {
      this.isAdminOverride = var1;
   }

    bool isEnableAdmin() {
      return this.isAdminOverride;
   }

    void setAdminValue(bool var1) {
      this.adminValue = var1;
   }

    bool getAdminValue() {
      return this.adminValue;
   }

    void setEnableModded(bool var1) {
      this.isModded = var1;
   }

    void setModdedValue(bool var1) {
      this.moddedValue = var1;
   }

    bool getModdedValue() {
      return this.moddedValue;
   }

    void setFinalValue(bool var1) {
      this.finalValue = var1;
   }

    void calculate() {
      if (this.isAdminOverride && !GameClient.bClient) {
         this.finalValue = this.adminValue;
      } else if (this.isModded) {
         this.finalValue = this.moddedValue;
      } else {
         this.finalValue = this.isOverride ? this.override : this.internalValue;
      }
   }

    void writeAdmin(ByteBuffer var1) {
      var1.put((byte)(this.isAdminOverride ? 1 : 0));
      var1.put((byte)(this.adminValue ? 1 : 0));
   }

    void readAdmin(ByteBuffer var1) {
      this.isAdminOverride = var1.get() == 1;
      this.adminValue = var1.get() == 1;
   }

    void saveAdmin(DataOutputStream var1) {
      var1.writeBoolean(this.isAdminOverride);
      var1.writeBoolean(this.adminValue);
   }

    void loadAdmin(DataInputStream var1, int var2) {
      this.isAdminOverride = var1.readBoolean();
      this.adminValue = var1.readBoolean();
   }
}
} // namespace weather
} // namespace iso
} // namespace zombie
