#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace radio {
namespace globals {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

enum class EditGlobalEvent {
  OnSetActive,
  OnPostDelay,
  OnPlayerListens,
  OnPlayerListensOnce,
  OnBroadcastSetActive,
  OnBroadcastRemove,
  OnExit;
}
} // namespace globals
} // namespace radio
} // namespace zombie
