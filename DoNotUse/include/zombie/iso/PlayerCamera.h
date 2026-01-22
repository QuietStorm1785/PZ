#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/joml/Vector3f.h"
#include "zombie/GameWindow.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Core.h"
#include "zombie/core/PerformanceSettings.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/input/GameKeyboard.h"
#include "zombie/input/JoypadManager.h"
#include "zombie/input/Mouse.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/network/GameServer.h"
#include "zombie/ui/UIManager.h"
#include "zombie/vehicles/BaseVehicle.h"
#include "zombie/vehicles/BaseVehicle/Vector3fObjectPool.h"

namespace zombie {
namespace iso {


class PlayerCamera {
public:
    const int playerIndex;
    float OffX;
    float OffY;
    float TOffX;
    float TOffY;
    float lastOffX;
    float lastOffY;
    float RightClickTargetX;
    float RightClickTargetY;
    float RightClickX;
    float RightClickY;
    float RightClickX_f;
    float RightClickY_f;
    float DeferedX;
    float DeferedY;
    float zoom;
    int OffscreenWidth;
    int OffscreenHeight;
    static const Vector2 offVec = std::make_shared<Vector2>();
    static float PAN_SPEED = 1.0F;
    long panTime = -1L;
    const Vector3f m_lastVehicleForwardDirection = std::make_shared<Vector3f>();

    public PlayerCamera(int var1) {
      this.playerIndex = var1;
   }

    void center() {
    float var1 = this.OffX;
    float var2 = this.OffY;
      if (IsoCamera.CamCharacter != nullptr) {
    IsoGameCharacter var3 = IsoCamera.CamCharacter;
         var1 = IsoUtils.XToScreen(var3.x + this.DeferedX, var3.y + this.DeferedY, var3.z, 0);
         var2 = IsoUtils.YToScreen(var3.x + this.DeferedX, var3.y + this.DeferedY, var3.z, 0);
         var1 -= IsoCamera.getOffscreenWidth(this.playerIndex) / 2;
         var2 -= IsoCamera.getOffscreenHeight(this.playerIndex) / 2;
         var2 -= var3.getOffsetY() * 1.5F;
         var1 += IsoCamera.PLAYER_OFFSET_X;
         var2 += IsoCamera.PLAYER_OFFSET_Y;
      }

      this.OffX = this.TOffX = var1;
      this.OffY = this.TOffY = var2;
   }

