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

enum class ValidatePacket {
   Request,
   Success;
}
} // namespace packets
} // namespace network
} // namespace zombie
