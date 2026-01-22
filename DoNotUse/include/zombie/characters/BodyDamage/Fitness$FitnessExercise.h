#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/j2se/KahluaTableImpl.h"
#include <algorithm>

namespace zombie {
namespace characters {
namespace BodyDamage {


class Fitness {
public:
    std::string type = nullptr;
    Metabolics metabolics = nullptr;
   std::vector<std::string> stiffnessInc = nullptr;
    float xpModifier = 1.0F;

   public Fitness$FitnessExercise(KahluaTableImpl var1) {
      this.type = var1.rawgetStr("type");
      this.metabolics = (Metabolics)var1.rawget("metabolics");
      this.stiffnessInc = new std::vector<>(Arrays.asList(var1.rawgetStr("stiffness").split(",")));
      if (var1.rawgetFloat("xpMod") > 0.0F) {
         this.xpModifier = var1.rawgetFloat("xpMod");
      }
   }
}
} // namespace BodyDamage
} // namespace characters
} // namespace zombie
