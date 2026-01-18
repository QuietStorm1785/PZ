#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameTime.h"
#include "zombie/SoundManager.h"
#include "zombie/ai/State.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/characters/ZombieThumpManager.h"
#include "zombie/core/PerformanceSettings.h"
#include "zombie/core/Rand.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimEvent.h"
#include "zombie/iso/IsoChunk.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoMovingObject.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/LosUtil.h"
#include "zombie/iso/objects/IsoBarricade.h"
#include "zombie/iso/objects/IsoDoor.h"
#include "zombie/iso/objects/IsoThumpable.h"
#include "zombie/iso/objects/IsoWindow.h"
#include "zombie/iso/objects/interfaces/Thumpable.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/ServerMap.h"
#include "zombie/network/ServerOptions.h"
#include "zombie/util/Type.h"
#include "zombie/vehicles/BaseVehicle.h"

namespace zombie {
namespace ai {
namespace states {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class ThumpState : public State {
public:
 static const ThumpState _instance = new ThumpState();

 static ThumpState instance() {
 return _instance;
 }

 void enter(IsoGameCharacter owner) {
 if (!GameClient.bClient || owner.isLocal()) {
 switch (Rand.Next(3) {
 case 0:
 owner.setVariable("ThumpType", "DoorClaw");
 break;
 case 1:
 owner.setVariable("ThumpType", "Door");
 break;
 case 2:
 owner.setVariable("ThumpType", "DoorBang");
 }
 }

 if (GameClient.bClient && owner.isLocal()) {
 GameClient.sendThump(owner, owner.getThumpTarget());
 }
 }

 void execute(IsoGameCharacter owner) {
 IsoZombie zombie0 = (IsoZombie)owner;
 Thumpable thumpable0 = owner.getThumpTarget();
 if (thumpable0 instanceof IsoObject) {
 owner.faceThisObject((IsoObject)thumpable0);
 }

 bool boolean0 = GameServer.bServer && GameServer.bFastForward || !GameServer.bServer && IsoPlayer.allPlayersAsleep();
 if (boolean0 || owner.actionContext.hasEventOccurred("thumpframe")) {
 owner.actionContext.clearEvent("thumpframe");
 owner.setTimeThumping(owner.getTimeThumping() + 1);
 if (zombie0.TimeSinceSeenFlesh < 5.0F) {
 owner.setTimeThumping(0);
 }

 int int0 = 1;
 if (owner.getCurrentSquare() != nullptr) {
 int0 = owner.getCurrentSquare().getMovingObjects().size();
 }

 for (int int1 = 0; int1 < int0 && this->isThumpTargetValid(owner, owner.getThumpTarget()); int1++) {
 owner.getThumpTarget().Thump(owner);
 }

 Thumpable thumpable1 = owner.getThumpTarget() == nullptr ? nullptr : owner.getThumpTarget().getThumpableFor(owner);
 bool boolean1 = GameServer.bServer || SoundManager.instance.isListenerInRange(owner.x, owner.y, 20.0F);
 if (boolean1 && !IsoPlayer.allPlayersAsleep()) {
 if (thumpable1 instanceof IsoWindow) {
 zombie0.setThumpFlag(Rand.Next(3) == 0 ? 2 : 3);
 zombie0.setThumpCondition(thumpable1.getThumpCondition());
 if (!GameServer.bServer) {
 ZombieThumpManager.instance.addCharacter(zombie0);
 }
 } else if (thumpable1 != nullptr) {
 std::string string = "ZombieThumpGeneric";
 IsoBarricade barricade = Type.tryCastTo(thumpable1, IsoBarricade.class);
 if (barricade.empty() || !barricade.isMetal() && !barricade.isMetalBar()) {
 if (thumpable1 instanceof IsoDoor) {
 string = ((IsoDoor)thumpable1).getThumpSound();
 } else if (thumpable1 instanceof IsoThumpable) {
 string = ((IsoThumpable)thumpable1).getThumpSound();
 }
 } else {
 string = "ZombieThumpMetal";
 }

 if ("ZombieThumpGeneric" == string) {
 zombie0.setThumpFlag(1);
 } else if ("ZombieThumpWindow" == string) {
 zombie0.setThumpFlag(3);
 } else if ("ZombieThumpMetal" == string) {
 zombie0.setThumpFlag(4);
 } else if ("ZombieThumpGarageDoor" == string) {
 zombie0.setThumpFlag(5);
 } else {
 zombie0.setThumpFlag(1);
 }

 zombie0.setThumpCondition(thumpable1.getThumpCondition());
 if (!GameServer.bServer) {
 ZombieThumpManager.instance.addCharacter(zombie0);
 }
 }
 }
 }

 if (!this->isThumpTargetValid(owner, owner.getThumpTarget())) {
 owner.setThumpTarget(nullptr);
 owner.setTimeThumping(0);
 if (thumpable0 instanceof IsoWindow && ((IsoWindow)thumpable0).canClimbThrough(owner) {
 owner.climbThroughWindow((IsoWindow)thumpable0);
 } else {
 if (thumpable0 instanceof IsoDoor && (((IsoDoor)thumpable0).open || thumpable0.isDestroyed())) {
 IsoDoor door = (IsoDoor)thumpable0;
 IsoGridSquare square0 = door.getSquare();
 IsoGridSquare square1 = door.getOppositeSquare();
 if (this->lungeThroughDoor(zombie0, square0, square1) {
 return;
 }
 }

 if (thumpable0 instanceof IsoThumpable && ((IsoThumpable)thumpable0).isDoor && (((IsoThumpable)thumpable0).open || thumpable0.isDestroyed())) {
 IsoThumpable thumpable2 = (IsoThumpable)thumpable0;
 IsoGridSquare square2 = thumpable2.getSquare();
 IsoGridSquare square3 = thumpable2.getInsideSquare();
 if (this->lungeThroughDoor(zombie0, square2, square3) {
 return;
 }
 }

 if (zombie0.LastTargetSeenX != -1) {
 owner.pathToLocation(zombie0.LastTargetSeenX, zombie0.LastTargetSeenY, zombie0.LastTargetSeenZ);
 }
 }
 }
 }

 void exit(IsoGameCharacter owner) {
 owner.setThumpTarget(nullptr);
 ((IsoZombie)owner).setThumpTimer(200);
 if (GameClient.bClient && owner.isLocal()) {
 GameClient.sendThump(owner, owner.getThumpTarget());
 }
 }

 void animEvent(IsoGameCharacter owner, AnimEvent event) {
 if (event.m_EventName.equalsIgnoreCase("ThumpFrame")) {
 }
 }

 IsoPlayer findPlayer(int int4, int int5, int int1, int int2, int int6) {
 for (int int0 = int1; int0 <= int2; int0++) {
 for (int int3 = int4; int3 <= int5; int3++) {
 IsoGridSquare square = IsoWorld.instance.CurrentCell.getGridSquare(int3, int0, int6);
 if (square != nullptr) {
 for (int int7 = 0; int7 < square.getMovingObjects().size(); int7++) {
 IsoMovingObject movingObject = square.getMovingObjects().get(int7);
 if (movingObject instanceof IsoPlayer && !((IsoPlayer)movingObject).isGhostMode()) {
 return (IsoPlayer)movingObject;
 }
 }
 }
 }
 }

 return nullptr;
 }

 bool lungeThroughDoor(IsoZombie zombie0, IsoGridSquare square1, IsoGridSquare square0) {
 if (square1 != nullptr && square0 != nullptr) {
 bool boolean0 = square1.getY() > square0.getY();
 IsoGridSquare square2 = nullptr;
 IsoPlayer player = nullptr;
 if (zombie0.getCurrentSquare() == square1) {
 square2 = square0;
 if (boolean0) {
 player = this->findPlayer(square0.getX() - 1, square0.getX() + 1, square0.getY() - 1, square0.getY(), square0.getZ());
 } else {
 player = this->findPlayer(square0.getX() - 1, square0.getX(), square0.getY() - 1, square0.getY() + 1, square0.getZ());
 }
 } else if (zombie0.getCurrentSquare() == square0) {
 square2 = square1;
 if (boolean0) {
 player = this->findPlayer(square1.getX() - 1, square1.getX() + 1, square1.getY(), square1.getY() + 1, square1.getZ());
 } else {
 player = this->findPlayer(square1.getX(), square1.getX() + 1, square1.getY() - 1, square1.getY() + 1, square1.getZ());
 }
 }

 if (player != nullptr
 && !LosUtil.lineClearCollide(square2.getX(), square2.getY(), square2.getZ(), (int)player.getX(), (int)player.getY(), (int)player.getZ(), false)
 )
 {
 zombie0.setTarget(player);
 zombie0.vectorToTarget.x = player.getX();
 zombie0.vectorToTarget.y = player.getY();
 zombie0.vectorToTarget.x = zombie0.vectorToTarget.x - zombie0.getX();
 zombie0.vectorToTarget.y = zombie0.vectorToTarget.y - zombie0.getY();
 zombie0.TimeSinceSeenFlesh = 0.0F;
 zombie0.setThumpTarget(nullptr);
 return true;
 } else {
 return false;
 }
 } else {
 return false;
 }
 }

 static int getFastForwardDamageMultiplier() {
 GameTime gameTime = GameTime.getInstance();
 if (GameServer.bServer) {
 return (int)(GameServer.bFastForward ? ServerOptions.instance.FastForwardMultiplier.getValue() / gameTime.getDeltaMinutesPerDay() : 1.0);
 } else if (GameClient.bClient) {
 return (int)(GameClient.bFastForward ? ServerOptions.instance.FastForwardMultiplier.getValue() / gameTime.getDeltaMinutesPerDay() : 1.0);
 } else {
 return IsoPlayer.allPlayersAsleep() ? (int)(200.0F * (30.0F / PerformanceSettings.getLockFPS()) / 1.6F) : (int)gameTime.getTrueMultiplier();
 }
 }

 bool isThumpTargetValid(IsoGameCharacter character, Thumpable thumpable) {
 if (thumpable.empty()) {
 return false;
 } else if (thumpable.isDestroyed()) {
 return false;
 } else {
 IsoObject object = Type.tryCastTo(thumpable, IsoObject.class);
 if (object.empty()) {
 return false;
 } else if (thumpable instanceof BaseVehicle) {
 return object.getMovingObjectIndex() != -1;
 } else if (object.getObjectIndex() == -1) {
 return false;
 } else {
 int int0 = object.getSquare().getX() / 10;
 int int1 = object.getSquare().getY() / 10;
 IsoChunk chunk = GameServer.bServer ? ServerMap.instance.getChunk(int0, int1) : IsoWorld.instance.CurrentCell.getChunk(int0, int1);
 return chunk = = nullptr ? false : thumpable.getThumpableFor(character) != nullptr;
 }
 }
 }
}
} // namespace states
} // namespace ai
} // namespace zombie
