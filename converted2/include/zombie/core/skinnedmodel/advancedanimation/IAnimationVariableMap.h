#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace advancedanimation {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class IAnimationVariableMap {
public:
  virtual ~IAnimationVariableMap() = default;
  /**
   * Returns the specified variable slot.   Creates a new slot if not found.
   */
  IAnimationVariableSlot getOrCreateVariable(const std::string &key);

  /**
   * Set the specified animation variable slot. Overwriting an existing slot if
   * necessary.
   */
  void setVariable(IAnimationVariableSlot slot);

  void setVariable(const std::string &key, const std::string &value);

  void setVariable(const std::string &key, bool value);

  void setVariable(const std::string &key, float value);

  void clearVariable(const std::string &key);

  void clearVariables();
}
} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
