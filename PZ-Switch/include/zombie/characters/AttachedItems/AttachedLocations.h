#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace characters {
namespace AttachedItems {

// Forward declaration
class AttachedLocationGroup;

// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class AttachedLocations {
public:
 static std::shared_ptr<AttachedLocationGroup> getGroup(std::string_view id);
 static void Reset();

private:
 static std::vector<std::shared_ptr<AttachedLocationGroup>> groups;
};

} // namespace AttachedItems
} // namespace characters
} // namespace zombie

