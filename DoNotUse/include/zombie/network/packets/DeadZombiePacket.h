#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/iso/objects/IsoDeadBody.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/ServerMap.h"
#include <filesystem>

namespace zombie {
namespace network {
namespace packets {


class DeadZombiePacket : public DeadCharacterPacket {
public:
    uint8_t zombieFlags;
    IsoZombie zombie;

    void set(IsoGameCharacter var1) {
      super.set(var1);
      this.zombie = (IsoZombie)var1;
      this.zombieFlags = (byte)(this.zombieFlags | (byte)(this.zombie.isCrawling() ? 1 : 0));
   }

    void process() {
      if (this.zombie != nullptr) {
         this.zombie.setCrawler((this.zombieFlags & 1) != 0);
         super.process();
      }
   }

    void parse(ByteBuffer var1, UdpConnection var2) {
      super.parse(var1, var2);
      if (GameServer.bServer) {
         this.zombie = (IsoZombie)ServerMap.instance.ZombieMap.get(this.id);
      } else if (GameClient.bClient) {
         this.zombie = (IsoZombie)GameClient.IDToZombieMap.get(this.id);
      }

      if (this.zombie != nullptr) {
         this.character = this.zombie;
         if (!GameServer.bServer || !this.zombie.isReanimatedPlayer()) {
            this.parseCharacterInventory(var1);
            this.parseCharacterHumanVisuals(var1);
         }

         this.character.setHealth(0.0F);
         this.character.getHitReactionNetworkAI().process(this.x, this.y, this.z, this.angle);
         this.character.getNetworkCharacterAI().setDeadBody(this);
      } else {
    IsoDeadBody var3 = this.getDeadBody();
         if (var3 != nullptr) {
            this.parseDeadBodyInventory(var3, var1);
            this.parseDeadBodyHumanVisuals(var3, var1);
         }
      }
   }

    void write(ByteBufferWriter var1) {
      super.write(var1);
      this.writeCharacterInventory(var1);
      this.writeCharacterHumanVisuals(var1);
   }

    std::string getDescription() {
      return super.getDescription() + std::string.format(" | isCrawling=%b", (this.zombieFlags & 1) != 0);
   }

    IsoZombie getZombie() {
      return this.zombie;
   }
}
} // namespace packets
} // namespace network
} // namespace zombie
