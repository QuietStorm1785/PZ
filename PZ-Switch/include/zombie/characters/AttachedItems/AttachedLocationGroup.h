#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "java/lang/exceptions.h"

namespace zombie {
namespace characters {
namespace AttachedItems {

// Forward declaration
class AttachedLocation;

// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class AttachedLocationGroup {
private:
 std::vector<std::shared_ptr<AttachedLocation>> locations;

public:
 const std::string id;

 AttachedLocationGroup(const std::string &_id);

 std::shared_ptr<AttachedLocation> getLocation(const std::string &locationId);

 std::shared_ptr<AttachedLocation> getOrCreateLocation(const std::string &locationId);

 std::shared_ptr<AttachedLocation> getLocationByIndex(int index);

 int size() const;

 int indexOf(const std::string &locationId);

 void checkValid(const std::string &locationId);
};
} // namespace AttachedItems
} // namespace characters
} // namespace zombie
