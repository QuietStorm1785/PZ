#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameTime.h"
#include "zombie/characters/CharacterTimedActions/BaseAction.h"
#include "zombie/core/Core.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/core/utils/UpdateLimit.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugType.h"
#include "zombie/iso/IsoUtils.h"
#include "zombie/iso/Vector2.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/NetworkVariables.h"
#include "zombie/network/PacketValidator.h"
#include "zombie/network/packets/DeadCharacterPacket.h"
#include "zombie/network/packets/hit/IMovable.h"
#include "zombie/network/packets/hit/VehicleHitPacket.h"
#include <algorithm>

namespace zombie {
namespace characters {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class NetworkCharacterAI {
public:
 static const short VEHICLE_HIT_DELAY_MS = 500;
 private NetworkCharacterAI.SpeedChecker speedChecker = new NetworkCharacterAI.SpeedChecker();
 public NetworkVariables.PredictionTypes predictionType;
 DeadCharacterPacket deadBody;
 VehicleHitPacket vehicleHit;
 float timestamp;
 BaseAction action;
 std::string performingAction;
 long noCollisionTime;
 bool wasLocal;
 const HitReactionNetworkAI hitReaction;
 const IsoGameCharacter character;
 public NetworkTeleport.NetworkTeleportDebug teleportDebug;
 public HashMap<Integer, String> debugData = new LinkedHashMap<Integer, String>() {
 bool removeEldestEntry(String> var1) {
 return this->size() > 10;
 }
 };

 public NetworkCharacterAI(IsoGameCharacter _character) {
 this->character = _character;
 this->deadBody = nullptr;
 this->wasLocal = false;
 this->vehicleHit = nullptr;
 this->noCollisionTime = 0L;
 this->hitReaction = new HitReactionNetworkAI(_character);
 this->predictionType = NetworkVariables.PredictionTypes.None;
 this->clearTeleportDebug();
 this->speedChecker.reset();
 }

 void reset() {
 this->deadBody = nullptr;
 this->wasLocal = false;
 this->vehicleHit = nullptr;
 this->noCollisionTime = 0L;
 this->hitReaction.finish();
 this->predictionType = NetworkVariables.PredictionTypes.None;
 this->clearTeleportDebug();
 this->speedChecker.reset();
 }

 void setLocal(bool _wasLocal) {
 this->wasLocal = _wasLocal;
 }

 bool wasLocal() {
 return this->wasLocal;
 }

 public NetworkTeleport.NetworkTeleportDebug getTeleportDebug() {
 return this->teleportDebug;
 }

 void clearTeleportDebug() {
 this->teleportDebug = nullptr;
 this->debugData.clear();
 }

 void setTeleportDebug(NetworkTeleport.NetworkTeleportDebug _teleportDebug) {
 this->teleportDebug = _teleportDebug;
 this->debugData.entrySet().stream().sorted(Entry.comparingByKey(Comparator.naturalOrder())).forEach(entry -> {
 if (Core.bDebug) {
 DebugLog.log(DebugType.Multiplayer, "==> " + entry.getValue());
 }
 });
 if (Core.bDebug) {
 DebugLog.log(
 DebugType.Multiplayer,
 String.format(
 "NetworkTeleport %s id=%d distance=%.3f prediction=%s",
 this->character.getClass().getSimpleName(),
 this->character.getOnlineID(),
 _teleportDebug.getDistance(),
 this->predictionType
 )
 );
 }
 }

 void addTeleportData(int time, const std::string& prediction) {
 this->debugData.put(time, prediction);
 }

 void processDeadBody() {
 if (this->isSetDeadBody() && !this->hitReaction.isSetup() && !this->hitReaction.isStarted()) {
 this->deadBody.process();
 this->setDeadBody(nullptr);
 }
 }

 void setDeadBody(DeadCharacterPacket packet) {
 this->deadBody = packet;
 DebugLog.Death.trace(packet.empty() ? "processed" : "postpone");
 }

 bool isSetDeadBody() {
 return this->deadBody != nullptr && this->deadBody.isConsistent();
 }

 void setPerformingAction(const std::string& animation) {
 this->performingAction = animation;
 }

 std::string getPerformingAction() {
 return this->performingAction;
 }

 void setAction(BaseAction _action) {
 this->action = _action;
 }

 BaseAction getAction() {
 return this->action;
 }

 void startAction() {
 if (this->action != nullptr) {
 this->action.start();
 }
 }

 void stopAction() {
 if (this->action != nullptr) {
 this->setOverride(false, nullptr, nullptr);
 this->action.stop();
 }
 }

