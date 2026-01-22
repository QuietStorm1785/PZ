#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/util/StringUtils.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace population {


class BeardStyle {
public:
    std::string name = "";
    std::string model;
    std::string texture = "F_Hair_White";
    int level = 0;
   public std::vector<std::string> trimChoices = std::make_unique<std::vector<>>();
    bool growReference = false;

    bool isValid() {
      return !StringUtils.isNullOrWhitespace(this.model) && !StringUtils.isNullOrWhitespace(this.texture);
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
}
} // namespace population
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