    void update() {
      this.center();
    float var1 = (this.TOffX - this.OffX) / 15.0F;
    float var2 = (this.TOffY - this.OffY) / 15.0F;
      this.OffX += var1;
      this.OffY += var2;
      if (this.lastOffX == 0.0F && this.lastOffY == 0.0F) {
         this.lastOffX = this.OffX;
         this.lastOffY = this.OffY;
      }

    long var3 = System.currentTimeMillis();
      PAN_SPEED = 110.0F;
    float var5 = this.panTime < 0L ? 1.0F : (float)(var3 - this.panTime) / 1000.0F * PAN_SPEED;
      var5 = 1.0F / var5;
      this.panTime = var3;
    IsoPlayer var6 = IsoPlayer.players[this.playerIndex];
    bool var7 = GameWindow.ActivatedJoyPad != nullptr && var6 != nullptr && var6.JoypadBind != -1;
    BaseVehicle var8 = var6 == nullptr ? nullptr : var6.getVehicle();
      if (var8 != nullptr && var8.getCurrentSpeedKmHour() <= 1.0F) {
         var8.getForwardVector(this.m_lastVehicleForwardDirection);
      }

      if (Core.getInstance().getOptionPanCameraWhileDriving() && var8 != nullptr && var8.getCurrentSpeedKmHour() > 1.0F) {
    float var28 = Core.getInstance().getZoom(this.playerIndex);
    float var30 = var8.getCurrentSpeedKmHour() * BaseVehicle.getFakeSpeedModifier() / 10.0F;
         var30 *= var28;
    Vector3f var33 = var8.getForwardVector((Vector3f)((Vector3fObjectPool)BaseVehicle.TL_vector3f_pool.get()).alloc());
    float var35 = this.m_lastVehicleForwardDirection.angle(var33) * (180.0F / (float)Math.PI);
         if (var35 > 1.0F) {
    float var38 = var35 / 180.0F / PerformanceSettings.getLockFPS();
            var38 = PZMath.max(var38, 0.1F);
            this.m_lastVehicleForwardDirection.lerp(var33, var38, var33);
            this.m_lastVehicleForwardDirection.set(var33);
         }

         this.RightClickTargetX = (int)IsoUtils.XToScreen(var33.x * var30, var33.z * var30, var6.z, 0);
         this.RightClickTargetY = (int)IsoUtils.YToScreen(var33.x * var30, var33.z * var30, var6.z, 0);
         ((Vector3fObjectPool)BaseVehicle.TL_vector3f_pool.get()).release(var33);
    uint8_t var40 = 0;
    uint8_t var43 = 0;
    int var46 = IsoCamera.getOffscreenWidth(this.playerIndex);
    int var48 = IsoCamera.getOffscreenHeight(this.playerIndex);
    float var50 = var40 + var46 / 2.0F;
    float var52 = var43 + var48 / 2.0F;
    float var53 = 150.0F * var28;
         this.RightClickTargetX = (int)PZMath.clamp(var50 + this.RightClickTargetX, var53, var46 - var53) - var50;
         this.RightClickTargetY = (int)PZMath.clamp(var52 + this.RightClickTargetY, var53, var48 - var53) - var52;
         if (Math.abs(var30) < 5.0F) {
    float var54 = 1.0F - Math.abs(var30) / 5.0F;
            this.returnToCenter(1.0F / (16.0F * var5 / var54));
         } else {
            var5 /= 0.5F * var28;
    float var55 = IsoUtils.XToScreenExact(var6.x, var6.y, var6.z, 0);
    float var21 = IsoUtils.YToScreenExact(var6.x, var6.y, var6.z, 0);
            if (var55 < var53 / 2.0F || var55 > var46 - var53 / 2.0F || var21 < var53 / 2.0F || var21 > var48 - var53 / 2.0F) {
               var5 /= 4.0F;
            }

            this.RightClickX_f = PZMath.step(
               this.RightClickX_f, this.RightClickTargetX, 1.875F * PZMath.sign(this.RightClickTargetX - this.RightClickX_f) / var5
            );
            this.RightClickY_f = PZMath.step(
               this.RightClickY_f, this.RightClickTargetY, 1.875F * PZMath.sign(this.RightClickTargetY - this.RightClickY_f) / var5
            );
            this.RightClickX = (int)this.RightClickX_f;
            this.RightClickY = (int)this.RightClickY_f;
         }
      } else if (var7 && var6 != nullptr) {
         if ((var6.IsAiming() || var6.isLookingWhileInVehicle()) && JoypadManager.instance.isRBPressed(var6.JoypadBind) && !var6.bJoypadIgnoreAimUntilCentered) {
            this.RightClickTargetX = JoypadManager.instance.getAimingAxisX(var6.JoypadBind) * 1500.0F;
            this.RightClickTargetY = JoypadManager.instance.getAimingAxisY(var6.JoypadBind) * 1500.0F;
            var5 /= 0.5F * Core.getInstance().getZoom(this.playerIndex);
            this.RightClickX_f = PZMath.step(this.RightClickX_f, this.RightClickTargetX, (this.RightClickTargetX - this.RightClickX_f) / (80.0F * var5));
            this.RightClickY_f = PZMath.step(this.RightClickY_f, this.RightClickTargetY, (this.RightClickTargetY - this.RightClickY_f) / (80.0F * var5));
            this.RightClickX = (int)this.RightClickX_f;
            this.RightClickY = (int)this.RightClickY_f;
            var6.dirtyRecalcGridStackTime = 2.0F;
         } else {
            this.returnToCenter(1.0F / (16.0F * var5));
         }
      } else if (this.playerIndex == 0 && var6 != nullptr && !var6.isBlockMovement() && GameKeyboard.isKeyDown(Core.getInstance().getKey("PanCamera"))) {
    int var27 = IsoCamera.getScreenWidth(this.playerIndex);
    int var29 = IsoCamera.getScreenHeight(this.playerIndex);
    int var32 = IsoCamera.getScreenLeft(this.playerIndex);
    int var34 = IsoCamera.getScreenTop(this.playerIndex);
    float var36 = Mouse.getXA() - (var32 + var27 / 2.0F);
    float var41 = Mouse.getYA() - (var34 + var29 / 2.0F);
    float var44;
         if (var27 > var29) {
            var44 = (float)var29 / var27;
            var36 *= var44;
         } else {
            var44 = (float)var27 / var29;
            var41 *= var44;
         }

         var44 *= var27 / 1366.0F;
         offVec.set(var36, var41);
         offVec.setLength(Math.min(offVec.getLength(), Math.min(var27, var29) / 2.0F));
         var36 = offVec.x / var44;
         var41 = offVec.y / var44;
         this.RightClickTargetX = var36 * 2.0F;
         this.RightClickTargetY = var41 * 2.0F;
         var5 /= 0.5F * Core.getInstance().getZoom(this.playerIndex);
         this.RightClickX_f = PZMath.step(this.RightClickX_f, this.RightClickTargetX, (this.RightClickTargetX - this.RightClickX_f) / (80.0F * var5));
         this.RightClickY_f = PZMath.step(this.RightClickY_f, this.RightClickTargetY, (this.RightClickTargetY - this.RightClickY_f) / (80.0F * var5));
         this.RightClickX = (int)this.RightClickX_f;
         this.RightClickY = (int)this.RightClickY_f;
         var6.dirtyRecalcGridStackTime = 2.0F;
         IsoSprite.globalOffsetX = -1.0F;
      } else if (this.playerIndex == 0 && Core.getInstance().getOptionPanCameraWhileAiming()) {
    bool var9 = !GameServer.bServer;
    bool var10 = !UIManager.isMouseOverInventory() && var6 != nullptr && var6.isAiming();
    bool var11 = !var7 && var6 != nullptr && !var6.isDead();
         if (var9 && var10 && var11) {
    int var12 = IsoCamera.getScreenWidth(this.playerIndex);
    int var13 = IsoCamera.getScreenHeight(this.playerIndex);
    int var14 = IsoCamera.getScreenLeft(this.playerIndex);
    int var15 = IsoCamera.getScreenTop(this.playerIndex);
    float var16 = Mouse.getXA() - (var14 + var12 / 2.0F);
    float var17 = Mouse.getYA() - (var15 + var13 / 2.0F);
    float var18;
            if (var12 > var13) {
               var18 = (float)var13 / var12;
               var16 *= var18;
            } else {
               var18 = (float)var12 / var13;
               var17 *= var18;
            }

            var18 *= var12 / 1366.0F;
    float var19 = Math.min(var12, var13) / 6.0F;
    float var20 = Math.min(var12, var13) / 2.0F - var19;
            offVec.set(var16, var17);
            if (offVec.getLength() < var20) {
               var17 = 0.0F;
               var16 = 0.0F;
            } else {
               offVec.setLength(Math.min(offVec.getLength(), Math.min(var12, var13) / 2.0F) - var20);
               var16 = offVec.x / var18;
               var17 = offVec.y / var18;
            }

            this.RightClickTargetX = var16 * 7.0F;
            this.RightClickTargetY = var17 * 7.0F;
            var5 /= 0.5F * Core.getInstance().getZoom(this.playerIndex);
            this.RightClickX_f = PZMath.step(this.RightClickX_f, this.RightClickTargetX, (this.RightClickTargetX - this.RightClickX_f) / (80.0F * var5));
            this.RightClickY_f = PZMath.step(this.RightClickY_f, this.RightClickTargetY, (this.RightClickTargetY - this.RightClickY_f) / (80.0F * var5));
            this.RightClickX = (int)this.RightClickX_f;
            this.RightClickY = (int)this.RightClickY_f;
            var6.dirtyRecalcGridStackTime = 2.0F;
         } else {
            this.returnToCenter(1.0F / (16.0F * var5));
         }

         IsoSprite.globalOffsetX = -1.0F;
      } else {
         this.returnToCenter(1.0F / (16.0F * var5));
      }

      this.zoom = Core.getInstance().getZoom(this.playerIndex);
   }

