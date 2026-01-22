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
    float internalValue;
    float finalValue;
    bool isOverride = false;
    float override;
    float interpolate;
    bool isModded = false;
    float moddedValue;
    float modInterpolate;
    bool isAdminOverride = false;
    float adminValue;
    float min = 0.0F;
    float max = 1.0F;
    int ID;
    std::string name;

   public ClimateManager$ClimateFloat init(int var1, std::string var2) {
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

    float getMin() {
      return this.min;
   }

    float getMax() {
      return this.max;
   }

    float getInternalValue() {
      return this.internalValue;
   }

    float getOverride() {
      return this.override;
   }

    float getOverrideInterpolate() {
      return this.interpolate;
   }

    void setOverride(float var1, float var2) {
      this.override = var1;
      this.interpolate = var2;
      this.isOverride = true;
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

    void setAdminValue(float var1) {
      this.adminValue = ClimateManager.clamp(this.min, this.max, var1);
   }

    float getAdminValue() {
      return this.adminValue;
   }

    void setEnableModded(bool var1) {
      this.isModded = var1;
   }

    void setModdedValue(float var1) {
      this.moddedValue = ClimateManager.clamp(this.min, this.max, var1);
   }

    float getModdedValue() {
      return this.moddedValue;
   }

    void setModdedInterpolate(float var1) {
      this.modInterpolate = ClimateManager.clamp01(var1);
   }

    void setFinalValue(float var1) {
      this.finalValue = var1;
   }

    float getFinalValue() {
      return this.finalValue;
   }

    void calculate() {
      if (this.isAdminOverride && !GameClient.bClient) {
         this.finalValue = this.adminValue;
      } else {
         if (this.isModded && this.modInterpolate > 0.0F) {
            this.internalValue = ClimateManager.lerp(this.modInterpolate, this.internalValue, this.moddedValue);
         }

         if (this.isOverride && this.interpolate > 0.0F) {
            this.finalValue = ClimateManager.lerp(this.interpolate, this.internalValue, this.override);
         } else {
            this.finalValue = this.internalValue;
         }
      }
   }

    void writeAdmin(ByteBuffer var1) {
      var1.put((byte)(this.isAdminOverride ? 1 : 0));
      var1.putFloat(this.adminValue);
   }

    void readAdmin(ByteBuffer var1) {
      this.isAdminOverride = var1.get() == 1;
      this.adminValue = var1.getFloat();
   }

    void saveAdmin(DataOutputStream var1) {
      var1.writeBoolean(this.isAdminOverride);
      var1.writeFloat(this.adminValue);
   }

    void loadAdmin(DataInputStream var1, int var2) {
      this.isAdminOverride = var1.readBoolean();
      this.adminValue = var1.readFloat();
   }
}
} // namespace weather
} // namespace iso
} // namespace zombie
