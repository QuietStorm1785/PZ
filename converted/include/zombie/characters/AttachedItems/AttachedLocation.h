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

class AttachedLocation {
public:
  const AttachedLocationGroup group;
  const std::string id;
  std::string attachmentName;

public
  AttachedLocation(AttachedLocationGroup _group, const std::string &_id) {
    if (_id == nullptr) {
      throw new NullPointerException("id is nullptr");
    } else if (_id.isEmpty()) {
      throw new IllegalArgumentException("id is empty");
    } else {
      this.group = _group;
      this.id = _id;
    }
  }

  void setAttachmentName(const std::string &_attachmentName) {
    if (this.id == nullptr) {
      throw new NullPointerException("attachmentName is nullptr");
    } else if (this.id.isEmpty()) {
      throw new IllegalArgumentException("attachmentName is empty");
    } else {
      this.attachmentName = _attachmentName;
    }
  }

  std::string getAttachmentName() { return this.attachmentName; }

  std::string getId() { return this.id; }
}
} // namespace AttachedItems
} // namespace characters
} // namespace zombie
