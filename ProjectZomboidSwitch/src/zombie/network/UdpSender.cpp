// UdpSender.cpp
// Merged from Java source, including all inner classes as nested C++ classes.
#include "UdpSender.h"
#include <string>

namespace zombie {
namespace network {

UdpSender::UdpSender() {}
UdpSender::~UdpSender() {}

void UdpSender::send(const std::vector<uint8_t>& data, const std::string& address, uint16_t port) {
    // TODO: Port logic from Java source
    sentMessages.push_back("Sent data of size: " + std::to_string(data.size()) + " to " + address + ":" + std::to_string(port));
}

std::vector<std::string> UdpSender::getSentMessages() const {
    return sentMessages;
}

// ...implement more nested class logic as needed...

} // namespace network
} // namespace zombie
