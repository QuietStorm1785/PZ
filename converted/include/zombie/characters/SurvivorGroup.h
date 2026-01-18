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
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class SurvivorGroup {
public:
 public ArrayList<SurvivorDesc> Members = std::make_unique<ArrayList<>>();
 std::string Order;
 BuildingDef Safehouse;

 void addMember(SurvivorDesc member) {
 }

 void removeMember(SurvivorDesc member) {
 }

 SurvivorDesc getLeader() {
 return nullptr;
 }

 bool isLeader(SurvivorDesc member) {
 return false;
 }
}
} // namespace characters
} // namespace zombie
