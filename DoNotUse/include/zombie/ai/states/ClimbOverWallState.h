#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "fmod/fmod/FMODManager.h"
#include "zombie/GameTime.h"
#include "zombie/ZomboidGlobals.h"
#include "zombie/ai/State.h"
#include "zombie/ai/states/ClimbOverWallState/1.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/characters/Moodles/MoodleType.h"
#include "zombie/characters/Stats.h"
#include "zombie/characters/skills/PerkFactory/Perks.h"
#include "zombie/core/Core.h"
#include "zombie/core/Rand.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/properties/PropertyContainer.h"
#include "zombie/core/skinnedmodel/advancedanimation/AnimEvent.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoMovingObject.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/SpriteDetails/IsoFlagType.h"
#include "zombie/iso/SpriteDetails/IsoObjectType.h"

namespace zombie {
namespace ai {
namespace states {


class ClimbOverWallState : public State {
public:
    static const ClimbOverWallState _instance = std::make_shared<ClimbOverWallState>();
    static const int PARAM_START_X = 0;
    static const int PARAM_START_Y = 1;
    static const int PARAM_Z = 2;
    static const int PARAM_END_X = 3;
    static const int PARAM_END_Y = 4;
    static const int PARAM_DIR = 5;
    static const int FENCE_TYPE_WOOD = 0;
    static const int FENCE_TYPE_METAL = 1;
    static const int FENCE_TYPE_METAL_BARS = 2;

    static ClimbOverWallState instance() {
    return _instance;
   }

