#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/raknet/UdpConnection.h"
#include <filesystem>

namespace zombie {
namespace network {


class PacketTypes {
public:
    virtual ~PacketTypes() = default;
    void call(ByteBuffer var1, UdpConnection var2, short var3);
}
} // namespace network
} // namespace zombie
