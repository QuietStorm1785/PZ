#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/BodyDamage/BodyPart.h"
#include "zombie/characters/BodyDamage/BodyPartType.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/network/packets/INetworkPacket.h"
#include <filesystem>

namespace zombie {
namespace network {
namespace packets {
namespace hit {


class PlayerBodyPart {
public:
    uint8_t bodyPartIndex;
    BodyPart bodyPart;

    void set(BodyPart var1) {
      if (var1 == nullptr) {
         this.bodyPartIndex = -1;
      } else {
         this.bodyPartIndex = (byte)var1.getIndex();
      }

      this.bodyPart = var1;
   }

    void parse(ByteBuffer var1, IsoGameCharacter var2) {
    bool var3 = var1.get() == 1;
      if (var3) {
         this.bodyPartIndex = var1.get();
         if (var2 == nullptr) {
            this.bodyPart = nullptr;
         } else {
            this.bodyPart = var2.getBodyDamage().getBodyPart(BodyPartType.FromIndex(this.bodyPartIndex));
         }
      } else {
         this.bodyPart = nullptr;
      }
   }

    void parse(ByteBuffer var1, UdpConnection var2) {
      DebugLog.Multiplayer.error("PlayerBodyPart.parse is not implemented");
   }

    void write(ByteBufferWriter var1) {
      if (this.bodyPart == nullptr) {
         var1.putByte((byte)0);
      } else {
         var1.putByte((byte)1);
         var1.putByte((byte)this.bodyPart.getIndex());
      }
   }

    std::string getDescription() {
      return "\n\tPlayerBodyPart [ Item=" + (this.bodyPart == nullptr ? "?" : "\"" + this.bodyPart.getType().name() + "\"") + " ]";
   }

    BodyPart getBodyPart() {
      return this.bodyPart;
   }
}
} // namespace hit
} // namespace packets
} // namespace network
} // namespace zombie
