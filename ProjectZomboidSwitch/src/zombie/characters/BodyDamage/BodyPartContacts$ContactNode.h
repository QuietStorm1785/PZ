#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace characters {
namespace BodyDamage {

class BodyPartContacts {
public:
    BodyPartType bodyPart;
    int depth = -1;
   BodyPartContacts$ContactNode parent;
   BodyPartContacts$ContactNode[] children;
   BodyPartContacts$ContactNode[] allContacts;
    BodyPartType bodyPartParent;
   BodyPartType[] bodyPartChildren;
   BodyPartType[] bodyPartAllContacts;
    bool initialised = false;

   public BodyPartContacts$ContactNode(BodyPartType var1) {
      this.bodyPart = var1;
   }
}
} // namespace BodyDamage
} // namespace characters
} // namespace zombie
