#include <string>
#include "zombie\network\packets/PlayerVariables.h"

namespace zombie {
namespace network {
namespace packets {

public PlayerVariables::PlayerVariables() {
    // TODO: Implement PlayerVariables
    return nullptr;
}

void PlayerVariables::set(IsoPlayer var1) {
    // TODO: Implement set
}

void PlayerVariables::apply(IsoPlayer var1) {
    // TODO: Implement apply
}

void PlayerVariables::parse(ByteBuffer var1, UdpConnection var2) {
    // TODO: Implement parse
}

void PlayerVariables::write(ByteBufferWriter var1) {
    // TODO: Implement write
}

int PlayerVariables::getPacketSizeBytes() {
    // TODO: Implement getPacketSizeBytes
    return 0;
}

std::string PlayerVariables::getDescription() {
    // TODO: Implement getDescription
    return "";
}

void PlayerVariables::copy(PlayerVariables var1) {
    // TODO: Implement copy
}

} // namespace packets
} // namespace network
} // namespace zombie
