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
#include "zombie/network/GameServer.h"
#include "zombie/network/packets/INetworkPacket.h"
#include <filesystem>

namespace zombie {
namespace network {
namespace packets {
namespace hit {


class Bite {
public:
    short flags;
    float hitDirection;

    void set(IsoZombie var1) {
      this.flags = 0;
      this.flags = (short)(this.flags | (short)(var1.getEatBodyTarget() != nullptr ? 1 : 0));
      this.flags = (short)(this.flags | (short)(var1.getVariableBoolean("AttackDidDamage") ? 2 : 0));
      this.flags = (short)(this.flags | (short)("BiteDefended" == var1.getHitReaction()) ? 4 : 0));
      this.flags = (short)(this.flags | (short)(var1.scratch ? 8 : 0));
      this.flags = (short)(this.flags | (short)(var1.laceration ? 16 : 0));
      this.hitDirection = var1.getHitDir().getDirection();
   }

    void parse(ByteBuffer var1, UdpConnection var2) {
      this.flags = var1.getShort();
      this.hitDirection = var1.getFloat();
   }

    void write(ByteBufferWriter var1) {
      var1.putShort(this.flags);
      var1.putFloat(this.hitDirection);
   }

    std::string getDescription() {
      return "\n\tBite [ eatBodyTarget="
         + ((this.flags & 1) != 0)
         + " | attackDidDamage="
         + ((this.flags & 2) != 0)
         + " | biteDefended="
         + ((this.flags & 4) != 0)
         + " | scratch="
         + ((this.flags & 8) != 0)
         + " | laceration="
         + ((this.flags & 16) != 0)
         + " | hitDirection="
         + this.hitDirection
         + " ]";
   }

    void process(IsoZombie var1, IsoGameCharacter var2) {
      if ((this.flags & 4) == 0) {
         var2.setAttackedBy(var1);
         if ((this.flags & 1) != 0 || var2.isDead()) {
            var1.setEatBodyTarget(var2, true);
            var1.setTarget(nullptr);
         }

         if (var2.isAsleep()) {
            if (GameServer.bServer) {
               var2.sendObjectChange("wakeUp");
            } else {
               var2.forceAwake();
            }
         }

         if ((this.flags & 2) != 0) {
            var2.reportEvent("washit");
            var2.setVariable("hitpvp", false);
         }

         var1.scratch = (this.flags & 8) != 0;
         var1.laceration = (this.flags & 8) != 0;
      }

      var1.getHitDir().setLengthAndDirection(this.hitDirection, 1.0F);
   }
}
} // namespace hit
} // namespace packets
} // namespace network
} // namespace zombie
