#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/textures/Texture.h"

namespace zombie {
namespace core {
namespace znet {


class SteamFriend {
public:
    std::string name = "";
    long steamID;
    std::string steamIDString;

    public SteamFriend() {
   }

    public SteamFriend(const std::string& var1, long var2) {
      this.steamID = var2;
      this.steamIDString = SteamUtils.convertSteamIDToString(var2);
      this.name = var1;
   }

    std::string getName() {
      return this.name;
   }

    std::string getSteamID() {
      return this.steamIDString;
   }

    Texture getAvatar() {
      return Texture.getSteamAvatar(this.steamID);
   }

    std::string getState() {
    int var1 = SteamFriends.GetFriendPersonaState(this.steamID);
      switch (var1) {
         case 0:
            return "Offline";
         case 1:
            return "Online";
         case 2:
            return "Busy";
         case 3:
            return "Away";
         case 4:
            return "Snooze";
         case 5:
            return "LookingToTrade";
         case 6:
            return "LookingToPlay";
         default:
            return "Unknown";
      }
   }
}
} // namespace znet
} // namespace core
} // namespace zombie
