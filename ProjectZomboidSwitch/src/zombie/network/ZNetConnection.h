// ZNetConnection.h
// Merged from Java source, including all inner classes as nested C++ classes.
#pragma once

#include <string>
#include <vector>
#include <memory>
#include <cstdint>

namespace zombie {
namespace network {

class ZNetConnection {
public:
    ZNetConnection();
    ~ZNetConnection();

    // Example API (to be filled in with actual ported methods)
    void connect(const std::string& address, uint16_t port);
    void disconnect();
    bool isConnected() const;

    // Nested classes (merged from Java inner classes)
    // ...add as needed from Java source...

private:
    std::string remoteAddress;
    uint16_t remotePort;
    bool connected;
};

} // namespace network
} // namespace zombie
