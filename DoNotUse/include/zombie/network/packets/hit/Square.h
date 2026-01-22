#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/ServerMap.h"
#include "zombie/network/packets/INetworkPacket.h"
#include <filesystem>

namespace zombie {
namespace network {
namespace packets {
namespace hit {


class Square {
public:
    float positionX;
    float positionY;
    float positionZ;
    IsoGridSquare square;

    void set(IsoGameCharacter var1) {
      this.square = var1.getAttackTargetSquare();
      if (this.square != nullptr) {
         this.positionX = this.square.getX();
         this.positionY = this.square.getY();
         this.positionZ = this.square.getZ();
      } else {
         this.positionX = 0.0F;
         this.positionY = 0.0F;
         this.positionZ = 0.0F;
      }
   }

    void set(IsoGridSquare var1) {
      this.square = var1;
      if (this.square != nullptr) {
         this.positionX = this.square.getX();
         this.positionY = this.square.getY();
         this.positionZ = this.square.getZ();
      } else {
         this.positionX = 0.0F;
         this.positionY = 0.0F;
         this.positionZ = 0.0F;
      }
   }

    void parse(ByteBuffer var1, UdpConnection var2) {
      this.positionX = var1.getFloat();
      this.positionY = var1.getFloat();
      this.positionZ = var1.getFloat();
      if (GameServer.bServer) {
         this.square = ServerMap.instance.getGridSquare((int)Math.floor(this.positionX), (int)Math.floor(this.positionY), (int)Math.floor(this.positionZ));
      }

      if (GameClient.bClient) {
         this.square = IsoWorld.instance
            .CurrentCell
            .getGridSquare((int)Math.floor(this.positionX), (int)Math.floor(this.positionY), (int)Math.floor(this.positionZ));
      }
   }

    void write(ByteBufferWriter var1) {
      var1.putFloat(this.positionX);
      var1.putFloat(this.positionY);
      var1.putFloat(this.positionZ);
   }

    std::string getDescription() {
      return "\n\tSquare [ pos=( " + this.positionX + " ; " + this.positionY + " ; " + this.positionZ + " ) ]";
   }

    void process(IsoGameCharacter var1) {
      var1.setAttackTargetSquare(var1.getCell().getGridSquare(this.positionX, this.positionY, this.positionZ));
   }

    float getX() {
      return this.positionX;
   }

    float getY() {
      return this.positionY;
   }

    float getZ() {
      return this.positionZ;
   }

    IsoGridSquare getSquare() {
      return this.square;
   }

    bool isConsistent() {
      return this.square != nullptr;
   }
}
} // namespace hit
} // namespace packets
} // namespace network
} // namespace zombie
