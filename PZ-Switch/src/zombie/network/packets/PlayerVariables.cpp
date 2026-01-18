#include "zombie/network/packets/PlayerVariables.h"

namespace zombie {
namespace network {
namespace packets {

public
PlayerVariables::PlayerVariables() {
 // TODO: Implement PlayerVariables
 return nullptr;
}

void PlayerVariables::set(IsoPlayer player) {
 // TODO: Implement set
}

void PlayerVariables::apply(IsoPlayer player) {
 // TODO: Implement apply
}

void PlayerVariables::parse(ByteBuffer byteBuffer, UdpConnection var2) {
 // TODO: Implement parse
}

void PlayerVariables::write(ByteBufferWriter byteBufferWriter) {
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

void PlayerVariables::copy(PlayerVariables playerVariables0) {
 // TODO: Implement copy
}

void PlayerVariables::set(
 IsoPlayer player,
 PlayerVariables.NetworkPlayerVariableIDs networkPlayerVariableIDs) {
 // TODO: Implement set
}

} // namespace packets
} // namespace network
} // namespace zombie
