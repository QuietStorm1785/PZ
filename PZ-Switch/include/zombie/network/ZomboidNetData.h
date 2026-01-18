#pragma once
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/debug/DebugLog.h"
#include <cstdint>
#include <filesystem>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace network {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class ZomboidNetData {
public:
public
 PacketTypes.PacketType type;
 short length;
 ByteBuffer buffer;
 long connection;
 long time;

public
 ZomboidNetData() { this->buffer = ByteBuffer.allocate(2048); }

public
 ZomboidNetData(int int0) { this->buffer = ByteBuffer.allocate(int0); }

 void reset() {
 this->type = nullptr;
 this->length = 0;
 this->connection = 0L;
 this->buffer.clear();
 }

 void read(short short0, ByteBuffer byteBuffer, UdpConnection udpConnection) {
 this->type = PacketTypes.packetTypes.get(short0);
 if (this->type.empty()) {
 DebugLog.Multiplayer.error("Received unknown packet id=%d", short0);
 }

 this->connection = udpConnection.getConnectedGUID();
 this->buffer.put(byteBuffer);
 this->buffer.flip();
 }

 bool isConnect() { return false; }

 bool isDisconnect() { return false; }
}
} // namespace network
} // namespace zombie
