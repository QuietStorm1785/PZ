#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "fmod/fmod/FMODManager.h"
#include "zombie/GameTime.h"
#include "zombie/SoundManager.h"
#include "zombie/ai/State.h"
#include "zombie/ai/states/ClimbThroughWindowState/1.h"
#include "zombie/characterTextures/BloodBodyPartType.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/characters/MoveDeltaModifiers.h"
#include "zombie/characters/skills/PerkFactory/Perks.h"
#include "zombie/core/Rand.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/math/PZMath/SideOfLine.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimEvent.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoMovingObject.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/SpriteDetails/IsoFlagType.h"
#include "zombie/iso/Vector2.h"
#include "zombie/iso/objects/IsoThumpable.h"
#include "zombie/iso/objects/IsoWindow.h"
#include "zombie/iso/objects/IsoWindowFrame.h"
#include "zombie/util/Type.h"

namespace zombie {
namespace ai {
namespace states {


class ClimbThroughWindowState : public State {
public:
    static const ClimbThroughWindowState _instance = std::make_shared<ClimbThroughWindowState>();
    static const int PARAM_START_X = 0;
    static const int PARAM_START_Y = 1;
    static const int PARAM_Z = 2;
    static const int PARAM_OPPOSITE_X = 3;
    static const int PARAM_OPPOSITE_Y = 4;
    static const int PARAM_DIR = 5;
    static const int PARAM_ZOMBIE_ON_FLOOR = 6;
    static const int PARAM_PREV_STATE = 7;
    static const int PARAM_SCRATCH = 8;
    static const int PARAM_COUNTER = 9;
    static const int PARAM_SOLID_FLOOR = 10;
    static const int PARAM_SHEET_ROPE = 11;
    static const int PARAM_END_X = 12;
    static const int PARAM_END_Y = 13;

    static ClimbThroughWindowState instance() {
    return _instance;
   }

