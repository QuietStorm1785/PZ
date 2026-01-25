// UdpSender.h
// Merged from Java source, including all inner classes as nested C++ classes.
#pragma once

#include <cstdint>
#include <vector>
#include <string>

namespace zombie {
namespace network {

class UdpSender {
public:
    UdpSender();
    ~UdpSender();

    // Example API (to be filled in with actual ported methods)
    void send(const std::vector<uint8_t>& data, const std::string& address, uint16_t port);
    std::vector<std::string> getSentMessages() const;

    // Nested classes (merged from Java inner classes)
    // ...add as needed from Java source...

private:
    std::vector<std::string> sentMessages;
};

} // namespace network
} // namespace zombie
