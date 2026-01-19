#pragma once
#include "zombie/core/textures/Texture.h"
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace znet {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

/**
 * Created by Gennadiy on 11.06.2015.
 */
class SteamFriend {
public:
 std::string name = "";
 long steamID;
 std::string steamIDString;

public
 SteamFriend() {}

public
 SteamFriend(std::string_view _name, long _steamID) {
 this->steamID = _steamID;
 this->steamIDString = SteamUtils.convertSteamIDToString(_steamID);
 this->name = _name;
 }

 std::string getName() { return this->name; }

 std::string getSteamID() { return this->steamIDString; }

 Texture getAvatar() { return Texture.getSteamAvatar(this->steamID); }

 std::string getState() {
 int int0 = SteamFriends.GetFriendPersonaState(this->steamID);
 switch (int0) {
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
