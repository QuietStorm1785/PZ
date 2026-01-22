#pragma once
#include <list>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/scripting/objects/Fixing/FixerSkill.h"
#include <algorithm>

namespace zombie {
namespace scripting {
namespace objects {


class Fixing {
public:
    std::string fixerName = nullptr;
   private std::list<FixerSkill> skills = nullptr;
    int numberOfUse = 1;

   public Fixing$Fixer(std::string var1, std::list<FixerSkill> var2, int var3) {
      this.fixerName = var1;
      this.skills = var2;
      this.numberOfUse = var3;
   }

    std::string getFixerName() {
      return this.fixerName;
   }

   public std::list<FixerSkill> getFixerSkills() {
      return this.skills;
   }

    int getNumberOfUse() {
      return this.numberOfUse;
   }
}
} // namespace objects
} // namespace scripting
} // namespace zombie
