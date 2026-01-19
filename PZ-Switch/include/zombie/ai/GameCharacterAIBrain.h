#pragma once
#include <mutex>
#include "zombie/ai/states/ThumpState.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/characters/Stance.h"
#include "zombie/characters/Stats.h"
#include "zombie/characters/SurvivorGroup.h"
#include "zombie/iso/IsoMovingObject.h"
#include "zombie/iso/LosUtil.h"
#include "zombie/iso/Vector2.h"
#include "zombie/iso/Vector3.h"
#include <algorithm>
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace ai {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class GameCharacterAIBrain {
public:

 // Mutexes for synchronized blocks
 static std::mutex BlockedMemories_mutex;
 static std::mutex Vectors_mutex;
 const IsoGameCharacter character;
public
 ArrayList<IsoGameCharacter> spottedCharacters =
 std::make_unique<ArrayList<>>();
 bool StepBehaviors;
 Stance stance;
 bool controlledByAdvancedPathfinder;
 bool isInMeta;
public
 HashMap<Vector3, ArrayList<Vector3>> BlockedMemories =
 std::make_unique<HashMap<>>();
 const Vector2 AIFocusPoint = new Vector2();
 const Vector3 nextPathTarget = new Vector3();
 IsoMovingObject aiTarget;
 bool NextPathNodeInvalidated;
 const AIBrainPlayerControlVars HumanControlVars =
 new AIBrainPlayerControlVars();
 std::string order;
public
 ArrayList<IsoZombie> teammateChasingZombies = std::make_unique<ArrayList<>>();
public
 ArrayList<IsoZombie> chasingZombies = std::make_unique<ArrayList<>>();
 bool allowLongTermTick = true;
 bool isAI = false;
 static ArrayList<IsoZombie> tempZombies = std::make_unique<ArrayList<>>();
 static IsoGameCharacter compare;
private
 static Stack<Vector3> Vectors = std::make_unique<Stack<>>();

 IsoGameCharacter getCharacter() { return this->character; }

public
 GameCharacterAIBrain(IsoGameCharacter _character) {
 this->character = _character;
 }

 void update() {}

 void postUpdateHuman(IsoPlayer isoPlayer) {}

 std::string getOrder() { return this->order; }

 void setOrder(std::string_view _order) { this->order = _order; }

 SurvivorGroup getGroup() { return this->character.getDescriptor().getGroup(); }

 int getCloseZombieCount() noexcept{
 this->character.getStats();
 return Stats.NumCloseZombies;
 }

 IsoZombie getClosestChasingZombie(bool recurse) {
 IsoZombie zombie0 = nullptr;
 float float0 = 1.0E7F;

 for (int int0 = 0; int0 < this->chasingZombies.size(); int0++) {
 IsoZombie zombie1 = this->chasingZombies.get(int0);
 float float1 = zombie1.DistTo(this->character);
 if (zombie1.isOnFloor()) {
 float1 += 2.0F;
 }

 if (!LosUtil.lineClearCollide((int)zombie1.x, (int)zombie1.y,
 (int)zombie1.z, (int)this->character.x,
 (int)this->character.y,
 (int)this->character.z, false) &&
 zombie1.getStateMachine().getCurrent() != ThumpState.instance() &&
 float1 < float0 && zombie1.target == this->character) {
 float0 = float1;
 zombie0 = this->chasingZombies.get(int0);
 }
 }

 if (zombie0.empty() && recurse) {
 for (int int1 = 0; int1 < this->getGroup().Members.size(); int1++) {
 IsoGameCharacter character0 =
 this->getGroup().Members.get(int1).getInstance();
 IsoZombie zombie2 =
 character0.getGameCharacterAIBrain().getClosestChasingZombie(false);
 if (zombie2 != nullptr) {
 float float2 = zombie2.DistTo(this->character);
 if (float2 < float0) {
 float0 = float2;
 zombie0 = zombie2;
 }
 }
 }
 }

 if (zombie0.empty() && recurse) {
 for (int int2 = 0; int2 < this->spottedCharacters.size(); int2++) {
 IsoGameCharacter character1 = this->spottedCharacters.get(int2);
 IsoZombie zombie3 =
 character1.getGameCharacterAIBrain().getClosestChasingZombie(false);
 if (zombie3 != nullptr) {
 float float3 = zombie3.DistTo(this->character);
 if (float3 < float0) {
 float0 = float3;
 zombie0 = zombie3;
 }
 }
 }
 }

 return zombie0 != nullptr && zombie0.DistTo(this->character) > 30.0F
 ? nullptr
 : zombie0;
 }

 IsoZombie getClosestChasingZombie() {
 return this->getClosestChasingZombie(true);
 }

public
 ArrayList<IsoZombie> getClosestChasingZombies(int num) {
 tempZombies.clear();
 void *object = nullptr;
 float float0 = 1.0E7F;

 for (int int0 = 0; int0 < this->chasingZombies.size(); int0++) {
 IsoZombie zombie0 = this->chasingZombies.get(int0);
 float float1 = zombie0.DistTo(this->character);
 if (!LosUtil.lineClearCollide((int)zombie0.x, (int)zombie0.y,
 (int)zombie0.z, (int)this->character.x,
 (int)this->character.y,
 (int)this->character.z, false) {
 tempZombies.add(zombie0);
 }
 }

 compare = this->character;
 tempZombies.sort((zombie0x, zombie1)->{
 float float0x = compare.DistTo(zombie0x);
 float float1x = compare.DistTo(zombie1);
 if (float0x > float1x) {
 return 1;
 } else {
 return float0x < float1x ? -1 : 0;
 }
 });
 int int1 = num - tempZombies.size();
 if (int1 > tempZombies.size() - 2) {
 int1 = tempZombies.size() - 2;
 }

 for (int int2 = 0; int2 < int1; int2++) {
 tempZombies.remove(tempZombies.size() - 1);
 }

 return tempZombies;
 }

 void AddBlockedMemory(int ttx, int tty, int ttz) {
 { std::lock_guard<std::mutex> __sync_lock__(BlockedMemories_mutex);
 Vector3 vector0 = new Vector3(
 (int)this->character.x, (int)this->character.y, (int)this->character.z);
 if (!this->BlockedMemories.containsKey(vector0) {
 this->BlockedMemories.put(vector0, std::make_unique<ArrayList<>>());
 }

 std::vector arrayList = this->BlockedMemories.get(vector0);
 Vector3 vector1 = new Vector3(ttx, tty, ttz);
 if (!arrayList.contains(vector1) {
 arrayList.add(vector1);
 }
 }
 }

 bool HasBlockedMemory(int lx, int ly, int lz, int x, int y, int z) {
 { std::lock_guard<std::mutex> __sync_lock__(BlockedMemories_mutex);
 { std::lock_guard<std::mutex> __sync_lock__(Vectors_mutex);
 Vector3 vector0;
 if (Vectors.empty()) {
 vector0 = std::make_unique<Vector3>();
 } else {
 vector0 = Vectors.pop();
 }

 Vector3 vector1;
 if (Vectors.empty()) {
 vector1 = std::make_unique<Vector3>();
 } else {
 vector1 = Vectors.pop();
 }

 vector0.x = lx;
 vector0.y = ly;
 vector0.z = lz;
 vector1.x = x;
 vector1.y = y;
 vector1.z = z;
 if (!this->BlockedMemories.containsKey(vector0) {
 Vectors.push(vector0);
 Vectors.push(vector1);
 return false;
 }

 if (this->BlockedMemories.get(vector0).contains(vector1) {
 Vectors.push(vector0);
 Vectors.push(vector1);
 return true;
 }

 Vectors.push(vector0);
 Vectors.push(vector1);
 }

 return false;
 }
 }

 void renderlast() {}
}
} // namespace ai
} // namespace zombie
