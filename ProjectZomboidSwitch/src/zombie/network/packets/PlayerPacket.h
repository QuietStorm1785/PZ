#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/NetworkVariables/PredictionTypes.h"
#include <filesystem>

namespace zombie {
namespace network {
namespace packets {


class PlayerPacket {
public:
    static const int PACKET_SIZE_BYTES = 43;
    short id;
    float x;
    float y;
    uint8_t z;
    float direction;
    bool usePathFinder;
    PredictionTypes moveType;
    short VehicleID;
    short VehicleSeat;
    int booleanVariables;
    uint8_t footstepSoundRadius;
    uint8_t bleedingLevel;
    float realx;
    float realy;
    uint8_t realz;
    uint8_t realdir;
    int realt;
    float collidePointX;
    float collidePointY;
    PlayerVariables variables = std::make_shared<PlayerVariables>();

    void parse(ByteBuffer var1, UdpConnection var2) {
      this.id = var1.getShort();
      this.x = var1.getFloat();
      this.y = var1.getFloat();
      this.z = var1.get();
      this.direction = var1.getFloat();
      this.usePathFinder = var1.get() == 1;
      this.moveType = PredictionTypes.fromByte(var1.get());
      this.VehicleID = var1.getShort();
      this.VehicleSeat = var1.getShort();
      this.booleanVariables = var1.getInt();
      this.footstepSoundRadius = var1.get();
      this.bleedingLevel = var1.get();
      this.realx = var1.getFloat();
      this.realy = var1.getFloat();
      this.realz = var1.get();
      this.realdir = var1.get();
      this.realt = var1.getInt();
      this.collidePointX = var1.getFloat();
      this.collidePointY = var1.getFloat();
      this.variables.parse(var1, var2);
   }

    void write(ByteBufferWriter var1) {
      var1.putShort(this.id);
      var1.putFloat(this.x);
      var1.putFloat(this.y);
      var1.putByte(this.z);
      var1.putFloat(this.direction);
      var1.putBoolean(this.usePathFinder);
      var1.putByte((byte)this.moveType.ordinal());
      var1.putShort(this.VehicleID);
      var1.putShort(this.VehicleSeat);
      var1.putInt(this.booleanVariables);
      var1.putByte(this.footstepSoundRadius);
      var1.putByte(this.bleedingLevel);
      var1.putFloat(this.realx);
      var1.putFloat(this.realy);
      var1.putByte(this.realz);
      var1.putByte(this.realdir);
      var1.putInt(this.realt);
      var1.putFloat(this.collidePointX);
      var1.putFloat(this.collidePointY);
      this.variables.write(var1);
   }

    int getPacketSizeBytes() {
    return 43;
   }

    bool set(IsoPlayer var1) {
      if (GameClient.bClient) {
         this.id = (short)var1.getPlayerNum();
      } else {
         this.id = var1.OnlineID;
      }

      this.bleedingLevel = var1.bleedingLevel;
      this.variables.set(var1);
      return var1.networkAI.set(this);
   }

    void copy(PlayerPacket var1) {
      this.id = var1.id;
      this.x = var1.x;
      this.y = var1.y;
      this.z = var1.z;
      this.direction = var1.direction;
      this.usePathFinder = var1.usePathFinder;
      this.moveType = var1.moveType;
      this.VehicleID = var1.VehicleID;
      this.VehicleSeat = var1.VehicleSeat;
      this.booleanVariables = var1.booleanVariables;
      this.footstepSoundRadius = var1.footstepSoundRadius;
      this.bleedingLevel = var1.bleedingLevel;
      this.realx = var1.realx;
      this.realy = var1.realy;
      this.realz = var1.realz;
      this.realdir = var1.realdir;
      this.realt = var1.realt;
      this.collidePointX = var1.collidePointX;
      this.collidePointY = var1.collidePointY;
      this.variables.copy(var1.variables);
   }
}
} // namespace packets
} // namespace network
} // namespace zombie
