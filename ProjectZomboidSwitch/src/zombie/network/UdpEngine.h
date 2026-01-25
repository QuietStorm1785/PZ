// UdpEngine.h
// Merged from Java source, including all inner classes as nested C++ classes.
#pragma once

#include <string>
#include <vector>
#include <memory>
#include <cstdint>

namespace zombie {
namespace network {

class UdpEngine {
public:
    UdpEngine();
    ~UdpEngine();

    // Example API (to be filled in with actual ported methods)
    void start(uint16_t port);
    void stop();
    bool isRunning() const;

    // Nested classes (merged from Java inner classes)
    // ...add as needed from Java source...

private:
    uint16_t listenPort;
    bool running;
};

} // namespace network
} // namespace zombie
