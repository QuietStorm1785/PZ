#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/network/GameServer.h"
#include <filesystem>

namespace zombie {
namespace network {
namespace packets {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class PlayerDataRequestPacket {
public:
 short playerId = -1;

 void set(short short0) {
 this->playerId = short0;
 }

 void process(UdpConnection udpConnection) {
 IsoPlayer player = GameServer.IDToPlayerMap.get(this->playerId);
 if (udpConnection.RelevantTo(player.x, player.y) && !player.isInvisible() || udpConnection.accessLevel >= 1) {
 GameServer.sendPlayerConnect(player, udpConnection);
 }
 }

 void parse(ByteBuffer byteBuffer, UdpConnection var2) {
 this->playerId = byteBuffer.getShort();
 }

 void write(ByteBufferWriter byteBufferWriter) {
 byteBufferWriter.putShort(this->playerId);
 }
}
} // namespace packets
} // namespace network
} // namespace zombie
