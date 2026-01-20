#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/math/PZMath.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace advancedanimation {


class AnimationVariableSlotFloat : public AnimationVariableSlot {
public:
    float m_value = 0.0F;

    public AnimationVariableSlotFloat(const std::string& var1) {
      super(var1);
   }

    std::string getValueString() {
      return std::string.valueOf(this.m_value);
   }

    float getValueFloat() {
      return this.m_value;
   }

    bool getValueBool() {
      return this.m_value != 0.0F;
   }

    void setValue(const std::string& var1) {
      this.m_value = PZMath.tryParseFloat(var1, 0.0F);
   }

    void setValue(float var1) {
      this.m_value = var1;
   }

    void setValue(bool var1) {
      this.m_value = var1 ? 1.0F : 0.0F;
   }

    AnimationVariableType getType() {
      return AnimationVariableType.float;
   }

    bool canConvertFrom(const std::string& var1) {
      return PZMath.canParseFloat(var1);
   }

    void clear() {
      this.m_value = 0.0F;
   }
}
} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
