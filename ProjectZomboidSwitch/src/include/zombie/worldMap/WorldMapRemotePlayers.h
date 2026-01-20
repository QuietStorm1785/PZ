#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoPlayer.h"

namespace zombie {
namespace worldMap {


class WorldMapRemotePlayers {
public:
    static const WorldMapRemotePlayers instance = std::make_shared<WorldMapRemotePlayers>();
   private const std::vector<WorldMapRemotePlayer> playerList = std::make_unique<std::vector<>>();
   private const std::unordered_map<int16_t, WorldMapRemotePlayer> playerLookup = std::make_unique<std::unordered_map<>>();

    WorldMapRemotePlayer getOrCreatePlayerByID(short var1) {
    WorldMapRemotePlayer var2 = this.playerLookup.get(var1);
      if (var2 == nullptr) {
         var2 = std::make_shared<WorldMapRemotePlayer>(var1);
         this.playerList.push_back(var2);
         this.playerLookup.put(var1, var2);
      }

    return var2;
   }

    WorldMapRemotePlayer getOrCreatePlayer(IsoPlayer var1) {
      return this.getOrCreatePlayerByID(var1.OnlineID);
   }

    WorldMapRemotePlayer getPlayerByID(short var1) {
      return this.playerLookup.get(var1);
   }

   public std::vector<WorldMapRemotePlayer> getPlayers() {
      return this.playerList;
   }

    void removePlayerByID(short var1) {
      this.playerList.removeIf(var1x -> var1x.getOnlineID() == var1);
      this.playerLookup.remove(var1);
   }

    void Reset() {
      this.playerList.clear();
      this.playerLookup.clear();
   }
}
} // namespace worldMap
} // namespace zombie
