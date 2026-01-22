#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace scripting {
namespace objects {

class Fixing {
public:
    std::string skillName = nullptr;
    int skillLvl = 0;

   public Fixing$FixerSkill(std::string var1, int var2) {
      this.skillName = var1;
      this.skillLvl = var2;
   }

    std::string getSkillName() {
      return this.skillName;
   }

    int getSkillLevel() {
      return this.skillLvl;
   }
}
} // namespace objects
} // namespace scripting
} // namespace zombie
