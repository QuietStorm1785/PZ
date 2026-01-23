#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {

enum class ISoundSystem {
   FailToPlay,
   StopOldest,
   StopRandom;
}
} // namespace zombie
