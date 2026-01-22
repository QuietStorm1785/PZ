#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace network {
namespace packets {

class PlayerPacket {
public:
    static PlayerPacket playerPacket = std::make_shared<PlayerPacket>();
}
} // namespace packets
} // namespace network
} // namespace zombie
