#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/PacketTypes/PacketType.h"

namespace zombie {
namespace popman {


class DebugCommands {
public:
    static const uint8_t PKT_LOADED = 1;
    static const uint8_t PKT_REPOP = 2;
    static const uint8_t PKT_SPAWN_TIME_TO_ZERO = 3;
    static const uint8_t PKT_CLEAR_ZOMBIES = 4;
    static const uint8_t PKT_SPAWN_NOW = 5;

   private static native void n_debugCommand(int var0, int var1, int var2);

    void SpawnTimeToZero(int var1, int var2) {
      if (ZombiePopulationManager.instance.bClient) {
    ByteBufferWriter var3 = GameClient.connection.startPacket();
         PacketType.KeepAlive.doPacket(var3);
         var3.bb.put((byte)3);
         var3.bb.putShort((short)var1);
         var3.bb.putShort((short)var2);
         PacketType.KeepAlive.send(GameClient.connection);
      } else {
         n_debugCommand(3, var1, var2);
      }
   }

    void ClearZombies(int var1, int var2) {
      if (ZombiePopulationManager.instance.bClient) {
    ByteBufferWriter var3 = GameClient.connection.startPacket();
         PacketType.KeepAlive.doPacket(var3);
         var3.bb.put((byte)4);
         var3.bb.putShort((short)var1);
         var3.bb.putShort((short)var2);
         PacketType.KeepAlive.send(GameClient.connection);
      } else {
         n_debugCommand(4, var1, var2);
      }
   }

    void SpawnNow(int var1, int var2) {
      if (ZombiePopulationManager.instance.bClient) {
    ByteBufferWriter var3 = GameClient.connection.startPacket();
         PacketType.KeepAlive.doPacket(var3);
         var3.bb.put((byte)5);
         var3.bb.putShort((short)var1);
         var3.bb.putShort((short)var2);
         PacketType.KeepAlive.send(GameClient.connection);
      } else {
         n_debugCommand(5, var1, var2);
      }
   }
}
} // namespace popman
} // namespace zombie