    void enter(IsoGameCharacter var1) {
      var1.setIgnoreMovement(true);
      var1.setHideWeaponModel(true);
    std::unordered_map var2 = var1.getStateMachineParams(this);
    Stats var10000 = var1.getStats();
      var10000.endurance = (float)(var10000.endurance - ZomboidGlobals.RunningEnduranceReduce * 1200.0);
    IsoPlayer var3 = (IsoPlayer)var1;
    bool var4 = var3.isClimbOverWallStruggle();
      if (var4) {
         var10000 = var1.getStats();
         var10000.endurance = (float)(var10000.endurance - ZomboidGlobals.RunningEnduranceReduce * 500.0);
      }

    bool var5 = var3.isClimbOverWallSuccess();
      var1.setVariable("ClimbFenceFinished", false);
      var1.setVariable("ClimbFenceOutcome", var5 ? "success" : "fail");
      var1.setVariable("ClimbFenceStarted", false);
      var1.setVariable("ClimbFenceStruggle", var4);
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    void execute(IsoGameCharacter var1) {
    std::unordered_map var2 = var1.getStateMachineParams(this);
    IsoDirections var3 = (IsoDirections)var2.get(PARAM_DIR);
      var1.setAnimated(true);
      var1.setDir(var3);
    bool var4 = var1.getVariableBoolean("ClimbFenceStarted");
      if (!var4) {
    int var5 = (int)var2.get(PARAM_START_X);
    int var6 = (int)var2.get(PARAM_START_Y);
    float var7 = 0.15F;
    float var8 = var1.getX();
    float var9 = var1.getY();
         switch (1.$SwitchMap$zombie$iso$IsoDirections[var3.ordinal()]) {
            case 1:
               var9 = var6 + var7;
               break;
            case 2:
               var9 = var6 + 1 - var7;
               break;
            case 3:
               var8 = var5 + var7;
               break;
            case 4:
               var8 = var5 + 1 - var7;
         }

    float var10 = GameTime.getInstance().getMultiplier() / 1.6F / 8.0F;
         var1.setX(var1.x + (var8 - var1.x) * var10);
         var1.setY(var1.y + (var9 - var1.y) * var10);
      }
   }

    void exit(IsoGameCharacter var1) {
      var1.clearVariable("ClimbFenceFinished");
      var1.clearVariable("ClimbFenceOutcome");
      var1.clearVariable("ClimbFenceStarted");
      var1.clearVariable("ClimbFenceStruggle");
      var1.setIgnoreMovement(false);
      var1.setHideWeaponModel(false);
      if (dynamic_cast<IsoZombie*>(var1) != nullptr) {
         ((IsoZombie)var1).networkAI.isClimbing = false;
      }
   }

    void animEvent(IsoGameCharacter var1, AnimEvent var2) {
      if (var2.m_EventName.equalsIgnoreCase("PlayFenceSound")) {
    IsoObject var3 = this.getFence(var1);
         if (var3 == nullptr) {
            return;
         }

    int var4 = this.getFenceType(var3);
    long var5 = var1.getEmitter().playSoundImpl(var2.m_ParameterValue, nullptr);
         var1.getEmitter().setParameterValue(var5, FMODManager.instance.getParameterDescription("FenceTypeHigh"), var4);
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

    IsoObject getClimbableWallN(IsoGridSquare var1) {
      IsoObject[] var2 = (IsoObject[])var1.getObjects().getElements();
    int var3 = 0;

      for (int var4 = var1.getObjects().size(); var3 < var4; var3++) {
    IsoObject var5 = var2[var3];
    PropertyContainer var6 = var5.getProperties();
         if (var6 != nullptr
            && !var6.Is(IsoFlagType.CantClimb)
            && var5.getType() == IsoObjectType.wall
            && var6.Is(IsoFlagType.collideN)
            && !var6.Is(IsoFlagType.HoppableN)) {
    return var5;
         }
      }

    return nullptr;
   }

    IsoObject getClimbableWallW(IsoGridSquare var1) {
      IsoObject[] var2 = (IsoObject[])var1.getObjects().getElements();
    int var3 = 0;

      for (int var4 = var1.getObjects().size(); var3 < var4; var3++) {
    IsoObject var5 = var2[var3];
    PropertyContainer var6 = var5.getProperties();
         if (var6 != nullptr
            && !var6.Is(IsoFlagType.CantClimb)
            && var5.getType() == IsoObjectType.wall
            && var6.Is(IsoFlagType.collideW)
            && !var6.Is(IsoFlagType.HoppableW)) {
    return var5;
         }
      }

    return nullptr;
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    IsoObject getFence(IsoGameCharacter var1) {
    std::unordered_map var2 = var1.getStateMachineParams(this);
    int var3 = (int)var2.get(PARAM_START_X);
    int var4 = (int)var2.get(PARAM_START_Y);
    int var5 = (int)var2.get(PARAM_Z);
    IsoGridSquare var6 = IsoWorld.instance.CurrentCell.getGridSquare(var3, var4, var5);
    int var7 = (int)var2.get(PARAM_END_X);
    int var8 = (int)var2.get(PARAM_END_Y);
    IsoGridSquare var9 = IsoWorld.instance.CurrentCell.getGridSquare(var7, var8, var5);
      if (var6 != nullptr && var9 != nullptr) {
    IsoDirections var10 = (IsoDirections)var2.get(PARAM_DIR);

    return switch() {
            case 1 -> this.getClimbableWallN(var6);
            case 2 -> this.getClimbableWallN(var9);
            case 3 -> this.getClimbableWallW(var6);
            case 4 -> this.getClimbableWallW(var9);
            default -> nullptr;
         };
      } else {
    return nullptr;
      }
   }

    int getFenceType(IsoObject var1) {
      if (var1.getSprite() == nullptr) {
    return 0;
      } else {
    PropertyContainer var2 = var1.getSprite().getProperties();
    std::string var3 = var2.Val("FenceTypeHigh");
         if (var3 != nullptr) {
    return switch() {
               case "Wood" -> 0;
               case "Metal" -> 1;
               case "MetalGate" -> 2;
               default -> 0;
            };
         } else {
    return 0;
         }
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

      var3.put(PARAM_START_X, var4);
      var3.put(PARAM_START_Y, var5);
      var3.put(PARAM_Z, var6);
      var3.put(PARAM_END_X, var9);
      var3.put(PARAM_END_Y, var10);
      var3.put(PARAM_DIR, var2);
    IsoPlayer var11 = (IsoPlayer)var1;
      if (var11.isLocalPlayer()) {
    int var12 = 20;
         var12 += var1.getPerkLevel(Perks.Fitness) * 2;
         var12 += var1.getPerkLevel(Perks.Strength) * 2;
         var12 -= var1.getMoodles().getMoodleLevel(MoodleType.Endurance) * 5;
         var12 -= var1.getMoodles().getMoodleLevel(MoodleType.HeavyLoad) * 8;
         if (var1.getTraits().contains("Emaciated") || var1.Traits.Obese.isSet() || var1.getTraits().contains("Very Underweight")) {
            var12 -= 25;
         }

         if (var1.getTraits().contains("Underweight") || var1.getTraits().contains("Overweight")) {
            var12 -= 15;
         }

    IsoGridSquare var13 = var1.getCurrentSquare();
         if (var13 != nullptr) {
            for (int var14 = 0; var14 < var13.getMovingObjects().size(); var14++) {
    IsoMovingObject var15 = (IsoMovingObject)var13.getMovingObjects().get(var14);
               if (dynamic_cast<IsoZombie*>(var15) != nullptr) {
                  if (((IsoZombie)var15).target == var1 && ((IsoZombie)var15).getCurrentState() == AttackState.instance()) {
                     var12 -= 25;
                  } else {
                     var12 -= 7;
                  }
               }
            }
         }

         var12 = Math.max(0, var12);
    bool var21 = Rand.NextBool(var12 / 2);
         if ("Tutorial" == Core.GameMode)) {
            var21 = false;
         }

    bool var22 = !Rand.NextBool(var12);
         var11.setClimbOverWallStruggle(var21);
         var11.setClimbOverWallSuccess(var22);
      }
   }
}
} // namespace states
} // namespace ai
} // namespace zombie
