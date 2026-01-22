#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/debug/DebugLog.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace advancedanimation {


class AnimationVariableGenericSlot : public AnimationVariableSlot {
public:
    AnimationVariableType m_type = AnimationVariableType.Void;
    IAnimationVariableSlot m_valueSlot;

    public AnimationVariableGenericSlot(const std::string& var1) {
      super(var1);
   }

    std::string getValueString() {
      return this.m_valueSlot != nullptr ? this.m_valueSlot.getValueString() : nullptr;
   }

    float getValueFloat() {
      return this.m_valueSlot != nullptr ? this.m_valueSlot.getValueFloat() : 0.0F;
   }

    bool getValueBool() {
      return this.m_valueSlot != nullptr && this.m_valueSlot.getValueBool();
   }

    void setValue(const std::string& var1) {
      if (this.m_valueSlot == nullptr || !this.m_valueSlot.canConvertFrom(var1)) {
         this.m_valueSlot = std::make_shared<AnimationVariableSlotString>(this.getKey());
         this.setType(this.m_valueSlot.getType());
      }

      this.m_valueSlot.setValue(var1);
   }

    void setValue(float var1) {
      if (this.m_valueSlot == nullptr || this.m_type != AnimationVariableType.float) {
         this.m_valueSlot = std::make_shared<AnimationVariableSlotFloat>(this.getKey());
         this.setType(this.m_valueSlot.getType());
      }

      this.m_valueSlot.setValue(var1);
   }

    void setValue(bool var1) {
      if (this.m_valueSlot == nullptr || this.m_type != AnimationVariableType.bool) {
         this.m_valueSlot = std::make_shared<AnimationVariableSlotBool>(this.getKey());
         this.setType(this.m_valueSlot.getType());
      }

      this.m_valueSlot.setValue(var1);
   }

    AnimationVariableType getType() {
      return this.m_type;
   }

    void setType(AnimationVariableType var1) {
      if (this.m_type != var1) {
         if (this.m_type != AnimationVariableType.Void) {
            DebugLog.General.printf("Variable %s converting from %s to %s\n", new Object[]{this.getKey(), this.m_type, var1});
         }

         this.m_type = var1;
      }
   }

    bool canConvertFrom(const std::string& var1) {
    return true;
   }

    void clear() {
      this.m_type = AnimationVariableType.Void;
      this.m_valueSlot = nullptr;
   }
}
} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
