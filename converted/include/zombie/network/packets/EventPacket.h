#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameWindow.h"
#include "zombie/ai/states/ClimbDownSheetRopeState.h"
#include "zombie/ai/states/ClimbSheetRopeState.h"
#include "zombie/ai/states/FishingState.h"
#include "zombie/ai/states/SmashWindowState.h"
#include "zombie/characters/CharacterTimedActions/BaseAction.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/characters/NetworkPlayerVariables.h"
#include "zombie/core/Core.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugType.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/SpriteDetails/IsoFlagType.h"
#include "zombie/iso/objects/IsoThumpable.h"
#include "zombie/iso/objects/IsoWindow.h"
#include "zombie/iso/objects/IsoWindowFrame.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/util/StringUtils.h"
#include "zombie/vehicles/BaseVehicle.h"
#include "zombie/vehicles/VehicleManager.h"
#include "zombie/vehicles/VehiclePart.h"
#include "zombie/vehicles/VehicleWindow.h"
#include <filesystem>

namespace zombie {
namespace network {
namespace packets {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class EventPacket {
public:
 static const int MAX_PLAYER_EVENTS = 10;
 static const long EVENT_TIMEOUT = 5000L;
 static const short EVENT_FLAGS_VAULT_OVER_SPRINT = 1;
 static const short EVENT_FLAGS_VAULT_OVER_RUN = 2;
 static const short EVENT_FLAGS_BUMP_FALL = 4;
 static const short EVENT_FLAGS_BUMP_STAGGERED = 8;
 static const short EVENT_FLAGS_ACTIVATE_ITEM = 16;
 static const short EVENT_FLAGS_CLIMB_SUCCESS = 32;
 static const short EVENT_FLAGS_CLIMB_STRUGGLE = 64;
 static const short EVENT_FLAGS_BUMP_FROM_BEHIND = 128;
 static const short EVENT_FLAGS_BUMP_TARGET_TYPE = 256;
 static const short EVENT_FLAGS_PRESSED_MOVEMENT = 512;
 static const short EVENT_FLAGS_PRESSED_CANCEL_ACTION = 1024;
 static const short EVENT_FLAGS_SMASH_CAR_WINDOW = 2048;
 static const short EVENT_FLAGS_FITNESS_FINISHED = 4096;
 short id;
 float x;
 float y;
 float z;
 uint8_t eventID;
 std::string type1;
 std::string type2;
 std::string type3;
 std::string type4;
 float strafeSpeed;
 float walkSpeed;
 float walkInjury;
 int booleanVariables;
 short flags;
 IsoPlayer player;
 private EventPacket.EventType event;
 long timestamp;

 std::string getDescription() {
 return "[ player="
 + this->id
 + " \""
 + (this->player == nullptr ? "?" : this->player.getUsername())
 + "\" | name=\""
 + (this->event == nullptr ? "?" : this->event.name())
 + "\" | pos=( "
 + this->x
 + " ; "
 + this->y
 + " ; "
 + this->z
 + " ) | type1=\""
 + this->type1
 + "\" | type2=\""
 + this->type2
 + "\" | type3=\""
 + this->type3
 + "\" | type4=\""
 + this->type4
 + "\" | flags="
 + this->flags
 + "\" | variables="
 + this->booleanVariables
 + " ]";
 }

 bool isConsistent() {
 bool boolean0 = this->player != nullptr && this->event != nullptr;
 if (!boolean0 && Core.bDebug) {
 DebugLog.log(DebugType.Multiplayer, "[Event] is not consistent " + this->getDescription());
 }

 return boolean0;
 }

 void parse(ByteBuffer byteBuffer, UdpConnection var2) {
 this->id = byteBuffer.getShort();
 this->x = byteBuffer.getFloat();
 this->y = byteBuffer.getFloat();
 this->z = byteBuffer.getFloat();
 this->eventID = byteBuffer.get();
 this->type1 = GameWindow.ReadString(byteBuffer);
 this->type2 = GameWindow.ReadString(byteBuffer);
 this->type3 = GameWindow.ReadString(byteBuffer);
 this->type4 = GameWindow.ReadString(byteBuffer);
 this->strafeSpeed = byteBuffer.getFloat();
 this->walkSpeed = byteBuffer.getFloat();
 this->walkInjury = byteBuffer.getFloat();
 this->booleanVariables = byteBuffer.getInt();
 this->flags = byteBuffer.getShort();
 if (this->eventID >= 0 && this->eventID < EventPacket.EventType.values().length) {
 this->event = EventPacket.EventType.values()[this->eventID];
 } else {
 DebugLog.Multiplayer.warn("Unknown event=" + this->eventID);
 this->event = nullptr;
 }

 if (GameServer.bServer) {
 this->player = GameServer.IDToPlayerMap.get(this->id);
 } else if (GameClient.bClient) {
 this->player = GameClient.IDToPlayerMap.get(this->id);
 } else {
 this->player = nullptr;
 }

 this->timestamp = System.currentTimeMillis() + 5000L;
 }

