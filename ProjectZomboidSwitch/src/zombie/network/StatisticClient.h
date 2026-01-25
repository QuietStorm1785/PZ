// StatisticClient.h
// Merged from Java source, including all inner classes as nested C++ classes.
#pragma once

#include <string>
#include <vector>
#include <memory>

namespace zombie {
namespace network {

class StatisticClient {
public:
    StatisticClient();
    ~StatisticClient();

    // Example API (to be filled in with actual ported methods)
    void recordEvent(const std::string& eventName);
    int getEventCount(const std::string& eventName) const;

    // Nested classes (merged from Java inner classes)
    // ...add as needed from Java source...

private:
    std::vector<std::string> events;
};

} // namespace network
} // namespace zombie
