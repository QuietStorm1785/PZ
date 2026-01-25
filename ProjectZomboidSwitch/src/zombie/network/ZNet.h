// ZNet.h
// Merged from Java source, including all inner classes as nested C++ classes.
#pragma once

#include <string>
#include <vector>
#include <memory>

namespace zombie {
namespace network {

class ZNet {
public:
    ZNet();
    ~ZNet();

    // Example API (to be filled in with actual ported methods)
    void initialize();
    void shutdown();
    bool isInitialized() const;

    // Nested classes (merged from Java inner classes)
    // ...add as needed from Java source...

private:
    bool initialized;
};

} // namespace network
} // namespace zombie
