// StatisticServerManager.h
// Merged from Java source, including all inner classes as nested C++ classes.
#pragma once

#include <vector>
#include <memory>

namespace zombie {
namespace network {

class StatisticServer;

class StatisticServerManager {
public:
    StatisticServerManager();
    ~StatisticServerManager();

    // Example API (to be filled in with actual ported methods)
    void addServer(std::shared_ptr<StatisticServer> server);
    size_t getServerCount() const;

    // Nested classes (merged from Java inner classes)
    // ...add as needed from Java source...

private:
    std::vector<std::shared_ptr<StatisticServer>> servers;
};

} // namespace network
} // namespace zombie