 void write(ByteBufferWriter byteBufferWriter) {
 byteBufferWriter.putShort(this->id);
 byteBufferWriter.putFloat(this->x);
 byteBufferWriter.putFloat(this->y);
 byteBufferWriter.putFloat(this->z);
 byteBufferWriter.putByte(this->eventID);
 byteBufferWriter.putUTF(this->type1);
 byteBufferWriter.putUTF(this->type2);
 byteBufferWriter.putUTF(this->type3);
 byteBufferWriter.putUTF(this->type4);
 byteBufferWriter.putFloat(this->strafeSpeed);
 byteBufferWriter.putFloat(this->walkSpeed);
 byteBufferWriter.putFloat(this->walkInjury);
 byteBufferWriter.putInt(this->booleanVariables);
 byteBufferWriter.putShort(this->flags);
 }

 bool isRelevant(UdpConnection udpConnection) {
 return udpConnection.RelevantTo(this->x, this->y);
 }

 bool isMovableEvent() {
 return !this->isConsistent()
 ? false
 : EventPacket.EventType.EventClimbFence == this->event) || EventPacket.EventType.EventFallClimb == this->event);
 }

 bool requireNonMoving() {
 return this->isConsistent()
 && (
 EventPacket.EventType.EventClimbWindow == this->event)
 || EventPacket.EventType.EventClimbFence == this->event)
 || EventPacket.EventType.EventClimbDownRope == this->event)
 || EventPacket.EventType.EventClimbRope == this->event)
 || EventPacket.EventType.EventClimbWall == this->event)
 );
 }

 IsoWindow getWindow(IsoPlayer playerx) {
 for (IsoDirections directions : IsoDirections.values()) {
 IsoObject object = playerx.getContextDoorOrWindowOrWindowFrame(directions);
 if (object instanceof IsoWindow) {
 return (IsoWindow)object;
 }
 }

 return nullptr;
 }

 IsoObject getObject(IsoPlayer playerx) {
 for (IsoDirections directions : IsoDirections.values()) {
 IsoObject object = playerx.getContextDoorOrWindowOrWindowFrame(directions);
 if (object instanceof IsoWindow || object instanceof IsoThumpable || IsoWindowFrame.isWindowFrame(object) {
 return object;
 }
 }

 return nullptr;
 }

 IsoDirections checkCurrentIsEventGridSquareFence(IsoPlayer playerx) {
 IsoGridSquare square0 = playerx.getCell().getGridSquare((double)this->x, (double)this->y, (double)this->z);
 IsoGridSquare square1 = playerx.getCell().getGridSquare((double)this->x, (double)(this->y + 1.0F), (double)this->z);
 IsoGridSquare square2 = playerx.getCell().getGridSquare((double)(this->x + 1.0F), (double)this->y, (double)this->z);
 IsoDirections directions;
 if (square0 != nullptr && square0.Is(IsoFlagType.HoppableN) {
 directions = IsoDirections.N;
 } else if (square0 != nullptr && square0.Is(IsoFlagType.HoppableW) {
 directions = IsoDirections.W;
 } else if (square1 != nullptr && square1.Is(IsoFlagType.HoppableN) {
 directions = IsoDirections.S;
 } else if (square2 != nullptr && square2.Is(IsoFlagType.HoppableW) {
 directions = IsoDirections.E;
 } else {
 directions = IsoDirections.Max;
 }

 return directions;
 }

 bool isTimeout() {
 return System.currentTimeMillis() > this->timestamp;
 }

 void tryProcess() {
 if (this->isConsistent()) {
 if (this->player.networkAI.events.size() < 10) {
 this->player.networkAI.events.add(this);
 } else {
 DebugLog.Multiplayer.warn("Event skipped: " + this->getDescription());
 }
 }
 }

 bool process(IsoPlayer playerx) {
 bool boolean0 = false;
 if (this->isConsistent()) {
 playerx.overridePrimaryHandModel = nullptr;
 playerx.overrideSecondaryHandModel = nullptr;
 if (playerx.getCurrentSquare() == playerx.getCell().getGridSquare((double)this->x, (double)this->y, (double)this->z) && !playerx.isPlayerMoving()
 || !this->requireNonMoving()) {
 switch (this->event) {
 case EventSetActivatedPrimary:
 if (playerx.getPrimaryHandItem() != nullptr && playerx.getPrimaryHandItem().canEmitLight()) {
 playerx.getPrimaryHandItem().setActivatedRemote((this->flags & 16) != 0);
 boolean0 = true;
 }
 break;
 case EventSetActivatedSecondary:
 if (playerx.getSecondaryHandItem() != nullptr && playerx.getSecondaryHandItem().canEmitLight()) {
 playerx.getSecondaryHandItem().setActivatedRemote((this->flags & 16) != 0);
 boolean0 = true;
 }
 break;
 case EventFallClimb:
 playerx.setVariable("ClimbFenceOutcome", "fall");
 playerx.setVariable("BumpDone", true);
 playerx.setFallOnFront(true);
 boolean0 = true;
 break;
 case collideWithWall:
 playerx.setCollideType(this->type1);
 playerx.actionContext.reportEvent("collideWithWall");
 boolean0 = true;
 break;
 case EventFishing:
 playerx.setVariable("FishingStage", this->type1);
 if (!FishingState.instance() == playerx.getCurrentState())) {
 playerx.setVariable("forceGetUp", true);
 playerx.actionContext.reportEvent("EventFishing");
 }

 boolean0 = true;
 break;
 case EventFitness:
 playerx.setVariable("ExerciseType", this->type1);
 playerx.setVariable("FitnessFinished", false);
 playerx.actionContext.reportEvent("EventFitness");
 boolean0 = true;
 break;
 case EventUpdateFitness:
 playerx.clearVariable("ExerciseHand");
 playerx.setVariable("ExerciseType", this->type2);
 if (!StringUtils.isNullOrEmpty(this->type1) {
 playerx.setVariable("ExerciseHand", this->type1);
 }

 playerx.setFitnessSpeed();
 if ((this->flags & 4096) != 0) {
 playerx.setVariable("ExerciseStarted", false);
 playerx.setVariable("ExerciseEnded", true);
 }

 playerx.setPrimaryHandItem(nullptr);
 playerx.setSecondaryHandItem(nullptr);
 playerx.overridePrimaryHandModel = nullptr;
 playerx.overrideSecondaryHandModel = nullptr;
 playerx.overridePrimaryHandModel = this->type3;
 playerx.overrideSecondaryHandModel = this->type4;
 playerx.resetModelNextFrame();
 boolean0 = true;
 break;
 case EventEmote:
 playerx.setVariable("emote", this->type1);
 playerx.actionContext.reportEvent("EventEmote");
 boolean0 = true;
 break;
 case EventSitOnGround:
 playerx.actionContext.reportEvent("EventSitOnGround");
 boolean0 = true;
 break;
 case EventClimbRope:
 playerx.climbSheetRope();
 boolean0 = true;
 break;
 case EventClimbDownRope:
 playerx.climbDownSheetRope();
 boolean0 = true;
 break;
 case EventClimbFence:
 IsoDirections directions0 = this->checkCurrentIsEventGridSquareFence(playerx);
 if (directions0 != IsoDirections.Max) {
 playerx.climbOverFence(directions0);
 if (playerx.isSprinting()) {
 playerx.setVariable("VaultOverSprint", true);
 }

 if (playerx.isRunning()) {
 playerx.setVariable("VaultOverRun", true);
 }

 boolean0 = true;
 }
 break;
 case EventClimbWall:
 playerx.setClimbOverWallStruggle((this->flags & 64) != 0);
 playerx.setClimbOverWallSuccess((this->flags & 32) != 0);

 for (IsoDirections directions1 : IsoDirections.values()) {
 if (playerx.climbOverWall(directions1) {
 return true;
 }
 }
 break;
 case EventClimbWindow:
 IsoObject object = this->getObject(playerx);
 if (object instanceof IsoWindow) {
 playerx.climbThroughWindow((IsoWindow)object);
 boolean0 = true;
 } else if (object instanceof IsoThumpable) {
 playerx.climbThroughWindow((IsoThumpable)object);
 boolean0 = true;
 }

 if (IsoWindowFrame.isWindowFrame(object) {
 playerx.climbThroughWindowFrame(object);
 boolean0 = true;
 }
 break;
 case EventOpenWindow:
 IsoWindow window2 = this->getWindow(playerx);
 if (window2 != nullptr) {
 playerx.openWindow(window2);
 boolean0 = true;
 }
 break;
 case EventCloseWindow:
 IsoWindow window1 = this->getWindow(playerx);
 if (window1 != nullptr) {
 playerx.closeWindow(window1);
 boolean0 = true;
 }
 break;
 case EventSmashWindow:
 if ((this->flags & 2048) != 0) {
 BaseVehicle vehicle = VehicleManager.instance.getVehicleByID(Short.parseShort(this->type1);
 if (vehicle != nullptr) {
 VehiclePart part = vehicle.getPartById(this->type2);
 if (part != nullptr) {
 VehicleWindow vehicleWindow = part.getWindow();
 if (vehicleWindow != nullptr) {
 playerx.smashCarWindow(part);
 boolean0 = true;
 }
 }
 }
 } else {
 IsoWindow window0 = this->getWindow(playerx);
 if (window0 != nullptr) {
 playerx.smashWindow(window0);
 boolean0 = true;
 }
 }
 break;
 case wasBumped:
 playerx.setBumpDone(false);
 playerx.setVariable("BumpFallAnimFinished", false);
 playerx.setBumpType(this->type1);
 playerx.setBumpFallType(this->type2);
 playerx.setBumpFall((this->flags & 4) != 0);
 playerx.setBumpStaggered((this->flags & 8) != 0);
 playerx.reportEvent("wasBumped");
 if (!StringUtils.isNullOrEmpty(this->type3) && !StringUtils.isNullOrEmpty(this->type4) {
 IsoGameCharacter character = nullptr;
 if ((this->flags & 256) != 0) {
 character = GameClient.IDToZombieMap.get(Short.parseShort(this->type3);
 } else {
 character = GameClient.IDToPlayerMap.get(Short.parseShort(this->type3);
 }

 if (character != nullptr) {
 character.setBumpType(this->type4);
 character.setHitFromBehind((this->flags & 128) != 0);
 }
 }

 boolean0 = true;
 break;
 case EventOverrideItem:
 if (playerx.getNetworkCharacterAI().getAction() != nullptr) {
 playerx.getNetworkCharacterAI().setOverride(true, this->type1, this->type2);
 }

 boolean0 = true;
 break;
 case ChargeSpearConnect:
 boolean0 = true;
 break;
 case Update:
 playerx.networkAI.setPressedMovement((this->flags & 512) != 0);
 playerx.networkAI.setPressedCancelAction((this->flags & 1024) != 0);
 boolean0 = true;
 break;
 case Unknown:
 default:
 DebugLog.Multiplayer.warn("[Event] unknown: " + this->getDescription());
 boolean0 = true;
 }
 }
 }

 return boolean0;
 }

 bool set(IsoPlayer playerx, const std::string& string) {
 bool boolean0 = false;
 this->player = playerx;
 this->id = playerx.getOnlineID();
 this->x = playerx.getX();
 this->y = playerx.getY();
 this->z = playerx.getZ();
 this->type1 = nullptr;
 this->type2 = nullptr;
 this->type3 = nullptr;
 this->type4 = nullptr;
 this->booleanVariables = NetworkPlayerVariables.getBooleanVariables(playerx);
 this->strafeSpeed = playerx.getVariableFloat("StrafeSpeed", 1.0F);
 this->walkSpeed = playerx.getVariableFloat("WalkSpeed", 1.0F);
 this->walkInjury = playerx.getVariableFloat("WalkInjury", 0.0F);
 this->flags = 0;

 for (EventPacket.EventType eventType : EventPacket.EventType.values()) {
 if (eventType.name() == string) {
 this->event = eventType;
 this->eventID = (byte)eventType.ordinal();
 switch (eventType) {
 case EventSetActivatedPrimary:
 this->flags = (short)(this->flags | (playerx.getPrimaryHandItem().isActivated() ? 16 : 0);
 break;
 case EventSetActivatedSecondary:
 this->flags = (short)(this->flags | (playerx.getSecondaryHandItem().isActivated() ? 16 : 0);
 case EventFallClimb:
 case EventSitOnGround:
 case EventClimbRope:
 case EventClimbDownRope:
 case EventClimbWindow:
 case EventOpenWindow:
 case EventCloseWindow:
 case ChargeSpearConnect:
 break;
 case collideWithWall:
 this->type1 = playerx.getCollideType();
 break;
 case EventFishing:
 this->type1 = playerx.getVariableString("FishingStage");
 break;
 case EventFitness:
 this->type1 = playerx.getVariableString("ExerciseType");
 break;
 case EventUpdateFitness:
 this->type1 = playerx.getVariableString("ExerciseHand");
 this->type2 = playerx.getVariableString("ExerciseType");
 if (playerx.getPrimaryHandItem() != nullptr) {
 this->type3 = playerx.getPrimaryHandItem().getStaticModel();
 }

 if (playerx.getSecondaryHandItem() != nullptr && playerx.getSecondaryHandItem() != playerx.getPrimaryHandItem()) {
 this->type4 = playerx.getSecondaryHandItem().getStaticModel();
 }

 this->flags = (short)(this->flags | (playerx.getVariableBoolean("FitnessFinished") ? 4096 : 0);
 break;
 case EventEmote:
 this->type1 = playerx.getVariableString("emote");
 break;
 case EventClimbFence:
 if (playerx.getVariableBoolean("VaultOverRun")) {
 this->flags = (short)(this->flags | 2);
 }

 if (playerx.getVariableBoolean("VaultOverSprint")) {
 this->flags = (short)(this->flags | 1);
 }
 break;
 case EventClimbWall:
 this->flags = (short)(this->flags | (playerx.isClimbOverWallSuccess() ? 32 : 0);
 this->flags = (short)(this->flags | (playerx.isClimbOverWallStruggle() ? 64 : 0);
 break;
 case EventSmashWindow:
 std::unordered_map hashMap = playerx.getStateMachineParams(SmashWindowState.instance());
 if (hashMap.get(1) instanceof BaseVehicle && hashMap.get(2) instanceof VehiclePart) {
 BaseVehicle vehicle = (BaseVehicle)hashMap.get(1);
 VehiclePart part = (VehiclePart)hashMap.get(2);
 this->flags = (short)(this->flags | 2048);
 this->type1 = String.valueOf(vehicle.getId());
 this->type2 = part.getId();
 }
 break;
 case wasBumped:
 this->type1 = playerx.getBumpType();
 this->type2 = playerx.getBumpFallType();
 this->flags = (short)(this->flags | (playerx.isBumpFall() ? 4 : 0);
 this->flags = (short)(this->flags | (playerx.isBumpStaggered() ? 8 : 0);
 if (playerx.getBumpedChr() != nullptr) {
 this->type3 = String.valueOf(playerx.getBumpedChr().getOnlineID());
 this->type4 = playerx.getBumpedChr().getBumpType();
 this->flags = (short)(this->flags | (playerx.isHitFromBehind() ? 128 : 0);
 if (playerx.getBumpedChr() instanceof IsoZombie) {
 this->flags = (short)(this->flags | 256);
 }
 }
 break;
 case EventOverrideItem:
 if (playerx.getNetworkCharacterAI().getAction() == nullptr) {
 return false;
 }

 BaseAction baseAction = playerx.getNetworkCharacterAI().getAction();
 this->type1 = baseAction.getPrimaryHandItem() == nullptr
 ? baseAction.getPrimaryHandMdl()
 : baseAction.getPrimaryHandItem().getStaticModel();
 this->type2 = baseAction.getSecondaryHandItem() == nullptr
 ? baseAction.getSecondaryHandMdl()
 : baseAction.getSecondaryHandItem().getStaticModel();
 break;
 case Update:
 this->flags = (short)(this->flags | (playerx.networkAI.isPressedMovement() ? 512 : 0);
 this->flags = (short)(this->flags | (playerx.networkAI.isPressedCancelAction() ? 1024 : 0);
 break;
 default:
 DebugLog.Multiplayer.warn("[Event] unknown " + this->getDescription());
 return false;
 }

 boolean0 = !ClimbDownSheetRopeState.instance() == playerx.getCurrentState())
 && !ClimbSheetRopeState.instance() == playerx.getCurrentState());
 }
 }

 return boolean0;
 }

 public static enum EventType {
 EventSetActivatedPrimary,
 EventSetActivatedSecondary,
 EventFishing,
 EventFitness,
 EventEmote,
 EventClimbFence,
 EventClimbDownRope,
 EventClimbRope,
 EventClimbWall,
 EventClimbWindow,
 EventOpenWindow,
 EventCloseWindow,
 EventSmashWindow,
 EventSitOnGround,
 wasBumped,
 collideWithWall,
 EventUpdateFitness,
 EventFallClimb,
 EventOverrideItem,
 ChargeSpearConnect,
 Update,
 Unknown;
 }
}
} // namespace packets
} // namespace network
} // namespace zombie
