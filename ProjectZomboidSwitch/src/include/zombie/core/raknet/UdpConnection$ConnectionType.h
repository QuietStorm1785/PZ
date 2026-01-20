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

enum class UdpConnection {
   Disconnected,
   UDPRakNet,
   Steam;
}
} // namespace raknet
} // namespace core
} // namespace zombie
