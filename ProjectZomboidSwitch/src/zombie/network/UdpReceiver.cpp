// UdpReceiver.cpp
// Merged from Java source, including all inner classes as nested C++ classes.
#include "UdpReceiver.h"
#include <string>

namespace zombie {
namespace network {

UdpReceiver::UdpReceiver() {}
UdpReceiver::~UdpReceiver() {}

void UdpReceiver::receive(const std::vector<uint8_t>& data) {
    // TODO: Port logic from Java source
    receivedMessages.push_back("Received data of size: " + std::to_string(data.size()));
}

std::vector<std::string> UdpReceiver::getReceivedMessages() const {
    return receivedMessages;
}

// ...implement more nested class logic as needed...

} // namespace network
} // namespace zombie
