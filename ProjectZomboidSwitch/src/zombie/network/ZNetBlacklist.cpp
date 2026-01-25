// ZNetBlacklist.cpp
// Merged from Java source, including all inner classes as nested C++ classes.
#include "ZNetBlacklist.h"
#include <algorithm>

namespace zombie {
namespace network {

ZNetBlacklist::ZNetBlacklist() {}
ZNetBlacklist::~ZNetBlacklist() {}

void ZNetBlacklist::add(const std::string& entry) {
    if (std::find(blacklist.begin(), blacklist.end(), entry) == blacklist.end()) {
        blacklist.push_back(entry);
    }
}

void ZNetBlacklist::remove(const std::string& entry) {
    auto it = std::remove(blacklist.begin(), blacklist.end(), entry);
    if (it != blacklist.end()) {
        blacklist.erase(it, blacklist.end());
    }
}

bool ZNetBlacklist::isBlacklisted(const std::string& entry) const {
    return std::find(blacklist.begin(), blacklist.end(), entry) != blacklist.end();
}

// ...implement more nested class logic as needed...

} // namespace network
} // namespace zombie
