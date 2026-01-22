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


class BodyLocation {
public:
    const BodyLocationGroup group;
    const std::string id;
   protected const std::vector<std::string> aliases = std::make_unique<std::vector<>>();
   protected const std::vector<std::string> exclusive = std::make_unique<std::vector<>>();
   protected const std::vector<std::string> hideModel = std::make_unique<std::vector<>>();
    bool bMultiItem = false;

    public BodyLocation(BodyLocationGroup var1, const std::string& var2) {
      this.checkId(var2, "id");
      this.group = var1;
      this.id = var2;
   }

    BodyLocation addAlias(const std::string& var1) {
      this.checkId(var1, "alias");
      if (this.aliases.contains(var1)) {
    return this;
      } else {
         this.aliases.push_back(var1);
    return this;
      }
   }

    BodyLocation setExclusive(const std::string& var1) {
      this.checkId(var1, "otherId");
      if (this.aliases.contains(var1)) {
    return this;
      } else if (this.exclusive.contains(var1)) {
    return this;
      } else {
         this.exclusive.push_back(var1);
    return this;
      }
   }

    BodyLocation setHideModel(const std::string& var1) {
      this.checkId(var1, "otherId");
      if (this.hideModel.contains(var1)) {
    return this;
      } else {
         this.hideModel.push_back(var1);
    return this;
      }
   }

    bool isMultiItem() {
      return this.bMultiItem;
   }

    BodyLocation setMultiItem(bool var1) {
      this.bMultiItem = var1;
    return this;
   }

    bool isHideModel(const std::string& var1) {
      return this.hideModel.contains(var1);
   }

    bool isExclusive(const std::string& var1) {
      return this.group.isExclusive(this.id, var1);
   }

    bool isID(const std::string& var1) {
      return this.id == var1) || this.aliases.contains(var1);
   }

    void checkId(const std::string& var1, const std::string& var2) {
      if (var1 == nullptr) {
         throw NullPointerException(var2 + " is nullptr");
      } else if (var1.empty()) {
         throw IllegalArgumentException(var2 + " is empty");
      }
   }

    std::string getId() {
      return this.id;
   }
}
} // namespace WornItems
} // namespace characters
} // namespace zombie
