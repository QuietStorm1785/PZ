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


class AttachedWeaponDefinitions {
public:
   static const std::vector<AttachedWeaponDefinition> possibilities = std::make_unique<std::vector<>>();
   static const std::vector<AttachedWeaponDefinition> definitions = std::make_unique<std::vector<>>();

   private AttachedWeaponDefinitions$L_addRandomAttachedWeapon() {
   }
}
} // namespace AttachedItems
} // namespace characters
} // namespace zombie
