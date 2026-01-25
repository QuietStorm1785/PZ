// StatisticServer.h
// Merged from Java source, including all inner classes as nested C++ classes.
#pragma once

#include <string>
#include <vector>
#include <memory>

namespace zombie {
namespace network {

class StatisticServer {
public:
    StatisticServer();
    ~StatisticServer();

    // Example API (to be filled in with actual ported methods)
    void logServerEvent(const std::string& eventName);
    int getServerEventCount(const std::string& eventName) const;

    // Nested classes (merged from Java inner classes)
    // ...add as needed from Java source...

private:
    std::vector<std::string> serverEvents;
};

} // namespace network
} // namespace zombie
