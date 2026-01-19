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

// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class AttachedModelName {
public:
 std::string attachmentNameSelf;
 std::string attachmentNameParent;
 std::string modelName;
 float bloodLevel;
 std::vector<std::shared_ptr<AttachedModelName>> children;

 AttachedModelName(const AttachedModelName& other);
 
 AttachedModelName(std::string_view attachmentName,
 std::string_view _modelName, float _bloodLevel);
 
 AttachedModelName(std::string_view _attachmentNameSelf,
 std::string_view _attachmentNameParent,
 std::string_view _modelName, float _bloodLevel);

 void addChild(std::shared_ptr<AttachedModelName> child);
 int getChildCount() const;
 std::shared_ptr<AttachedModelName> getChildByIndex(int index) const;
};

} // namespace AttachedItems
} // namespace characters
} // namespace zombie
