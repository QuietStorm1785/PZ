#pragma once
#include "zombie/SandboxOptions.h"
#include "zombie/ai/ZombieGroupManager.h"
#include "zombie/iso/IsoUtils.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace characters {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class ZombieGroup {
public:
private
 ArrayList<IsoZombie> members = std::make_unique<ArrayList<>>();
 float lastSpreadOutTime;

 ZombieGroup reset() {
 this->members.clear();
 this->lastSpreadOutTime = -1.0F;
 return this;
 }

 void add(IsoZombie zombie) {
 if (!this->members.contains(zombie) {
 if (zombie.group != nullptr) {
 zombie.group.remove(zombie);
 }

 this->members.add(zombie);
 zombie.group = this;
 }
 }

 void remove(IsoZombie zombie) {
 this->members.remove(zombie);
 zombie.group = nullptr;
 }

 IsoZombie getLeader() {
 return this->members.empty() ? nullptr : this->members.get(0);
 }

 bool isEmpty() { return this->members.empty(); }

 int size() { return this->members.size(); }

 void update() {
 int int0 =
 SandboxOptions.instance.zombieConfig.RallyTravelDistance.getValue();

 for (int int1 = 0; int1 < this->members.size(); int1++) {
 IsoZombie zombie0 = this->members.get(int1);
 float float0 = 0.0F;
 if (int1 > 0) {
 float0 = IsoUtils.DistanceToSquared(this->members.get(0).getX(),
 this->members.get(0).getY(),
 zombie0.getX(), zombie0.getY());
 }

 if (zombie0.group != this || float0 > int0 * int0 ||
 !ZombieGroupManager.instance.shouldBeInGroup(zombie0) {
 if (zombie0.group == this) {
 zombie0.group = nullptr;
 }

 this->members.remove(int1--);
 }
 }
 }
}
} // namespace characters
} // namespace zombie
