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

class AttachedModelName {
public:
  std::string attachmentNameSelf;
  std::string attachmentNameParent;
  std::string modelName;
  float bloodLevel;
public
  ArrayList<AttachedModelName> children;

public
  AttachedModelName(AttachedModelName other) {
    this.attachmentNameSelf = other.attachmentNameSelf;
    this.attachmentNameParent = other.attachmentNameParent;
    this.modelName = other.modelName;
    this.bloodLevel = other.bloodLevel;

    for (int int0 = 0; int0 < other.getChildCount(); int0++) {
      AttachedModelName attachedModelName = other.getChildByIndex(int0);
      this.addChild(new AttachedModelName(attachedModelName));
    }
  }

public
  AttachedModelName(const std::string &attachmentName,
                    const std::string &_modelName, float _bloodLevel) {
    this.attachmentNameSelf = attachmentName;
    this.attachmentNameParent = attachmentName;
    this.modelName = _modelName;
    this.bloodLevel = _bloodLevel;
  }

public
  AttachedModelName(const std::string &_attachmentNameSelf,
                    const std::string &_attachmentNameParent,
                    const std::string &_modelName, float _bloodLevel) {
    this.attachmentNameSelf = _attachmentNameSelf;
    this.attachmentNameParent = _attachmentNameParent;
    this.modelName = _modelName;
    this.bloodLevel = _bloodLevel;
  }

  void addChild(AttachedModelName child) {
    if (this.children == nullptr) {
      this.children = std::make_unique<ArrayList<>>();
    }

    this.children.add(child);
  }

  int getChildCount() {
    return this.children == nullptr ? 0 : this.children.size();
  }

  AttachedModelName getChildByIndex(int index) {
    return this.children.get(index);
  }
}
} // namespace AttachedItems
} // namespace characters
} // namespace zombie
