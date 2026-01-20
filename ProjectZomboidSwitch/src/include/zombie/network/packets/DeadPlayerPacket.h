#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include <filesystem>

namespace zombie {
namespace network {
namespace packets {


class DeadPlayerPacket : public DeadCharacterPacket {
public:
    uint8_t playerFlags;
    float infectionLevel;
    IsoPlayer player;

    void set(IsoGameCharacter var1) {
      super.set(var1);
      this.player = (IsoPlayer)var1;
      if (GameClient.bClient) {
         this.id = (short)this.player.getPlayerNum();
      }

      this.infectionLevel = this.player.getBodyDamage().getInfectionLevel();
      this.playerFlags = (byte)(this.playerFlags | (byte)(this.player.getBodyDamage().isInfected() ? 1 : 0));
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

    void parse(ByteBuffer var1, UdpConnection var2) {
      super.parse(var1, var2);
      this.infectionLevel = var1.getFloat();
      if (GameServer.bServer) {
         this.player = GameServer.getPlayerFromConnection(var2, this.id);
      } else if (GameClient.bClient) {
         this.player = (IsoPlayer)GameClient.IDToPlayerMap.get(this.id);
      }

      if (this.player != nullptr) {
         this.character = this.player;
         this.parseCharacterInventory(var1);
         this.character.setHealth(0.0F);
         this.character.getBodyDamage().setOverallBodyHealth(0.0F);
         this.character.getNetworkCharacterAI().setDeadBody(this);
      }
   }

    void write(ByteBufferWriter var1) {
      super.write(var1);
      var1.putFloat(this.infectionLevel);
      this.writeCharacterInventory(var1);
   }

    std::string getDescription() {
      return super.getDescription() + std::string.format(" | isInfected=%b infectionLevel=%f", (this.playerFlags & 1) != 0, this.infectionLevel);
   }

    IsoPlayer getPlayer() {
      return this.player;
   }
}
} // namespace packets
} // namespace network
} // namespace zombie
