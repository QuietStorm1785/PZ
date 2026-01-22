#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace network {


class PacketTypes {
public:
    virtual ~PacketTypes() = default;
    void call(ByteBuffer var1, short var2);
}
} // namespace network
} // namespace zombie
