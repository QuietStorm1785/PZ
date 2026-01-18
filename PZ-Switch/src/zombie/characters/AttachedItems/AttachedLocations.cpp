#include "zombie/characters/AttachedItems/AttachedLocations.h"
#include "zombie/characters/AttachedItems/AttachedLocationGroup.h"

namespace zombie {
namespace characters {
namespace AttachedItems {

std::vector<std::shared_ptr<AttachedLocationGroup>> AttachedLocations::groups;

std::shared_ptr<AttachedLocationGroup> AttachedLocations::getGroup(const std::string &id) {
 for (const auto& group : groups) {
 if (group && group->id == id) {
 return group;
 }
 }
 
 auto newGroup = std::make_shared<AttachedLocationGroup>(id);
 groups.push_back(newGroup);
 return newGroup;
}

void AttachedLocations::Reset() {
 groups.clear();
}

} // namespace AttachedItems
} // namespace characters
} // namespace zombie
