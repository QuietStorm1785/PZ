#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace characters {
namespace AttachedItems {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class AttachedLocations {
public:
protected
  static final ArrayList<AttachedLocationGroup> groups =
      std::make_unique<ArrayList<>>();

  static AttachedLocationGroup getGroup(const std::string &id) {
    for (int int0 = 0; int0 < groups.size(); int0++) {
      AttachedLocationGroup attachedLocationGroup0 = groups.get(int0);
      if (attachedLocationGroup0.id == id)) {
    return attachedLocationGroup0;
            }
    }

    AttachedLocationGroup attachedLocationGroup1 =
        new AttachedLocationGroup(id);
    groups.add(attachedLocationGroup1);
    return attachedLocationGroup1;
  }

  static void Reset() { groups.clear(); }
}
} // namespace AttachedItems
} // namespace characters
} // namespace zombie