    void enter(IsoGameCharacter var1) {
      var1.setIgnoreMovement(true);
      var1.setHideWeaponModel(true);
    std::unordered_map var2 = var1.getStateMachineParams(this);
    bool var3 = var2.get(PARAM_COUNTER) == bool.TRUE;
      var1.setVariable("ClimbWindowStarted", false);
      var1.setVariable("ClimbWindowEnd", false);
      var1.setVariable("ClimbWindowFinished", false);
      var1.clearVariable("ClimbWindowGetUpBack");
      var1.clearVariable("ClimbWindowGetUpFront");
      var1.setVariable("ClimbWindowOutcome", var3 ? "obstacle" : "success");
      var1.clearVariable("ClimbWindowFlopped");
    IsoZombie var4 = (IsoZombie)Type.tryCastTo(var1, IsoZombie.class);
      if (!var3 && var4 != nullptr && var4.shouldDoFenceLunge()) {
         this.setLungeXVars(var4);
         var1.setVariable("ClimbWindowOutcome", "lunge");
      }

      if (var2.get(PARAM_SOLID_FLOOR) == bool.FALSE) {
         var1.setVariable("ClimbWindowOutcome", "fall");
      }

      if (!(dynamic_cast<IsoZombie*>(var1) != nullptr) && var2.get(PARAM_SHEET_ROPE) == bool.TRUE) {
         var1.setVariable("ClimbWindowOutcome", "rope");
      }

      if (dynamic_cast<IsoPlayer*>(var1) != nullptr && ((IsoPlayer)var1).isLocalPlayer()) {
         ((IsoPlayer)var1).dirtyRecalcGridStackTime = 20.0F;
      }
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    void execute(IsoGameCharacter var1) {
    std::unordered_map var2 = var1.getStateMachineParams(this);
      if (!this.isWindowClosing(var1)) {
    IsoDirections var3 = (IsoDirections)var2.get(PARAM_DIR);
         var1.setDir(var3);
    std::string var4 = var1.getVariableString("ClimbWindowOutcome");
         if (dynamic_cast<IsoZombie*>(var1) != nullptr) {
    bool var5 = var2.get(PARAM_ZOMBIE_ON_FLOOR) == bool.TRUE;
            if (!var1.isFallOnFront() && var5) {
    int var6 = (int)var2.get(PARAM_OPPOSITE_X);
    int var7 = (int)var2.get(PARAM_OPPOSITE_Y);
    int var8 = (int)var2.get(PARAM_Z);
    IsoGridSquare var9 = IsoWorld.instance.CurrentCell.getGridSquare(var6, var7, var8);
               if (var9 != nullptr && var9.getBrokenGlass() != nullptr) {
                  var1.addBlood(BloodBodyPartType.Head, true, true, true);
                  var1.addBlood(BloodBodyPartType.Head, true, true, true);
                  var1.addBlood(BloodBodyPartType.Head, true, true, true);
                  var1.addBlood(BloodBodyPartType.Head, true, true, true);
                  var1.addBlood(BloodBodyPartType.Head, true, true, true);
                  var1.addBlood(BloodBodyPartType.Neck, true, true, true);
                  var1.addBlood(BloodBodyPartType.Neck, true, true, true);
                  var1.addBlood(BloodBodyPartType.Neck, true, true, true);
                  var1.addBlood(BloodBodyPartType.Neck, true, true, true);
                  var1.addBlood(BloodBodyPartType.Torso_Upper, true, true, true);
                  var1.addBlood(BloodBodyPartType.Torso_Upper, true, true, true);
                  var1.addBlood(BloodBodyPartType.Torso_Upper, true, true, true);
               }
            }

            var1.setOnFloor(var5);
            ((IsoZombie)var1).setKnockedDown(var5);
            var1.setFallOnFront(var5);
         }

    float var11 = ((int)var2.get(PARAM_START_X)).intValue() + 0.5F;
    float var12 = ((int)var2.get(PARAM_START_Y)).intValue() + 0.5F;
         if (!var1.getVariableBoolean("ClimbWindowStarted")) {
            if (var1.x != var11 && (var3 == IsoDirections.N || var3 == IsoDirections.S)) {
               this.slideX(var1, var11);
            }

            if (var1.y != var12 && (var3 == IsoDirections.W || var3 == IsoDirections.E)) {
               this.slideY(var1, var12);
            }
         }

         if (dynamic_cast<IsoPlayer*>(var1) != nullptr && var4.equalsIgnoreCase("obstacle")) {
    float var13 = ((int)var2.get(PARAM_END_X)).intValue() + 0.5F;
    float var16 = ((int)var2.get(PARAM_END_Y)).intValue() + 0.5F;
            if (var1.DistToSquared(var13, var16) < 0.5625F) {
               var1.setVariable("ClimbWindowOutcome", "obstacleEnd");
            }
         }

         if (dynamic_cast<IsoPlayer*>(var1) != nullptr
            && !var1.getVariableBoolean("ClimbWindowEnd")
            && !"fallfront" == var4)
            && !"back" == var4)
            && !"fallback" == var4)) {
    int var14 = (int)var2.get(PARAM_OPPOSITE_X);
    int var17 = (int)var2.get(PARAM_OPPOSITE_Y);
    int var19 = (int)var2.get(PARAM_Z);
    IsoGridSquare var10 = IsoWorld.instance.CurrentCell.getGridSquare(var14, var17, var19);
            if (var10 != nullptr) {
               this.checkForFallingBack(var10, var1);
               if (var10 != var1.getSquare() && var10.TreatAsSolidFloor()) {
                  this.checkForFallingFront(var1.getSquare(), var1);
               }
            }
         }

