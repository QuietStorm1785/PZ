#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/network/packets/INetworkPacket.h"
#include <filesystem>

namespace zombie {
namespace network {
namespace packets {
namespace hit {


class NetObject {
public:
    const uint8_t objectTypeNone = 0;
    const uint8_t objectTypeObject = 1;
    bool isProcessed = false;
    uint8_t objectType = 0;
    short objectId;
    int squareX;
    int squareY;
    uint8_t squareZ;
    IsoObject object;

    void setObject(IsoObject var1) {
      this.object = var1;
      this.isProcessed = true;
      if (this.object == nullptr) {
         this.objectType = 0;
         this.objectId = 0;
      } else {
    IsoGridSquare var2 = this.object.square;
         this.objectType = 1;
         this.objectId = (short)var2.getObjects().indexOf(this.object);
         this.squareX = var2.getX();
         this.squareY = var2.getY();
         this.squareZ = (byte)var2.getZ();
      }
   }

    IsoObject getObject() {
      if (!this.isProcessed) {
         if (this.objectType == 0) {
            this.object = nullptr;
         }

         if (this.objectType == 1) {
    IsoGridSquare var1 = IsoWorld.instance.CurrentCell.getGridSquare(this.squareX, this.squareY, this.squareZ);
            if (var1 == nullptr) {
               this.object = nullptr;
            } else {
               this.object = (IsoObject)var1.getObjects().get(this.objectId);
            }
         }

         this.isProcessed = true;
      }

      return this.object;
   }

    void parse(ByteBuffer var1, UdpConnection var2) {
      this.objectType = var1.get();
      if (this.objectType == 1) {
         this.objectId = var1.getShort();
         this.squareX = var1.getInt();
         this.squareY = var1.getInt();
         this.squareZ = var1.get();
      }

      this.isProcessed = false;
   }

    void write(ByteBufferWriter var1) {
      var1.putByte(this.objectType);
      if (this.objectType == 1) {
         var1.putShort(this.objectId);
         var1.putInt(this.squareX);
         var1.putInt(this.squareY);
         var1.putByte(this.squareZ);
      }
   }

    int getPacketSizeBytes() {
      return this.objectType == 1 ? 12 : 1;
   }

    std::string getDescription() {
    std::string var1 = "";
      switch (this.objectType) {
         case 0:
            var1 = "None";
            break;
         case 1:
            var1 = "NetObject";
      }

      return "\n\tNetObject [type="
         + var1
         + "("
         + this.objectType
         + ") | id="
         + this.objectId
         + " | pos=("
         + this.squareX
         + ", "
         + this.squareY
         + ", "
         + this.squareZ
         + ") ]";
   }
}
} // namespace hit
} // namespace packets
} // namespace network
} // namespace zombie