    void returnToCenter(float var1) {
      this.RightClickTargetX = 0.0F;
      this.RightClickTargetY = 0.0F;
      if (this.RightClickTargetX != this.RightClickX || this.RightClickTargetY != this.RightClickY) {
         this.RightClickX_f = PZMath.step(this.RightClickX_f, this.RightClickTargetX, (this.RightClickTargetX - this.RightClickX_f) * var1);
         this.RightClickY_f = PZMath.step(this.RightClickY_f, this.RightClickTargetY, (this.RightClickTargetY - this.RightClickY_f) * var1);
         this.RightClickX = (int)this.RightClickX_f;
         this.RightClickY = (int)this.RightClickY_f;
         if (Math.abs(this.RightClickTargetX - this.RightClickX_f) < 0.001F) {
            this.RightClickX = (int)this.RightClickTargetX;
            this.RightClickX_f = this.RightClickX;
         }

         if (Math.abs(this.RightClickTargetY - this.RightClickY_f) < 0.001F) {
            this.RightClickY = (int)this.RightClickTargetY;
            this.RightClickY_f = this.RightClickY;
         }

    IsoPlayer var2 = IsoPlayer.players[this.playerIndex];
         var2.dirtyRecalcGridStackTime = 2.0F;
      }
   }

    float getOffX() {
      return (int)(this.OffX + this.RightClickX);
   }

