#pragma once
#include "zombie/characters/IsoPlayer.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace worldMap {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class WorldMapRemotePlayers {
public:
  static const WorldMapRemotePlayers instance = new WorldMapRemotePlayers();
private
  final ArrayList<WorldMapRemotePlayer> playerList =
      std::make_unique<ArrayList<>>();
private
  final HashMap<Short, WorldMapRemotePlayer> playerLookup =
      std::make_unique<HashMap<>>();

  WorldMapRemotePlayer getOrCreatePlayerByID(short short0) {
    WorldMapRemotePlayer worldMapRemotePlayer = this.playerLookup.get(short0);
    if (worldMapRemotePlayer == nullptr) {
      worldMapRemotePlayer = new WorldMapRemotePlayer(short0);
      this.playerList.add(worldMapRemotePlayer);
      this.playerLookup.put(short0, worldMapRemotePlayer);
    }

    return worldMapRemotePlayer;
  }

  WorldMapRemotePlayer getOrCreatePlayer(IsoPlayer player) {
    return this.getOrCreatePlayerByID(player.OnlineID);
  }

  WorldMapRemotePlayer getPlayerByID(short short0) {
    return this.playerLookup.get(short0);
  }

public
  ArrayList<WorldMapRemotePlayer> getPlayers() { return this.playerList; }

  void removePlayerByID(short short0) {
    this.playerList.removeIf(
        worldMapRemotePlayer->worldMapRemotePlayer.getOnlineID() == short0);
    this.playerLookup.remove(short0);
  }

  void Reset() {
    this.playerList.clear();
    this.playerLookup.clear();
  }
}
} // namespace worldMap
} // namespace zombie
