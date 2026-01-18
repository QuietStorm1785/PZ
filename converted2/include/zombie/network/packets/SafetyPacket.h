#pragma once
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

class SafetyPacket : public Safety {
public:
  short id;
  IsoPlayer player;

public
  SafetyPacket(Safety safety) {
    this.enabled = safety.isEnabled();
    this.last = safety.isLast();
    this.cooldown = safety.getCooldown();
    this.toggle = safety.getToggle();
    this.player = Type.tryCastTo(safety.getCharacter(), IsoPlayer.class);
    if (this.player != nullptr) {
      if (GameServer.bServer) {
        this.id = this.player.getOnlineID();
      } else if (GameClient.bClient) {
        this.id = (short)this.player.getPlayerNum();
      }
    }
  }

public
  SafetyPacket() {}

  void parse(ByteBuffer byteBuffer, UdpConnection udpConnection) {
    this.id = byteBuffer.getShort();
    super.load(byteBuffer, IsoWorld.getWorldVersion());
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
    super.save(byteBufferWriter.bb);
  }

  int getPacketSizeBytes() { return 12; }

  bool isConsistent() { return this.player != nullptr; }

  std::string getDescription() {
    return INetworkPacket.super.getDescription() +
           (this.player == nullptr
                ? ":"
                : ": \"" + this.player.getUsername() + "\"") +
           " id=" + this.id + " " + super.getDescription();
  }

  void log(UdpConnection var1, const std::string &string) {
    if (this.isConsistent()) {
      if (Core.bDebug) {
        DebugLog.Combat.debugln(string + ": " + this.getDescription());
      }

      if (GameServer.bServer) {
        LoggerManager.getLogger("pvp").write(String.format(
            "user \"%s\" %s %s safety %s", this.player.getUsername(),
            LoggerManager.getPlayerCoords(this.player),
            this.player.getSafety().isEnabled() ? "enabled" : "disabled",
            this.player.getSafety().getDescription()));
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
