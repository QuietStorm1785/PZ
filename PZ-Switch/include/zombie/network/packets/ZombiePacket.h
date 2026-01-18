#pragma once
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/network/NetworkVariables.h"
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
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class ZombiePacket {
public:
 static const int PACKET_SIZE_BYTES = 55;
 short id;
 float x;
 float y;
 uint8_t z;
 int descriptorID;
public
 NetworkVariables.PredictionTypes moveType;
 short booleanVariables;
 short target;
 int timeSinceSeenFlesh;
 int smParamTargetAngle;
 short speedMod;
public
 NetworkVariables.WalkType walkType;
 float realX;
 float realY;
 uint8_t realZ;
 short realHealth;
public
 NetworkVariables.ZombieState realState;
 short reanimatedBodyID;
 uint8_t pfbType;
 short pfbTarget;
 float pfbTargetX;
 float pfbTargetY;
 uint8_t pfbTargetZ;

 void parse(ByteBuffer byteBuffer, UdpConnection var2) {
 this->id = byteBuffer.getShort();
 this->x = byteBuffer.getFloat();
 this->y = byteBuffer.getFloat();
 this->z = byteBuffer.get();
 this->descriptorID = byteBuffer.getInt();
 this->moveType = NetworkVariables.PredictionTypes.fromByte(byteBuffer.get());
 this->booleanVariables = byteBuffer.getShort();
 this->target = byteBuffer.getShort();
 this->timeSinceSeenFlesh = byteBuffer.getInt();
 this->smParamTargetAngle = byteBuffer.getInt();
 this->speedMod = byteBuffer.getShort();
 this->walkType = NetworkVariables.WalkType.fromByte(byteBuffer.get());
 this->realX = byteBuffer.getFloat();
 this->realY = byteBuffer.getFloat();
 this->realZ = byteBuffer.get();
 this->realHealth = byteBuffer.getShort();
 this->realState = NetworkVariables.ZombieState.fromByte(byteBuffer.get());
 this->reanimatedBodyID = byteBuffer.getShort();
 this->pfbType = byteBuffer.get();
 if (this->pfbType == 1) {
 this->pfbTarget = byteBuffer.getShort();
 } else if (this->pfbType > 1) {
 this->pfbTargetX = byteBuffer.getFloat();
 this->pfbTargetY = byteBuffer.getFloat();
 this->pfbTargetZ = byteBuffer.get();
 }
 }

 void write(ByteBuffer byteBuffer) {
 byteBuffer.putShort(this->id);
 byteBuffer.putFloat(this->x);
 byteBuffer.putFloat(this->y);
 byteBuffer.put(this->z);
 byteBuffer.putInt(this->descriptorID);
 byteBuffer.put((byte)this->moveType.ordinal());
 byteBuffer.putShort(this->booleanVariables);
 byteBuffer.putShort(this->target);
 byteBuffer.putInt(this->timeSinceSeenFlesh);
 byteBuffer.putInt(this->smParamTargetAngle);
 byteBuffer.putShort(this->speedMod);
 byteBuffer.put((byte)this->walkType.ordinal());
 byteBuffer.putFloat(this->realX);
 byteBuffer.putFloat(this->realY);
 byteBuffer.put(this->realZ);
 byteBuffer.putShort(this->realHealth);
 byteBuffer.put((byte)this->realState.ordinal());
 byteBuffer.putShort(this->reanimatedBodyID);
 byteBuffer.put(this->pfbType);
 if (this->pfbType == 1) {
 byteBuffer.putShort(this->pfbTarget);
 } else if (this->pfbType > 1) {
 byteBuffer.putFloat(this->pfbTargetX);
 byteBuffer.putFloat(this->pfbTargetY);
 byteBuffer.put(this->pfbTargetZ);
 }
 }

 void write(ByteBufferWriter byteBufferWriter) {
 this->write(byteBufferWriter.bb);
 }

 int getPacketSizeBytes() { return 55; }

 void copy(ZombiePacket zombiePacket0) {
 this->id = zombiePacket0.id;
 this->x = zombiePacket0.x;
 this->y = zombiePacket0.y;
 this->z = zombiePacket0.z;
 this->descriptorID = zombiePacket0.descriptorID;
 this->moveType = zombiePacket0.moveType;
 this->booleanVariables = zombiePacket0.booleanVariables;
 this->target = zombiePacket0.target;
 this->timeSinceSeenFlesh = zombiePacket0.timeSinceSeenFlesh;
 this->smParamTargetAngle = zombiePacket0.smParamTargetAngle;
 this->speedMod = zombiePacket0.speedMod;
 this->walkType = zombiePacket0.walkType;
 this->realX = zombiePacket0.realX;
 this->realY = zombiePacket0.realY;
 this->realZ = zombiePacket0.realZ;
 this->realHealth = zombiePacket0.realHealth;
 this->reanimatedBodyID = zombiePacket0.reanimatedBodyID;
 this->realState = zombiePacket0.realState;
 this->pfbType = zombiePacket0.pfbType;
 this->pfbTarget = zombiePacket0.pfbTarget;
 this->pfbTargetX = zombiePacket0.pfbTargetX;
 this->pfbTargetY = zombiePacket0.pfbTargetY;
 this->pfbTargetZ = zombiePacket0.pfbTargetZ;
 }

 void set(IsoZombie zombie0) {
 this->id = zombie0.OnlineID;
 this->descriptorID = zombie0.getPersistentOutfitID();
 zombie0.networkAI.set(this);
 zombie0.networkAI.mindSync.set(this);
 zombie0.thumpSent = true;
 }
}
} // namespace packets
} // namespace network
} // namespace zombie
