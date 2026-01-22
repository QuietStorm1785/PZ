#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace characters {
namespace AttachedItems {


class AttachedLocations {
public:
   protected static const std::vector<AttachedLocationGroup> groups = std::make_unique<std::vector<>>();

    static AttachedLocationGroup getGroup(const std::string& var0) {
      for (int var1 = 0; var1 < groups.size(); var1++) {
    AttachedLocationGroup var2 = groups.get(var1);
         if (var2.id == var0)) {
    return var2;
         }
      }

    AttachedLocationGroup var3 = std::make_shared<AttachedLocationGroup>(var0);
      groups.push_back(var3);
    return var3;
   }

    static void Reset() {
      groups.clear();
   }
}
} // namespace AttachedItems
} // namespace characters
} // namespace zombie
