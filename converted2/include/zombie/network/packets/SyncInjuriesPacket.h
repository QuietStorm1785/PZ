#pragma once
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include <cstdint>
#include <filesystem>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace network {
namespace packets {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class SyncInjuriesPacket {
public:
  short id;
  float strafeSpeed;
  float walkSpeed;
  float walkInjury;
  IsoPlayer player;

  bool set(IsoPlayer playerx) {
    if (GameClient.bClient) {
      this.id = (short)playerx.getPlayerNum();
    } else if (GameServer.bServer) {
      this.id = playerx.getOnlineID();
    }

    this.strafeSpeed = playerx.getVariableFloat("StrafeSpeed", 1.0F);
    this.walkSpeed = playerx.getVariableFloat("WalkSpeed", 1.0F);
    this.walkInjury = playerx.getVariableFloat("WalkInjury", 0.0F);
    this.player = playerx;
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

  void parse(ByteBuffer byteBuffer, UdpConnection udpConnection) {
    this.id = byteBuffer.getShort();
    this.strafeSpeed = byteBuffer.getFloat();
    this.walkSpeed = byteBuffer.getFloat();
    this.walkInjury = byteBuffer.getFloat();
    if (GameServer.bServer) {
      this.player = GameServer.getPlayerFromConnection(udpConnection, this.id);
    } else if (GameClient.bClient) {
      this.player = GameClient.IDToPlayerMap.get(this.id);
    } else {
      this.player = nullptr;
    }
  }

  void write(ByteBufferWriter byteBufferWriter) {
    byteBufferWriter.putShort(this.id);
    byteBufferWriter.putFloat(this.strafeSpeed);
    byteBufferWriter.putFloat(this.walkSpeed);
    byteBufferWriter.putFloat(this.walkInjury);
  }

  int getPacketSizeBytes() { return 14; }

  std::string getDescription() {
    return "SyncInjuriesPacket: id=" + this.id +
           ", strafeSpeed=" + this.strafeSpeed +
           ", walkSpeed=" + this.walkSpeed + ", walkInjury=" + this.walkInjury;
  }
}
} // namespace packets
} // namespace network
} // namespace zombie
