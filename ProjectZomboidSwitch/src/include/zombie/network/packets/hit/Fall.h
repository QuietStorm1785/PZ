#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/HitReactionNetworkAI.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/network/packets/INetworkPacket.h"
#include <filesystem>

namespace zombie {
namespace network {
namespace packets {
namespace hit {


class Fall {
public:
    float dropPositionX;
    float dropPositionY;
    uint8_t dropPositionZ;
    float dropDirection;

    void set(HitReactionNetworkAI var1) {
      this.dropPositionX = var1.finalPosition.x;
      this.dropPositionY = var1.finalPosition.y;
      this.dropPositionZ = var1.finalPositionZ;
      this.dropDirection = var1.finalDirection.getDirection();
   }

    void set(float var1, float var2, uint8_t var3, float var4) {
      this.dropPositionX = var1;
      this.dropPositionY = var2;
      this.dropPositionZ = var3;
      this.dropDirection = var4;
   }

    void parse(ByteBuffer var1, UdpConnection var2) {
      this.dropPositionX = var1.getFloat();
      this.dropPositionY = var1.getFloat();
      this.dropPositionZ = var1.get();
      this.dropDirection = var1.getFloat();
   }

    void write(ByteBufferWriter var1) {
      var1.putFloat(this.dropPositionX);
      var1.putFloat(this.dropPositionY);
      var1.putByte(this.dropPositionZ);
      var1.putFloat(this.dropDirection);
   }

    std::string getDescription() {
      return "\n\tFall [ direction="
         + this.dropDirection
         + " | position=( "
         + this.dropPositionX
         + " ; "
         + this.dropPositionY
         + " ; "
         + this.dropPositionZ
         + " ) ]";
   }

    void process(IsoGameCharacter var1) {
      if (this.isSetup() && var1.getHitReactionNetworkAI() != nullptr) {
         var1.getHitReactionNetworkAI().process(this.dropPositionX, this.dropPositionY, this.dropPositionZ, this.dropDirection);
      }
   }

    bool isSetup() {
      return this.dropPositionX != 0.0F && this.dropPositionY != 0.0F;
   }
}
} // namespace hit
} // namespace packets
} // namespace network
} // namespace zombie
