#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace chat {
namespace defaultChats {

enum class WhisperChat {
   None,
   Creating,
   PlayerNotFound;
}
} // namespace defaultChats
} // namespace chat
} // namespace zombie
