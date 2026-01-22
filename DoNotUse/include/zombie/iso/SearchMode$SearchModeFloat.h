#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/math/PZMath.h"

namespace zombie {
namespace iso {


class SearchMode {
public:
    const float min;
    const float max;
    const float stepsize;
    float exterior;
    float targetExterior;
    float interior;
    float targetInterior;

   private SearchMode$SearchModeFloat(float var1, float var2, float var3) {
      this.min = var1;
      this.max = var2;
      this.stepsize = var3;
   }

    void set(float var1, float var2, float var3, float var4) {
      this.setExterior(var1);
      this.setTargetExterior(var2);
      this.setInterior(var3);
      this.setTargetInterior(var4);
   }

    void setTargets(float var1, float var2) {
      this.setTargetExterior(var1);
      this.setTargetInterior(var2);
   }

    float getExterior() {
      return this.exterior;
   }

    void setExterior(float var1) {
      this.exterior = var1;
   }

    float getTargetExterior() {
      return this.targetExterior;
   }

    void setTargetExterior(float var1) {
      this.targetExterior = var1;
   }

    float getInterior() {
      return this.interior;
   }

    void setInterior(float var1) {
      this.interior = var1;
   }

    float getTargetInterior() {
      return this.targetInterior;
   }

    void setTargetInterior(float var1) {
      this.targetInterior = var1;
   }

    void update(float var1) {
      this.exterior = var1 * this.targetExterior;
      this.interior = var1 * this.targetInterior;
   }

    void equalise() {
      if (!PZMath.equal(this.exterior, this.targetExterior, 0.001F)) {
         this.exterior = PZMath.lerp(this.exterior, this.targetExterior, 0.01F);
      } else {
         this.exterior = this.targetExterior;
      }

      if (!PZMath.equal(this.interior, this.targetInterior, 0.001F)) {
         this.interior = PZMath.lerp(this.interior, this.targetInterior, 0.01F);
      } else {
         this.interior = this.targetInterior;
      }
   }

    void reset() {
      this.exterior = 0.0F;
      this.interior = 0.0F;
   }

    float getMin() {
      return this.min;
   }

    float getMax() {
      return this.max;
   }

    float getStepsize() {
      return this.stepsize;
   }
}
} // namespace iso
} // namespace zombie
