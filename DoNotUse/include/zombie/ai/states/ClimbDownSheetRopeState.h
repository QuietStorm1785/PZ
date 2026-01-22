#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameTime.h"
#include "zombie/ai/State.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/skills/PerkFactory/Perks.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/SpriteDetails/IsoFlagType.h"
#include "zombie/iso/objects/IsoWindow.h"

namespace zombie {
namespace ai {
namespace states {


class ClimbDownSheetRopeState : public State {
public:
    static const float CLIMB_DOWN_SPEED = 0.16F;
    static const float CLIMB_DOWN_SLOWDOWN = 0.5F;
    static const ClimbDownSheetRopeState _instance = std::make_shared<ClimbDownSheetRopeState>();

    static ClimbDownSheetRopeState instance() {
    return _instance;
   }

    void enter(IsoGameCharacter var1) {
      var1.setIgnoreMovement(true);
      var1.setHideWeaponModel(true);
      var1.setbClimbing(true);
      var1.setVariable("ClimbRope", true);
   }

    void execute(IsoGameCharacter var1) {
    std::unordered_map var2 = var1.getStateMachineParams(this);
    float var3 = 0.0F;
    float var4 = 0.0F;
      if (var1.getCurrentSquare().getProperties().Is(IsoFlagType.climbSheetTopN) || var1.getCurrentSquare().getProperties().Is(IsoFlagType.climbSheetN)) {
         var1.setDir(IsoDirections.N);
         var3 = 0.54F;
         var4 = 0.39F;
      }

      if (var1.getCurrentSquare().getProperties().Is(IsoFlagType.climbSheetTopS) || var1.getCurrentSquare().getProperties().Is(IsoFlagType.climbSheetS)) {
         var1.setDir(IsoDirections.S);
         var3 = 0.118F;
         var4 = 0.5756F;
      }

      if (var1.getCurrentSquare().getProperties().Is(IsoFlagType.climbSheetTopW) || var1.getCurrentSquare().getProperties().Is(IsoFlagType.climbSheetW)) {
         var1.setDir(IsoDirections.W);
         var3 = 0.4F;
         var4 = 0.7F;
      }

      if (var1.getCurrentSquare().getProperties().Is(IsoFlagType.climbSheetTopE) || var1.getCurrentSquare().getProperties().Is(IsoFlagType.climbSheetE)) {
         var1.setDir(IsoDirections.E);
         var3 = 0.5417F;
         var4 = 0.3144F;
      }

    float var5 = var1.x - (int)var1.x;
    float var6 = var1.y - (int)var1.y;
      if (var5 != var3) {
    float var7 = (var3 - var5) / 4.0F;
         var5 += var7;
         var1.x = (int)var1.x + var5;
      }

      if (var6 != var4) {
    float var14 = (var4 - var6) / 4.0F;
         var6 += var14;
         var1.y = (int)var1.y + var6;
      }

      var1.nx = var1.x;
      var1.ny = var1.y;
    float var15 = this.getClimbDownSheetRopeSpeed(var1);
      var1.getSpriteDef().AnimFrameIncrease = var15;
    float var8 = var1.z - var15 / 10.0F * GameTime.instance.getMultiplier();
      var8 = Math.max(var8, 0.0F);

      for (int var9 = (int)var1.z; var9 >= (int)var8; var9--) {
    IsoCell var10 = IsoWorld.instance.getCell();
    IsoGridSquare var11 = var10.getGridSquare(var1.getX(), var1.getY(), var9);
         if ((var11.Is(IsoFlagType.solidtrans) || var11.TreatAsSolidFloor() || var9 == 0) && var8 <= var9) {
            var1.z = var9;
            var2.clear();
            var1.clearVariable("ClimbRope");
            var1.setCollidable(true);
            var1.setbClimbing(false);
            return;
         }
      }

      var1.z = var8;
      if (!IsoWindow.isSheetRopeHere(var1.getCurrentSquare())) {
         var1.setCollidable(true);
         var1.setbClimbing(false);
         var1.setbFalling(true);
         var1.clearVariable("ClimbRope");
      }

      if (dynamic_cast<IsoPlayer*>(var1) != nullptr && ((IsoPlayer)var1).isLocalPlayer()) {
         ((IsoPlayer)var1).dirtyRecalcGridStackTime = 2.0F;
      }
   }

    void exit(IsoGameCharacter var1) {
      var1.setIgnoreMovement(false);
      var1.setHideWeaponModel(false);
      var1.clearVariable("ClimbRope");
      var1.setbClimbing(false);
   }

    float getClimbDownSheetRopeSpeed(IsoGameCharacter var1) {
    float var2 = 0.16F;
      switch (var1.getPerkLevel(Perks.Strength)) {
         case 0:
            var2 -= 0.12F;
            break;
         case 1:
         case 2:
         case 3:
            var2 -= 0.09F;
         case 4:
         case 5:
         default:
            break;
         case 6:
         case 7:
            var2 += 0.05F;
            break;
         case 8:
         case 9:
            var2 += 0.09F;
            break;
         case 10:
            var2 += 0.12F;
      }

      return var2 * 0.5F;
   }
}
} // namespace states
} // namespace ai
} // namespace zombie
