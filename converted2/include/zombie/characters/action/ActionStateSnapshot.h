#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace characters {
namespace action {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

/**
 * Used for Playback   Holds the current ActionContext state, and any sub-states
 */
class ActionStateSnapshot {
public:
  std::string stateName;
public
  String[] childStateNames;
}
} // namespace action
} // namespace characters
} // namespace zombie
