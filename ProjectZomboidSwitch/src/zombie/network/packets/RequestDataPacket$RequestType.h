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

enum class RequestDataPacket {
   None,
   Request,
   FullData,
   PartData,
   PartDataACK;
}
} // namespace packets
} // namespace network
} // namespace zombie
