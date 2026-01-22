#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace iso {

class IsoPuddles {
public:
    float finalValue;
    bool isAdminOverride = false;
    float adminValue;
    float min = 0.0F;
    float max = 1.0F;
    float delta = 0.01F;
    int ID;
    std::string name;

   public IsoPuddles$PuddlesFloat init(int var1, std::string var2) {
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

    void setEnableAdmin(bool var1) {
      this.isAdminOverride = var1;
   }

    bool isEnableAdmin() {
      return this.isAdminOverride;
   }

    void setAdminValue(float var1) {
      this.adminValue = Math.max(this.min, Math.min(this.max, var1));
   }

    float getAdminValue() {
      return this.adminValue;
   }

    void setFinalValue(float var1) {
      this.finalValue = Math.max(this.min, Math.min(this.max, var1));
   }

    void addFinalValue(float var1) {
      this.finalValue = Math.max(this.min, Math.min(this.max, this.finalValue + var1));
   }

    void addFinalValueForMax(float var1, float var2) {
      this.finalValue = Math.max(this.min, Math.min(var2, this.finalValue + var1));
   }

    float getFinalValue() {
      return this.isAdminOverride ? this.adminValue : this.finalValue;
   }

    void interpolateFinalValue(float var1) {
      if (Math.abs(this.finalValue - var1) < this.delta) {
         this.finalValue = var1;
      } else if (var1 > this.finalValue) {
         this.finalValue = this.finalValue + this.delta;
      } else {
         this.finalValue = this.finalValue - this.delta;
      }
   }

    void calculate() {
      if (this.isAdminOverride) {
         this.finalValue = this.adminValue;
      }
   }
}
} // namespace iso
} // namespace zombie
