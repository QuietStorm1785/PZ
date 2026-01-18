#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace com {
namespace jcraft {
namespace jogg {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class Packet {
public:
 int b_o_s;
 int bytes;
 int e_o_s;
 long granulepos;
 int packet;
public
 byte[] packet_base;
 long packetno;
}
} // namespace jogg
} // namespace jcraft
} // namespace com
