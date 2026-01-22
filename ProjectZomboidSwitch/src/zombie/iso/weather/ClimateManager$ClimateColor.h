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
    ClimateColorInfo internalValue = std::make_shared<ClimateColorInfo>();
    ClimateColorInfo finalValue = std::make_shared<ClimateColorInfo>();
    bool isOverride = false;
    ClimateColorInfo override = std::make_shared<ClimateColorInfo>();
    float interpolate;
    bool isModded = false;
    ClimateColorInfo moddedValue = std::make_shared<ClimateColorInfo>();
    float modInterpolate;
    bool isAdminOverride = false;
    ClimateColorInfo adminValue = std::make_shared<ClimateColorInfo>();
    int ID;
    std::string name;

   public ClimateManager$ClimateColor init(int var1, std::string var2) {
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

    ClimateColorInfo getInternalValue() {
      return this.internalValue;
   }

    ClimateColorInfo getOverride() {
      return this.override;
   }

    float getOverrideInterpolate() {
      return this.interpolate;
   }

    void setOverride(ClimateColorInfo var1, float var2) {
      this.override.setTo(var1);
      this.interpolate = var2;
      this.isOverride = true;
   }

    void setOverride(ByteBuffer var1, float var2) {
      this.override.read(var1);
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

    void setAdminValue(float var1, float var2, float var3, float var4, float var5, float var6, float var7, float var8) {
      this.adminValue.getExterior().r = var1;
      this.adminValue.getExterior().g = var2;
      this.adminValue.getExterior().b = var3;
      this.adminValue.getExterior().a = var4;
      this.adminValue.getInterior().r = var5;
      this.adminValue.getInterior().g = var6;
      this.adminValue.getInterior().b = var7;
      this.adminValue.getInterior().a = var8;
   }

    void setAdminValueExterior(float var1, float var2, float var3, float var4) {
      this.adminValue.getExterior().r = var1;
      this.adminValue.getExterior().g = var2;
      this.adminValue.getExterior().b = var3;
      this.adminValue.getExterior().a = var4;
   }

    void setAdminValueInterior(float var1, float var2, float var3, float var4) {
      this.adminValue.getInterior().r = var1;
      this.adminValue.getInterior().g = var2;
      this.adminValue.getInterior().b = var3;
      this.adminValue.getInterior().a = var4;
   }

    void setAdminValue(ClimateColorInfo var1) {
      this.adminValue.setTo(var1);
   }

    ClimateColorInfo getAdminValue() {
      return this.adminValue;
   }

    void setEnableModded(bool var1) {
      this.isModded = var1;
   }

    void setModdedValue(ClimateColorInfo var1) {
      this.moddedValue.setTo(var1);
   }

    ClimateColorInfo getModdedValue() {
      return this.moddedValue;
   }

    void setModdedInterpolate(float var1) {
      this.modInterpolate = ClimateManager.clamp01(var1);
   }

    void setFinalValue(ClimateColorInfo var1) {
      this.finalValue.setTo(var1);
   }

    ClimateColorInfo getFinalValue() {
      return this.finalValue;
   }

    void calculate() {
      if (this.isAdminOverride && !GameClient.bClient) {
         this.finalValue.setTo(this.adminValue);
      } else {
         if (this.isModded && this.modInterpolate > 0.0F) {
            this.internalValue.interp(this.moddedValue, this.modInterpolate, this.internalValue);
         }

         if (this.isOverride && this.interpolate > 0.0F) {
            this.internalValue.interp(this.override, this.interpolate, this.finalValue);
         } else {
            this.finalValue.setTo(this.internalValue);
         }
      }
   }

    void writeAdmin(ByteBuffer var1) {
      var1.put((byte)(this.isAdminOverride ? 1 : 0));
      this.adminValue.write(var1);
   }

    void readAdmin(ByteBuffer var1) {
      this.isAdminOverride = var1.get() == 1;
      this.adminValue.read(var1);
   }

    void saveAdmin(DataOutputStream var1) {
      var1.writeBoolean(this.isAdminOverride);
      this.adminValue.save(var1);
   }

    void loadAdmin(DataInputStream var1, int var2) {
      this.isAdminOverride = var1.readBoolean();
      if (var2 < 143) {
         this.adminValue.getInterior().r = var1.readFloat();
         this.adminValue.getInterior().g = var1.readFloat();
         this.adminValue.getInterior().b = var1.readFloat();
         this.adminValue.getInterior().a = var1.readFloat();
         this.adminValue.getExterior().r = this.adminValue.getInterior().r;
         this.adminValue.getExterior().g = this.adminValue.getInterior().g;
         this.adminValue.getExterior().b = this.adminValue.getInterior().b;
         this.adminValue.getExterior().a = this.adminValue.getInterior().a;
      } else {
         this.adminValue.load(var1, var2);
      }
   }
}
} // namespace weather
} // namespace iso
} // namespace zombie
