#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace com {
namespace jcraft {
namespace jogg {

class Packet {
public:
    int b_o_s;
    int bytes;
    int e_o_s;
    long granulepos;
    int packet;
   public byte[] packet_base;
    long packetno;
}
} // namespace jogg
} // namespace jcraft
} // namespace com
