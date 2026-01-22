#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/network/NetworkVariables/PredictionTypes.h"
#include "zombie/network/NetworkVariables/WalkType.h"
#include "zombie/network/NetworkVariables/ZombieState.h"
#include <filesystem>

namespace zombie {
namespace network {
namespace packets {


class ZombiePacket {
public:
    static const int PACKET_SIZE_BYTES = 55;
    short id;
    float x;
    float y;
    uint8_t z;
    int descriptorID;
    PredictionTypes moveType;
    short booleanVariables;
    short target;
    int timeSinceSeenFlesh;
    int smParamTargetAngle;
    short speedMod;
    WalkType walkType;
    float realX;
    float realY;
    uint8_t realZ;
    short realHealth;
    ZombieState realState;
    short reanimatedBodyID;
    uint8_t pfbType;
    short pfbTarget;
    float pfbTargetX;
    float pfbTargetY;
    uint8_t pfbTargetZ;

    void parse(ByteBuffer var1, UdpConnection var2) {
      this.id = var1.getShort();
      this.x = var1.getFloat();
      this.y = var1.getFloat();
      this.z = var1.get();
      this.descriptorID = var1.getInt();
      this.moveType = PredictionTypes.fromByte(var1.get());
      this.booleanVariables = var1.getShort();
      this.target = var1.getShort();
      this.timeSinceSeenFlesh = var1.getInt();
      this.smParamTargetAngle = var1.getInt();
      this.speedMod = var1.getShort();
      this.walkType = WalkType.fromByte(var1.get());
      this.realX = var1.getFloat();
      this.realY = var1.getFloat();
      this.realZ = var1.get();
      this.realHealth = var1.getShort();
      this.realState = ZombieState.fromByte(var1.get());
      this.reanimatedBodyID = var1.getShort();
      this.pfbType = var1.get();
      if (this.pfbType == 1) {
         this.pfbTarget = var1.getShort();
      } else if (this.pfbType > 1) {
         this.pfbTargetX = var1.getFloat();
         this.pfbTargetY = var1.getFloat();
         this.pfbTargetZ = var1.get();
      }
   }

    void write(ByteBuffer var1) {
      var1.putShort(this.id);
      var1.putFloat(this.x);
      var1.putFloat(this.y);
      var1.put(this.z);
      var1.putInt(this.descriptorID);
      var1.put((byte)this.moveType.ordinal());
      var1.putShort(this.booleanVariables);
      var1.putShort(this.target);
      var1.putInt(this.timeSinceSeenFlesh);
      var1.putInt(this.smParamTargetAngle);
      var1.putShort(this.speedMod);
      var1.put((byte)this.walkType.ordinal());
      var1.putFloat(this.realX);
      var1.putFloat(this.realY);
      var1.put(this.realZ);
      var1.putShort(this.realHealth);
      var1.put((byte)this.realState.ordinal());
      var1.putShort(this.reanimatedBodyID);
      var1.put(this.pfbType);
      if (this.pfbType == 1) {
         var1.putShort(this.pfbTarget);
      } else if (this.pfbType > 1) {
         var1.putFloat(this.pfbTargetX);
         var1.putFloat(this.pfbTargetY);
         var1.put(this.pfbTargetZ);
      }
   }

    void write(ByteBufferWriter var1) {
      this.write(var1.bb);
   }

    int getPacketSizeBytes() {
    return 55;
   }

    void copy(ZombiePacket var1) {
      this.id = var1.id;
      this.x = var1.x;
      this.y = var1.y;
      this.z = var1.z;
      this.descriptorID = var1.descriptorID;
      this.moveType = var1.moveType;
      this.booleanVariables = var1.booleanVariables;
      this.target = var1.target;
      this.timeSinceSeenFlesh = var1.timeSinceSeenFlesh;
      this.smParamTargetAngle = var1.smParamTargetAngle;
      this.speedMod = var1.speedMod;
      this.walkType = var1.walkType;
      this.realX = var1.realX;
      this.realY = var1.realY;
      this.realZ = var1.realZ;
      this.realHealth = var1.realHealth;
      this.reanimatedBodyID = var1.reanimatedBodyID;
      this.realState = var1.realState;
      this.pfbType = var1.pfbType;
      this.pfbTarget = var1.pfbTarget;
      this.pfbTargetX = var1.pfbTargetX;
      this.pfbTargetY = var1.pfbTargetY;
      this.pfbTargetZ = var1.pfbTargetZ;
   }

    void set(IsoZombie var1) {
      this.id = var1.OnlineID;
      this.descriptorID = var1.getPersistentOutfitID();
      var1.networkAI.set(this);
      var1.networkAI.mindSync.set(this);
      var1.thumpSent = true;
   }
}
} // namespace packets
} // namespace network
} // namespace zombie
