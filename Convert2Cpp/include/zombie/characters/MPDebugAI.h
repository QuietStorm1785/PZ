#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/ai/states/PathFindState.h"
#include "zombie/characters/IsoPlayer/InputState.h"
#include "zombie/characters/IsoPlayer/MoveVars.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/Vector2.h"
#include "zombie/network/GameClient.h"
#include "zombie/vehicles/PathFindBehavior2.h"

namespace zombie {
namespace characters {


class MPDebugAI {
public:
    static auto tempo = std::make_shared<Vector2>();
    static auto tempo2 = std::make_shared<Vector2>();

    static IsoPlayer getNearestPlayer(IsoPlayer var0) {
    IsoPlayer var1 = null;

      for (IsoPlayer var3 : GameClient.IDToPlayerMap.values()) {
         if (var3 != var0 && (var1 == nullptr || var1.getDistanceSq(var0) > var3.getDistanceSq(var0))) {
            var1 = var3;
         }
      }

    return var1;
   }

    static bool updateMovementFromInput(IsoPlayer var0, MoveVars var1) {
      if (GameClient.bClient
         && var0.isLocalPlayer()
         && (DebugOptions.instance.MultiplayerAttackPlayer.getValue() || DebugOptions.instance.MultiplayerFollowPlayer.getValue())) {
    IsoPlayer var2 = getNearestPlayer(var0);
         if (var2 != nullptr) {
    auto var3 = std::make_shared<Vector2>(var2.x - var0.x, var0.y - var2.y);
            var3.rotate((float) (-Math.PI / 4));
            var3.normalize();
            var1.moveX = var3.x;
            var1.moveY = var3.y;
            var1.NewFacing = IsoDirections.fromAngle(var3);
            if (var2.isTeleporting() || var2.getDistanceSq(var0) > 10.0F) {
               var0.removeFromSquare();
               var0.setX(var2.realx);
               var0.setY(var2.realy);
               var0.setZ(var2.realz);
               var0.setLx(var2.realx);
               var0.setLy(var2.realy);
               var0.setLz(var2.realz);
               var0.ensureOnTile();
            } else if (var2.getDistanceSq(var0) > 5.0F) {
               var0.setRunning(true);
               var0.setSprinting(true);
            } else if (var2.getDistanceSq(var0) > 2.5F) {
               var0.setRunning(true);
            } else if (var2.getDistanceSq(var0) < 1.25F) {
               var1.moveX = 0.0F;
               var1.moveY = 0.0F;
            }
         }

    PathFindBehavior2 var10 = var0.getPathFindBehavior2();
         if (var1.moveX == 0.0F && var1.moveY == 0.0F && var0.getPath2() != nullptr && var10.isStrafing() && !var10.bStopping) {
    Vector2 var4 = tempo.set(var10.getTargetX() - var0.x, var10.getTargetY() - var0.y);
    Vector2 var5 = tempo2.set(-1.0F, 0.0F);
    float var6 = 1.0F;
    float var7 = var4.dot(var5);
    float var8 = var7 / var6;
            var5 = tempo2.set(0.0F, -1.0F);
            var7 = var4.dot(var5);
    float var9 = var7 / var6;
            tempo.set(var9, var8);
            tempo.normalize();
            tempo.rotate((float) (Math.PI / 4));
            var1.moveX = tempo.x;
            var1.moveY = tempo.y;
         }

         if (var1.moveX != 0.0F || var1.moveY != 0.0F) {
            if (var0.stateMachine.getCurrent() == PathFindState.instance()) {
               var0.setDefaultState();
            }

            var0.setJustMoved(true);
            var0.setMoveDelta(1.0F);
            if (var0.isStrafing()) {
               tempo.set(var1.moveX, var1.moveY);
               tempo.normalize();
    float var11 = var0.legsSprite.modelSlot.model.AnimPlayer.getRenderedAngle();
               var11 = (float)(var11 + (Math.PI / 4));
               if (var11 > Math.PI * 2) {
                  var11 = (float)(var11 - (Math.PI * 2));
               }

               if (var11 < 0.0F) {
                  var11 = (float)(var11 + (Math.PI * 2));
               }

               tempo.rotate(var11);
               var1.strafeX = tempo.x;
               var1.strafeY = tempo.y;
            } else {
               tempo.set(var1.moveX, -var1.moveY);
               tempo.normalize();
               tempo.rotate((float) (-Math.PI / 4));
               var0.setForwardDirection(tempo);
            }
         }

    return true;
      } else {
    return false;
      }
   }

    static bool updateInputState(IsoPlayer var0, InputState var1) {
      if (GameClient.bClient && var0.isLocalPlayer() && DebugOptions.instance.MultiplayerAttackPlayer.getValue()) {
    IsoPlayer var3 = getNearestPlayer(var0);
         var1.bMelee = false;
         var1.isAttacking = false;
         var1.isCharging = false;
         var1.isAiming = false;
         var1.bRunning = false;
         var1.bSprinting = false;
         if (var3 != nullptr) {
            var1.isCharging = true;
            var1.isAiming = false;
            if (var3.getDistanceSq(var0) < 0.5F) {
               var1.bMelee = true;
               var1.isAttacking = true;
            }
         }

    return true;
      } else if (GameClient.bClient && var0.isLocalPlayer() && DebugOptions.instance.MultiplayerFollowPlayer.getValue()) {
    IsoPlayer var2 = getNearestPlayer(var0);
         var1.bMelee = false;
         var1.isAttacking = false;
         var1.isCharging = false;
         var1.isAiming = false;
         var1.bRunning = false;
         var1.bSprinting = false;
    return true;
      } else {
    return false;
      }
   }
}
} // namespace characters
} // namespace zombie
