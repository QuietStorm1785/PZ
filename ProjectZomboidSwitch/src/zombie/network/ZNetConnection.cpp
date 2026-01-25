// ZNetConnection.cpp
// Merged from Java source, including all inner classes as nested C++ classes.
#include "ZNetConnection.h"

namespace zombie {
namespace network {

ZNetConnection::ZNetConnection() : remotePort(0), connected(false) {}
ZNetConnection::~ZNetConnection() {}

void ZNetConnection::connect(const std::string& address, uint16_t port) {
    remoteAddress = address;
    remotePort = port;
    connected = true;
}

void ZNetConnection::disconnect() {
    connected = false;
}

bool ZNetConnection::isConnected() const {
    return connected;
}

// ...implement more nested class logic as needed...

} // namespace network
} // namespace zombie
