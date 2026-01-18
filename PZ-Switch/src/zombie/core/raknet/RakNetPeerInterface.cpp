#include "zombie/core/raknet/RakNetPeerInterface.h"

namespace zombie {
namespace core {
namespace raknet {

void RakNetPeerInterface::init() {
 // TODO: Implement init
}

int RakNetPeerInterface::Startup(int maxConnections) {
 // TODO: Implement Startup
 return 0;
}

bool RakNetPeerInterface::Receive(ByteBuffer buffer) {
 // TODO: Implement Receive
 return false;
}

int RakNetPeerInterface::Send(ByteBuffer data, int PacketPriority,
 int PacketReliability, uint8_t orderingChannel,
 long guid, bool broadcast) {
 // TODO: Implement Send
 return 0;
}

int RakNetPeerInterface::SendRaw(ByteBuffer data, int PacketPriority,
 int PacketReliability, uint8_t orderingChannel,
 long guid, bool broadcast) {
 // TODO: Implement SendRaw
 return 0;
}

void RakNetPeerInterface::connectionStateChangedCallback(
 const std::string &string0, const std::string &string1) {
 // TODO: Implement connectionStateChangedCallback
}

} // namespace raknet
} // namespace core
} // namespace zombie
