#pragma once
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/PacketTypes.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace popman {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class DebugCommands {
public:
 static const uint8_t PKT_LOADED = 1;
 static const uint8_t PKT_REPOP = 2;
 static const uint8_t PKT_SPAWN_TIME_TO_ZERO = 3;
 static const uint8_t PKT_CLEAR_ZOMBIES = 4;
 static const uint8_t PKT_SPAWN_NOW = 5;

private
 static void n_debugCommand(int var0, int var1, int var2);

 void SpawnTimeToZero(int int0, int int1) {
 if (ZombiePopulationManager.instance.bClient) {
 ByteBufferWriter byteBufferWriter = GameClient.connection.startPacket();
 PacketTypes.PacketType.KeepAlive.doPacket(byteBufferWriter);
 byteBufferWriter.bb.put((byte)3);
 byteBufferWriter.bb.putShort((short)int0);
 byteBufferWriter.bb.putShort((short)int1);
 PacketTypes.PacketType.KeepAlive.send(GameClient.connection);
 } else {
 n_debugCommand(3, int0, int1);
 }
 }

 void ClearZombies(int int0, int int1) {
 if (ZombiePopulationManager.instance.bClient) {
 ByteBufferWriter byteBufferWriter = GameClient.connection.startPacket();
 PacketTypes.PacketType.KeepAlive.doPacket(byteBufferWriter);
 byteBufferWriter.bb.put((byte)4);
 byteBufferWriter.bb.putShort((short)int0);
 byteBufferWriter.bb.putShort((short)int1);
 PacketTypes.PacketType.KeepAlive.send(GameClient.connection);
 } else {
 n_debugCommand(4, int0, int1);
 }
 }

 void SpawnNow(int int0, int int1) {
 if (ZombiePopulationManager.instance.bClient) {
 ByteBufferWriter byteBufferWriter = GameClient.connection.startPacket();
 PacketTypes.PacketType.KeepAlive.doPacket(byteBufferWriter);
 byteBufferWriter.bb.put((byte)5);
 byteBufferWriter.bb.putShort((short)int0);
 byteBufferWriter.bb.putShort((short)int1);
 PacketTypes.PacketType.KeepAlive.send(GameClient.connection);
 } else {
 n_debugCommand(5, int0, int1);
 }
 }
}
} // namespace popman
} // namespace zombie
