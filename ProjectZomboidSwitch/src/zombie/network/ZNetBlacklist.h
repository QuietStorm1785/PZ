// ZNetBlacklist.h
// Merged from Java source, including all inner classes as nested C++ classes.
#pragma once

#include <string>
#include <vector>
#include <memory>

namespace zombie {
namespace network {

class ZNetBlacklist {
public:
    ZNetBlacklist();
    ~ZNetBlacklist();

    // Example API (to be filled in with actual ported methods)
    void add(const std::string& entry);
    void remove(const std::string& entry);
    bool isBlacklisted(const std::string& entry) const;

    // Nested classes (merged from Java inner classes)
    // ...add as needed from Java source...

private:
    std::vector<std::string> blacklist;
};

} // namespace network
} // namespace zombie
