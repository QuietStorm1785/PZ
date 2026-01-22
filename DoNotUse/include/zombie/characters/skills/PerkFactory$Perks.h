#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/skills/PerkFactory/Perk.h"

namespace zombie {
namespace characters {
namespace skills {


class PerkFactory {
public:
    static const Perk None = std::make_shared<Perk>("None");
    static const Perk Agility = std::make_shared<Perk>("Agility");
    static const Perk Cooking = std::make_shared<Perk>("Cooking");
    static const Perk Melee = std::make_shared<Perk>("Melee");
    static const Perk Crafting = std::make_shared<Perk>("Crafting");
    static const Perk Fitness = std::make_shared<Perk>("Fitness");
    static const Perk Strength = std::make_shared<Perk>("Strength");
    static const Perk Blunt = std::make_shared<Perk>("Blunt");
    static const Perk Axe = std::make_shared<Perk>("Axe");
    static const Perk Sprinting = std::make_shared<Perk>("Sprinting");
    static const Perk Lightfoot = std::make_shared<Perk>("Lightfoot");
    static const Perk Nimble = std::make_shared<Perk>("Nimble");
    static const Perk Sneak = std::make_shared<Perk>("Sneak");
    static const Perk Woodwork = std::make_shared<Perk>("Woodwork");
    static const Perk Aiming = std::make_shared<Perk>("Aiming");
    static const Perk Reloading = std::make_shared<Perk>("Reloading");
    static const Perk Farming = std::make_shared<Perk>("Farming");
    static const Perk Survivalist = std::make_shared<Perk>("Survivalist");
    static const Perk Fishing = std::make_shared<Perk>("Fishing");
    static const Perk Trapping = std::make_shared<Perk>("Trapping");
    static const Perk Passiv = std::make_shared<Perk>("Passiv");
    static const Perk Firearm = std::make_shared<Perk>("Firearm");
    static const Perk PlantScavenging = std::make_shared<Perk>("PlantScavenging");
    static const Perk Doctor = std::make_shared<Perk>("Doctor");
    static const Perk Electricity = std::make_shared<Perk>("Electricity");
    static const Perk Blacksmith = std::make_shared<Perk>("Blacksmith");
    static const Perk MetalWelding = std::make_shared<Perk>("MetalWelding");
    static const Perk Melting = std::make_shared<Perk>("Melting");
    static const Perk Mechanics = std::make_shared<Perk>("Mechanics");
    static const Perk Spear = std::make_shared<Perk>("Spear");
    static const Perk Maintenance = std::make_shared<Perk>("Maintenance");
    static const Perk SmallBlade = std::make_shared<Perk>("SmallBlade");
    static const Perk LongBlade = std::make_shared<Perk>("LongBlade");
    static const Perk SmallBlunt = std::make_shared<Perk>("SmallBlunt");
    static const Perk Combat = std::make_shared<Perk>("Combat");
    static const Perk Tailoring = std::make_shared<Perk>("Tailoring");
    static const Perk MAX = std::make_shared<Perk>("MAX");

    static int getMaxIndex() {
      return MAX.index();
   }

    static Perk fromIndex(int var0) {
      return var0 >= 0 && var0 <= PerkFactory.NextPerkID ? PerkFactory.PerkByIndex[var0] : nullptr;
   }

    static Perk FromString(const std::string& var0) {
      return PerkFactory.PerkById.getOrDefault(var0, MAX);
   }
}
} // namespace skills
} // namespace characters
} // namespace zombie
