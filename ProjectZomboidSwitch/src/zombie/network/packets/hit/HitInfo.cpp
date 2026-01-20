#include <string>
#include "zombie\network\packets\hit/HitInfo.h"

namespace zombie {
namespace network {
namespace packets {
namespace hit {

public HitInfo::HitInfo() {
    // TODO: Implement HitInfo
    return nullptr;
}

HitInfo HitInfo::init(IsoMovingObject var1, float var2, float var3, float var4, float var5, float var6) {
    // TODO: Implement init
    return nullptr;
}

HitInfo HitInfo::init(IsoWindow var1, float var2, float var3) {
    // TODO: Implement init
    return nullptr;
}

IsoMovingObject HitInfo::getObject() {
    // TODO: Implement getObject
    return nullptr;
}

void HitInfo::parse(ByteBuffer var1, UdpConnection var2) {
    // TODO: Implement parse
}

void HitInfo::write(ByteBufferWriter var1) {
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
