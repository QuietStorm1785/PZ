#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/network/packets/INetworkPacket.h"
#include <filesystem>

namespace zombie {
namespace network {
namespace packets {
namespace hit {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class Instance {
public:
 short ID;

 void set(short short0) {
 this->ID = short0;
 }

 void parse(ByteBuffer byteBuffer, UdpConnection var2) {
 this->ID = byteBuffer.getShort();
 }

 void write(ByteBufferWriter byteBufferWriter) {
 byteBufferWriter.putShort(this->ID);
 }

 bool isConsistent() {
 return this->ID != -1;
 }

 std::string getDescription() {
 return "ID=" + this->ID;
 }
}
} // namespace hit
} // namespace packets
} // namespace network
} // namespace zombie
