#pragma once
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
 IAnimationVariableSlot getVariable(std::string_view key);

 /**
 * Returns the specified variable. Or an empty string "" if not found.
 */
 std::string getVariableString(std::string_view name);

 /**
 * Returns the specified variable, as a float. Attempts to convert the
 * string variable to a float. If that fails, or if variable not found,
 * returns the defaultValue
 */
 float getVariableFloat(std::string_view name, float defaultVal);

 /**
 * Returns the specified variable, as a boolean. Attempts to convert the
 * string variable to a boolean. If that fails, or if variable not found,
 * returns FALSE
 */
 bool getVariableBoolean(std::string_view name);

 /**
 * Returns the specified variable, as a boolean. Attempts to convert the
 * string variable to a boolean. If that fails, or if variable not found,
 * returns defaultVal
 */
 bool getVariableBoolean(std::string_view key, bool defaultVal);

 /**
 * Returns all Game variables.
 */
 Iterable<IAnimationVariableSlot> getGameVariables();

 /**
 * Compares (ignoring case) the value of the specified variable. Returns TRUE
 * if they match.
 */
 bool isVariable(std::string_view name, std::string_view val);

 bool containsVariable(std::string_view name);
}
} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
