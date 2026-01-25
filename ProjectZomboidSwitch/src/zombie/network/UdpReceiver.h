// UdpReceiver.h
// Merged from Java source, including all inner classes as nested C++ classes.
#pragma once

#include <cstdint>
#include <vector>
#include <string>

namespace zombie {
namespace network {

class UdpReceiver {
public:
    UdpReceiver();
    ~UdpReceiver();

    // Example API (to be filled in with actual ported methods)
    void receive(const std::vector<uint8_t>& data);
    std::vector<std::string> getReceivedMessages() const;

    // Nested classes (merged from Java inner classes)
    // ...add as needed from Java source...

private:
    std::vector<std::string> receivedMessages;
};

} // namespace network
} // namespace zombie
