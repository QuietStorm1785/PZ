#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include <filesystem>

namespace zombie {
namespace network {
namespace packets {


class SyncInjuriesPacket {
public:
    short id;
    float strafeSpeed;
    float walkSpeed;
    float walkInjury;
    IsoPlayer player;

    bool set(IsoPlayer var1) {
      if (GameClient.bClient) {
         this.id = (short)var1.getPlayerNum();
      } else if (GameServer.bServer) {
         this.id = var1.getOnlineID();
      }

      this.strafeSpeed = var1.getVariableFloat("StrafeSpeed", 1.0F);
      this.walkSpeed = var1.getVariableFloat("WalkSpeed", 1.0F);
      this.walkInjury = var1.getVariableFloat("WalkInjury", 0.0F);
      this.player = var1;
    return true;
   }

    bool process() {
      if (this.player != nullptr && !this.player.isLocalPlayer()) {
         this.player.setVariable("StrafeSpeed", this.strafeSpeed);
         this.player.setVariable("WalkSpeed", this.walkSpeed);
         this.player.setVariable("WalkInjury", this.walkInjury);
    return true;
      } else {
    return false;
      }
   }

    void parse(ByteBuffer var1, UdpConnection var2) {
      this.id = var1.getShort();
      this.strafeSpeed = var1.getFloat();
      this.walkSpeed = var1.getFloat();
      this.walkInjury = var1.getFloat();
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
      var1.putFloat(this.strafeSpeed);
      var1.putFloat(this.walkSpeed);
      var1.putFloat(this.walkInjury);
   }

    int getPacketSizeBytes() {
    return 14;
   }

    std::string getDescription() {
      return "SyncInjuriesPacket: id=" + this.id + ", strafeSpeed=" + this.strafeSpeed + ", walkSpeed=" + this.walkSpeed + ", walkInjury=" + this.walkInjury;
   }
}
} // namespace packets
} // namespace network
} // namespace zombie
