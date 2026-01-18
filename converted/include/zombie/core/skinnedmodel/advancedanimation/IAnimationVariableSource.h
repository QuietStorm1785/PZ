#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace advancedanimation {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.

class IAnimationVariableSource {
public:
 virtual ~IAnimationVariableSource() = default;
 /**
 * Returns the specified variable slot. Or NULL if not found.
 */
 IAnimationVariableSlot getVariable(AnimationVariableHandle handle);

 /**
 * Returns the specified variable slot. Or NULL if not found.
 */
 IAnimationVariableSlot getVariable(const std::string& key);

 /**
 * Returns the specified variable. Or an empty string "" if not found.
 */
 std::string getVariableString(const std::string& name);

 /**
 * Returns the specified variable, as a float. Attempts to convert the string variable to a float. If that fails, or if variable not found, returns the defaultValue
 */
 float getVariableFloat(const std::string& name, float defaultVal);

 /**
 * Returns the specified variable, as a boolean. Attempts to convert the string variable to a boolean. If that fails, or if variable not found, returns FALSE
 */
 bool getVariableBoolean(const std::string& name);

 /**
 * Returns the specified variable, as a boolean. Attempts to convert the string variable to a boolean. If that fails, or if variable not found, returns defaultVal
 */
 bool getVariableBoolean(const std::string& key, bool defaultVal);

 /**
 * Returns all Game variables.
 */
 Iterable<IAnimationVariableSlot> getGameVariables();

 /**
 * Compares (ignoring case) the value of the specified variable. Returns TRUE if they match.
 */
 bool isVariable(const std::string& name, const std::string& val);

 bool containsVariable(const std::string& name);
}
} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
