#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace core {
namespace raknet {

enum class VoiceManagerData {
   Unknown,
   Voice,
   Radio,
   Cheat;
}
} // namespace raknet
} // namespace core
} // namespace zombie
