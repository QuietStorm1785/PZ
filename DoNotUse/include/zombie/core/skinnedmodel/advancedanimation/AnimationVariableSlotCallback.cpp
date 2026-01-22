#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/skinnedmodel/advancedanimation/AnimationVariableSlotCallback/CallbackGet.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimationVariableSlotCallback/CallbackSet.h"
#include "zombie/debug/DebugLog.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace advancedanimation {


class AnimationVariableSlotCallback {
public:
   private const CallbackGet<VariableType> m_callbackGet;
   private const CallbackSet<VariableType> m_callbackSet;

    protected AnimationVariableSlotCallback(const std::string& var1, CallbackGet<VariableType> var2) {
      this(var1, var2, nullptr);
   }

    protected AnimationVariableSlotCallback(const std::string& var1, CallbackGet<VariableType> var2, CallbackSet<VariableType> var3) {
      super(var1);
      this.m_callbackGet = var2;
      this.m_callbackSet = var3;
   }

    VariableType getValue() {
      return (VariableType)this.m_callbackGet.call();
   }

   public abstract VariableType getDefaultValue();

    bool trySetValue(VariableType var1) {
      if (this.isReadOnly()) {
         DebugLog.General.warn("Trying to set read-only variable \"%s\"", new Object[]{super.getKey()});
    return false;
      } else {
         this.m_callbackSet.call(var1);
    return true;
      }
   }

    bool isReadOnly() {
      return this.m_callbackSet == nullptr;
   }

    void clear() {
      if (!this.isReadOnly()) {
         this.trySetValue(this.getDefaultValue());
      }
   }
}
} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
