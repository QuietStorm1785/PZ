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
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class AnimationVariableSlotCallback {
public:
 private AnimationVariableSlotCallback.CallbackGet<VariableType> m_callbackGet;
 private AnimationVariableSlotCallback.CallbackSet<VariableType> m_callbackSet;

 protected AnimationVariableSlotCallback(const std::string& string, AnimationVariableSlotCallback.CallbackGet<VariableType> callbackGet) {
 this(string, callbackGet, nullptr);
 }

 protected AnimationVariableSlotCallback(
 String string, AnimationVariableSlotCallback.CallbackGet<VariableType> callbackGet, AnimationVariableSlotCallback.CallbackSet<VariableType> callbackSet
 ) {
 super(string);
 this->m_callbackGet = callbackGet;
 this->m_callbackSet = callbackSet;
 }

 VariableType getValue() {
 return this->m_callbackGet.call();
 }

 public VariableType getDefaultValue();

 bool trySetValue(VariableType object) {
 if (this->isReadOnly()) {
 DebugLog.General.warn("Trying to set read-only variable \"%s\"", super.getKey());
 return false;
 } else {
 this->m_callbackSet.call((VariableType)object);
 return true;
 }
 }

 bool isReadOnly() {
 return this->m_callbackSet.empty();
 }

 void clear() {
 if (!this->isReadOnly()) {
 this->trySetValue(this->getDefaultValue());
 }
 }

 public interface CallbackGet<VariableType> {
 VariableType call();
 }

 public interface CallbackSet<VariableType> {
 void call(VariableType var1);
 }
}
} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
