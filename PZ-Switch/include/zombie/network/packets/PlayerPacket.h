#pragma once
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/network/GameClient.h"
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

class PlayerPacket {
public:
 static const int PACKET_SIZE_BYTES = 43;
 short id;
 float x;
 float y;
 uint8_t z;
 float direction;
 bool usePathFinder;
public
 NetworkVariables.PredictionTypes moveType;
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
 PlayerVariables variables = new PlayerVariables();

 void parse(ByteBuffer byteBuffer, UdpConnection udpConnection) {
 this->id = byteBuffer.getShort();
 this->x = byteBuffer.getFloat();
 this->y = byteBuffer.getFloat();
 this->z = byteBuffer.get();
 this->direction = byteBuffer.getFloat();
 this->usePathFinder = byteBuffer.get() == 1;
 this->moveType = NetworkVariables.PredictionTypes.fromByte(byteBuffer.get());
 this->VehicleID = byteBuffer.getShort();
 this->VehicleSeat = byteBuffer.getShort();
 this->booleanVariables = byteBuffer.getInt();
 this->footstepSoundRadius = byteBuffer.get();
 this->bleedingLevel = byteBuffer.get();
 this->realx = byteBuffer.getFloat();
 this->realy = byteBuffer.getFloat();
 this->realz = byteBuffer.get();
 this->realdir = byteBuffer.get();
 this->realt = byteBuffer.getInt();
 this->collidePointX = byteBuffer.getFloat();
 this->collidePointY = byteBuffer.getFloat();
 this->variables.parse(byteBuffer, udpConnection);
 }

 void write(ByteBufferWriter byteBufferWriter) {
 byteBufferWriter.putShort(this->id);
 byteBufferWriter.putFloat(this->x);
 byteBufferWriter.putFloat(this->y);
 byteBufferWriter.putByte(this->z);
 byteBufferWriter.putFloat(this->direction);
 byteBufferWriter.putBoolean(this->usePathFinder);
 byteBufferWriter.putByte((byte)this->moveType.ordinal());
 byteBufferWriter.putShort(this->VehicleID);
 byteBufferWriter.putShort(this->VehicleSeat);
 byteBufferWriter.putInt(this->booleanVariables);
 byteBufferWriter.putByte(this->footstepSoundRadius);
 byteBufferWriter.putByte(this->bleedingLevel);
 byteBufferWriter.putFloat(this->realx);
 byteBufferWriter.putFloat(this->realy);
 byteBufferWriter.putByte(this->realz);
 byteBufferWriter.putByte(this->realdir);
 byteBufferWriter.putInt(this->realt);
 byteBufferWriter.putFloat(this->collidePointX);
 byteBufferWriter.putFloat(this->collidePointY);
 this->variables.write(byteBufferWriter);
 }

 int getPacketSizeBytes() noexcept{ return 43; }

 bool set(IsoPlayer player) {
 if (GameClient.bClient) {
 this->id = (short)player.getPlayerNum();
 } else {
 this->id = player.OnlineID;
 }

 this->bleedingLevel = player.bleedingLevel;
 this->variables.set(player);
 return player.networkAI.set(this);
 }

 void copy(PlayerPacket playerPacket0) {
 this->id = playerPacket0.id;
 this->x = playerPacket0.x;
 this->y = playerPacket0.y;
 this->z = playerPacket0.z;
 this->direction = playerPacket0.direction;
 this->usePathFinder = playerPacket0.usePathFinder;
 this->moveType = playerPacket0.moveType;
 this->VehicleID = playerPacket0.VehicleID;
 this->VehicleSeat = playerPacket0.VehicleSeat;
 this->booleanVariables = playerPacket0.booleanVariables;
 this->footstepSoundRadius = playerPacket0.footstepSoundRadius;
 this->bleedingLevel = playerPacket0.bleedingLevel;
 this->realx = playerPacket0.realx;
 this->realy = playerPacket0.realy;
 this->realz = playerPacket0.realz;
 this->realdir = playerPacket0.realdir;
 this->realt = playerPacket0.realt;
 this->collidePointX = playerPacket0.collidePointX;
 this->collidePointY = playerPacket0.collidePointY;
 this->variables.copy(playerPacket0.variables);
 }

public
 static class l_receive {
 static PlayerPacket playerPacket = new PlayerPacket();
 }

 public static class l_send {
 static PlayerPacket playerPacket = new PlayerPacket();
 }
}
} // namespace packets
} // namespace network
} // namespace zombie
