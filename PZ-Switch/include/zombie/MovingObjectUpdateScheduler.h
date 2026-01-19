#pragma once
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/iso/IsoMovingObject.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/network/GameServer.h"
#include "zombie/vehicles/BaseVehicle.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class MovingObjectUpdateScheduler {
public:
 static const MovingObjectUpdateScheduler instance =
 new MovingObjectUpdateScheduler();
 const MovingObjectUpdateSchedulerUpdateBucket fullSimulation =
 new MovingObjectUpdateSchedulerUpdateBucket(1);
 const MovingObjectUpdateSchedulerUpdateBucket halfSimulation =
 new MovingObjectUpdateSchedulerUpdateBucket(2);
 const MovingObjectUpdateSchedulerUpdateBucket quarterSimulation =
 new MovingObjectUpdateSchedulerUpdateBucket(4);
 const MovingObjectUpdateSchedulerUpdateBucket eighthSimulation =
 new MovingObjectUpdateSchedulerUpdateBucket(8);
 const MovingObjectUpdateSchedulerUpdateBucket sixteenthSimulation =
 new MovingObjectUpdateSchedulerUpdateBucket(16);
 long frameCounter;
 bool isEnabled = true;

 long getFrameCounter() noexcept{ return this->frameCounter; }

 void startFrame() {
 this->frameCounter++;
 this->fullSimulation.clear();
 this->halfSimulation.clear();
 this->quarterSimulation.clear();
 this->eighthSimulation.clear();
 this->sixteenthSimulation.clear();
 std::vector arrayList = IsoWorld.instance.getCell().getObjectList();

 for (int int0 = 0; int0 < arrayList.size(); int0++) {
 IsoMovingObject movingObject = (IsoMovingObject)arrayList.get(int0);
 if (!GameServer.bServer || !(movingObject instanceof IsoZombie) {
 bool boolean0 = false;
 bool boolean1 = false;
 float float0 = 1.0E8F;
 bool boolean2 = false;

 for (int int1 = 0; int1 < IsoPlayer.numPlayers; int1++) {
 IsoPlayer player = IsoPlayer.players[int1];
 if (player != nullptr) {
 if (movingObject.getCurrentSquare() == nullptr) {
 movingObject.setCurrent(IsoWorld.instance.getCell().getGridSquare(
 (double)movingObject.x, (double)movingObject.y,
 (double)movingObject.z);
 }

 if (player == movingObject) {
 boolean2 = true;
 }

 if (movingObject.getCurrentSquare() != nullptr) {
 if (movingObject.getCurrentSquare().isCouldSee(int1) {
 boolean0 = true;
 }

 if (movingObject.getCurrentSquare().isCanSee(int1) {
 boolean1 = true;
 }

 float float1 = movingObject.DistTo(player);
 if (float1 < float0) {
 float0 = float1;
 }
 }
 }
 }

 int int2 = 3;
 if (!boolean1) {
 int2--;
 }

 if (!boolean0 && float0 > 10.0F) {
 int2--;
 }

 if (float0 > 30.0F) {
 int2--;
 }

 if (float0 > 60.0F) {
 int2--;
 }

 if (float0 > 80.0F) {
 int2--;
 }

 if (movingObject instanceof IsoPlayer) {
 int2 = 3;
 }

 if (movingObject instanceof BaseVehicle) {
 int2 = 3;
 }

 if (GameServer.bServer) {
 int2 = 3;
 }

 if (boolean2) {
 int2 = 3;
 }

 if (!this->isEnabled) {
 int2 = 3;
 }

 if (int2 == 3) {
 this->fullSimulation.add(movingObject);
 }

 if (int2 == 2) {
 this->halfSimulation.add(movingObject);
 }

 if (int2 == 1) {
 this->quarterSimulation.add(movingObject);
 }

 if (int2 == 0) {
 this->eighthSimulation.add(movingObject);
 }

 if (int2 < 0) {
 this->sixteenthSimulation.add(movingObject);
 }
 }
 }
 }

 void update() {
 GameTime.getInstance().PerObjectMultiplier = 1.0F;
 this->fullSimulation.update((int)this->frameCounter);
 this->halfSimulation.update((int)this->frameCounter);
 this->quarterSimulation.update((int)this->frameCounter);
 this->eighthSimulation.update((int)this->frameCounter);
 this->sixteenthSimulation.update((int)this->frameCounter);
 }

 void postupdate() {
 GameTime.getInstance().PerObjectMultiplier = 1.0F;
 this->fullSimulation.postupdate((int)this->frameCounter);
 this->halfSimulation.postupdate((int)this->frameCounter);
 this->quarterSimulation.postupdate((int)this->frameCounter);
 this->eighthSimulation.postupdate((int)this->frameCounter);
 this->sixteenthSimulation.postupdate((int)this->frameCounter);
 }

 bool isEnabled() { return this->isEnabled; }

 void setEnabled(bool boolean0) { this->isEnabled = boolean0; }

 void removeObject(IsoMovingObject movingObject) {
 this->fullSimulation.removeObject(movingObject);
 this->halfSimulation.removeObject(movingObject);
 this->quarterSimulation.removeObject(movingObject);
 this->eighthSimulation.removeObject(movingObject);
 this->sixteenthSimulation.removeObject(movingObject);
 }

public
 ArrayList<IsoMovingObject> getBucket() {
 return this->fullSimulation.getBucket((int)this->frameCounter);
 }
}
} // namespace zombie
