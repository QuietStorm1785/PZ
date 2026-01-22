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


class BodyLocationGroup {
public:
    const std::string id;
   protected const std::vector<BodyLocation> locations = std::make_unique<std::vector<>>();

    public BodyLocationGroup(const std::string& var1) {
      if (var1 == nullptr) {
         throw NullPointerException("id is nullptr");
      } else if (var1.empty()) {
         throw IllegalArgumentException("id is empty");
      } else {
         this.id = var1;
      }
   }

    BodyLocation getLocation(const std::string& var1) {
      for (int var2 = 0; var2 < this.locations.size(); var2++) {
    BodyLocation var3 = this.locations.get(var2);
         if (var3.isID(var1)) {
    return var3;
         }
      }

    return nullptr;
   }

    BodyLocation getLocationNotNull(const std::string& var1) {
    BodyLocation var2 = this.getLocation(var1);
      if (var2 == nullptr) {
         throw RuntimeException("unknown location \"" + var1 + "\"");
      } else {
    return var2;
      }
   }

    BodyLocation getOrCreateLocation(const std::string& var1) {
    BodyLocation var2 = this.getLocation(var1);
      if (var2 == nullptr) {
         var2 = std::make_shared<BodyLocation>(this, var1);
         this.locations.push_back(var2);
      }

    return var2;
   }

    BodyLocation getLocationByIndex(int var1) {
      return var1 >= 0 && var1 < this.size() ? this.locations.get(var1) : nullptr;
   }

    int size() {
      return this.locations.size();
   }

    void setExclusive(const std::string& var1, const std::string& var2) {
    BodyLocation var3 = this.getLocationNotNull(var1);
    BodyLocation var4 = this.getLocationNotNull(var2);
      var3.setExclusive(var2);
      var4.setExclusive(var1);
   }

    bool isExclusive(const std::string& var1, const std::string& var2) {
    BodyLocation var3 = this.getLocationNotNull(var1);
      this.checkValid(var2);
      return var3.exclusive.contains(var2);
   }

    void setHideModel(const std::string& var1, const std::string& var2) {
    BodyLocation var3 = this.getLocationNotNull(var1);
      this.checkValid(var2);
      var3.setHideModel(var2);
   }

    bool isHideModel(const std::string& var1, const std::string& var2) {
    BodyLocation var3 = this.getLocationNotNull(var1);
      this.checkValid(var2);
      return var3.isHideModel(var2);
   }

    int indexOf(const std::string& var1) {
      for (int var2 = 0; var2 < this.locations.size(); var2++) {
    BodyLocation var3 = this.locations.get(var2);
         if (var3.isID(var1)) {
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
         throw RuntimeException("unknown location \"" + var1 + "\"");
      }
   }

    void setMultiItem(const std::string& var1, bool var2) {
    BodyLocation var3 = this.getLocationNotNull(var1);
      var3.setMultiItem(var2);
   }

    bool isMultiItem(const std::string& var1) {
    BodyLocation var2 = this.getLocationNotNull(var1);
      return var2.isMultiItem();
   }

   public std::vector<BodyLocation> getAllLocations() {
      return this.locations;
   }
}
} // namespace WornItems
} // namespace characters
} // namespace zombie
