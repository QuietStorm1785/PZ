#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace core {
namespace znet {

class GameServerDetails {
public:
    std::string address;
    int port;
    long steamId;
    std::string name;
    std::string gamedir;
    std::string map;
    std::string gameDescription;
    std::string tags;
    int ping;
    int numPlayers;
    int maxPlayers;
    bool passwordProtected;
    int version;

    public GameServerDetails() {
   }

   public GameServerDetails(
      std::string var1,
      int var2,
      long var3,
      std::string var5,
      std::string var6,
      std::string var7,
      std::string var8,
      std::string var9,
      int var10,
      int var11,
      int var12,
      boolean var13,
      int var14
   ) {
      this.address = var1;
      this.port = var2;
      this.steamId = var3;
      this.name = var5;
      this.gamedir = var6;
      this.map = var7;
      this.gameDescription = var8;
      this.tags = var9;
      this.ping = var10;
      this.numPlayers = var11;
      this.maxPlayers = var12;
      this.passwordProtected = var13;
      this.version = var14;
   }
}
} // namespace znet
} // namespace core
} // namespace zombie
