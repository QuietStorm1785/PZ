#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/Safety.h"
#include "zombie/core/Core.h"
#include "zombie/core/logger/LoggerManager.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/util/Type.h"
#include <filesystem>

namespace zombie {
namespace network {
namespace packets {


class SafetyPacket : public Safety {
public:
    short id;
    IsoPlayer player;

    public SafetyPacket(Safety var1) {
      this.enabled = var1.isEnabled();
      this.last = var1.isLast();
      this.cooldown = var1.getCooldown();
      this.toggle = var1.getToggle();
      this.player = (IsoPlayer)Type.tryCastTo(var1.getCharacter(), IsoPlayer.class);
      if (this.player != nullptr) {
         if (GameServer.bServer) {
            this.id = this.player.getOnlineID();
         } else if (GameClient.bClient) {
            this.id = (short)this.player.getPlayerNum();
         }
      }
   }

    public SafetyPacket() {
   }

    void parse(ByteBuffer var1, UdpConnection var2) {
      this.id = var1.getShort();
      super.load(var1, IsoWorld.getWorldVersion());
      if (GameServer.bServer) {
         this.player = GameServer.getPlayerFromConnection(var2, this.id);
      } else if (GameClient.bClient) {
         this.player = (IsoPlayer)GameClient.IDToPlayerMap.get(this.id);
      } else {
         this.player = nullptr;
      }
   }

    void write(ByteBufferWriter var1) {
      var1.putShort(this.id);
      super.save(var1.bb);
   }

    int getPacketSizeBytes() {
    return 12;
   }

    bool isConsistent() {
      return this.player != nullptr;
   }

    std::string getDescription() {
      return super.getDescription() + (this.player == nullptr ? ":" : ": \"" + this.player.getUsername() + "\"") + " id=" + this.id + " " + super.getDescription();
   }

    void log(UdpConnection var1, const std::string& var2) {
      if (this.isConsistent()) {
         if (Core.bDebug) {
            DebugLog.Combat.debugln(var2 + ": " + this.getDescription());
         }

         if (GameServer.bServer) {
            LoggerManager.getLogger("pvp")
               .write(
                  std::string.format(
                     "user \"%s\" %s %s safety %s",
                     this.player.getUsername(),
                     LoggerManager.getPlayerCoords(this.player),
                     this.player.getSafety().isEnabled() ? "enabled" : "disabled",
                     this.player.getSafety().getDescription()
                  )
               );
         }
      }
   }

    void process() {
      if (this.isConsistent()) {
         if (GameServer.bServer) {
            this.player.getSafety().toggleSafety();
         } else if (GameClient.bClient) {
            this.player.setSafety(this);
         }
      }
   }
}
} // namespace packets
} // namespace network
} // namespace zombie
