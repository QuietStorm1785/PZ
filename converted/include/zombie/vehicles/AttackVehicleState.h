#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "fmod/fmod/FMODSoundEmitter.h"
#include "org/joml/Vector3f.h"
#include "zombie/GameTime.h"
#include "zombie/ai/State.h"
#include "zombie/ai/states/ZombieIdleState.h"
#include "zombie/audio/BaseSoundEmitter.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/Core.h"
#include "zombie/core/Rand.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimEvent.h"
#include "zombie/network/GameServer.h"

namespace zombie {
namespace vehicles {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class AttackVehicleState : public State {
public:
 static const AttackVehicleState _instance = new AttackVehicleState();
 BaseSoundEmitter emitter;
 const Vector3f worldPos = new Vector3f();

 static AttackVehicleState instance() {
 return _instance;
 }

 void enter(IsoGameCharacter var1) {
 }

 void execute(IsoGameCharacter character0) {
 IsoZombie zombie0 = (IsoZombie)character0;
 if (zombie0.target instanceof IsoGameCharacter character1) {
 if (character1.isDead()) {
 if (character1.getLeaveBodyTimedown() > 3600.0F) {
 zombie0.changeState(ZombieIdleState.instance());
 zombie0.setTarget(nullptr);
 } else {
 character1.setLeaveBodyTimedown(character1.getLeaveBodyTimedown() + GameTime.getInstance().getMultiplier() / 1.6F);
 if (!GameServer.bServer && !Core.SoundDisabled && Rand.Next(Rand.AdjustForFramerate(15) == 0) {
 if (this->emitter == nullptr) {
 this->emitter = std::make_unique<FMODSoundEmitter>();
 }

 std::string string = zombie0.isFemale() ? "FemaleZombieEating" : "MaleZombieEating";
 if (!this->emitter.isPlaying(string) {
 this->emitter.playSound(string);
 }
 }
 }

 zombie0.TimeSinceSeenFlesh = 0.0F;
 } else {
 BaseVehicle vehicle = character1.getVehicle();
 if (vehicle != nullptr && vehicle.isCharacterAdjacentTo(character0) {
 Vector3f vector3f = vehicle.chooseBestAttackPosition(character1, character0, this->worldPos);
 if (vector3f == nullptr) {
 if (zombie0.AllowRepathDelay <= 0.0F) {
 character0.pathToCharacter(character1);
 zombie0.AllowRepathDelay = 6.25F;
 }
 } else if (vector3f != nullptr && (Math.abs(vector3f.x - character0.x) > 0.1F || Math.abs(vector3f.y - character0.y) > 0.1F) {
 if (!(Math.abs(vehicle.getCurrentSpeedKmHour()) > 0.8F)
 || !vehicle.isCharacterAdjacentTo(character0) && !(vehicle.DistToSquared(character0) < 16.0F) {
 if (zombie0.AllowRepathDelay <= 0.0F) {
 character0.pathToCharacter(character1);
 zombie0.AllowRepathDelay = 6.25F;
 }
 }
 } else {
 character0.faceThisObject(character1);
 }
 }
 }
 }
 }

 void exit(IsoGameCharacter var1) {
 }

 void animEvent(IsoGameCharacter character0, AnimEvent animEvent) {
 IsoZombie zombie0 = (IsoZombie)character0;
 if (zombie0.target instanceof IsoGameCharacter character1) {
 BaseVehicle vehicle = character1.getVehicle();
 if (vehicle != nullptr) {
 if (!character1.isDead()) {
 if (animEvent.m_EventName.equalsIgnoreCase("AttackCollisionCheck")) {
 character1.getBodyDamage().AddRandomDamageFromZombie(zombie0, nullptr);
 character1.getBodyDamage().Update();
 if (character1.isDead()) {
 if (character1.isFemale()) {
 zombie0.getEmitter().playVocals("FemaleBeingEatenDeath");
 } else {
 zombie0.getEmitter().playVocals("MaleBeingEatenDeath");
 }

 character1.setHealth(0.0F);
 } else if (character1.isAsleep()) {
 if (GameServer.bServer) {
 character1.sendObjectChange("wakeUp");
 character1.setAsleep(false);
 } else {
 character1.forceAwake();
 }
 }
 } else if (animEvent.m_EventName.equalsIgnoreCase("ThumpFrame")) {
 VehicleWindow vehicleWindow = nullptr;
 VehiclePart part0 = nullptr;
 int int0 = vehicle.getSeat(character1);
 std::string string = vehicle.getPassengerArea(int0);
 if (vehicle.isInArea(string, character0) {
 VehiclePart part1 = vehicle.getPassengerDoor(int0);
 if (part1 != nullptr && part1.getDoor() != nullptr && part1.getInventoryItem() != nullptr && !part1.getDoor().isOpen()) {
 vehicleWindow = part1.findWindow();
 if (vehicleWindow != nullptr && !vehicleWindow.isHittable()) {
 vehicleWindow = nullptr;
 }

 if (vehicleWindow == nullptr) {
 part0 = part1;
 }
 }
 } else {
 part0 = vehicle.getNearestBodyworkPart(character0);
 if (part0 != nullptr) {
 vehicleWindow = part0.getWindow();
 if (vehicleWindow == nullptr) {
 vehicleWindow = part0.findWindow();
 }

 if (vehicleWindow != nullptr && !vehicleWindow.isHittable()) {
 vehicleWindow = nullptr;
 }

 if (vehicleWindow != nullptr) {
 part0 = nullptr;
 }
 }
 }

 if (vehicleWindow != nullptr) {
 vehicleWindow.damage(zombie0.strength);
 vehicle.setBloodIntensity(vehicleWindow.part.getId(), vehicle.getBloodIntensity(vehicleWindow.part.getId()) + 0.025F);
 if (!GameServer.bServer) {
 zombie0.setVehicleHitLocation(vehicle);
 character0.getEmitter().playSound("ZombieThumpVehicleWindow", vehicle);
 }

 zombie0.setThumpFlag(3);
 } else {
 if (!GameServer.bServer) {
 zombie0.setVehicleHitLocation(vehicle);
 character0.getEmitter().playSound("ZombieThumpVehicle", vehicle);
 }

 zombie0.setThumpFlag(1);
 }

 vehicle.setAddThumpWorldSound(true);
 if (part0 != nullptr && part0.getWindow() == nullptr && part0.getCondition() > 0) {
 part0.setCondition(part0.getCondition() - zombie0.strength);
 part0.doInventoryItemStats(part0.getInventoryItem(), 0);
 vehicle.transmitPartCondition(part0);
 }

 if (character1.isAsleep()) {
 if (GameServer.bServer) {
 character1.sendObjectChange("wakeUp");
 character1.setAsleep(false);
 } else {
 character1.forceAwake();
 }
 }
 }
 }
 }
 }
 }

 bool isAttacking(IsoGameCharacter var1) {
 return true;
 }

 bool isPassengerExposed(IsoGameCharacter character0) {
 if (!(character0 instanceof IsoZombie zombie0) {
 return false;
 } else if (!(zombie0.target instanceof IsoGameCharacter character1) {
 return false;
 } else {
 BaseVehicle vehicle = character1.getVehicle();
 if (vehicle == nullptr) {
 return false;
 } else {
 bool boolean0 = false;
 void* object = nullptr;
 int int0 = vehicle.getSeat(character1);
 std::string string = vehicle.getPassengerArea(int0);
 VehiclePart part = nullptr;
 if (vehicle.isInArea(string, character0) {
 part = vehicle.getPassengerDoor(int0);
 if (part != nullptr && part.getDoor() != nullptr) {
 if (part.getInventoryItem() != nullptr && !part.getDoor().isOpen()) {
 object = part.findWindow();
 if (object != nullptr) {
 if (!((VehicleWindow)object).isHittable()) {
 object = nullptr;
 }

 boolean0 = object == nullptr;
 } else {
 boolean0 = false;
 }
 } else {
 boolean0 = true;
 }
 }
 } else {
 part = vehicle.getNearestBodyworkPart(character0);
 if (part != nullptr) {
 object = part.findWindow();
 if (object != nullptr && !((VehicleWindow)object).isHittable()) {
 object = nullptr;
 }
 }
 }

 return boolean0;
 }
 }
 }
}
} // namespace vehicles
} // namespace zombie
