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


class BodyLocations {
public:
   protected static const std::vector<BodyLocationGroup> groups = std::make_unique<std::vector<>>();

    static BodyLocationGroup getGroup(const std::string& var0) {
      for (int var1 = 0; var1 < groups.size(); var1++) {
    BodyLocationGroup var2 = groups.get(var1);
         if (var2.id == var0)) {
    return var2;
         }
      }

    BodyLocationGroup var3 = std::make_shared<BodyLocationGroup>(var0);
      groups.push_back(var3);
    return var3;
   }

    static void Reset() {
      groups.clear();
   }
}
} // namespace WornItems
} // namespace characters
} // namespace zombie
