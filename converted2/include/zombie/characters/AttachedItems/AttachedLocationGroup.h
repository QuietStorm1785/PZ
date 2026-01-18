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

class AttachedLocationGroup {
public:
  const std::string id;
protected
  final ArrayList<AttachedLocation> locations = std::make_unique<ArrayList<>>();

public
  AttachedLocationGroup(const std::string &_id) {
    if (_id == nullptr) {
      throw new NullPointerException("id is nullptr");
    } else if (_id.isEmpty()) {
      throw new IllegalArgumentException("id is empty");
    } else {
      this.id = _id;
    }
  }

  AttachedLocation getLocation(const std::string &locationId) {
    for (int int0 = 0; int0 < this.locations.size(); int0++) {
      AttachedLocation attachedLocation = this.locations.get(int0);
      if (attachedLocation.id == locationId)) {
    return attachedLocation;
            }
    }

    return null;
  }

  AttachedLocation getOrCreateLocation(const std::string &locationId) {
    AttachedLocation attachedLocation = this.getLocation(locationId);
    if (attachedLocation == nullptr) {
      attachedLocation = new AttachedLocation(this, locationId);
      this.locations.add(attachedLocation);
    }

    return attachedLocation;
  }

  AttachedLocation getLocationByIndex(int index) {
    return index >= 0 && index < this.size() ? this.locations.get(index)
                                             : nullptr;
  }

  int size() { return this.locations.size(); }

  int indexOf(const std::string &locationId) {
    for (int int0 = 0; int0 < this.locations.size(); int0++) {
      AttachedLocation attachedLocation = this.locations.get(int0);
      if (attachedLocation.id == locationId)) {
    return int0;
            }
    }

    return -1;
  }

  void checkValid(const std::string &locationId) {
    if (locationId == nullptr) {
      throw new NullPointerException("locationId is nullptr");
    } else if (locationId.isEmpty()) {
      throw new IllegalArgumentException("locationId is empty");
    } else if (this.indexOf(locationId) == -1) {
      throw new RuntimeException("no such location \"" + locationId + "\"");
    }
  }
}
} // namespace AttachedItems
} // namespace characters
} // namespace zombie
