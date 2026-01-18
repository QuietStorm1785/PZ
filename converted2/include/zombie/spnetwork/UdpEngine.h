#pragma once
#include <cstdint>
#include <filesystem>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace spnetwork {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class UdpEngine {
public:
public
  abstract void Send(ByteBuffer bb);

public
  abstract void Receive(ByteBuffer bb);
}
} // namespace spnetwork
} // namespace zombie
