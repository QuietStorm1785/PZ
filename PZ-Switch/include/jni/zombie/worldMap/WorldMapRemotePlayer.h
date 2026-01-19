#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoPlayer.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/ServerOptions.h"

namespace zombie {
namespace worldMap {


class WorldMapRemotePlayer {
:
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

     WorldMapRemotePlayer(short var1) {
      this.OnlineID = var1;
   }

    void setPlayer(IsoPlayer var1) {
    bool var2 = false;
      if (!this.username == var1.username)) {
         this.username = var1.username;
         var2 = true;
      }

      if (!this.forename == var1.getDescriptor().getForename())) {
         this.forename = var1.getDescriptor().getForename();
         var2 = true;
      }

      if (!this.surname == var1.getDescriptor().getSurname())) {
         this.surname = var1.getDescriptor().getSurname();
         var2 = true;
      }

      if (!this.accessLevel == var1.accessLevel)) {
         this.accessLevel = var1.accessLevel;
         var2 = true;
      }

      this.x = var1.x;
      this.y = var1.y;
      if (this.invisible != var1.isInvisible()) {
         this.invisible = var1.isInvisible();
         var2 = true;
      }

      if (var2) {
         this.changeCount++;
      }
   }

    void setFullData(short var1, const std::string& var2, const std::string& var3, const std::string& var4, const std::string& var5, float var6, float var7, bool var8) {
      this.changeCount = var1;
      this.username = var2;
      this.forename = var3;
      this.surname = var4;
      this.accessLevel = var5;
      this.x = var6;
      this.y = var7;
      this.invisible = var8;
      this.bHasFullData = true;
   }

    void setPosition(float var1, float var2) {
      this.x = var1;
      this.y = var2;
   }

    short getOnlineID() const {
      return this.OnlineID;
   }

    std::string getForename() const {
      return this.forename;
   }

    std::string getSurname() const {
      return this.surname;
   }

    float getX() const {
      return this.x;
   }

    float getY() const {
      return this.y;
   }

    short getChangeCount() const {
      return this.changeCount;
   }

    bool isInvisible() {
      return this.invisible;
   }

    bool hasFullData() {
      return this.bHasFullData;
   }

    std::string getUsername(bool var1) {
    std::string var2 = this.username;
      if (var1 && GameClient.bClient && ServerOptions.instance.ShowFirstAndLastName.getValue() && this.isAccessLevel("None")) {
         var2 = this.forename + " " + this.surname;
         if (ServerOptions.instance.DisplayUserName.getValue()) {
            var2 = var2 + " (" + this.username + ")";
         }
      }

    return var2;
   }

    std::string getUsername() const {
      return this.getUsername(false);
   }

    std::string getAccessLevel() const {
    std::string var1 = this.accessLevel;

    return switch() {
         case "admin" -> "Admin";
         case "moderator" -> "Moderator";
         case "overseer" -> "Overseer";
         case "gm" -> "GM";
         case "observer" -> "Observer";
         default -> "None";
      };
   }

    bool isAccessLevel(const std::string& var1) {
      return this.getAccessLevel().equalsIgnoreCase(var1);
   }
}
} // namespace worldMap
} // namespace zombie