    float getOffY() {
      return (int)(this.OffY + this.RightClickY);
   }

    float getTOffX() {
    float var1 = this.TOffX - this.OffX;
      return (int)(this.OffX + this.RightClickX - var1);
   }

    float getTOffY() {
    float var1 = this.TOffY - this.OffY;
      return (int)(this.OffY + this.RightClickY - var1);
   }

    float getLastOffX() {
      return (int)(this.lastOffX + this.RightClickX);
   }

    float getLastOffY() {
      return (int)(this.lastOffY + this.RightClickY);
   }

    float XToIso(float var1, float var2, float var3) {
      var1 = (int)var1;
      var2 = (int)var2;
    float var4 = var1 + this.getOffX();
    float var5 = var2 + this.getOffY();
    float var6 = (var4 + 2.0F * var5) / (64.0F * Core.TileScale);
      return var6 + 3.0F * var3;
   }

    float YToIso(float var1, float var2, float var3) {
      var1 = (int)var1;
      var2 = (int)var2;
    float var4 = var1 + this.getOffX();
    float var5 = var2 + this.getOffY();
    float var6 = (var4 - 2.0F * var5) / (-64.0F * Core.TileScale);
      return var6 + 3.0F * var3;
   }

    float YToScreenExact(float var1, float var2, float var3, int var4) {
    float var5 = IsoUtils.YToScreen(var1, var2, var3, var4);
      return var5 - this.getOffY();
   }

    float XToScreenExact(float var1, float var2, float var3, int var4) {
    float var5 = IsoUtils.XToScreen(var1, var2, var3, var4);
      return var5 - this.getOffX();
   }

    void copyFrom(PlayerCamera var1) {
      this.OffX = var1.OffX;
      this.OffY = var1.OffY;
      this.TOffX = var1.TOffX;
      this.TOffY = var1.TOffY;
      this.lastOffX = var1.lastOffX;
      this.lastOffY = var1.lastOffY;
      this.RightClickTargetX = var1.RightClickTargetX;
      this.RightClickTargetY = var1.RightClickTargetY;
      this.RightClickX = var1.RightClickX;
      this.RightClickY = var1.RightClickY;
      this.DeferedX = var1.DeferedX;
      this.DeferedY = var1.DeferedY;
      this.zoom = var1.zoom;
      this.OffscreenWidth = var1.OffscreenWidth;
      this.OffscreenHeight = var1.OffscreenHeight;
   }

    void initFromIsoCamera(int var1) {
      this.copyFrom(IsoCamera.cameras[var1]);
      this.zoom = Core.getInstance().getZoom(var1);
      this.OffscreenWidth = IsoCamera.getOffscreenWidth(var1);
      this.OffscreenHeight = IsoCamera.getOffscreenHeight(var1);
   }
}
} // namespace iso
} // namespace zombie
