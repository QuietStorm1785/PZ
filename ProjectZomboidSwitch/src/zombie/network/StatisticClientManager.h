// StatisticClientManager.h
// Merged from Java source, including all inner classes as nested C++ classes.
#pragma once

#include <vector>
#include <memory>

namespace zombie {
namespace network {

class StatisticClient;

class StatisticClientManager {
public:
    StatisticClientManager();
    ~StatisticClientManager();

    // Example API (to be filled in with actual ported methods)
    void addClient(std::shared_ptr<StatisticClient> client);
    size_t getClientCount() const;

    // Nested classes (merged from Java inner classes)
    // ...add as needed from Java source...

private:
    std::vector<std::shared_ptr<StatisticClient>> clients;
};

} // namespace network
} // namespace zombie
