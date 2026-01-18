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

/**
 * An Animation Variable Slot Used to store a variable's key+value pair, and its current type.
 */
class IAnimationVariableSlot {
public:
 virtual ~IAnimationVariableSlot() = default;
 /**
 * This variable's unique key
 */
 std::string getKey();

 /**
 * This variable's value, in String form.
 */
 std::string getValueString();

 /**
 * This variable's value, as a Float.
 */
 float getValueFloat();

 /**
 * This variable's value, as a Boolean.
 */
 bool getValueBool();

 /**
 * Set this variable's value
 */
 void setValue(const std::string& val);

 /**
 * Set this variable's value
 */
 void setValue(float val);

 /**
 * Set this variable's value
 */
 void setValue(bool val);

 /**
 * This variable's value type
 */
 AnimationVariableType getType();

 /**
 * Returns TRUE if this variable slot can accept and/or convert the supplied value object. Returns FALSE if the conversion would result in a loss of data. Eg. If a String is given to a Float variable, and the string is not of a numeric format, then the string value would be lost.
 */
 bool canConvertFrom(const std::string& val);

 /**
 * Clear this variable, its value is set to a nullptr-value. Blank for Strings, 0 for Floats, False for Booleans, etc.
 */
 void clear();

 /**
 * Returns TRUE if this variable is not writable. Typically, the value of this variable is specified by an outside condition, such as whether the character is currently falling, etc.
 */
 default boolean isReadOnly() {
 return false;
 }
}
} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
