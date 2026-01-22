#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace network {

enum class FakeClientManager {
   CONNECT,
   LOGIN,
   CHECKSUM,
   PLAYER_CONNECT,
   PLAYER_EXTRA_INFO,
   LOAD,
   RUN,
   WAIT,
   DISCONNECT,
   QUIT;
}
} // namespace network
} // namespace zombie
