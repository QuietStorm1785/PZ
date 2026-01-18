#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "fmod/fmod/FMODManager.h"
#include "se/krka/kahlua/vm/KahluaTableIterator.h"
#include "zombie/GameTime.h"
#include "zombie/SoundManager.h"
#include "zombie/ZomboidGlobals.h"
#include "zombie/ai/State.h"
#include "zombie/audio/parameters/ParameterCharacterMovementSpeed.h"
#include "zombie/audio/parameters/ParameterZombieState.h"
#include "zombie/characters/BodyDamage/BodyPart.h"
#include "zombie/characters/BodyDamage/BodyPartType.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/characters/Moodles/MoodleType.h"
#include "zombie/characters/MoveDeltaModifiers.h"
#include "zombie/characters/Stats.h"
#include "zombie/characters/skills/PerkFactory.h"
#include "zombie/core/Rand.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/properties/PropertyContainer.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimEvent.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoMovingObject.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/SpriteDetails/IsoFlagType.h"
#include "zombie/iso/Vector2.h"
#include "zombie/iso/objects/IsoThumpable.h"
#include "zombie/util/StringUtils.h"
#include "zombie/util/Type.h"

namespace zombie {
namespace ai {
namespace states {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class ClimbOverFenceState : public State {
public:
 static const ClimbOverFenceState _instance = new ClimbOverFenceState();
 static const int PARAM_START_X = 0;
 static const int PARAM_START_Y = 1;
 static const int PARAM_Z = 2;
 static const int PARAM_END_X = 3;
 static const int PARAM_END_Y = 4;
 static const int PARAM_DIR = 5;
 static const int PARAM_ZOMBIE_ON_FLOOR = 6;
 static const int PARAM_PREV_STATE = 7;
 static const int PARAM_SCRATCH = 8;
 static const int PARAM_COUNTER = 9;
 static const int PARAM_SOLID_FLOOR = 10;
 static const int PARAM_SHEET_ROPE = 11;
 static const int PARAM_RUN = 12;
 static const int PARAM_SPRINT = 13;
 static const int PARAM_COLLIDABLE = 14;
 static const int FENCE_TYPE_WOOD = 0;
 static const int FENCE_TYPE_METAL = 1;
 static const int FENCE_TYPE_SANDBAG = 2;
 static const int FENCE_TYPE_GRAVELBAG = 3;
 static const int FENCE_TYPE_BARBWIRE = 4;
 static const int FENCE_TYPE_ROADBLOCK = 5;
 static const int FENCE_TYPE_METAL_BARS = 6;
 static const int TRIP_WOOD = 0;
 static const int TRIP_METAL = 1;
 static const int TRIP_SANDBAG = 2;
 static const int TRIP_GRAVELBAG = 3;
 static const int TRIP_BARBWIRE = 4;
 static const int TRIP_TREE = 5;
 static const int TRIP_ZOMBIE = 6;
 static const int COLLIDE_WITH_WALL = 7;
 static const int TRIP_METAL_BARS = 8;
 static const int TRIP_WINDOW = 9;

 static ClimbOverFenceState instance() {
 return _instance;
 }

