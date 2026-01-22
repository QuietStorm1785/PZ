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
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/packets/hit/Instance.h"
#include <filesystem>

namespace zombie {
namespace network {
namespace packets {


class PlayerID : public Instance {
public:
    IsoPlayer player;
    uint8_t playerIndex;

    void set(IsoPlayer var1) {
      super.set(var1.OnlineID);
      this.playerIndex = var1.isLocal() ? (byte)var1.getPlayerNum() : -1;
      this.player = var1;
   }

    void parsePlayer(UdpConnection var1) {
      if (GameServer.bServer) {
         if (var1 != nullptr && this.playerIndex != -1) {
            this.player = GameServer.getPlayerFromConnection(var1, this.playerIndex);
         } else {
            this.player = (IsoPlayer)GameServer.IDToPlayerMap.get(this.ID);
         }
      } else if (GameClient.bClient) {
         this.player = (IsoPlayer)GameClient.IDToPlayerMap.get(this.ID);
      }
   }

    void parse(ByteBuffer var1, UdpConnection var2) {
      super.parse(var1, var2);
      this.playerIndex = var1.get();
   }

    void write(ByteBufferWriter var1) {
      super.write(var1);
      var1.putByte(this.playerIndex);
   }

    bool isConsistent() {
      return super.isConsistent() && this.getCharacter() != nullptr;
   }

    std::string getDescription() {
      return super.getDescription() + "\n\tPlayer [ player " + (this.player == nullptr ? "?" : "\"" + this.player.getUsername() + "\"") + " ]";
   }

    IsoPlayer getCharacter() {
      return this.player;
   }
}
} // namespace packets
} // namespace network
} // namespace zombie
