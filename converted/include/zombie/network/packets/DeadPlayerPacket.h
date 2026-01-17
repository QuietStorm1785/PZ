#pragma once
#include "zombie/characters/IsoGameCharacter.h"
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

class DeadPlayerPacket : public DeadCharacterPacket {
public:
  uint8_t playerFlags;
  float infectionLevel;
  IsoPlayer player;

  void set(IsoGameCharacter character) {
    super.set(character);
    this.player = (IsoPlayer)character;
    if (GameClient.bClient) {
      this.id = (short)this.player.getPlayerNum();
    }

    this.infectionLevel = this.player.getBodyDamage().getInfectionLevel();
    this.playerFlags =
        (byte)(this.playerFlags |
               (byte)(this.player.getBodyDamage().isInfected() ? 1 : 0));
  }

  void process() {
    if (this.player != nullptr) {
      this.character.setHealth(0.0F);
      this.player.getBodyDamage().setOverallBodyHealth(0.0F);
      this.player.getBodyDamage().setInfected((this.playerFlags & 1) != 0);
      this.player.getBodyDamage().setInfectionLevel(this.infectionLevel);
      super.process();
    }
  }

  void parse(ByteBuffer byteBuffer, UdpConnection udpConnection) {
    super.parse(byteBuffer, udpConnection);
    this.infectionLevel = byteBuffer.getFloat();
    if (GameServer.bServer) {
      this.player = GameServer.getPlayerFromConnection(udpConnection, this.id);
    } else if (GameClient.bClient) {
      this.player = GameClient.IDToPlayerMap.get(this.id);
    }

    if (this.player != nullptr) {
      this.character = this.player;
      this.parseCharacterInventory(byteBuffer);
      this.character.setHealth(0.0F);
      this.character.getBodyDamage().setOverallBodyHealth(0.0F);
      this.character.getNetworkCharacterAI().setDeadBody(this);
    }
  }

  void write(ByteBufferWriter byteBufferWriter) {
    super.write(byteBufferWriter);
    byteBufferWriter.putFloat(this.infectionLevel);
    this.writeCharacterInventory(byteBufferWriter);
  }

  std::string getDescription() {
    return super.getDescription() +
           String.format(" | isInfected=%b infectionLevel=%f",
                         (this.playerFlags & 1) != 0, this.infectionLevel);
  }

  IsoPlayer getPlayer() { return this.player; }
}
} // namespace packets
} // namespace network
} // namespace zombie
