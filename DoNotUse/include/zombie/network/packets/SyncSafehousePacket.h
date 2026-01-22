#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameWindow.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/iso/areas/SafeHouse.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/PacketValidator.h"
#include "zombie/network/ServerOptions.h"
#include <algorithm>
#include <filesystem>

namespace zombie {
namespace network {
namespace packets {


class SyncSafehousePacket {
public:
    const uint8_t requiredManagerAccessLevel = 56;
    int x;
    int y;
    short w;
    short h;
    std::string ownerUsername;
   std::vector<std::string> members = std::make_unique<std::vector<>>();
   std::vector<std::string> membersRespawn = std::make_unique<std::vector<>>();
    bool remove = false;
    std::string title = "";
    SafeHouse safehouse;
    bool shouldCreateChat;

    void set(SafeHouse var1, bool var2) {
      this.x = var1.getX();
      this.y = var1.getY();
      this.w = (short)var1.getW();
      this.h = (short)var1.getH();
      this.ownerUsername = var1.getOwner();
      this.members.clear();
      this.members.addAll(var1.getPlayers());
      this.membersRespawn.clear();
      this.membersRespawn.addAll(var1.playersRespawn);
      this.remove = var2;
      this.title = var1.getTitle();
   }

    void parse(ByteBuffer var1, UdpConnection var2) {
      this.x = var1.getInt();
      this.y = var1.getInt();
      this.w = var1.getShort();
      this.h = var1.getShort();
      this.ownerUsername = GameWindow.ReadString(var1);
    short var3 = var1.getShort();
      this.members.clear();

      for (int var4 = 0; var4 < var3; var4++) {
         this.members.push_back(GameWindow.ReadString(var1));
      }

    short var6 = var1.getShort();

      for (int var5 = 0; var5 < var6; var5++) {
         this.membersRespawn.push_back(GameWindow.ReadString(var1));
      }

      this.remove = var1.get() == 1;
      this.title = GameWindow.ReadString(var1);
   }

    void write(ByteBufferWriter var1) {
      var1.putInt(this.x);
      var1.putInt(this.y);
      var1.putShort(this.w);
      var1.putShort(this.h);
      var1.putUTF(this.ownerUsername);
      var1.putShort((short)this.members.size());

      for (std::string var3 : this.members) {
         var1.putUTF(var3);
      }

      var1.putShort((short)this.membersRespawn.size());

      for (std::string var5 : this.membersRespawn) {
         var1.putUTF(var5);
      }

      var1.putByte((byte)(this.remove ? 1 : 0));
      var1.putUTF(this.title);
   }

    void process() {
      this.safehouse = SafeHouse.getSafeHouse(this.x, this.y, this.w, this.h);
      this.shouldCreateChat = false;
      if (this.safehouse == nullptr) {
         this.safehouse = SafeHouse.addSafeHouse(this.x, this.y, this.w, this.h, this.ownerUsername, GameClient.bClient);
         this.shouldCreateChat = true;
      }

      if (this.safehouse != nullptr) {
         this.safehouse.getPlayers().clear();
         this.safehouse.getPlayers().addAll(this.members);
         this.safehouse.playersRespawn.clear();
         this.safehouse.playersRespawn.addAll(this.membersRespawn);
         this.safehouse.setTitle(this.title);
         this.safehouse.setOwner(this.ownerUsername);
         if (this.remove) {
            SafeHouse.getSafehouseList().remove(this.safehouse);
            DebugLog.log("safehouse: removed " + this.x + "," + this.y + "," + this.w + "," + this.h + " owner=" + this.safehouse.getOwner());
         }
      }
   }

    bool validate(UdpConnection var1) {
    bool var2 = (var1.accessLevel & 56) != 0;
      this.safehouse = SafeHouse.getSafeHouse(this.x, this.y, this.w, this.h);
      if (this.safehouse == nullptr) {
         if (var1.accessLevel == 1 && SafeHouse.hasSafehouse(this.ownerUsername) != nullptr) {
            if (ServerOptions.instance.AntiCheatProtectionType19.getValue() && PacketValidator.checkUser(var1)) {
               PacketValidator.doKickUser(var1, this.getClass().getSimpleName(), "Type19", this.getDescription());
            }

    return false;
         } else {
    double var3 = 100.0 * ServerOptions.instance.AntiCheatProtectionType20ThresholdMultiplier.getValue();
            if (var1.accessLevel == 1 && (this.h > var3 || this.w > var3)) {
               if (ServerOptions.instance.AntiCheatProtectionType20.getValue() && PacketValidator.checkUser(var1)) {
                  PacketValidator.doKickUser(var1, this.getClass().getSimpleName(), "Type20", this.getDescription());
               }

    return false;
            } else {
    return true;
            }
         }
      } else {
         return !var2 ? true : PacketValidator.checkSafehouseAuth(var1, this.safehouse.getOwner(), this.getClass().getSimpleName());
      }
   }

    std::string getDescription() {
    std::string var1 = "\n\t" + this.getClass().getSimpleName() + " [";
      var1 = var1 + "position=(" + this.x + ", " + this.y + ", " + this.w + ", " + this.h + ") | ";
      var1 = var1 + "ownerUsername=" + this.ownerUsername + " | ";
      var1 = var1 + "members=" + Arrays.toString(this.members.toArray()) + " | ";
      var1 = var1 + "membersRespawn=" + Arrays.toString(this.membersRespawn.toArray()) + " | ";
      var1 = var1 + "remove=" + this.remove + " | ";
      return var1 + "title=" + this.title + "] ";
   }
}
} // namespace packets
} // namespace network
} // namespace zombie
