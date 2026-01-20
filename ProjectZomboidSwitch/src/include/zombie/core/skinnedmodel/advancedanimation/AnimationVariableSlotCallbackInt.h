#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/math/PZMath.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimationVariableSlotCallbackInt/CallbackGetStrongTyped.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimationVariableSlotCallbackInt/CallbackSetStrongTyped.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace advancedanimation {


class AnimationVariableSlotCallbackInt : public AnimationVariableSlotCallback {
public:
    int m_defaultValue = 0;

    public AnimationVariableSlotCallbackInt(const std::string& var1, CallbackGetStrongTyped var2) {
      super(var1, var2);
   }

    public AnimationVariableSlotCallbackInt(const std::string& var1, CallbackGetStrongTyped var2, CallbackSetStrongTyped var3) {
      super(var1, var2, var3);
   }

    public AnimationVariableSlotCallbackInt(const std::string& var1, int var2, CallbackGetStrongTyped var3) {
      super(var1, var3);
      this.m_defaultValue = var2;
   }

    public AnimationVariableSlotCallbackInt(const std::string& var1, int var2, CallbackGetStrongTyped var3, CallbackSetStrongTyped var4) {
      super(var1, var3, var4);
      this.m_defaultValue = var2;
   }

    int getDefaultValue() {
      return this.m_defaultValue;
   }

    std::string getValueString() {
      return ((int)this.getValue());
   }

    float getValueFloat() {
      return ((int)this.getValue()).intValue();
   }

    bool getValueBool() {
      return this.getValueFloat() != 0.0F;
   }

    void setValue(const std::string& var1) {
      this.trySetValue(PZMath.tryParseInt(var1, 0));
   }

    void setValue(float var1) {
      this.trySetValue((int)var1);
   }

    void setValue(bool var1) {
      this.trySetValue(var1 ? 1 : 0);
   }

    AnimationVariableType getType() {
      return AnimationVariableType.float;
   }

    bool canConvertFrom(const std::string& var1) {
    return true;
   }
}
} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
