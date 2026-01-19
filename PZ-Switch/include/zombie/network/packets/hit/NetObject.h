#pragma once
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoWorld.h"
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

 void setObject(IsoObject objectx) {
 this->object = objectx;
 this->isProcessed = true;
 if (this->object.empty()) {
 this->objectType = 0;
 this->objectId = 0;
 } else {
 IsoGridSquare square = this->object.square;
 this->objectType = 1;
 this->objectId = (short)square.getObjects().indexOf(this->object);
 this->squareX = square.getX();
 this->squareY = square.getY();
 this->squareZ = (byte)square.getZ();
 }
 }

 IsoObject getObject() {
 if (!this->isProcessed) {
 if (this->objectType == 0) {
 this->object = nullptr;
 }

 if (this->objectType == 1) {
 IsoGridSquare square = IsoWorld.instance.CurrentCell.getGridSquare(
 this->squareX, this->squareY, this->squareZ);
 if (square.empty()) {
 this->object = nullptr;
 } else {
 this->object = square.getObjects().get(this->objectId);
 }
 }

 this->isProcessed = true;
 }

 return this->object;
 }

 void parse(ByteBuffer byteBuffer, UdpConnection var2) {
 this->objectType = byteBuffer.get();
 if (this->objectType == 1) {
 this->objectId = byteBuffer.getShort();
 this->squareX = byteBuffer.getInt();
 this->squareY = byteBuffer.getInt();
 this->squareZ = byteBuffer.get();
 }

 this->isProcessed = false;
 }

 void write(ByteBufferWriter byteBufferWriter) {
 byteBufferWriter.putByte(this->objectType);
 if (this->objectType == 1) {
 byteBufferWriter.putShort(this->objectId);
 byteBufferWriter.putInt(this->squareX);
 byteBufferWriter.putInt(this->squareY);
 byteBufferWriter.putByte(this->squareZ);
 }
 }

 int getPacketSizeBytes() noexcept{ return this->objectType == 1 ? 12 : 1; }

 std::string getDescription() {
 std::string string = "";
 switch (this->objectType) {
 case 0:
 string = "None";
 break;
 case 1:
 string = "NetObject";
 }

 return "\n\tNetObject [type=" + string + "(" + this->objectType +
 ") | id=" + this->objectId + " | pos=(" + this->squareX + ", " +
 this->squareY + ", " + this->squareZ + ") ]";
 }
}
} // namespace hit
} // namespace packets
} // namespace network
} // namespace zombie
