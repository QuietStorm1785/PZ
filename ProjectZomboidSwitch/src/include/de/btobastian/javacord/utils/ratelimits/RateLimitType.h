#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace de {
namespace btobastian {
namespace javacord {
namespace utils {
namespace ratelimits {

enum class RateLimitType {
   PRIVATE_MESSAGE,
   SERVER_MESSAGE,
   NAME_CHANGE,
   PRIVATE_MESSAGE_DELETE,
   SERVER_MESSAGE_DELETE,
   UNKNOWN;
}
} // namespace ratelimits
} // namespace utils
} // namespace javacord
} // namespace btobastian
} // namespace de
