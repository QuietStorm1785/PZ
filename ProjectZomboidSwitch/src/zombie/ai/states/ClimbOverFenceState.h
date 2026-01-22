#pragma once
#include <stack>
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
#include "zombie/ai/states/ClimbOverFenceState/1.h"
#include "zombie/audio/parameters/ParameterCharacterMovementSpeed.h"
#include "zombie/characters/BodyDamage/BodyPart.h"
#include "zombie/characters/BodyDamage/BodyPartType.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/characters/Moodles/MoodleType.h"
#include "zombie/characters/MoveDeltaModifiers.h"
#include "zombie/characters/Stats.h"
#include "zombie/characters/skills/PerkFactory/Perks.h"
#include "zombie/core/Rand.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/math/PZMath/SideOfLine.h"
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


class ClimbOverFenceState : public State {
public:
    static const ClimbOverFenceState _instance = std::make_shared<ClimbOverFenceState>();
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

    void enter(IsoGameCharacter var1) {
      var1.setVariable("FenceLungeX", 0.0F);
      var1.setVariable("FenceLungeY", 0.0F);
    std::unordered_map var2 = var1.getStateMachineParams(this);
      var1.setIgnoreMovement(true);
      if (var2.get(PARAM_RUN) == bool.TRUE) {
         var1.setVariable("VaultOverRun", true);
    Stats var10000 = var1.getStats();
         var10000.endurance = (float)(var10000.endurance - ZomboidGlobals.RunningEnduranceReduce * 300.0);
      } else if (var2.get(PARAM_SPRINT) == bool.TRUE) {
         var1.setVariable("VaultOverSprint", true);
    Stats var5 = var1.getStats();
         var5.endurance = (float)(var5.endurance - ZomboidGlobals.RunningEnduranceReduce * 700.0);
      }

    bool var3 = var2.get(PARAM_COUNTER) == bool.TRUE;
      var1.setVariable("ClimbingFence", true);
      var1.setVariable("ClimbFenceStarted", false);
      var1.setVariable("ClimbFenceFinished", false);
      var1.setVariable("ClimbFenceOutcome", var3 ? "obstacle" : "success");
      var1.clearVariable("ClimbFenceFlopped");
      if ((var1.getVariableBoolean("VaultOverRun") || var1.getVariableBoolean("VaultOverSprint")) && this.shouldFallAfterVaultOver(var1)) {
         var1.setVariable("ClimbFenceOutcome", "fall");
      }

    IsoZombie var4 = (IsoZombie)Type.tryCastTo(var1, IsoZombie.class);
      if (!var3 && var4 != nullptr && var4.shouldDoFenceLunge()) {
         var1.setVariable("ClimbFenceOutcome", "lunge");
         this.setLungeXVars(var4);
      }

      if (var2.get(PARAM_SOLID_FLOOR) == bool.FALSE) {
         var1.setVariable("ClimbFenceOutcome", "falling");
      }

      if (!(dynamic_cast<IsoZombie*>(var1) != nullptr) && var2.get(PARAM_SHEET_ROPE) == bool.TRUE) {
         var1.setVariable("ClimbFenceOutcome", "rope");
      }

      if (dynamic_cast<IsoPlayer*>(var1) != nullptr && ((IsoPlayer)var1).isLocalPlayer()) {
         ((IsoPlayer)var1).dirtyRecalcGridStackTime = 20.0F;
      }
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    void setLungeXVars(IsoZombie var1) {
    IsoMovingObject var2 = var1.getTarget();
      if (var2 != nullptr) {
         var1.setVariable("FenceLungeX", 0.0F);
         var1.setVariable("FenceLungeY", 0.0F);
    float var3 = 0.0F;
    Vector2 var4 = var1.getForwardDirection();
    SideOfLine var5 = PZMath.testSideOfLine(var1.x, var1.y, var1.x + var4.x, var1.y + var4.y, var2.x, var2.y);
    float var6 = (float)Math.acos(var1.getDotWithForwardDirection(var2.x, var2.y));
    float var7 = PZMath.clamp(PZMath.radToDeg(var6), 0.0F, 90.0F);
         switch (1.$SwitchMap$zombie$core$math$PZMath$SideOfLine[var5.ordinal()]) {
            case 1:
               var3 = -var7 / 90.0F;
               break;
            case 2:
               var3 = 0.0F;
               break;
            case 3:
               var3 = var7 / 90.0F;
         }

         var1.setVariable("FenceLungeX", var3);
      }
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    void execute(IsoGameCharacter var1) {
    std::unordered_map var2 = var1.getStateMachineParams(this);
    IsoDirections var3 = (IsoDirections)Type.tryCastTo(var2.get(PARAM_DIR), IsoDirections.class);
    int var4 = (int)var2.get(PARAM_END_X);
    int var5 = (int)var2.get(PARAM_END_Y);
      var1.setAnimated(true);
      if (var3 == IsoDirections.N) {
         var1.setDir(IsoDirections.N);
      } else if (var3 == IsoDirections.S) {
         var1.setDir(IsoDirections.S);
      } else if (var3 == IsoDirections.W) {
         var1.setDir(IsoDirections.W);
      } else if (var3 == IsoDirections.E) {
         var1.setDir(IsoDirections.E);
      }

    std::string var6 = var1.getVariableString("ClimbFenceOutcome");
      if (!"lunge" == var6)) {
    float var7 = 0.05F;
         if (var3 == IsoDirections.N || var3 == IsoDirections.S) {
            var1.x = var1.nx = PZMath.clamp(var1.x, var4 + var7, var4 + 1 - var7);
         } else if (var3 == IsoDirections.W || var3 == IsoDirections.E) {
            var1.y = var1.ny = PZMath.clamp(var1.y, var5 + var7, var5 + 1 - var7);
         }
      }

      if (var1.getVariableBoolean("ClimbFenceStarted")
         && !"back" == var6)
         && !"fallback" == var6)
         && !"lunge".equalsIgnoreCase(var6)
         && !"obstacle" == var6)
         && !"obstacleEnd" == var6)) {
    float var9 = ((int)var2.get(PARAM_START_X)).intValue();
    float var8 = ((int)var2.get(PARAM_START_Y)).intValue();
         switch (1.$SwitchMap$zombie$iso$IsoDirections[var3.ordinal()]) {
            case 1:
               var8 -= 0.1F;
               break;
            case 2:
               var8++;
               break;
            case 3:
               var9 -= 0.1F;
               break;
            case 4:
               var9++;
         }

         if ((int)var1.x != (int)var9 && (var3 == IsoDirections.W || var3 == IsoDirections.E)) {
            this.slideX(var1, var9);
         }

         if ((int)var1.y != (int)var8 && (var3 == IsoDirections.N || var3 == IsoDirections.S)) {
            this.slideY(var1, var8);
         }
      }

      if (dynamic_cast<IsoZombie*>(var1) != nullptr) {
    bool var10 = var2.get(PARAM_ZOMBIE_ON_FLOOR) == bool.TRUE;
         var1.setOnFloor(var10);
         ((IsoZombie)var1).setKnockedDown(var10);
         var1.setFallOnFront(var10);
      }
   }

    void exit(IsoGameCharacter var1) {
    std::unordered_map var2 = var1.getStateMachineParams(this);
      if (dynamic_cast<IsoPlayer*>(var1) != nullptr && "fall" == var1.getVariableString("ClimbFenceOutcome"))) {
         var1.setSprinting(false);
      }

      var1.clearVariable("ClimbingFence");
      var1.clearVariable("ClimbFenceFinished");
      var1.clearVariable("ClimbFenceOutcome");
      var1.clearVariable("ClimbFenceStarted");
      var1.clearVariable("ClimbFenceFlopped");
      var1.ClearVariable("VaultOverSprint");
      var1.ClearVariable("VaultOverRun");
      var1.setIgnoreMovement(false);
    IsoZombie var3 = (IsoZombie)Type.tryCastTo(var1, IsoZombie.class);
      if (var3 != nullptr) {
         var3.AllowRepathDelay = 0.0F;
         if (var2.get(PARAM_PREV_STATE) == PathFindState.instance()) {
            if (var1.getPathFindBehavior2().getTargetChar() == nullptr) {
               var1.setVariable("bPathfind", true);
               var1.setVariable("bMoving", false);
            } else if (var3.isTargetLocationKnown()) {
               var1.pathToCharacter(var1.getPathFindBehavior2().getTargetChar());
            } else if (var3.LastTargetSeenX != -1) {
               var1.pathToLocation(var3.LastTargetSeenX, var3.LastTargetSeenY, var3.LastTargetSeenZ);
            }
         } else if (var2.get(PARAM_PREV_STATE) == WalkTowardState.instance() || var2.get(PARAM_PREV_STATE) == WalkTowardNetworkState.instance()) {
            var1.setVariable("bPathFind", false);
            var1.setVariable("bMoving", true);
         }
      }

      if (dynamic_cast<IsoZombie*>(var1) != nullptr) {
         ((IsoZombie)var1).networkAI.isClimbing = false;
      }
   }

    void animEvent(IsoGameCharacter var1, AnimEvent var2) {
    std::unordered_map var3 = var1.getStateMachineParams(this);
    IsoZombie var4 = (IsoZombie)Type.tryCastTo(var1, IsoZombie.class);
      if (var2.m_EventName.equalsIgnoreCase("CheckAttack") && var4 != nullptr && var4.dynamic_cast<IsoGameCharacter*>(target) != nullptr) {
         ((IsoGameCharacter)var4.target).attackFromWindowsLunge(var4);
      }

      if (var2.m_EventName.equalsIgnoreCase("ActiveAnimFinishing")) {
      }

      if (var2.m_EventName.equalsIgnoreCase("VaultSprintFallLanded")) {
         var1.dropHandItems();
         var1.fallenOnKnees();
      }

      if (var2.m_EventName.equalsIgnoreCase("FallenOnKnees")) {
         var1.fallenOnKnees();
      }

      if (var2.m_EventName.equalsIgnoreCase("OnFloor")) {
         var3.put(PARAM_ZOMBIE_ON_FLOOR, bool.parseBoolean(var2.m_ParameterValue));
         if (bool.parseBoolean(var2.m_ParameterValue)) {
            this.setLungeXVars((IsoZombie)var1);
    IsoObject var5 = this.getFence(var1);
            if (this.countZombiesClimbingOver(var5) >= 2) {
               var5.Damage = (short)(var5.Damage - Rand.Next(7, 12) / (this.isMetalFence(var5) ? 2 : 1));
               if (var5.Damage <= 0) {
    IsoDirections var6 = (IsoDirections)Type.tryCastTo(var3.get(PARAM_DIR), IsoDirections.class);
                  var5.destroyFence(var6);
               }
            }

            var1.setVariable("ClimbFenceFlopped", true);
         }
      }

      if (var2.m_EventName.equalsIgnoreCase("PlayFenceSound")) {
         if (!SoundManager.instance.isListenerInRange(var1.getX(), var1.getY(), 10.0F)) {
            return;
         }

    IsoObject var11 = this.getFence(var1);
         if (var11 == nullptr) {
            return;
         }

    int var14 = this.getFenceType(var11);
    long var7 = var1.getEmitter().playSoundImpl(var2.m_ParameterValue, nullptr);
         if (dynamic_cast<IsoPlayer*>(var1) != nullptr) {
    ParameterCharacterMovementSpeed var9 = ((IsoPlayer)var1).getParameterCharacterMovementSpeed();
            var1.getEmitter().setParameterValue(var7, var9.getParameterDescription(), var9.calculateCurrentValue());
         }

         var1.getEmitter().setParameterValue(var7, FMODManager.instance.getParameterDescription("FenceTypeLow"), var14);
      }

      if (var2.m_EventName.equalsIgnoreCase("PlayTripSound")) {
         if (!SoundManager.instance.isListenerInRange(var1.getX(), var1.getY(), 10.0F)) {
            return;
         }

    IsoObject var12 = this.getFence(var1);
         if (var12 == nullptr) {
            return;
         }

    int var15 = this.getTripType(var12);
    long var16 = var1.getEmitter().playSoundImpl(var2.m_ParameterValue, nullptr);
    ParameterCharacterMovementSpeed var17 = ((IsoPlayer)var1).getParameterCharacterMovementSpeed();
         var1.getEmitter().setParameterValue(var16, var17.getParameterDescription(), var17.calculateCurrentValue());
         var1.getEmitter().setParameterValue(var16, FMODManager.instance.getParameterDescription("TripObstacleType"), var15);
      }

      if (var2.m_EventName.equalsIgnoreCase("SetCollidable")) {
         var3.put(PARAM_COLLIDABLE, bool.parseBoolean(var2.m_ParameterValue));
      }

      if (var2.m_EventName.equalsIgnoreCase("SetState")) {
         if (var4 == nullptr) {
            return;
         }

         try {
            zombie.audio.parameters.ParameterZombieState.State var13 = zombie.audio.parameters.ParameterZombieState.State.valueOf(var2.m_ParameterValue);
            var4.parameterZombieState.setState(var13);
         } catch (IllegalArgumentException var10) {
         }
      }

      if (var2.m_EventName.equalsIgnoreCase("VaultOverStarted")) {
         if (dynamic_cast<IsoPlayer*>(var1) != nullptr && !((IsoPlayer)var1).isLocalPlayer()) {
            return;
         }

         if (var1.isVariable("ClimbFenceOutcome", "fall")) {
            var1.reportEvent("EventFallClimb");
            var1.setVariable("BumpDone", true);
            var1.setFallOnFront(true);
         }
      }
   }

    void getDeltaModifiers(IsoGameCharacter var1, MoveDeltaModifiers var2) {
    bool var3 = var1.getPath2() != nullptr;
    bool var4 = dynamic_cast<IsoPlayer*>(var1) != nullptr;
      if (var3 && var4) {
         var2.turnDelta = Math.max(var2.turnDelta, 10.0F);
      }
   }

    bool isIgnoreCollide(IsoGameCharacter var1, int var2, int var3, int var4, int var5, int var6, int var7) {
    std::unordered_map var8 = var1.getStateMachineParams(this);
    int var9 = (int)var8.get(PARAM_START_X);
    int var10 = (int)var8.get(PARAM_START_Y);
    int var11 = (int)var8.get(PARAM_END_X);
    int var12 = (int)var8.get(PARAM_END_Y);
    int var13 = (int)var8.get(PARAM_Z);
      if (var13 == var4 && var13 == var7) {
    int var14 = PZMath.min(var9, var11);
    int var15 = PZMath.min(var10, var12);
    int var16 = PZMath.max(var9, var11);
    int var17 = PZMath.max(var10, var12);
    int var18 = PZMath.min(var2, var5);
    int var19 = PZMath.min(var3, var6);
    int var20 = PZMath.max(var2, var5);
    int var21 = PZMath.max(var3, var6);
         return var14 <= var18 && var15 <= var19 && var16 >= var20 && var17 >= var21;
      } else {
    return false;
      }
   }

    void slideX(IsoGameCharacter var1, float var2) {
    float var3 = 0.05F * GameTime.getInstance().getMultiplier() / 1.6F;
      var3 = var2 > var1.x ? Math.min(var3, var2 - var1.x) : Math.max(-var3, var2 - var1.x);
      var1.x += var3;
      var1.nx = var1.x;
   }

    void slideY(IsoGameCharacter var1, float var2) {
    float var3 = 0.05F * GameTime.getInstance().getMultiplier() / 1.6F;
      var3 = var2 > var1.y ? Math.min(var3, var2 - var1.y) : Math.max(-var3, var2 - var1.y);
      var1.y += var3;
      var1.ny = var1.y;
   }

    IsoObject getFence(IsoGameCharacter var1) {
    std::unordered_map var2 = var1.getStateMachineParams(this);
    int var3 = (int)var2.get(PARAM_START_X);
    int var4 = (int)var2.get(PARAM_START_Y);
    int var5 = (int)var2.get(PARAM_Z);
    IsoGridSquare var6 = IsoWorld.instance.CurrentCell.getGridSquare(var3, var4, var5);
    int var7 = (int)var2.get(PARAM_END_X);
    int var8 = (int)var2.get(PARAM_END_Y);
    IsoGridSquare var9 = IsoWorld.instance.CurrentCell.getGridSquare(var7, var8, var5);
      return var6 != nullptr && var9 != nullptr ? var6.getHoppableTo(var9) : nullptr;
   }

    int getFenceType(IsoObject var1) {
      if (var1.getSprite() == nullptr) {
    return 0;
      } else {
    PropertyContainer var2 = var1.getSprite().getProperties();
    std::string var3 = var2.Val("FenceTypeLow");
         if (var3 != nullptr) {
            if ("Sandbag" == var3) && var1.getName() != nullptr && StringUtils.containsIgnoreCase(var1.getName(), "Gravel")) {
               var3 = "Gravelbag";
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

    int getTripType(IsoObject var1) {
      if (var1.getSprite() == nullptr) {
    return 0;
      } else {
    PropertyContainer var2 = var1.getSprite().getProperties();
    std::string var3 = var2.Val("FenceTypeLow");
         if (var3 != nullptr) {
            if ("Sandbag" == var3) && var1.getName() != nullptr && StringUtils.containsIgnoreCase(var1.getName(), "Gravel")) {
               var3 = "Gravelbag";
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

    bool shouldFallAfterVaultOver(IsoGameCharacter var1) {
      if (dynamic_cast<IsoPlayer*>(var1) != nullptr && !((IsoPlayer)var1).isLocalPlayer()) {
         return ((IsoPlayer)var1).networkAI.climbFenceOutcomeFall;
      } else if (DebugOptions.instance.char.Debug.AlwaysTripOverFence.getValue()) {
    return true;
      } else {
    float var2 = 0.0F;
         if (var1.getVariableBoolean("VaultOverSprint")) {
            var2 = 10.0F;
         }

         if (var1.getMoodles() != nullptr) {
            var2 += var1.getMoodles().getMoodleLevel(MoodleType.Endurance) * 10;
            var2 += var1.getMoodles().getMoodleLevel(MoodleType.HeavyLoad) * 13;
            var2 += var1.getMoodles().getMoodleLevel(MoodleType.Pain) * 5;
         }

    BodyPart var3 = var1.getBodyDamage().getBodyPart(BodyPartType.Torso_Lower);
         if (var3.getAdditionalPain(true) > 20.0F) {
            var2 += (var3.getAdditionalPain(true) - 20.0F) / 10.0F;
         }

         if (var1.Traits.Clumsy.isSet()) {
            var2 += 10.0F;
         }

         if (var1.Traits.Graceful.isSet()) {
            var2 -= 10.0F;
         }

         if (var1.Traits.VeryUnderweight.isSet()) {
            var2 += 20.0F;
         }

         if (var1.Traits.Underweight.isSet()) {
            var2 += 10.0F;
         }

         if (var1.Traits.Obese.isSet()) {
            var2 += 20.0F;
         }

         if (var1.Traits.Overweight.isSet()) {
            var2 += 10.0F;
         }

         var2 -= var1.getPerkLevel(Perks.Fitness);
         return Rand.Next(100) < var2;
      }
   }

    int countZombiesClimbingOver(IsoObject var1) {
      if (var1 != nullptr && var1.getSquare() != nullptr) {
    int var2 = 0;
    IsoGridSquare var3 = var1.getSquare();
         var2 += this.countZombiesClimbingOver(var1, var3);
         if (var1.getProperties().Is(IsoFlagType.HoppableN)) {
            var3 = var3.getAdjacentSquare(IsoDirections.N);
         } else {
            var3 = var3.getAdjacentSquare(IsoDirections.W);
         }

         return var2 + this.countZombiesClimbingOver(var1, var3);
      } else {
    return 0;
      }
   }

    int countZombiesClimbingOver(IsoObject var1, IsoGridSquare var2) {
      if (var2 == nullptr) {
    return 0;
      } else {
    int var3 = 0;

         for (int var4 = 0; var4 < var2.getMovingObjects().size(); var4++) {
    IsoZombie var5 = (IsoZombie)Type.tryCastTo((IsoMovingObject)var2.getMovingObjects().get(var4), IsoZombie.class);
            if (var5 != nullptr && var5.target != nullptr && var5.isCurrentState(this) && this.getFence(var5) == var1) {
               var3++;
            }
         }

    return var3;
      }
   }

    bool isMetalFence(IsoObject var1) {
      if (var1 != nullptr && var1.getProperties() != nullptr) {
    PropertyContainer var2 = var1.getProperties();
    std::string var3 = var2.Val("Material");
    std::string var4 = var2.Val("Material2");
    std::string var5 = var2.Val("Material3");
         if ("MetalBars" == var3) || "MetalBars" == var4) || "MetalBars" == var5)) {
    return true;
         } else if (!"MetalWire" == var3) && !"MetalWire" == var4) && !"MetalWire" == var5)) {
            if (dynamic_cast<IsoThumpable*>(var1) != nullptr && var1.hasModData()) {
    KahluaTableIterator var6 = var1.getModData().iterator();

               while (var6.advance()) {
    std::string var7 = (std::string)Type.tryCastTo(var6.getKey(), std::string.class);
                  if (var7 != nullptr && var7.contains("MetalPipe")) {
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

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    void setParams(IsoGameCharacter var1, IsoDirections var2) {
    std::unordered_map var3 = var1.getStateMachineParams(this);
    int var4 = var1.getSquare().getX();
    int var5 = var1.getSquare().getY();
    int var6 = var1.getSquare().getZ();
    int var9 = var4;
    int var10 = var5;
      switch (1.$SwitchMap$zombie$iso$IsoDirections[var2.ordinal()]) {
         case 1:
            var10 = var5 - 1;
            break;
         case 2:
            var10 = var5 + 1;
            break;
         case 3:
            var9 = var4 - 1;
            break;
         case 4:
            var9 = var4 + 1;
            break;
         default:
            throw IllegalArgumentException("invalid direction");
      }

    IsoGridSquare var11 = IsoWorld.instance.CurrentCell.getGridSquare(var9, var10, var6);
    bool var12 = false;
    bool var13 = var11 != nullptr && var11.Is(IsoFlagType.solidtrans);
    bool var14 = var11 != nullptr && var11.TreatAsSolidFloor();
    bool var15 = var11 != nullptr && var1.canClimbDownSheetRope(var11);
      var3.put(PARAM_START_X, var4);
      var3.put(PARAM_START_Y, var5);
      var3.put(PARAM_Z, var6);
      var3.put(PARAM_END_X, var9);
      var3.put(PARAM_END_Y, var10);
      var3.put(PARAM_DIR, var2);
      var3.put(PARAM_ZOMBIE_ON_FLOOR, bool.FALSE);
      var3.put(PARAM_PREV_STATE, var1.getCurrentState());
      var3.put(PARAM_SCRATCH, var12 ? bool.TRUE : bool.FALSE);
      var3.put(PARAM_COUNTER, var13 ? bool.TRUE : bool.FALSE);
      var3.put(PARAM_SOLID_FLOOR, var14 ? bool.TRUE : bool.FALSE);
      var3.put(PARAM_SHEET_ROPE, var15 ? bool.TRUE : bool.FALSE);
      var3.put(PARAM_RUN, var1.isRunning() ? bool.TRUE : bool.FALSE);
      var3.put(PARAM_SPRINT, var1.isSprinting() ? bool.TRUE : bool.FALSE);
      var3.put(PARAM_COLLIDABLE, bool.FALSE);
   }
}
} // namespace states
} // namespace ai
} // namespace zombie
