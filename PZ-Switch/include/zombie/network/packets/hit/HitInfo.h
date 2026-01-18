#pragma once
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/iso/IsoMovingObject.h"
#include "zombie/iso/objects/IsoWindow.h"
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

class HitInfo {
public:
 MovingObject object;
 NetObject window;
 float x;
 float y;
 float z;
 float dot;
 float distSq;
 int chance = 0;

public
 HitInfo() {
 this->object = std::make_unique<MovingObject>();
 this->window = std::make_unique<NetObject>();
 }

 HitInfo init(IsoMovingObject movingObject, float float3, float float4,
 float float0, float float1, float float2) {
 this->object = std::make_unique<MovingObject>();
 this->window = std::make_unique<NetObject>();
 this->object.setMovingObject(movingObject);
 this->window.setObject(nullptr);
 this->x = float0;
 this->y = float1;
 this->z = float2;
 this->dot = float3;
 this->distSq = float4;
 return this;
 }

 HitInfo init(IsoWindow windowx, float float0, float float1) {
 this->object = std::make_unique<MovingObject>();
 this->window = std::make_unique<NetObject>();
 this->object.setMovingObject(nullptr);
 this->window.setObject(windowx);
 this->z = windowx.getZ();
 this->dot = float0;
 this->distSq = float1;
 return this;
 }

 IsoMovingObject getObject() { return this->object.getMovingObject(); }

 void parse(ByteBuffer byteBuffer, UdpConnection udpConnection) {
 this->object.parse(byteBuffer, udpConnection);
 this->window.parse(byteBuffer, udpConnection);
 this->x = byteBuffer.getFloat();
 this->y = byteBuffer.getFloat();
 this->z = byteBuffer.getFloat();
 this->dot = byteBuffer.getFloat();
 this->distSq = byteBuffer.getFloat();
 this->chance = byteBuffer.getInt();
 }

 void write(ByteBufferWriter byteBufferWriter) {
 this->object.write(byteBufferWriter);
 this->window.write(byteBufferWriter);
 byteBufferWriter.putFloat(this->x);
 byteBufferWriter.putFloat(this->y);
 byteBufferWriter.putFloat(this->z);
 byteBufferWriter.putFloat(this->dot);
 byteBufferWriter.putFloat(this->distSq);
 byteBufferWriter.putInt(this->chance);
 }

 int getPacketSizeBytes() {
 return 24 + this->object.getPacketSizeBytes() +
 this->window.getPacketSizeBytes();
 }

 std::string getDescription() {
 return "\n\tHitInfo [ x=" + this->x + " y=" + this->y + " z=" + this->z +
 " dot=" + this->dot + " distSq=" + this->distSq +
 " chance=" + this->chance +
 "\n\t Object: " + this->object.getDescription() +
 "\n\t Window: " + this->window.getDescription() + " ]";
 }
}
} // namespace hit
} // namespace packets
} // namespace network
} // namespace zombie
