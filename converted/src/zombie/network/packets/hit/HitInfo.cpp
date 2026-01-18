#include "zombie/network/packets/hit/HitInfo.h"

namespace zombie {
namespace network {
namespace packets {
namespace hit {

public HitInfo::HitInfo() {
 // TODO: Implement HitInfo
 return nullptr;
}

HitInfo HitInfo::init(IsoMovingObject movingObject, float float3, float float4, float float0, float float1, float float2) {
 // TODO: Implement init
 return nullptr;
}

HitInfo HitInfo::init(IsoWindow windowx, float float0, float float1) {
 // TODO: Implement init
 return nullptr;
}

IsoMovingObject HitInfo::getObject() {
 // TODO: Implement getObject
 return nullptr;
}

void HitInfo::parse(ByteBuffer byteBuffer, UdpConnection udpConnection) {
 // TODO: Implement parse
}

void HitInfo::write(ByteBufferWriter byteBufferWriter) {
 // TODO: Implement write
}

int HitInfo::getPacketSizeBytes() {
 // TODO: Implement getPacketSizeBytes
 return 0;
}

std::string HitInfo::getDescription() {
 // TODO: Implement getDescription
 return "";
}

} // namespace hit
} // namespace packets
} // namespace network
} // namespace zombie