         if (var1.getVariableBoolean("ClimbWindowStarted")
            && !"back" == var4)
            && !"fallback" == var4)
            && !"lunge" == var4)
            && !"obstacle" == var4)
            && !"obstacleEnd" == var4)) {
    float var15 = ((int)var2.get(PARAM_START_X)).intValue();
    float var18 = ((int)var2.get(PARAM_START_Y)).intValue();
            switch (1.$SwitchMap$zombie$iso$IsoDirections[var3.ordinal()]) {
               case 1:
                  var18 -= 0.1F;
                  break;
               case 2:
                  var18++;
                  break;
               case 3:
                  var15 -= 0.1F;
                  break;
               case 4:
                  var15++;
            }

            if ((int)var1.x != (int)var15 && (var3 == IsoDirections.W || var3 == IsoDirections.E)) {
               this.slideX(var1, var15);
            }

            if ((int)var1.y != (int)var18 && (var3 == IsoDirections.N || var3 == IsoDirections.S)) {
               this.slideY(var1, var18);
            }
         }

         if (var1.getVariableBoolean("ClimbWindowStarted") && var2.get(PARAM_SCRATCH) == bool.TRUE) {
            var2.put(PARAM_SCRATCH, bool.FALSE);
            var1.getBodyDamage().setScratchedWindow();
         }
      }
   }

    void checkForFallingBack(IsoGridSquare var1, IsoGameCharacter var2) {
      for (int var3 = 0; var3 < var1.getMovingObjects().size(); var3++) {
    IsoMovingObject var4 = (IsoMovingObject)var1.getMovingObjects().get(var3);
    IsoZombie var5 = (IsoZombie)Type.tryCastTo(var4, IsoZombie.class);
         if (var5 != nullptr && !var5.isOnFloor() && !var5.isSitAgainstWall()) {
            if (!var5.isVariable("AttackOutcome", "success") && Rand.Next(5 + var2.getPerkLevel(Perks.Fitness)) != 0) {
               var5.playHurtSound();
               var2.setVariable("ClimbWindowOutcome", "back");
            } else {
               var5.playHurtSound();
               var2.setVariable("ClimbWindowOutcome", "fallback");
            }
         }
      }
   }

    void checkForFallingFront(IsoGridSquare var1, IsoGameCharacter var2) {
      for (int var3 = 0; var3 < var1.getMovingObjects().size(); var3++) {
    IsoMovingObject var4 = (IsoMovingObject)var1.getMovingObjects().get(var3);
    IsoZombie var5 = (IsoZombie)Type.tryCastTo(var4, IsoZombie.class);
         if (var5 != nullptr && !var5.isOnFloor() && !var5.isSitAgainstWall() && var5.isVariable("AttackOutcome", "success")) {
            var5.playHurtSound();
            var2.setVariable("ClimbWindowOutcome", "fallfront");
         }
      }
   }

    void exit(IsoGameCharacter var1) {
      var1.setIgnoreMovement(false);
      var1.setHideWeaponModel(false);
    std::unordered_map var2 = var1.getStateMachineParams(this);
      if (var1.isVariable("ClimbWindowOutcome", "fall")
         || var1.isVariable("ClimbWindowOutcome", "fallback")
         || var1.isVariable("ClimbWindowOutcome", "fallfront")) {
         var1.setHitReaction("");
      }

      var1.clearVariable("ClimbWindowFinished");
      var1.clearVariable("ClimbWindowOutcome");
      var1.clearVariable("ClimbWindowStarted");
      var1.clearVariable("ClimbWindowFlopped");
      if (dynamic_cast<IsoZombie*>(var1) != nullptr) {
         var1.setOnFloor(false);
         ((IsoZombie)var1).setKnockedDown(false);
      }

    IsoZombie var3 = (IsoZombie)Type.tryCastTo(var1, IsoZombie.class);
      if (var3 != nullptr) {
         var3.AllowRepathDelay = 0.0F;
         if (var2.get(PARAM_PREV_STATE) == PathFindState.instance()) {
            if (var1.getPathFindBehavior2().getTargetChar() == nullptr) {
               var1.setVariable("bPathFind", true);
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

    void animEvent(IsoGameCharacter var1, AnimEvent var2) {
    std::unordered_map var3 = var1.getStateMachineParams(this);
    IsoZombie var4 = (IsoZombie)Type.tryCastTo(var1, IsoZombie.class);
      if (var2.m_EventName.equalsIgnoreCase("CheckAttack") && var4 != nullptr && var4.dynamic_cast<IsoGameCharacter*>(target) != nullptr) {
         ((IsoGameCharacter)var4.target).attackFromWindowsLunge(var4);
      }

      if (var2.m_EventName.equalsIgnoreCase("OnFloor") && var4 != nullptr) {
    bool var5 = bool.parseBoolean(var2.m_ParameterValue);
         var3.put(PARAM_ZOMBIE_ON_FLOOR, var5);
         if (var5) {
            this.setLungeXVars(var4);
    IsoThumpable var6 = (IsoThumpable)Type.tryCastTo(this.getWindow(var1), IsoThumpable.class);
            if (var6 != nullptr && var6.getSquare() != nullptr && var4.target != nullptr) {
               var6.Health = var6.Health - Rand.Next(10, 20);
               if (var6.Health <= 0) {
                  var6.destroy();
               }
            }

            var1.setVariable("ClimbWindowFlopped", true);
         }
      }

      if (var2.m_EventName.equalsIgnoreCase("PlayWindowSound")) {
         if (!SoundManager.instance.isListenerInRange(var1.getX(), var1.getY(), 10.0F)) {
            return;
         }

    long var8 = var1.getEmitter().playSoundImpl(var2.m_ParameterValue, nullptr);
         var1.getEmitter().setParameterValue(var8, FMODManager.instance.getParameterDescription("TripObstacleType"), 9.0F);
      }

      if (var2.m_EventName.equalsIgnoreCase("SetState")) {
         if (var4 == nullptr) {
            return;
         }

         try {
            zombie.audio.parameters.ParameterZombieState.State var9 = zombie.audio.parameters.ParameterZombieState.State.valueOf(var2.m_ParameterValue);
            var4.parameterZombieState.setState(var9);
         } catch (IllegalArgumentException var7) {
         }
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

    IsoObject getWindow(IsoGameCharacter var1) {
      if (!var1.isCurrentState(this)) {
    return nullptr;
      } else {
    std::unordered_map var2 = var1.getStateMachineParams(this);
    int var3 = (int)var2.get(PARAM_START_X);
    int var4 = (int)var2.get(PARAM_START_Y);
    int var5 = (int)var2.get(PARAM_Z);
    IsoGridSquare var6 = IsoWorld.instance.CurrentCell.getGridSquare(var3, var4, var5);
    int var7 = (int)var2.get(PARAM_END_X);
    int var8 = (int)var2.get(PARAM_END_Y);
    IsoGridSquare var9 = IsoWorld.instance.CurrentCell.getGridSquare(var7, var8, var5);
         if (var6 != nullptr && var9 != nullptr) {
    void* var10 = var6.getWindowTo(var9);
            if (var10 == nullptr) {
               var10 = var6.getWindowThumpableTo(var9);
            }

            if (var10 == nullptr) {
               var10 = var6.getHoppableTo(var9);
            }

            return (IsoObject)var10;
         } else {
    return nullptr;
         }
      }
   }

    bool isWindowClosing(IsoGameCharacter var1) {
    std::unordered_map var2 = var1.getStateMachineParams(this);
      if (var1.getVariableBoolean("ClimbWindowStarted")) {
    return false;
      } else {
    int var3 = (int)var2.get(PARAM_START_X);
    int var4 = (int)var2.get(PARAM_START_Y);
    int var5 = (int)var2.get(PARAM_Z);
    IsoGridSquare var6 = IsoWorld.instance.CurrentCell.getGridSquare(var3, var4, var5);
         if (var1.getCurrentSquare() != var6) {
    return false;
         } else {
    IsoWindow var7 = (IsoWindow)Type.tryCastTo(this.getWindow(var1), IsoWindow.class);
            if (var7 == nullptr) {
    return false;
            } else {
    IsoGameCharacter var8 = var7.getFirstCharacterClosing();
               if (var8 != nullptr && var8.isVariable("CloseWindowOutcome", "success")) {
                  if (var1.isZombie()) {
                     var1.setHitReaction("HeadLeft");
                  } else {
                     var1.setVariable("ClimbWindowFinished", true);
                  }

    return true;
               } else {
    return false;
               }
            }
         }
      }
   }

    void getDeltaModifiers(IsoGameCharacter var1, MoveDeltaModifiers var2) {
    bool var3 = var1.getPath2() != nullptr;
    bool var4 = dynamic_cast<IsoPlayer*>(var1) != nullptr;
      if (var3 && var4) {
         var2.turnDelta = Math.max(var2.turnDelta, 10.0F);
      }

      if (var4 && var1.getVariableBoolean("isTurning")) {
         var2.turnDelta = Math.max(var2.turnDelta, 5.0F);
      }
   }

    bool isFreeSquare(IsoGridSquare var1) {
      return var1 != nullptr && var1.TreatAsSolidFloor() && !var1.Is(IsoFlagType.solid) && !var1.Is(IsoFlagType.solidtrans);
   }

    bool isObstacleSquare(IsoGridSquare var1) {
      return var1 != nullptr && var1.TreatAsSolidFloor() && !var1.Is(IsoFlagType.solid) && var1.Is(IsoFlagType.solidtrans) && !var1.Is(IsoFlagType.water);
   }

    IsoGridSquare getFreeSquareAfterObstacles(IsoGridSquare var1, IsoDirections var2) {
      while (true) {
    IsoGridSquare var3 = var1.getAdjacentSquare(var2);
         if (var3 == nullptr || var1.isSomethingTo(var3) || var1.getWindowFrameTo(var3) != nullptr || var1.getWindowThumpableTo(var3) != nullptr) {
    return nullptr;
         }

         if (this.isFreeSquare(var3)) {
    return var3;
         }

         if (!this.isObstacleSquare(var3)) {
    return nullptr;
         }

         var1 = var3;
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

    bool isPastInnerEdgeOfSquare(IsoGameCharacter var1, int var2, int var3, IsoDirections var4) {
      if (var4 == IsoDirections.N) {
         return var1.y < var3 + 1 - 0.3F;
      } else if (var4 == IsoDirections.S) {
         return var1.y > var3 + 0.3F;
      } else if (var4 == IsoDirections.W) {
         return var1.x < var2 + 1 - 0.3F;
      } else if (var4 == IsoDirections.E) {
         return var1.x > var2 + 0.3F;
      } else {
         throw IllegalArgumentException("unhandled direction");
      }
   }

    bool isPastOuterEdgeOfSquare(IsoGameCharacter var1, int var2, int var3, IsoDirections var4) {
      if (var4 == IsoDirections.N) {
         return var1.y < var3 - 0.3F;
      } else if (var4 == IsoDirections.S) {
         return var1.y > var3 + 1 + 0.3F;
      } else if (var4 == IsoDirections.W) {
         return var1.x < var2 - 0.3F;
      } else if (var4 == IsoDirections.E) {
         return var1.x > var2 + 1 + 0.3F;
      } else {
         throw IllegalArgumentException("unhandled direction");
      }
   }

    void setParams(IsoGameCharacter var1, IsoObject var2) {
    std::unordered_map var3 = var1.getStateMachineParams(this);
      var3.clear();
    bool var5 = false;
    bool var4;
      if (dynamic_cast<IsoWindow*>(var2) != nullptr var6) {
         var4 = var6.north;
         if (dynamic_cast<IsoPlayer*>(var1) != nullptr && var6.isDestroyed() && !var6.isGlassRemoved() && Rand.Next(2) == 0) {
            var5 = true;
         }
      } else if (dynamic_cast<IsoThumpable*>(var2) != nullptr var21) {
         var4 = var21.north;
         if (dynamic_cast<IsoPlayer*>(var1) != nullptr && var21.getName() == "Barbed Fence") && Rand.Next(101) > 75) {
            var5 = true;
         }
      } else {
         if (!IsoWindowFrame.isWindowFrame(var2)) {
            throw IllegalArgumentException("expected thumpable, window, or window-frame");
         }

         var4 = IsoWindowFrame.isWindowFrame(var2, true);
      }

    int var7 = var2.getSquare().getX();
    int var8 = var2.getSquare().getY();
    int var9 = var2.getSquare().getZ();
    int var10 = var7;
    int var11 = var8;
    int var12 = var7;
    int var13 = var8;
    IsoDirections var22;
      if (var4) {
         if (var8 < var1.getY()) {
            var13 = var8 - 1;
            var22 = IsoDirections.N;
         } else {
            var11 = var8 - 1;
            var22 = IsoDirections.S;
         }
      } else if (var7 < var1.getX()) {
         var12 = var7 - 1;
         var22 = IsoDirections.W;
      } else {
         var10 = var7 - 1;
         var22 = IsoDirections.E;
      }

    IsoGridSquare var14 = IsoWorld.instance.CurrentCell.getGridSquare(var12, var13, var9);
    bool var15 = var14 != nullptr && var14.Is(IsoFlagType.solidtrans);
    bool var16 = var14 != nullptr && var14.TreatAsSolidFloor();
    bool var17 = var14 != nullptr && var1.canClimbDownSheetRope(var14);
    int var18 = var12;
    int var19 = var13;
      if (var15 && var1.isZombie()) {
    IsoGridSquare var20 = var14.getAdjacentSquare(var22);
         if (this.isFreeSquare(var20) && !var14.isSomethingTo(var20) && var14.getWindowFrameTo(var20) == nullptr && var14.getWindowThumpableTo(var20) == nullptr) {
            var18 = var20.x;
            var19 = var20.y;
         } else {
            var15 = false;
         }
      }

      if (var15 && !var1.isZombie()) {
    IsoGridSquare var23 = this.getFreeSquareAfterObstacles(var14, var22);
         if (var23 == nullptr) {
            var15 = false;
         } else {
            var18 = var23.x;
            var19 = var23.y;
         }
      }

      var3.put(PARAM_START_X, var10);
      var3.put(PARAM_START_Y, var11);
      var3.put(PARAM_Z, var9);
      var3.put(PARAM_OPPOSITE_X, var12);
      var3.put(PARAM_OPPOSITE_Y, var13);
      var3.put(PARAM_END_X, var18);
      var3.put(PARAM_END_Y, var19);
      var3.put(PARAM_DIR, var22);
      var3.put(PARAM_ZOMBIE_ON_FLOOR, bool.FALSE);
      var3.put(PARAM_PREV_STATE, var1.getCurrentState());
      var3.put(PARAM_SCRATCH, var5 ? bool.TRUE : bool.FALSE);
      var3.put(PARAM_COUNTER, var15 ? bool.TRUE : bool.FALSE);
      var3.put(PARAM_SOLID_FLOOR, var16 ? bool.TRUE : bool.FALSE);
      var3.put(PARAM_SHEET_ROPE, var17 ? bool.TRUE : bool.FALSE);
   }
}
} // namespace states
} // namespace ai
} // namespace zombie
