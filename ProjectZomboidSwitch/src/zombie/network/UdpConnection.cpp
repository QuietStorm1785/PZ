// UdpConnection.cpp
// Merged from Java source, including all inner classes as nested C++ classes.
#include "UdpConnection.h"

namespace zombie {
namespace network {

UdpConnection::UdpConnection() : remotePort(0), connected(false) {}
UdpConnection::~UdpConnection() {}

void UdpConnection::connect(const std::string& address, uint16_t port) {
    remoteAddress = address;
    remotePort = port;
    connected = true;
}

void UdpConnection::disconnect() {
    connected = false;
}

bool UdpConnection::isConnected() const {
    return connected;
}

// ...implement more nested class logic as needed...

} // namespace network
} // namespace zombie
