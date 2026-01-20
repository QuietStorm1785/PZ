#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/IndieGL.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/Core.h"
#include "zombie/core/PerformanceSettings.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/iso/BuildingDef.h"
#include "zombie/iso/IsoCamera.h"
#include "zombie/iso/IsoMetaCell.h"
#include "zombie/iso/IsoMetaGrid.h"
#include "zombie/iso/IsoUtils.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/LotHeader.h"
#include "zombie/iso/RoomDef.h"
#include "zombie/iso/RoomDef/RoomRect.h"
#include "zombie/network/GameClient.h"
#include "zombie/popman/ZombiePopulationManager.h"
#include "zombie/ui/RadarPanel/ZombiePos.h"
#include "zombie/ui/RadarPanel/ZombiePosPool.h"
#include <algorithm>

namespace zombie {
namespace ui {


class RadarPanel : public UIElement {
public:
    int playerIndex;
    float xPos;
    float yPos;
    float offx;
    float offy;
    float zoom;
    float draww;
    float drawh;
    Texture mask;
    Texture border;
   private std::vector<ZombiePos> zombiePos = std::make_unique<std::vector<>>();
    ZombiePosPool zombiePosPool = std::make_shared<ZombiePosPool>();
    int zombiePosFrameCount;
   private boolean[] zombiePosOccupied = new boolean[360];

    public RadarPanel(int var1) {
      this.setX(IsoCamera.getScreenLeft(var1) + 20);
      this.setY(IsoCamera.getScreenTop(var1) + IsoCamera.getScreenHeight(var1) - 120 - 20);
      this.setWidth(120.0);
      this.setHeight(120.0);
      this.mask = Texture.getSharedTexture("media/ui/RadarMask.png");
      this.border = Texture.getSharedTexture("media/ui/RadarBorder.png");
      this.playerIndex = var1;
   }

    void update() {
    uint8_t var1 = 0;
      if (IsoPlayer.players[this.playerIndex] != nullptr && IsoPlayer.players[this.playerIndex].getJoypadBind() != -1) {
         var1 = -72;
      }

      this.setX(IsoCamera.getScreenLeft(this.playerIndex) + 20);
      this.setY(IsoCamera.getScreenTop(this.playerIndex) + IsoCamera.getScreenHeight(this.playerIndex) - this.getHeight() - 20.0 + var1);
   }

    void render() {
      if (this.isVisible()) {
         if (IsoPlayer.players[this.playerIndex] != nullptr) {
            if (!GameClient.bClient) {
               this.draww = this.getWidth().intValue();
               this.drawh = this.getHeight().intValue();
               this.xPos = IsoPlayer.players[this.playerIndex].getX();
               this.yPos = IsoPlayer.players[this.playerIndex].getY();
               this.offx = this.getAbsoluteX().intValue();
               this.offy = this.getAbsoluteY().intValue();
               this.zoom = 3.0F;
               this.stencilOn();
               SpriteRenderer.instance.render(nullptr, this.offx, this.offy, this.getWidth().intValue(), this.drawh, 0.0F, 0.2F, 0.0F, 0.66F, nullptr);
               this.renderBuildings();
               this.renderRect(this.xPos - 0.5F, this.yPos - 0.5F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F);
               this.stencilOff();
               this.renderZombies();
               SpriteRenderer.instance
                  .render(this.border, this.offx - 4.0F, this.offy - 4.0F, this.draww + 8.0F, this.drawh + 8.0F, 1.0F, 1.0F, 1.0F, 0.25F, nullptr);
            }
         }
      }
   }

    void stencilOn() {
      IndieGL.glStencilMask(255);
      IndieGL.glClear(1280);
      IndieGL.enableStencilTest();
      IndieGL.glStencilFunc(519, 128, 255);
      IndieGL.glStencilOp(7680, 7680, 7681);
      IndieGL.enableAlphaTest();
      IndieGL.glAlphaFunc(516, 0.1F);
      IndieGL.glColorMask(false, false, false, false);
      SpriteRenderer.instance.renderi(this.mask, (int)this.x, (int)this.y, (int)this.width, (int)this.height, 1.0F, 1.0F, 1.0F, 1.0F, nullptr);
      IndieGL.glColorMask(true, true, true, true);
      IndieGL.glAlphaFunc(516, 0.0F);
      IndieGL.glStencilFunc(514, 128, 128);
      IndieGL.glStencilOp(7680, 7680, 7680);
   }

    void stencilOff() {
      IndieGL.glAlphaFunc(519, 0.0F);
      IndieGL.disableStencilTest();
      IndieGL.disableAlphaTest();
      IndieGL.glStencilFunc(519, 255, 255);
      IndieGL.glStencilOp(7680, 7680, 7680);
      IndieGL.glClear(1280);
   }

