#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace chat {

enum class ChatManager {
   notStarted,
   starting,
   working;
}
} // namespace chat
} // namespace zombie