 void setOverride(bool override, const std::string& primaryHandModel, const std::string& secondaryHandModel) {
 if (this->action != nullptr) {
 this->action.chr.forceNullOverride = override;
 this->action.chr.overridePrimaryHandModel = primaryHandModel;
 this->action.chr.overrideSecondaryHandModel = secondaryHandModel;
 this->action.chr.resetModelNextFrame();
 }
 }

 void processVehicleHit() {
 this->vehicleHit.tryProcessInternal();
 this->setVehicleHit(nullptr);
 }

 void setVehicleHit(VehicleHitPacket packet) {
 this->vehicleHit = packet;
 this->timestamp = (float)TimeUnit.NANOSECONDS.toMillis(GameTime.getServerTime());
 DebugLog.Damage.noise(packet.empty() ? "processed" : "postpone");
 }

 bool isSetVehicleHit() {
 return this->vehicleHit != nullptr && this->vehicleHit.isConsistent();
 }

 void resetVehicleHitTimeout() {
 this->timestamp = (float)(TimeUnit.NANOSECONDS.toMillis(GameTime.getServerTime()) - 500L);
 if (this->vehicleHit.empty()) {
 DebugLog.Damage.noise("VehicleHit is not set");
 }
 }

 bool isVehicleHitTimeout() {
 bool boolean0 = (float)TimeUnit.NANOSECONDS.toMillis(GameTime.getServerTime()) - this->timestamp >= 500.0F;
 if (boolean0) {
 DebugLog.Damage.noise("VehicleHit timeout");
 }

 return boolean0;
 }

 void updateHitVehicle() {
 if (this->isSetVehicleHit() && this->isVehicleHitTimeout()) {
 this->processVehicleHit();
 }
 }

 bool isCollisionEnabled() {
 return this->noCollisionTime == 0L;
 }

 bool isNoCollisionTimeout() {
 bool boolean0 = GameTime.getServerTimeMills() > this->noCollisionTime;
 if (boolean0) {
 this->setNoCollision(0L);
 }

 return boolean0;
 }

 void setNoCollision(long interval) {
 if (interval == 0L) {
 this->noCollisionTime = 0L;
 if (Core.bDebug) {
 DebugLog.log(DebugType.Multiplayer, "SetNoCollision: disabled");
 }
 } else {
 this->noCollisionTime = GameTime.getServerTimeMills() + interval;
 if (Core.bDebug) {
 DebugLog.log(DebugType.Multiplayer, "SetNoCollision: enabled for " + interval + " ms");
 }
 }
 }

 bool checkPosition(UdpConnection connection, IsoGameCharacter _character, float x, float y) {
 if (GameServer.bServer && _character.isAlive()) {
 this->speedChecker.set(x, y, _character.isSeatedInVehicle());
 boolean boolean0 = PacketValidator.checkSpeed(
 connection, this->speedChecker, _character.getClass().getSimpleName() + NetworkCharacterAI.SpeedChecker.class.getSimpleName()
 );
 if (32 == connection.accessLevel) {
 boolean0 = true;
 }

 return boolean0;
 } else {
 return true;
 }
 }

 void resetSpeedLimiter() {
 this->speedChecker.reset();
 }

 private static class SpeedChecker implements IMovable {
 static const int checkDelay = 5000;
 static const int checkInterval = 1000;
 const UpdateLimit updateLimit = new UpdateLimit(5000L);
 const Vector2 position = new Vector2();
 bool isInVehicle;
 float speed;

 float getSpeed() {
 return this->speed;
 }

 bool isVehicle() {
 return this->isInVehicle;
 }

 void set(float arg0, float arg1, bool arg2) {
 if (this->updateLimit.Check()) {
 if (5000L == this->updateLimit.getDelay()) {
 this->updateLimit.Reset(1000L);
 this->position.set(0.0F, 0.0F);
 this->speed = 0.0F;
 }

 this->isInVehicle = arg2;
 if (this->position.getLength() != 0.0F) {
 this->speed = IsoUtils.DistanceTo(this->position.x, this->position.y, arg0, arg1);
 }

 this->position.set(arg0, arg1);
 }
 }

 void reset() {
 this->updateLimit.Reset(5000L);
 this->isInVehicle = false;
 this->position.set(0.0F, 0.0F);
 this->speed = 0.0F;
 }

 std::string getDescription() {
 return "SpeedChecker: speed=" + this->speed + " x=" + this->position.x + " y=" + this->position.y + " vehicle=" + this->isInVehicle;
 }
 }
}
} // namespace characters
} // namespace zombie
