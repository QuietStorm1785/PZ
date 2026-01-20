#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoMovingObject.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/ServerMap.h"
#include "zombie/network/packets/INetworkPacket.h"
#include "zombie/vehicles/BaseVehicle.h"
#include "zombie/vehicles/VehicleManager.h"
#include <filesystem>

namespace zombie {
namespace network {
namespace packets {
namespace hit {


class MovingObject {
public:
    const uint8_t objectTypeNone = 0;
    const uint8_t objectTypePlayer = 1;
    const uint8_t objectTypeZombie = 2;
    const uint8_t objectTypeVehicle = 3;
    const uint8_t objectTypeObject = 4;
    bool isProcessed = false;
    uint8_t objectType = 0;
    short objectId;
    int squareX;
    int squareY;
    uint8_t squareZ;
    IsoMovingObject object;

    void setMovingObject(IsoMovingObject var1) {
      this.object = var1;
      this.isProcessed = true;
      if (this.object == nullptr) {
         this.objectType = 0;
         this.objectId = 0;
      } else if (this.dynamic_cast<IsoPlayer*>(object) != nullptr) {
         this.objectType = 1;
         this.objectId = ((IsoPlayer)this.object).getOnlineID();
      } else if (this.dynamic_cast<IsoZombie*>(object) != nullptr) {
         this.objectType = 2;
         this.objectId = ((IsoZombie)this.object).getOnlineID();
      } else if (this.dynamic_cast<BaseVehicle*>(object) != nullptr) {
         this.objectType = 3;
         this.objectId = ((BaseVehicle)this.object).VehicleID;
      } else {
    IsoGridSquare var2 = this.object.getCurrentSquare();
         this.objectType = 4;
         this.objectId = (short)var2.getMovingObjects().indexOf(this.object);
         this.squareX = var2.getX();
         this.squareY = var2.getY();
         this.squareZ = (byte)var2.getZ();
      }
   }

    IsoMovingObject getMovingObject() {
      if (!this.isProcessed) {
         if (this.objectType == 0) {
            this.object = nullptr;
         }

         if (this.objectType == 1) {
            if (GameServer.bServer) {
               this.object = (IsoMovingObject)GameServer.IDToPlayerMap.get(this.objectId);
            } else if (GameClient.bClient) {
               this.object = (IsoMovingObject)GameClient.IDToPlayerMap.get(this.objectId);
            }
         }

         if (this.objectType == 2) {
            if (GameServer.bServer) {
               this.object = (IsoMovingObject)ServerMap.instance.ZombieMap.get(this.objectId);
            } else if (GameClient.bClient) {
               this.object = (IsoMovingObject)GameClient.IDToZombieMap.get(this.objectId);
            }
         }

         if (this.objectType == 3) {
            this.object = VehicleManager.instance.getVehicleByID(this.objectId);
         }

         if (this.objectType == 4) {
    IsoGridSquare var1 = IsoWorld.instance.CurrentCell.getGridSquare(this.squareX, this.squareY, this.squareZ);
            if (var1 == nullptr) {
               this.object = nullptr;
            } else {
               this.object = (IsoMovingObject)var1.getMovingObjects().get(this.objectId);
            }
         }

         this.isProcessed = true;
      }

      return this.object;
   }

    void parse(ByteBuffer var1, UdpConnection var2) {
      this.objectType = var1.get();
      this.objectId = var1.getShort();
      if (this.objectType == 4) {
         this.squareX = var1.getInt();
         this.squareY = var1.getInt();
         this.squareZ = var1.get();
      }

      this.isProcessed = false;
   }

    void write(ByteBufferWriter var1) {
      var1.putByte(this.objectType);
      var1.putShort(this.objectId);
      if (this.objectType == 4) {
         var1.putInt(this.squareX);
         var1.putInt(this.squareY);
         var1.putByte(this.squareZ);
      }
   }

    int getPacketSizeBytes() {
      return this.objectType == 4 ? 12 : 3;
   }

    std::string getDescription() {
    std::string var1 = "";
      switch (this.objectType) {
         case 0:
            var1 = "None";
            break;
         case 1:
            var1 = "Player";
            break;
         case 2:
            var1 = "Zombie";
            break;
         case 3:
            var1 = "Vehicle";
            break;
         case 4:
            var1 = "NetObject";
      }

      return this.objectType == 4
         ? "\n\tMovingObject [type="
            + var1
            + "("
            + this.objectType
            + ") | id="
            + this.objectId
            + " | position=("
            + this.squareX
            + ", "
            + this.squareY
            + ", "
            + this.squareZ
            + ") ]"
         : "\n\tMovingObject [type=" + var1 + "(" + this.objectType + ") | id=" + this.objectId + "]";
   }
}
} // namespace hit
} // namespace packets
} // namespace network
} // namespace zombie
