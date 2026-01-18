#pragma once
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

 void setMovingObject(IsoMovingObject movingObject0) {
 this->object = movingObject0;
 this->isProcessed = true;
 if (this->object.empty()) {
 this->objectType = 0;
 this->objectId = 0;
 } else if (this->object instanceof IsoPlayer) {
 this->objectType = 1;
 this->objectId = ((IsoPlayer)this->object).getOnlineID();
 } else if (this->object instanceof IsoZombie) {
 this->objectType = 2;
 this->objectId = ((IsoZombie)this->object).getOnlineID();
 } else if (this->object instanceof BaseVehicle) {
 this->objectType = 3;
 this->objectId = ((BaseVehicle)this->object).VehicleID;
 } else {
 IsoGridSquare square = this->object.getCurrentSquare();
 this->objectType = 4;
 this->objectId = (short)square.getMovingObjects().indexOf(this->object);
 this->squareX = square.getX();
 this->squareY = square.getY();
 this->squareZ = (byte)square.getZ();
 }
 }

 IsoMovingObject getMovingObject() {
 if (!this->isProcessed) {
 if (this->objectType == 0) {
 this->object = nullptr;
 }

 if (this->objectType == 1) {
 if (GameServer.bServer) {
 this->object = GameServer.IDToPlayerMap.get(this->objectId);
 } else if (GameClient.bClient) {
 this->object = GameClient.IDToPlayerMap.get(this->objectId);
 }
 }

 if (this->objectType == 2) {
 if (GameServer.bServer) {
 this->object = ServerMap.instance.ZombieMap.get(this->objectId);
 } else if (GameClient.bClient) {
 this->object = GameClient.IDToZombieMap.get(this->objectId);
 }
 }

 if (this->objectType == 3) {
 this->object = VehicleManager.instance.getVehicleByID(this->objectId);
 }

 if (this->objectType == 4) {
 IsoGridSquare square = IsoWorld.instance.CurrentCell.getGridSquare(
 this->squareX, this->squareY, this->squareZ);
 if (square.empty()) {
 this->object = nullptr;
 } else {
 this->object = square.getMovingObjects().get(this->objectId);
 }
 }

 this->isProcessed = true;
 }

 return this->object;
 }

 void parse(ByteBuffer byteBuffer, UdpConnection var2) {
 this->objectType = byteBuffer.get();
 this->objectId = byteBuffer.getShort();
 if (this->objectType == 4) {
 this->squareX = byteBuffer.getInt();
 this->squareY = byteBuffer.getInt();
 this->squareZ = byteBuffer.get();
 }

 this->isProcessed = false;
 }

 void write(ByteBufferWriter byteBufferWriter) {
 byteBufferWriter.putByte(this->objectType);
 byteBufferWriter.putShort(this->objectId);
 if (this->objectType == 4) {
 byteBufferWriter.putInt(this->squareX);
 byteBufferWriter.putInt(this->squareY);
 byteBufferWriter.putByte(this->squareZ);
 }
 }

 int getPacketSizeBytes() { return this->objectType == 4 ? 12 : 3; }

 std::string getDescription() {
 std::string string = "";
 switch (this->objectType) {
 case 0:
 string = "None";
 break;
 case 1:
 string = "Player";
 break;
 case 2:
 string = "Zombie";
 break;
 case 3:
 string = "Vehicle";
 break;
 case 4:
 string = "NetObject";
 }

 return this->objectType == 4
 ? "\n\tMovingObject [type=" + string + "(" + this->objectType +
 ") | id=" + this->objectId + " | position=(" +
 this->squareX + ", " + this->squareY + ", " + this->squareZ +
 ") ]"
 : "\n\tMovingObject [type=" + string + "(" + this->objectType +
 ") | id=" + this->objectId + "]";
 }
}
} // namespace hit
} // namespace packets
} // namespace network
} // namespace zombie
