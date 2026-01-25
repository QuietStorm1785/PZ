// UdpLogger.h
// Merged from Java source, including all inner classes as nested C++ classes.
#pragma once

#include <string>
#include <vector>
#include <memory>

namespace zombie {
namespace network {

class UdpLogger {
public:
    UdpLogger();
    ~UdpLogger();

    // Example API (to be filled in with actual ported methods)
    void log(const std::string& message);
    const std::vector<std::string>& getLogs() const;

    // Nested classes (merged from Java inner classes)
    // ...add as needed from Java source...

private:
    std::vector<std::string> logs;
};

} // namespace network
} // namespace zombie
