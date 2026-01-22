#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/math/PZMath.h"
#include "zombie/util/StringUtils.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace advancedanimation {


class AnimationVariableSlotString : public AnimationVariableSlot {
public:
    std::string m_value;

    public AnimationVariableSlotString(const std::string& var1) {
      super(var1);
   }

    std::string getValueString() {
      return this.m_value;
   }

    float getValueFloat() {
      return PZMath.tryParseFloat(this.m_value, 0.0F);
   }

    bool getValueBool() {
      return StringUtils.tryParseBoolean(this.m_value);
   }

    void setValue(const std::string& var1) {
      this.m_value = var1;
   }

    void setValue(float var1) {
      this.m_value = std::string.valueOf(var1);
   }

    void setValue(bool var1) {
      this.m_value = var1 ? "true" : "false";
   }

    AnimationVariableType getType() {
      return AnimationVariableType.std::string;
   }

    bool canConvertFrom(const std::string& var1) {
    return true;
   }

    void clear() {
      this.m_value = "";
   }
}
} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
