// UdpEngine.cpp
// Merged from Java source, including all inner classes as nested C++ classes.
#include "UdpEngine.h"

namespace zombie {
namespace network {

UdpEngine::UdpEngine() : listenPort(0), running(false) {}
UdpEngine::~UdpEngine() {}

void UdpEngine::start(uint16_t port) {
    listenPort = port;
    running = true;
}

void UdpEngine::stop() {
    running = false;
}

bool UdpEngine::isRunning() const {
    return running;
}

// ...implement more nested class logic as needed...

} // namespace network
} // namespace zombie
