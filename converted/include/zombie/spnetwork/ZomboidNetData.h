#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/network/IZomboidPacket.h"
#include <filesystem>

namespace zombie {
namespace spnetwork {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class ZomboidNetData {
public:
 short type;
 short length;
 ByteBuffer buffer;
 UdpConnection connection;

 public ZomboidNetData() {
 this->buffer = ByteBuffer.allocate(2048);
 }

 public ZomboidNetData(int int0) {
 this->buffer = ByteBuffer.allocate(int0);
 }

 void reset() {
 this->type = 0;
 this->length = 0;
 this->buffer.clear();
 this->connection = nullptr;
 }

 void read(short short0, ByteBuffer byteBuffer, UdpConnection udpConnection) {
 this->type = short0;
 this->connection = udpConnection;
 this->buffer.put(byteBuffer);
 this->buffer.flip();
 }

 bool isConnect() {
 return false;
 }

 bool isDisconnect() {
 return false;
 }
}
} // namespace spnetwork
} // namespace zombie