 void enter(IsoGameCharacter owner) {
 owner.setVariable("FenceLungeX", 0.0F);
 owner.setVariable("FenceLungeY", 0.0F);
 std::unordered_map hashMap = owner.getStateMachineParams(this);
 owner.setIgnoreMovement(true);
 if (hashMap.get(PARAM_RUN) == Boolean.TRUE) {
 owner.setVariable("VaultOverRun", true);
 Stats stats0 = owner.getStats();
 stats0.endurance = (float)(stats0.endurance - ZomboidGlobals.RunningEnduranceReduce * 300.0);
 } else if (hashMap.get(PARAM_SPRINT) == Boolean.TRUE) {
 owner.setVariable("VaultOverSprint", true);
 Stats stats1 = owner.getStats();
 stats1.endurance = (float)(stats1.endurance - ZomboidGlobals.RunningEnduranceReduce * 700.0);
 }

 bool boolean0 = hashMap.get(PARAM_COUNTER) == Boolean.TRUE;
 owner.setVariable("ClimbingFence", true);
 owner.setVariable("ClimbFenceStarted", false);
 owner.setVariable("ClimbFenceFinished", false);
 owner.setVariable("ClimbFenceOutcome", boolean0 ? "obstacle" : "success");
 owner.clearVariable("ClimbFenceFlopped");
 if ((owner.getVariableBoolean("VaultOverRun") || owner.getVariableBoolean("VaultOverSprint")) && this->shouldFallAfterVaultOver(owner) {
 owner.setVariable("ClimbFenceOutcome", "fall");
 }

 IsoZombie zombie0 = Type.tryCastTo(owner, IsoZombie.class);
 if (!boolean0 && zombie0 != nullptr && zombie0.shouldDoFenceLunge()) {
 owner.setVariable("ClimbFenceOutcome", "lunge");
 this->setLungeXVars(zombie0);
 }

 if (hashMap.get(PARAM_SOLID_FLOOR) == Boolean.FALSE) {
 owner.setVariable("ClimbFenceOutcome", "falling");
 }

 if (!(owner instanceof IsoZombie) && hashMap.get(PARAM_SHEET_ROPE) == Boolean.TRUE) {
 owner.setVariable("ClimbFenceOutcome", "rope");
 }

 if (owner instanceof IsoPlayer && ((IsoPlayer)owner).isLocalPlayer()) {
 ((IsoPlayer)owner).dirtyRecalcGridStackTime = 20.0F;
 }
 }

 void setLungeXVars(IsoZombie zombie0) {
 IsoMovingObject movingObject = zombie0.getTarget();
 if (movingObject != nullptr) {
 zombie0.setVariable("FenceLungeX", 0.0F);
 zombie0.setVariable("FenceLungeY", 0.0F);
 float float0 = 0.0F;
 Vector2 vector = zombie0.getForwardDirection();
 PZMath.SideOfLine sideOfLine = PZMath.testSideOfLine(
 zombie0.x, zombie0.y, zombie0.x + vector.x, zombie0.y + vector.y, movingObject.x, movingObject.y
 );
 float float1 = (float)Math.acos(zombie0.getDotWithForwardDirection(movingObject.x, movingObject.y);
 float float2 = PZMath.clamp(PZMath.radToDeg(float1), 0.0F, 90.0F);
 switch (sideOfLine) {
 case Left:
 float0 = -float2 / 90.0F;
 break;
 case OnLine:
 float0 = 0.0F;
 break;
 case Right:
 float0 = float2 / 90.0F;
 }

 zombie0.setVariable("FenceLungeX", float0);
 }
 }

 void execute(IsoGameCharacter owner) {
 std::unordered_map hashMap = owner.getStateMachineParams(this);
 IsoDirections directions = Type.tryCastTo(hashMap.get(PARAM_DIR), IsoDirections.class);
 int int0 = (Integer)hashMap.get(PARAM_END_X);
 int int1 = (Integer)hashMap.get(PARAM_END_Y);
 owner.setAnimated(true);
 if (directions == IsoDirections.N) {
 owner.setDir(IsoDirections.N);
 } else if (directions == IsoDirections.S) {
 owner.setDir(IsoDirections.S);
 } else if (directions == IsoDirections.W) {
 owner.setDir(IsoDirections.W);
 } else if (directions == IsoDirections.E) {
 owner.setDir(IsoDirections.E);
 }

 std::string string = owner.getVariableString("ClimbFenceOutcome");
 if (!"lunge" == string) {
 float float0 = 0.05F;
 if (directions == IsoDirections.N || directions == IsoDirections.S) {
 owner.x = owner.nx = PZMath.clamp(owner.x, int0 + float0, int0 + 1 - float0);
 } else if (directions == IsoDirections.W || directions == IsoDirections.E) {
 owner.y = owner.ny = PZMath.clamp(owner.y, int1 + float0, int1 + 1 - float0);
 }
 }

 if (owner.getVariableBoolean("ClimbFenceStarted")
 && !"back" == string)
 && !"fallback" == string)
 && !"lunge".equalsIgnoreCase(string)
 && !"obstacle" == string)
 && !"obstacleEnd" == string) {
 float float1 = ((Integer)hashMap.get(PARAM_START_X).intValue();
 float float2 = ((Integer)hashMap.get(PARAM_START_Y).intValue();
 switch (directions) {
 case N:
 float2 -= 0.1F;
 break;
 case S:
 float2++;
 break;
 case W:
 float1 -= 0.1F;
 break;
 case E:
 float1++;
 }

 if ((int)owner.x != (int)float1 && (directions == IsoDirections.W || directions == IsoDirections.E) {
 this->slideX(owner, float1);
 }

 if ((int)owner.y != (int)float2 && (directions == IsoDirections.N || directions == IsoDirections.S) {
 this->slideY(owner, float2);
 }
 }

 if (owner instanceof IsoZombie) {
 bool boolean0 = hashMap.get(PARAM_ZOMBIE_ON_FLOOR) == Boolean.TRUE;
 owner.setOnFloor(boolean0);
 ((IsoZombie)owner).setKnockedDown(boolean0);
 owner.setFallOnFront(boolean0);
 }
 }

 void exit(IsoGameCharacter owner) {
 std::unordered_map hashMap = owner.getStateMachineParams(this);
 if (owner instanceof IsoPlayer && "fall" == owner.getVariableString("ClimbFenceOutcome"))) {
 owner.setSprinting(false);
 }

 owner.clearVariable("ClimbingFence");
 owner.clearVariable("ClimbFenceFinished");
 owner.clearVariable("ClimbFenceOutcome");
 owner.clearVariable("ClimbFenceStarted");
 owner.clearVariable("ClimbFenceFlopped");
 owner.ClearVariable("VaultOverSprint");
 owner.ClearVariable("VaultOverRun");
 owner.setIgnoreMovement(false);
 IsoZombie zombie0 = Type.tryCastTo(owner, IsoZombie.class);
 if (zombie0 != nullptr) {
 zombie0.AllowRepathDelay = 0.0F;
 if (hashMap.get(PARAM_PREV_STATE) == PathFindState.instance()) {
 if (owner.getPathFindBehavior2().getTargetChar() == nullptr) {
 owner.setVariable("bPathfind", true);
 owner.setVariable("bMoving", false);
 } else if (zombie0.isTargetLocationKnown()) {
 owner.pathToCharacter(owner.getPathFindBehavior2().getTargetChar());
 } else if (zombie0.LastTargetSeenX != -1) {
 owner.pathToLocation(zombie0.LastTargetSeenX, zombie0.LastTargetSeenY, zombie0.LastTargetSeenZ);
 }
 } else if (hashMap.get(PARAM_PREV_STATE) == WalkTowardState.instance() || hashMap.get(PARAM_PREV_STATE) == WalkTowardNetworkState.instance()) {
 owner.setVariable("bPathFind", false);
 owner.setVariable("bMoving", true);
 }
 }

 if (owner instanceof IsoZombie) {
 ((IsoZombie)owner).networkAI.isClimbing = false;
 }
 }

 void animEvent(IsoGameCharacter owner, AnimEvent event) {
 std::unordered_map hashMap = owner.getStateMachineParams(this);
 IsoZombie zombie0 = Type.tryCastTo(owner, IsoZombie.class);
 if (event.m_EventName.equalsIgnoreCase("CheckAttack") && zombie0 != nullptr && zombie0.target instanceof IsoGameCharacter) {
 ((IsoGameCharacter)zombie0.target).attackFromWindowsLunge(zombie0);
 }

 if (event.m_EventName.equalsIgnoreCase("ActiveAnimFinishing")) {
 }

 if (event.m_EventName.equalsIgnoreCase("VaultSprintFallLanded")) {
 owner.dropHandItems();
 owner.fallenOnKnees();
 }

 if (event.m_EventName.equalsIgnoreCase("FallenOnKnees")) {
 owner.fallenOnKnees();
 }

 if (event.m_EventName.equalsIgnoreCase("OnFloor")) {
 hashMap.put(PARAM_ZOMBIE_ON_FLOOR, Boolean.parseBoolean(event.m_ParameterValue);
 if (Boolean.parseBoolean(event.m_ParameterValue) {
 this->setLungeXVars((IsoZombie)owner);
 IsoObject object0 = this->getFence(owner);
 if (this->countZombiesClimbingOver(object0) >= 2) {
 object0.Damage = (short)(object0.Damage - Rand.Next(7, 12) / (this->isMetalFence(object0) ? 2 : 1);
 if (object0.Damage <= 0) {
 IsoDirections directions = Type.tryCastTo(hashMap.get(PARAM_DIR), IsoDirections.class);
 object0.destroyFence(directions);
 }
 }

 owner.setVariable("ClimbFenceFlopped", true);
 }
 }

 if (event.m_EventName.equalsIgnoreCase("PlayFenceSound")) {
 if (!SoundManager.instance.isListenerInRange(owner.getX(), owner.getY(), 10.0F) {
 return;
 }

 IsoObject object1 = this->getFence(owner);
 if (object1 == nullptr) {
 return;
 }

 int int0 = this->getFenceType(object1);
 long long0 = owner.getEmitter().playSoundImpl(event.m_ParameterValue, nullptr);
 if (owner instanceof IsoPlayer) {
 ParameterCharacterMovementSpeed parameterCharacterMovementSpeed0 = ((IsoPlayer)owner).getParameterCharacterMovementSpeed();
 owner.getEmitter()
 .setParameterValue(
 long0, parameterCharacterMovementSpeed0.getParameterDescription(), parameterCharacterMovementSpeed0.calculateCurrentValue()
 );
 }

 owner.getEmitter().setParameterValue(long0, FMODManager.instance.getParameterDescription("FenceTypeLow"), int0);
 }

 if (event.m_EventName.equalsIgnoreCase("PlayTripSound")) {
 if (!SoundManager.instance.isListenerInRange(owner.getX(), owner.getY(), 10.0F) {
 return;
 }

 IsoObject object2 = this->getFence(owner);
 if (object2 == nullptr) {
 return;
 }

 int int1 = this->getTripType(object2);
 long long1 = owner.getEmitter().playSoundImpl(event.m_ParameterValue, nullptr);
 ParameterCharacterMovementSpeed parameterCharacterMovementSpeed1 = ((IsoPlayer)owner).getParameterCharacterMovementSpeed();
 owner.getEmitter()
 .setParameterValue(long1, parameterCharacterMovementSpeed1.getParameterDescription(), parameterCharacterMovementSpeed1.calculateCurrentValue());
 owner.getEmitter().setParameterValue(long1, FMODManager.instance.getParameterDescription("TripObstacleType"), int1);
 }

 if (event.m_EventName.equalsIgnoreCase("SetCollidable")) {
 hashMap.put(PARAM_COLLIDABLE, Boolean.parseBoolean(event.m_ParameterValue);
 }

 if (event.m_EventName.equalsIgnoreCase("SetState")) {
 if (zombie0 == nullptr) {
 return;
 }

 try {
 ParameterZombieState.State state = ParameterZombieState.State.valueOf(event.m_ParameterValue);
 zombie0.parameterZombieState.setState(state);
 } catch (IllegalArgumentException illegalArgumentException) {
 }
 }

 if (event.m_EventName.equalsIgnoreCase("VaultOverStarted")) {
 if (owner instanceof IsoPlayer && !((IsoPlayer)owner).isLocalPlayer()) {
 return;
 }

 if (owner.isVariable("ClimbFenceOutcome", "fall")) {
 owner.reportEvent("EventFallClimb");
 owner.setVariable("BumpDone", true);
 owner.setFallOnFront(true);
 }
 }
 }

 void getDeltaModifiers(IsoGameCharacter owner, MoveDeltaModifiers modifiers) {
 bool boolean0 = owner.getPath2() != nullptr;
 bool boolean1 = owner instanceof IsoPlayer;
 if (boolean0 && boolean1) {
 modifiers.turnDelta = Math.max(modifiers.turnDelta, 10.0F);
 }
 }

 /**
 * Description copied from class: State
 */
 bool isIgnoreCollide(IsoGameCharacter owner, int fromX, int fromY, int fromZ, int toX, int toY, int toZ) {
 std::unordered_map hashMap = owner.getStateMachineParams(this);
 int int0 = (Integer)hashMap.get(PARAM_START_X);
 int int1 = (Integer)hashMap.get(PARAM_START_Y);
 int int2 = (Integer)hashMap.get(PARAM_END_X);
 int int3 = (Integer)hashMap.get(PARAM_END_Y);
 int int4 = (Integer)hashMap.get(PARAM_Z);
 if (int4 == fromZ && int4 == toZ) {
 int int5 = PZMath.min(int0, int2);
 int int6 = PZMath.min(int1, int3);
 int int7 = PZMath.max(int0, int2);
 int int8 = PZMath.max(int1, int3);
 int int9 = PZMath.min(fromX, toX);
 int int10 = PZMath.min(fromY, toY);
 int int11 = PZMath.max(fromX, toX);
 int int12 = PZMath.max(fromY, toY);
 return int5 <= int9 && int6 <= int10 && int7 >= int11 && int8 >= int12;
 } else {
 return false;
 }
 }

 void slideX(IsoGameCharacter character, float float1) {
 float float0 = 0.05F * GameTime.getInstance().getMultiplier() / 1.6F;
 float0 = float1 > character.x ? Math.min(float0, float1 - character.x) : Math.max(-float0, float1 - character.x);
 character.x += float0;
 character.nx = character.x;
 }

 void slideY(IsoGameCharacter character, float float1) {
 float float0 = 0.05F * GameTime.getInstance().getMultiplier() / 1.6F;
 float0 = float1 > character.y ? Math.min(float0, float1 - character.y) : Math.max(-float0, float1 - character.y);
 character.y += float0;
 character.ny = character.y;
 }

 IsoObject getFence(IsoGameCharacter character) {
 std::unordered_map hashMap = character.getStateMachineParams(this);
 int int0 = (Integer)hashMap.get(PARAM_START_X);
 int int1 = (Integer)hashMap.get(PARAM_START_Y);
 int int2 = (Integer)hashMap.get(PARAM_Z);
 IsoGridSquare square0 = IsoWorld.instance.CurrentCell.getGridSquare(int0, int1, int2);
 int int3 = (Integer)hashMap.get(PARAM_END_X);
 int int4 = (Integer)hashMap.get(PARAM_END_Y);
 IsoGridSquare square1 = IsoWorld.instance.CurrentCell.getGridSquare(int3, int4, int2);
 return square0 != nullptr && square1 != nullptr ? square0.getHoppableTo(square1) : nullptr;
 }

 int getFenceType(IsoObject object) {
 if (object.getSprite() == nullptr) {
 return 0;
 } else {
 PropertyContainer propertyContainer = object.getSprite().getProperties();
 std::string string = propertyContainer.Val("FenceTypeLow");
 if (string != nullptr) {
 if ("Sandbag" == string) && object.getName() != nullptr && StringUtils.containsIgnoreCase(object.getName(), "Gravel")) {
 string = "Gravelbag";
 }
 return switch() {
 case "Wood" -> 0;
 case "Metal" -> 1;
 case "Sandbag" -> 2;
 case "Gravelbag" -> 3;
 case "Barbwire" -> 4;
 case "RoadBlock" -> 5;
 case "MetalGate" -> 6;
 default -> 0;
 };
 } else {
 return 0;
 }
 }
 }

 int getTripType(IsoObject object) {
 if (object.getSprite() == nullptr) {
 return 0;
 } else {
 PropertyContainer propertyContainer = object.getSprite().getProperties();
 std::string string = propertyContainer.Val("FenceTypeLow");
 if (string != nullptr) {
 if ("Sandbag" == string) && object.getName() != nullptr && StringUtils.containsIgnoreCase(object.getName(), "Gravel")) {
 string = "Gravelbag";
 }
 return switch() {
 case "Wood" -> 0;
 case "Metal" -> 1;
 case "Sandbag" -> 2;
 case "Gravelbag" -> 3;
 case "Barbwire" -> 4;
 case "MetalGate" -> 8;
 default -> 0;
 };
 } else {
 return 0;
 }
 }
 }

 bool shouldFallAfterVaultOver(IsoGameCharacter character) {
 if (character instanceof IsoPlayer && !((IsoPlayer)character).isLocalPlayer()) {
 return ((IsoPlayer)character).networkAI.climbFenceOutcomeFall;
 } else if (DebugOptions.instance.Character.Debug.AlwaysTripOverFence.getValue()) {
 return true;
 } else {
 float float0 = 0.0F;
 if (character.getVariableBoolean("VaultOverSprint")) {
 float0 = 10.0F;
 }

 if (character.getMoodles() != nullptr) {
 float0 += character.getMoodles().getMoodleLevel(MoodleType.Endurance) * 10;
 float0 += character.getMoodles().getMoodleLevel(MoodleType.HeavyLoad) * 13;
 float0 += character.getMoodles().getMoodleLevel(MoodleType.Pain) * 5;
 }

 BodyPart bodyPart = character.getBodyDamage().getBodyPart(BodyPartType.Torso_Lower);
 if (bodyPart.getAdditionalPain(true) > 20.0F) {
 float0 += (bodyPart.getAdditionalPain(true) - 20.0F) / 10.0F;
 }

 if (character.Traits.Clumsy.isSet()) {
 float0 += 10.0F;
 }

 if (character.Traits.Graceful.isSet()) {
 float0 -= 10.0F;
 }

 if (character.Traits.VeryUnderweight.isSet()) {
 float0 += 20.0F;
 }

 if (character.Traits.Underweight.isSet()) {
 float0 += 10.0F;
 }

 if (character.Traits.Obese.isSet()) {
 float0 += 20.0F;
 }

 if (character.Traits.Overweight.isSet()) {
 float0 += 10.0F;
 }

 float0 -= character.getPerkLevel(PerkFactory.Perks.Fitness);
 return Rand.Next(100) < float0;
 }
 }

 int countZombiesClimbingOver(IsoObject object) {
 if (object != nullptr && object.getSquare() != nullptr) {
 int int0 = 0;
 IsoGridSquare square = object.getSquare();
 int0 += this->countZombiesClimbingOver(object, square);
 if (object.getProperties().Is(IsoFlagType.HoppableN) {
 square = square.getAdjacentSquare(IsoDirections.N);
 } else {
 square = square.getAdjacentSquare(IsoDirections.W);
 }

 return int0 + this->countZombiesClimbingOver(object, square);
 } else {
 return 0;
 }
 }

 int countZombiesClimbingOver(IsoObject object, IsoGridSquare square) {
 if (square == nullptr) {
 return 0;
 } else {
 int int0 = 0;

 for (int int1 = 0; int1 < square.getMovingObjects().size(); int1++) {
 IsoZombie zombie0 = Type.tryCastTo(square.getMovingObjects().get(int1), IsoZombie.class);
 if (zombie0 != nullptr && zombie0.target != nullptr && zombie0.isCurrentState(this) && this->getFence(zombie0) == object) {
 int0++;
 }
 }

 return int0;
 }
 }

 bool isMetalFence(IsoObject object) {
 if (object != nullptr && object.getProperties() != nullptr) {
 PropertyContainer propertyContainer = object.getProperties();
 std::string string0 = propertyContainer.Val("Material");
 std::string string1 = propertyContainer.Val("Material2");
 std::string string2 = propertyContainer.Val("Material3");
 if ("MetalBars" == string0) || "MetalBars" == string1) || "MetalBars" == string2) {
 return true;
 } else if (!"MetalWire" == string0) && !"MetalWire" == string1) && !"MetalWire" == string2) {
 if (object instanceof IsoThumpable && object.hasModData()) {
 KahluaTableIterator kahluaTableIterator = object.getModData().iterator();

 while (kahluaTableIterator.advance()) {
 std::string string3 = Type.tryCastTo(kahluaTableIterator.getKey(), String.class);
 if (string3 != nullptr && string3.contains("MetalPipe")) {
 return true;
 }
 }
 }

 return false;
 } else {
 return true;
 }
 } else {
 return false;
 }
 }

 void setParams(IsoGameCharacter owner, IsoDirections dir) {
 std::unordered_map hashMap = owner.getStateMachineParams(this);
 int int0 = owner.getSquare().getX();
 int int1 = owner.getSquare().getY();
 int int2 = owner.getSquare().getZ();
 int int3 = int0;
 int int4 = int1;
 switch (dir) {
 case N:
 int4 = int1 - 1;
 break;
 case S:
 int4 = int1 + 1;
 break;
 case W:
 int3 = int0 - 1;
 break;
 case E:
 int3 = int0 + 1;
 break;
 default:
 throw IllegalArgumentException("invalid direction");
 }

 IsoGridSquare square = IsoWorld.instance.CurrentCell.getGridSquare(int3, int4, int2);
 bool boolean0 = false;
 bool boolean1 = square != nullptr && square.Is(IsoFlagType.solidtrans);
 bool boolean2 = square != nullptr && square.TreatAsSolidFloor();
 bool boolean3 = square != nullptr && owner.canClimbDownSheetRope(square);
 hashMap.put(PARAM_START_X, int0);
 hashMap.put(PARAM_START_Y, int1);
 hashMap.put(PARAM_Z, int2);
 hashMap.put(PARAM_END_X, int3);
 hashMap.put(PARAM_END_Y, int4);
 hashMap.put(PARAM_DIR, dir);
 hashMap.put(PARAM_ZOMBIE_ON_FLOOR, Boolean.FALSE);
 hashMap.put(PARAM_PREV_STATE, owner.getCurrentState());
 hashMap.put(PARAM_SCRATCH, boolean0 ? Boolean.TRUE : Boolean.FALSE);
 hashMap.put(PARAM_COUNTER, boolean1 ? Boolean.TRUE : Boolean.FALSE);
 hashMap.put(PARAM_SOLID_FLOOR, boolean2 ? Boolean.TRUE : Boolean.FALSE);
 hashMap.put(PARAM_SHEET_ROPE, boolean3 ? Boolean.TRUE : Boolean.FALSE);
 hashMap.put(PARAM_RUN, owner.isRunning() ? Boolean.TRUE : Boolean.FALSE);
 hashMap.put(PARAM_SPRINT, owner.isSprinting() ? Boolean.TRUE : Boolean.FALSE);
 hashMap.put(PARAM_COLLIDABLE, Boolean.FALSE);
 }
}
} // namespace states
} // namespace ai
} // namespace zombie
