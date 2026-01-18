#pragma once
#include "zombie/characterTextures/BloodBodyPartType.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace characters {
namespace AttachedItems {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class AttachedWeaponDefinition {
public:
 std::string id;
 int chance;
public
 ArrayList<String> outfit = std::make_unique<ArrayList<>>();
public
 ArrayList<String> weaponLocation = std::make_unique<ArrayList<>>();
public
 ArrayList<BloodBodyPartType> bloodLocations =
 std::make_unique<ArrayList<>>();
 bool addHoles;
 int daySurvived;
 std::string ensureItem;
public
 ArrayList<String> weapons = std::make_unique<ArrayList<>>();
}
} // namespace AttachedItems
} // namespace characters
} // namespace zombie
