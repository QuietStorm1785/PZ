#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameWindow.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/core/znet/SteamUtils.h"
#include "zombie/network/GameServer.h"
#include <filesystem>

namespace zombie {
namespace savefile {


class ServerPlayerDB {
public:
   byte[] buffer;
    std::string username;
    std::string steamid;
    int playerIndex;
    std::string playerName;
    float x;
    float y;
    float z;
    bool isDead;
    int worldVersion;

   public ServerPlayerDB$NetworkCharacterData(ByteBuffer var1, UdpConnection var2) {
      this.playerIndex = var1.get();
      this.playerName = GameWindow.ReadStringUTF(var1);
      this.x = var1.getFloat();
      this.y = var1.getFloat();
      this.z = var1.getFloat();
      this.isDead = var1.get() == 1;
      this.worldVersion = var1.getInt();
    int var3 = var1.getInt();
      this.buffer = new byte[var3];
      var1.get(this.buffer);
      if (GameServer.bCoop && SteamUtils.isSteamModeEnabled()) {
         this.steamid = var2.idStr;
      } else {
         this.steamid = "";
      }

      this.username = var2.username;
   }
}
} // namespace savefile
} // namespace zombie
