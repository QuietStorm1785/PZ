#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace radio {

enum class GameMode {
   SinglePlayer,
   Server,
   Client;
}
} // namespace radio
} // namespace zombie
