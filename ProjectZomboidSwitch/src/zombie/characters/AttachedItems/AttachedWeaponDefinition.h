#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characterTextures/BloodBodyPartType.h"

namespace zombie {
namespace characters {
namespace AttachedItems {


class AttachedWeaponDefinition {
public:
    std::string id;
    int chance;
   public const std::vector<std::string> outfit = std::make_unique<std::vector<>>();
   public const std::vector<std::string> weaponLocation = std::make_unique<std::vector<>>();
   public const std::vector<BloodBodyPartType> bloodLocations = std::make_unique<std::vector<>>();
    bool addHoles;
    int daySurvived;
    std::string ensureItem;
   public const std::vector<std::string> weapons = std::make_unique<std::vector<>>();
}
} // namespace AttachedItems
} // namespace characters
} // namespace zombie