    void renderBuildings() {
    IsoMetaGrid var1 = IsoWorld.instance.MetaGrid;
      IsoMetaCell[][] var2 = var1.Grid;
    int var3 = (int)((this.xPos - 100.0F) / 300.0F) - var1.minX;
    int var4 = (int)((this.yPos - 100.0F) / 300.0F) - var1.minY;
    int var5 = (int)((this.xPos + 100.0F) / 300.0F) - var1.minX;
    int var6 = (int)((this.yPos + 100.0F) / 300.0F) - var1.minY;
      var3 = Math.max(var3, 0);
      var4 = Math.max(var4, 0);
      var5 = Math.min(var5, var2.length - 1);
      var6 = Math.min(var6, var2[0].length - 1);

      for (int var7 = var3; var7 <= var5; var7++) {
         for (int var8 = var4; var8 <= var6; var8++) {
    LotHeader var9 = var2[var7][var8].info;
            if (var9 != nullptr) {
               for (int var10 = 0; var10 < var9.Buildings.size(); var10++) {
    BuildingDef var11 = (BuildingDef)var9.Buildings.get(var10);

                  for (int var12 = 0; var12 < var11.rooms.size(); var12++) {
                     if (((RoomDef)var11.rooms.get(var12)).level <= 0) {
    std::vector var13 = ((RoomDef)var11.rooms.get(var12)).getRects();

                        for (int var14 = 0; var14 < var13.size(); var14++) {
    RoomRect var15 = (RoomRect)var13.get(var14);
                           this.renderRect(var15.getX(), var15.getY(), var15.getW(), var15.getH(), 0.5F, 0.5F, 0.8F, 0.3F);
                        }
                     }
                  }
               }
            }
         }
      }
   }

    void renderZombies() {
    float var1 = this.offx + this.draww / 2.0F;
    float var2 = this.offy + this.drawh / 2.0F;
    float var3 = this.draww / 2.0F;
    float var4 = 0.5F * this.zoom;
      if (++this.zombiePosFrameCount >= PerformanceSettings.getLockFPS() / 5) {
         this.zombiePosFrameCount = 0;
         this.zombiePosPool.release(this.zombiePos);
         this.zombiePos.clear();
         Arrays.fill(this.zombiePosOccupied, false);
    std::vector var5 = IsoWorld.instance.CurrentCell.getZombieList();

         for (int var6 = 0; var6 < var5.size(); var6++) {
    IsoZombie var7 = (IsoZombie)var5.get(var6);
    float var8 = this.worldToScreenX(var7.getX());
    float var9 = this.worldToScreenY(var7.getY());
    float var10 = IsoUtils.DistanceToSquared(var1, var2, var8, var9);
            if (var10 > var3 * var3) {
    double var11 = Math.atan2(var9 - var2, var8 - var1) + Math.PI;
    double var13 = (Math.toDegrees(var11) + 180.0) % 360.0;
               this.zombiePosOccupied[(int)var13] = true;
            } else {
               this.zombiePos.push_back(this.zombiePosPool.alloc(var7.x, var7.y));
            }
         }

         if (Core.bLastStand) {
            if (ZombiePopulationManager.instance.radarXY == nullptr) {
               ZombiePopulationManager.instance.radarXY = new float[2048];
            }

            float[] var21 = ZombiePopulationManager.instance.radarXY;
            /* synchronized - TODO: add std::mutex */ (var21) {
               for (int var26 = 0; var26 < ZombiePopulationManager.instance.radarCount; var26++) {
    float var27 = var21[var26 * 2 + 0];
    float var28 = var21[var26 * 2 + 1];
    float var29 = this.worldToScreenX(var27);
    float var12 = this.worldToScreenY(var28);
    float var30 = IsoUtils.DistanceToSquared(var1, var2, var29, var12);
                  if (var30 > var3 * var3) {
    double var14 = Math.atan2(var12 - var2, var29 - var1) + Math.PI;
    double var16 = (Math.toDegrees(var14) + 180.0) % 360.0;
                     this.zombiePosOccupied[(int)var16] = true;
                  } else {
                     this.zombiePos.push_back(this.zombiePosPool.alloc(var27, var28));
                  }
               }

               ZombiePopulationManager.instance.radarRenderFlag = true;
            }
         }
      }

    int var20 = this.zombiePos.size();

      for (int var22 = 0; var22 < var20; var22++) {
    ZombiePos var24 = this.zombiePos.get(var22);
         this.renderRect(var24.x - 0.5F, var24.y - 0.5F, 1.0F, 1.0F, 1.0F, 0.0F, 0.0F, 1.0F);
      }

      for (int var23 = 0; var23 < this.zombiePosOccupied.length; var23++) {
         if (this.zombiePosOccupied[var23]) {
    double var25 = Math.toRadians((float)var23 / this.zombiePosOccupied.length * 360.0F);
            SpriteRenderer.instance
               .render(
                  nullptr,
                  var1 + (var3 + 1.0F) * (float)Math.cos(var25) - var4,
                  var2 + (var3 + 1.0F) * (float)Math.sin(var25) - var4,
                  1.0F * this.zoom,
                  1.0F * this.zoom,
                  1.0F,
                  1.0F,
                  0.0F,
                  1.0F,
                  nullptr
               );
         }
      }
   }

    float worldToScreenX(float var1) {
      var1 -= this.xPos;
      var1 *= this.zoom;
      var1 += this.offx;
      return var1 + this.draww / 2.0F;
   }

    float worldToScreenY(float var1) {
      var1 -= this.yPos;
      var1 *= this.zoom;
      var1 += this.offy;
      return var1 + this.drawh / 2.0F;
   }

    void renderRect(float var1, float var2, float var3, float var4, float var5, float var6, float var7, float var8) {
    float var9 = this.worldToScreenX(var1);
    float var10 = this.worldToScreenY(var2);
    float var11 = this.worldToScreenX(var1 + var3);
    float var12 = this.worldToScreenY(var2 + var4);
      var3 = var11 - var9;
      var4 = var12 - var10;
      if (!(var9 >= this.offx + this.draww) && !(var11 < this.offx) && !(var10 >= this.offy + this.drawh) && !(var12 < this.offy)) {
         SpriteRenderer.instance.render(nullptr, var9, var10, var3, var4, var5, var6, var7, var8, nullptr);
      }
   }
}
} // namespace ui
} // namespace zombie
