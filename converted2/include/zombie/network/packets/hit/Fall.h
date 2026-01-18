#pragma once
#include "zombie/characters/HitReactionNetworkAI.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/network/packets/INetworkPacket.h"
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
namespace hit {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class Fall {
public:
  float dropPositionX;
  float dropPositionY;
  uint8_t dropPositionZ;
  float dropDirection;

  void set(HitReactionNetworkAI hitReactionNetworkAI) {
    this.dropPositionX = hitReactionNetworkAI.finalPosition.x;
    this.dropPositionY = hitReactionNetworkAI.finalPosition.y;
    this.dropPositionZ = hitReactionNetworkAI.finalPositionZ;
    this.dropDirection = hitReactionNetworkAI.finalDirection.getDirection();
  }

  void set(float float0, float float1, uint8_t byte0, float float2) {
    this.dropPositionX = float0;
    this.dropPositionY = float1;
    this.dropPositionZ = byte0;
    this.dropDirection = float2;
  }

  void parse(ByteBuffer byteBuffer, UdpConnection var2) {
    this.dropPositionX = byteBuffer.getFloat();
    this.dropPositionY = byteBuffer.getFloat();
    this.dropPositionZ = byteBuffer.get();
    this.dropDirection = byteBuffer.getFloat();
  }

  void write(ByteBufferWriter byteBufferWriter) {
    byteBufferWriter.putFloat(this.dropPositionX);
    byteBufferWriter.putFloat(this.dropPositionY);
    byteBufferWriter.putByte(this.dropPositionZ);
    byteBufferWriter.putFloat(this.dropDirection);
  }

  std::string getDescription() {
    return "\n\tFall [ direction=" + this.dropDirection + " | position=( " +
           this.dropPositionX + " ; " + this.dropPositionY + " ; " +
           this.dropPositionZ + " ) ]";
  }

  void process(IsoGameCharacter character) {
    if (this.isSetup() && character.getHitReactionNetworkAI() != nullptr) {
      character.getHitReactionNetworkAI().process(
          this.dropPositionX, this.dropPositionY, this.dropPositionZ,
          this.dropDirection);
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
