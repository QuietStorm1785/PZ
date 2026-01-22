#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace network {

class IZomboidPacket {
public:
    virtual ~IZomboidPacket() = default;
    bool isConnect();

    bool isDisconnect();
}
} // namespace network
} // namespace zombie
