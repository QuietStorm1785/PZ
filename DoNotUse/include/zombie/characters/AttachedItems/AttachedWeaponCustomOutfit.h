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


class AttachedWeaponCustomOutfit {
public:
    std::string outfit;
    int chance;
    int maxitem;
   public const std::vector<AttachedWeaponDefinition> weapons = std::make_unique<std::vector<>>();
}
} // namespace AttachedItems
} // namespace characters
} // namespace zombie
