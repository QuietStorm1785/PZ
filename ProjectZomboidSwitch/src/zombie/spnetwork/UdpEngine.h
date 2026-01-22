#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <filesystem>

namespace zombie {
namespace spnetwork {


class UdpEngine {
public:
   public abstract void Send(ByteBuffer var1);

   public abstract void Receive(ByteBuffer var1);
}
} // namespace spnetwork
} // namespace zombie
