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


class AttachedLocationGroup {
public:
    const std::string id;
   protected const std::vector<AttachedLocation> locations = std::make_unique<std::vector<>>();

    public AttachedLocationGroup(const std::string& var1) {
      if (var1 == nullptr) {
         throw NullPointerException("id is nullptr");
      } else if (var1.empty()) {
         throw IllegalArgumentException("id is empty");
      } else {
         this.id = var1;
      }
   }

    AttachedLocation getLocation(const std::string& var1) {
      for (int var2 = 0; var2 < this.locations.size(); var2++) {
    AttachedLocation var3 = this.locations.get(var2);
         if (var3.id == var1)) {
    return var3;
         }
      }

    return nullptr;
   }

    AttachedLocation getOrCreateLocation(const std::string& var1) {
    AttachedLocation var2 = this.getLocation(var1);
      if (var2 == nullptr) {
         var2 = std::make_shared<AttachedLocation>(this, var1);
         this.locations.push_back(var2);
      }

    return var2;
   }

    AttachedLocation getLocationByIndex(int var1) {
      return var1 >= 0 && var1 < this.size() ? this.locations.get(var1) : nullptr;
   }

    int size() {
      return this.locations.size();
   }

    int indexOf(const std::string& var1) {
      for (int var2 = 0; var2 < this.locations.size(); var2++) {
    AttachedLocation var3 = this.locations.get(var2);
         if (var3.id == var1)) {
    return var2;
         }
      }

      return -1;
   }

    void checkValid(const std::string& var1) {
      if (var1 == nullptr) {
         throw NullPointerException("locationId is nullptr");
      } else if (var1.empty()) {
         throw IllegalArgumentException("locationId is empty");
      } else if (this.indexOf(var1) == -1) {
         throw RuntimeException("no such location \"" + var1 + "\"");
      }
   }
}
} // namespace AttachedItems
} // namespace characters
} // namespace zombie
