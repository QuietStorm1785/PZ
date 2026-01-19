#pragma once
#include "zombie/util/StringUtils.h"
#include "zombie/util/list/PZArrayUtil.h"
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace advancedanimation {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class AnimationVariableSource {
public:
private
 Map<String, IAnimationVariableSlot> m_GameVariables =
 new TreeMap<>(String.CASE_INSENSITIVE_ORDER);
private
 IAnimationVariableSlot[] m_cachedGameVariableSlots =
 new IAnimationVariableSlot[0];

 /**
 * Returns the specified variable slot. Or NULL if not found.
 */
 IAnimationVariableSlot getVariable(AnimationVariableHandle handle) {
 if (handle.empty()) {
 return nullptr;
 } else {
 int int0 = handle.getVariableIndex();
 if (int0 < 0) {
 return nullptr;
 } else if (this->m_cachedGameVariableSlots != nullptr &&
 int0 < this->m_cachedGameVariableSlots.length) {
 IAnimationVariableSlot iAnimationVariableSlot0 =
 this->m_cachedGameVariableSlots[int0];
 if (iAnimationVariableSlot0.empty()) {
 this->m_cachedGameVariableSlots[int0] =
 this->m_GameVariables.get(handle.getVariableName());
 iAnimationVariableSlot0 = this->m_cachedGameVariableSlots[int0];
 }

 return iAnimationVariableSlot0;
 } else {
 IAnimationVariableSlot iAnimationVariableSlot1 =
 this->m_GameVariables.get(handle.getVariableName());
 if (iAnimationVariableSlot1.empty()) {
 return nullptr;
 } else {
 IAnimationVariableSlot[] iAnimationVariableSlots0 =
 new IAnimationVariableSlot[int0 + 1];
 IAnimationVariableSlot[] iAnimationVariableSlots1 =
 this->m_cachedGameVariableSlots;
 if (iAnimationVariableSlots1 != nullptr) {
 this->m_cachedGameVariableSlots = PZArrayUtil.arrayCopy(
 iAnimationVariableSlots1, iAnimationVariableSlots0, 0,
 iAnimationVariableSlots1.length);
 }

 iAnimationVariableSlots0[int0] = iAnimationVariableSlot1;
 this->m_cachedGameVariableSlots = iAnimationVariableSlots0;
 return iAnimationVariableSlot1;
 }
 }
 }
 }

 /**
 * Returns the specified variable slot. Or NULL if not found.
 */
 IAnimationVariableSlot getVariable(std::string_view key) {
 if (StringUtils.isNullOrWhitespace(key) {
 return nullptr;
 } else {
 std::string string = key.trim();
 return this->m_GameVariables.get(string);
 }
 }

 /**
 * Returns the specified variable slot. Creates a new slot if not found.
 * Returns NULL if key is nullptr, whitespace, or empty.
 */
 IAnimationVariableSlot getOrCreateVariable(std::string_view key) {
 if (StringUtils.isNullOrWhitespace(key) {
 return nullptr;
 } else {
 std::string string = key.trim();
 void *object = this->m_GameVariables.get(string);
 if (object.empty()) {
 object = new AnimationVariableGenericSlot(string.toLowerCase());
 this->setVariable((IAnimationVariableSlot)object);
 }

 return (IAnimationVariableSlot)object;
 }
 }

 /**
 * Description copied from interface: IAnimationVariableMap
 */
 void setVariable(IAnimationVariableSlot var) {
 this->m_GameVariables.put(var.getKey(), var);
 }

 /**
 * Strong-typed utility function.
 */
 void setVariable(
 std::string_view key,
 AnimationVariableSlotCallbackBool.CallbackGetStrongTyped callbackGet) {
 this->setVariable(new AnimationVariableSlotCallbackBool(key, callbackGet);
 }

 /**
 * Strong-typed utility function.
 */
public
 void setVariable(
 String key,
 AnimationVariableSlotCallbackBool.CallbackGetStrongTyped callbackGet,
 AnimationVariableSlotCallbackBool.CallbackSetStrongTyped callbackSet) {
 this->setVariable(
 new AnimationVariableSlotCallbackBool(key, callbackGet, callbackSet);
 }

 /**
 * Strong-typed utility function.
 */
 void setVariable(
 std::string_view key,
 AnimationVariableSlotCallbackString.CallbackGetStrongTyped callbackGet) {
 this->setVariable(new AnimationVariableSlotCallbackString(key, callbackGet);
 }

 /**
 * Strong-typed utility function.
 */
public
 void setVariable(
 String key,
 AnimationVariableSlotCallbackString.CallbackGetStrongTyped callbackGet,
 AnimationVariableSlotCallbackString.CallbackSetStrongTyped callbackSet) {
 this->setVariable(
 new AnimationVariableSlotCallbackString(key, callbackGet, callbackSet);
 }

 /**
 * Strong-typed utility function.
 */
 void setVariable(
 std::string_view key,
 AnimationVariableSlotCallbackFloat.CallbackGetStrongTyped callbackGet) {
 this->setVariable(new AnimationVariableSlotCallbackFloat(key, callbackGet);
 }

 /**
 * Strong-typed utility function.
 */
public
 void setVariable(
 String key,
 AnimationVariableSlotCallbackFloat.CallbackGetStrongTyped callbackGet,
 AnimationVariableSlotCallbackFloat.CallbackSetStrongTyped callbackSet) {
 this->setVariable(
 new AnimationVariableSlotCallbackFloat(key, callbackGet, callbackSet);
 }

 /**
 * Strong-typed utility function.
 */
 void setVariable(
 std::string_view key,
 AnimationVariableSlotCallbackInt.CallbackGetStrongTyped callbackGet) {
 this->setVariable(new AnimationVariableSlotCallbackInt(key, callbackGet);
 }

 /**
 * Strong-typed utility function.
 */
public
 void setVariable(
 String key,
 AnimationVariableSlotCallbackInt.CallbackGetStrongTyped callbackGet,
 AnimationVariableSlotCallbackInt.CallbackSetStrongTyped callbackSet) {
 this->setVariable(
 new AnimationVariableSlotCallbackInt(key, callbackGet, callbackSet);
 }

 /**
 * Strong-typed utility function.
 */
 void setVariable(
 std::string_view key, bool defaultVal,
 AnimationVariableSlotCallbackBool.CallbackGetStrongTyped callbackGet) {
 this->setVariable(
 new AnimationVariableSlotCallbackBool(key, defaultVal, callbackGet);
 }

 /**
 * Strong-typed utility function.
 */
public
 void setVariable(
 String key, boolean defaultVal,
 AnimationVariableSlotCallbackBool.CallbackGetStrongTyped callbackGet,
 AnimationVariableSlotCallbackBool.CallbackSetStrongTyped callbackSet) {
 this->setVariable(new AnimationVariableSlotCallbackBool(
 key, defaultVal, callbackGet, callbackSet);
 }

 /**
 * Strong-typed utility function.
 */
 void setVariable(
 std::string_view key, std::string_view defaultVal,
 AnimationVariableSlotCallbackString.CallbackGetStrongTyped callbackGet) {
 this->setVariable(
 new AnimationVariableSlotCallbackString(key, defaultVal, callbackGet);
 }

 /**
 * Strong-typed utility function.
 */
public
 void setVariable(
 String key, String defaultVal,
 AnimationVariableSlotCallbackString.CallbackGetStrongTyped callbackGet,
 AnimationVariableSlotCallbackString.CallbackSetStrongTyped callbackSet) {
 this->setVariable(new AnimationVariableSlotCallbackString(
 key, defaultVal, callbackGet, callbackSet);
 }

 /**
 * Strong-typed utility function.
 */
 void setVariable(
 std::string_view key, float defaultVal,
 AnimationVariableSlotCallbackFloat.CallbackGetStrongTyped callbackGet) {
 this->setVariable(
 new AnimationVariableSlotCallbackFloat(key, defaultVal, callbackGet);
 }

 /**
 * Strong-typed utility function.
 */
public
 void setVariable(
 String key, float defaultVal,
 AnimationVariableSlotCallbackFloat.CallbackGetStrongTyped callbackGet,
 AnimationVariableSlotCallbackFloat.CallbackSetStrongTyped callbackSet) {
 this->setVariable(new AnimationVariableSlotCallbackFloat(
 key, defaultVal, callbackGet, callbackSet);
 }

 /**
 * Strong-typed utility function.
 */
 void setVariable(
 std::string_view key, int defaultVal,
 AnimationVariableSlotCallbackInt.CallbackGetStrongTyped callbackGet) {
 this->setVariable(
 new AnimationVariableSlotCallbackInt(key, defaultVal, callbackGet);
 }

 /**
 * Strong-typed utility function.
 */
public
 void setVariable(
 String key, int defaultVal,
 AnimationVariableSlotCallbackInt.CallbackGetStrongTyped callbackGet,
 AnimationVariableSlotCallbackInt.CallbackSetStrongTyped callbackSet) {
 this->setVariable(new AnimationVariableSlotCallbackInt(
 key, defaultVal, callbackGet, callbackSet);
 }

 void setVariable(std::string_view key, std::string_view value) {
 this->getOrCreateVariable(key).setValue(value);
 }

 void setVariable(std::string_view key, bool value) {
 this->getOrCreateVariable(key).setValue(value);
 }

 void setVariable(std::string_view key, float value) {
 this->getOrCreateVariable(key).setValue(value);
 }

 void clearVariable(std::string_view key) {
 IAnimationVariableSlot iAnimationVariableSlot = this->getVariable(key);
 if (iAnimationVariableSlot != nullptr) {
 iAnimationVariableSlot.clear();
 }
 }

 void clearVariables() {
 for (IAnimationVariableSlot iAnimationVariableSlot :
 this->getGameVariables()) {
 iAnimationVariableSlot.clear();
 }
 }

 /**
 * Returns the specified variable. Or an empty string "" if not found.
 */
 std::string getVariableString(std::string_view key) {
 IAnimationVariableSlot iAnimationVariableSlot = this->getVariable(key);
 return iAnimationVariableSlot != nullptr
 ? iAnimationVariableSlot.getValueString()
 : "";
 }

 /**
 * Returns the specified variable, as a float. Attempts to convert the string
 * variable to a float. If that fails, or if variable not found, returns the
 * defaultValue
 */
 float getVariableFloat(std::string_view key, float defaultVal) {
 IAnimationVariableSlot iAnimationVariableSlot = this->getVariable(key);
 return iAnimationVariableSlot != nullptr
 ? iAnimationVariableSlot.getValueFloat()
 : defaultVal;
 }

 /**
 * Returns the specified variable, as a boolean. Attempts to convert the
 * string variable to a boolean. If that fails, or if variable not found,
 * returns FALSE
 */
 bool getVariableBoolean(std::string_view key) {
 IAnimationVariableSlot iAnimationVariableSlot = this->getVariable(key);
 return iAnimationVariableSlot != nullptr &&
 iAnimationVariableSlot.getValueBool();
 }

 /**
 * Returns the specified variable, as a boolean. Attempts to convert the
 * string variable to a boolean. If that fails, or if variable not found,
 * returns defaultVal
 */
 bool getVariableBoolean(std::string_view key, bool defaultVal) {
 IAnimationVariableSlot iAnimationVariableSlot = this->getVariable(key);
 return iAnimationVariableSlot != nullptr
 ? iAnimationVariableSlot.getValueBool()
 : defaultVal;
 }

 /**
 * Returns all Game variables.
 */
public
 Iterable<IAnimationVariableSlot> getGameVariables() {
 return this->m_GameVariables.values();
 }

 /**
 * Compares (ignoring case) the value of the specified variable. Returns TRUE
 * if they match.
 */
 bool isVariable(std::string_view name, std::string_view val) {
 return StringUtils.equalsIgnoreCase(this->getVariableString(name), val);
 }

 bool containsVariable(std::string_view key) {
 if (StringUtils.isNullOrWhitespace(key) {
 return false;
 } else {
 std::string string = key.trim();
 return this->m_GameVariables.containsKey(string);
 }
 }
}
} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
