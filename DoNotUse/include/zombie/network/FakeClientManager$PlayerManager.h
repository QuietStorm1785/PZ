#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/network/FakeClientManager/Player.h"
#include "zombie/network/FakeClientManager/PlayerManager/RemotePlayer.h"
#include "zombie/network/packets/PlayerPacket.h"
#include <filesystem>

namespace zombie {
namespace network {


class FakeClientManager {
public:
    Player player = nullptr;
    const PlayerPacket playerPacket = std::make_shared<PlayerPacket>();
   public const std::unordered_map<int, RemotePlayer> players = std::make_unique<std::unordered_map<>>();

   public FakeClientManager$PlayerManager(Player var1) {
      this.player = var1;
   }

    void parsePlayer(ByteBuffer var1) {
    PlayerPacket var2 = this.playerPacket;
      var2.parse(var1, nullptr);
      /* synchronized - TODO: add std::mutex */ (this.players) {
    RemotePlayer var4 = this.players.get(var2.id);
         if (var4 == nullptr) {
            var4 = std::make_shared<RemotePlayer>(this, var2.id);
            this.players.put(int.valueOf(var2.id), var4);
            FakeClientManager.trace(this.player.movement.id, std::string.format("New player %s", var4.OnlineID));
         }

         var4.playerPacket.copy(var2);
         var4.x = var2.realx;
         var4.y = var2.realy;
         var4.z = var2.realz;
      }
   }

    void parsePlayerTimeout(ByteBuffer var1) {
    short var2 = var1.getShort();
      /* synchronized - TODO: add std::mutex */ (this.players) {
         this.players.remove(var2);
      }

      FakeClientManager.trace(this.player.movement.id, std::string.format("Remove player %s", var2));
   }
}
} // namespace network
} // namespace zombie
