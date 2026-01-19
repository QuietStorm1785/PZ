#pragma once
#include "zombie/characters/IsoPlayer.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/ServerOptions.h"
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace worldMap {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class WorldMapRemotePlayer {
public:
 short changeCount = 0;
 const short OnlineID;
 std::string username = "???";
 std::string forename = "???";
 std::string surname = "???";
 std::string accessLevel = "None";
 float x;
 float y;
 bool invisible = false;
 bool bHasFullData = false;

public
 WorldMapRemotePlayer(short short0) { this->OnlineID = short0; }

 void setPlayer(IsoPlayer player) {
 bool boolean0 = false;
 if (!this->username == player.username) {
 this->username = player.username;
 boolean0 = true;
 }

 if (!this->forename == player.getDescriptor().getForename())) {
 this->forename = player.getDescriptor().getForename();
 boolean0 = true;
 }

 if (!this->surname == player.getDescriptor().getSurname())) {
 this->surname = player.getDescriptor().getSurname();
 boolean0 = true;
 }

 if (!this->accessLevel == player.accessLevel) {
 this->accessLevel = player.accessLevel;
 boolean0 = true;
 }

 this->x = player.x;
 this->y = player.y;
 if (this->invisible != player.isInvisible()) {
 this->invisible = player.isInvisible();
 boolean0 = true;
 }

 if (boolean0) {
 this->changeCount++;
 }
 }

 void setFullData(short short0, std::string_view string0,
 std::string_view string1, std::string_view string2,
 std::string_view string3, float float0, float float1,
 bool boolean0) {
 this->changeCount = short0;
 this->username = string0;
 this->forename = string1;
 this->surname = string2;
 this->accessLevel = string3;
 this->x = float0;
 this->y = float1;
 this->invisible = boolean0;
 this->bHasFullData = true;
 }

 void setPosition(float float0, float float1) {
 this->x = float0;
 this->y = float1;
 }

 short getOnlineID() { return this->OnlineID; }

 std::string getForename() { return this->forename; }

 std::string getSurname() { return this->surname; }

 float getX() { return this->x; }

 float getY() { return this->y; }

 short getChangeCount() noexcept{ return this->changeCount; }

 bool isInvisible() { return this->invisible; }

 bool hasFullData() { return this->bHasFullData; }

 std::string getUsername(bool boolean0) {
 std::string string = this->username;
 if (boolean0 && GameClient.bClient &&
 ServerOptions.instance.ShowFirstAndLastName.getValue() &&
 this->isAccessLevel("None")) {
 string = this->forename + " " + this->surname;
 if (ServerOptions.instance.DisplayUserName.getValue()) {
 string = string + " (" + this->username + ")";
 }
 }

 return string;
 }

 std::string getUsername() { return this->getUsername(false); }

 std::string getAccessLevel() {
 std::string string = this->accessLevel;

 return switch () {
 case "admin" -> "Admin";
 case "moderator" -> "Moderator";
 case "overseer" -> "Overseer";
 case "gm" -> "GM";
 case "observer" -> "Observer";
 default -> "None";
 };
 }

 bool isAccessLevel(std::string_view string) {
 return this->getAccessLevel().equalsIgnoreCase(string);
 }
}
} // namespace worldMap
} // namespace zombie
