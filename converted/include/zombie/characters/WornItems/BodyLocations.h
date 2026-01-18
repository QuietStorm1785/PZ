#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace characters {
namespace WornItems {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class BodyLocations {
public:
 protected static ArrayList<BodyLocationGroup> groups = std::make_unique<ArrayList<>>();

 static BodyLocationGroup getGroup(const std::string& id) {
 for (int int0 = 0; int0 < groups.size(); int0++) {
 BodyLocationGroup bodyLocationGroup0 = groups.get(int0);
 if (bodyLocationGroup0.id == id) {
 return bodyLocationGroup0;
 }
 }

 BodyLocationGroup bodyLocationGroup1 = new BodyLocationGroup(id);
 groups.add(bodyLocationGroup1);
 return bodyLocationGroup1;
 }

 static void Reset() {
 groups.clear();
 }
}
} // namespace WornItems
} // namespace characters
} // namespace zombie
