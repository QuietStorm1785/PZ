#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/iso/BuildingDef.h"

namespace zombie {
namespace characters {


class SurvivorGroup {
public:
   public const std::vector<SurvivorDesc> Members = std::make_unique<std::vector<>>();
    std::string Order;
    BuildingDef Safehouse;

    void addMember(SurvivorDesc var1) {
   }

    void removeMember(SurvivorDesc var1) {
   }

    SurvivorDesc getLeader() {
    return nullptr;
   }

    bool isLeader(SurvivorDesc var1) {
    return false;
   }
}
} // namespace characters
} // namespace zombie
