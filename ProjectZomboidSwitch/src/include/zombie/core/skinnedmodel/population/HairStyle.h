#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/skinnedmodel/population/HairStyle/Alternate.h"
#include "zombie/util/StringUtils.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace population {


class HairStyle {
public:
    std::string name = "";
    std::string model;
    std::string texture = "F_Hair_White";
   public const std::vector<Alternate> alternate = std::make_unique<std::vector<>>();
    int level = 0;
   public const std::vector<std::string> trimChoices = std::make_unique<std::vector<>>();
    bool growReference = false;
    bool attachedHair = false;
    bool noChoose = false;

    bool isValid() {
      return !StringUtils.isNullOrWhitespace(this.model) && !StringUtils.isNullOrWhitespace(this.texture);
   }

    std::string getAlternate(const std::string& var1) {
      for (int var2 = 0; var2 < this.alternate.size(); var2++) {
    Alternate var3 = this.alternate.get(var2);
         if (var1.equalsIgnoreCase(var3.category)) {
            return var3.style;
         }
      }

      return this.name;
   }

    int getLevel() {
      return this.level;
   }

    std::string getName() {
      return this.name;
   }

   public std::vector<std::string> getTrimChoices() {
      return this.trimChoices;
   }

    bool isAttachedHair() {
      return this.attachedHair;
   }

    bool isGrowReference() {
      return this.growReference;
   }

    bool isNoChoose() {
      return this.noChoose;
   }
}
} // namespace population
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
