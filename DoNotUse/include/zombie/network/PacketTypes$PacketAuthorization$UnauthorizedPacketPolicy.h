#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/raknet/UdpConnection.h"

namespace zombie {
namespace network {


class PacketTypes {
public:
    virtual ~PacketTypes() = default;
    void call(UdpConnection var1, const std::string& var2);
}
} // namespace network
} // namespace zombie
