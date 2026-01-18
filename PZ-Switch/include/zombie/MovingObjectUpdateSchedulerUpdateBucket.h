#pragma once
#include "zombie/characters/IsoZombie.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugType.h"
#include "zombie/iso/IsoMovingObject.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/objects/IsoDeadBody.h"
#include "zombie/util/Type.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class MovingObjectUpdateSchedulerUpdateBucket {
public:
 int frameMod;
 ArrayList<IsoMovingObject>[] buckets;

public
 MovingObjectUpdateSchedulerUpdateBucket(int int0) { this->init(int0); }

 void init(int int0) {
 this->frameMod = int0;
 this->buckets = new ArrayList[int0];

 for (int int1 = 0; int1 < this->buckets.length; int1++) {
 this->buckets[int1] = std::make_unique<ArrayList<>>();
 }
 }

 void clear() {
 for (int int0 = 0; int0 < this->buckets.length; int0++) {
 std::vector arrayList = this->buckets[int0];
 arrayList.clear();
 }
 }

 void remove(IsoMovingObject movingObject) {
 for (int int0 = 0; int0 < this->buckets.length; int0++) {
 std::vector arrayList = this->buckets[int0];
 arrayList.remove(movingObject);
 }
 }

 void add(IsoMovingObject movingObject) {
 int int0 = movingObject.getID() % this->frameMod;
 this->buckets[int0].add(movingObject);
 }

 void update(int int0) {
 GameTime.getInstance().PerObjectMultiplier = this->frameMod;
 std::vector arrayList = this->buckets[int0 % this->frameMod];

 for (int int1 = 0; int1 < arrayList.size(); int1++) {
 IsoMovingObject movingObject = (IsoMovingObject)arrayList.get(int1);
 if (movingObject instanceof IsoDeadBody) {
 IsoWorld.instance.getCell().getRemoveList().add(movingObject);
 } else {
 IsoZombie zombie0 = Type.tryCastTo(movingObject, IsoZombie.class);
 if (zombie0 != nullptr &&
 VirtualZombieManager.instance.isReused(zombie0) {
 DebugLog.log(DebugType.Zombie,
 "REUSABLE ZOMBIE IN "
 "MovingObjectUpdateSchedulerUpdateBucket IGNORED " +
 movingObject);
 } else {
 movingObject.preupdate();
 movingObject.update();
 }
 }
 }

 GameTime.getInstance().PerObjectMultiplier = 1.0F;
 }

 void postupdate(int int0) {
 GameTime.getInstance().PerObjectMultiplier = this->frameMod;
 std::vector arrayList = this->buckets[int0 % this->frameMod];

 for (int int1 = 0; int1 < arrayList.size(); int1++) {
 IsoMovingObject movingObject = (IsoMovingObject)arrayList.get(int1);
 IsoZombie zombie0 = Type.tryCastTo(movingObject, IsoZombie.class);
 if (zombie0 != nullptr &&
 VirtualZombieManager.instance.isReused(zombie0) {
 DebugLog.log(DebugType.Zombie,
 "REUSABLE ZOMBIE IN "
 "MovingObjectUpdateSchedulerUpdateBucket IGNORED " +
 movingObject);
 } else {
 movingObject.postupdate();
 }
 }

 GameTime.getInstance().PerObjectMultiplier = 1.0F;
 }

 void removeObject(IsoMovingObject movingObject) {
 for (int int0 = 0; int0 < this->buckets.length; int0++) {
 std::vector arrayList = this->buckets[int0];
 arrayList.remove(movingObject);
 }
 }

public
 ArrayList<IsoMovingObject> getBucket(int int0) {
 return this->buckets[int0 % this->frameMod];
 }
}
} // namespace zombie
