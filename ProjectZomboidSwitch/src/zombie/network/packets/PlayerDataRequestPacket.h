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


class PlayerDataRequestPacket {
public:
    short playerId = -1;

    void set(short var1) {
      this.playerId = var1;
   }

    void process(UdpConnection var1) {
    IsoPlayer var2 = (IsoPlayer)GameServer.IDToPlayerMap.get(this.playerId);
      if (var1.RelevantTo(var2.x, var2.y) && !var2.isInvisible() || var1.accessLevel >= 1) {
         GameServer.sendPlayerConnect(var2, var1);
      }
   }

    void parse(ByteBuffer var1, UdpConnection var2) {
      this.playerId = var1.getShort();
   }

    void write(ByteBufferWriter var1) {
      var1.putShort(this.playerId);
   }
}
} // namespace packets
} // namespace network
} // namespace zombie
