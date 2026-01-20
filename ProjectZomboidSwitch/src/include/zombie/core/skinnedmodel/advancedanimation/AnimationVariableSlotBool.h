#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/util/StringUtils.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace advancedanimation {


class AnimationVariableSlotBool : public AnimationVariableSlot {
public:
    bool m_value;

    public AnimationVariableSlotBool(const std::string& var1) {
      super(var1);
   }

    std::string getValueString() {
      return this.m_value ? "true" : "false";
   }

    float getValueFloat() {
      return this.m_value ? 1.0F : 0.0F;
   }

    bool getValueBool() {
      return this.m_value;
   }

    void setValue(const std::string& var1) {
      this.m_value = StringUtils.tryParseBoolean(var1);
   }

    void setValue(float var1) {
      this.m_value = var1 != 0.0;
   }

    void setValue(bool var1) {
      this.m_value = var1;
   }

    AnimationVariableType getType() {
      return AnimationVariableType.bool;
   }

    bool canConvertFrom(const std::string& var1) {
      return StringUtils.isBoolean(var1);
   }

    void clear() {
      this.m_value = false;
   }
}
} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
