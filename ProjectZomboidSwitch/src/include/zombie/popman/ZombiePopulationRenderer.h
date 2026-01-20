#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/MapCollisionData.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/ai/states/WalkTowardState.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/config/BooleanConfigOption.h"
#include "zombie/config/ConfigFile.h"
#include "zombie/config/ConfigOption.h"
#include "zombie/core/Core.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/iso/BuildingDef.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoChunkMap.h"
#include "zombie/iso/IsoMetaCell.h"
#include "zombie/iso/IsoMetaGrid.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/LotHeader.h"
#include "zombie/iso/RoomDef.h"
#include "zombie/iso/RoomDef/RoomRect.h"
#include "zombie/network/GameClient.h"
#include "zombie/popman/ZombiePopulationRenderer/BooleanDebugOption.h"
#include "zombie/ui/TextManager.h"
#include "zombie/ui/UIElement.h"
#include "zombie/ui/UIFont.h"
#include "zombie/vehicles/VehiclesDB2.h"
#include <fstream>
#include <iostream>

namespace zombie {
namespace popman {


class ZombiePopulationRenderer {
public:
    float xPos;
    float yPos;
    float offx;
    float offy;
    float zoom;
    float draww;
    float drawh;
    static const int VERSION = 1;
   private const std::vector<ConfigOption> options = std::make_unique<std::vector<>>();
    BooleanDebugOption CellGrid = std::make_shared<BooleanDebugOption>(this, "CellGrid", true);
    BooleanDebugOption MetaGridBuildings = std::make_shared<BooleanDebugOption>(this, "MetaGrid.Buildings", true);
    BooleanDebugOption ZombiesStanding = std::make_shared<BooleanDebugOption>(this, "Zombies.Standing", true);
    BooleanDebugOption ZombiesMoving = std::make_shared<BooleanDebugOption>(this, "Zombies.Moving", true);
    BooleanDebugOption MCDObstacles = std::make_shared<BooleanDebugOption>(this, "MapCollisionData.Obstacles", true);
    BooleanDebugOption MCDRegularChunkOutlines = std::make_shared<BooleanDebugOption>(this, "MapCollisionData.RegularChunkOutlines", true);
    BooleanDebugOption MCDRooms = std::make_shared<BooleanDebugOption>(this, "MapCollisionData.Rooms", true);
    BooleanDebugOption Vehicles = std::make_shared<BooleanDebugOption>(this, "Vehicles", true);

   private native void n_render(float var1, int var2, int var3, float var4, float var5, int var6, int var7);

   private native void n_setWallFollowerStart(int var1, int var2);

   private native void n_setWallFollowerEnd(int var1, int var2);

   private native void n_wallFollowerMouseMove(int var1, int var2);

   private native void n_setDebugOption(std::string var1, std::string var2);

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

    float uiToWorldX(float var1) {
      var1 -= this.draww / 2.0F;
      var1 /= this.zoom;
      return var1 + this.xPos;
   }

    float uiToWorldY(float var1) {
      var1 -= this.drawh / 2.0F;
      var1 /= this.zoom;
      return var1 + this.yPos;
   }

    void renderString(float var1, float var2, const std::string& var3, double var4, double var6, double var8, double var10) {
    float var12 = this.worldToScreenX(var1);
    float var13 = this.worldToScreenY(var2);
      SpriteRenderer.instance
         .render(
            nullptr,
            var12 - 2.0F,
            var13 - 2.0F,
            TextManager.instance.MeasureStringX(UIFont.Small, var3) + 4,
            TextManager.instance.font.getLineHeight() + 4,
            0.0F,
            0.0F,
            0.0F,
            0.75F,
            nullptr
         );
      TextManager.instance.DrawString(var12, var13, var3, var4, var6, var8, var10);
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

    void renderLine(float var1, float var2, float var3, float var4, float var5, float var6, float var7, float var8) {
    float var9 = this.worldToScreenX(var1);
    float var10 = this.worldToScreenY(var2);
    float var11 = this.worldToScreenX(var3);
    float var12 = this.worldToScreenY(var4);
      if ((!(var9 >= Core.getInstance().getScreenWidth()) || !(var11 >= Core.getInstance().getScreenWidth()))
         && (!(var10 >= Core.getInstance().getScreenHeight()) || !(var12 >= Core.getInstance().getScreenHeight()))
         && (!(var9 < 0.0F) || !(var11 < 0.0F))
         && (!(var10 < 0.0F) || !(var12 < 0.0F))) {
         SpriteRenderer.instance.renderline(nullptr, (int)var9, (int)var10, (int)var11, (int)var12, var5, var6, var7, var8);
      }
   }

    void renderCircle(float var1, float var2, float var3, float var4, float var5, float var6, float var7) {
    uint8_t var8 = 32;
    double var9 = var1 + var3 * Math.cos(Math.toRadians(0.0F / var8));
    double var11 = var2 + var3 * Math.sin(Math.toRadians(0.0F / var8));

      for (int var13 = 1; var13 <= var8; var13++) {
    double var14 = var1 + var3 * Math.cos(Math.toRadians(var13 * 360.0F / var8));
    double var16 = var2 + var3 * Math.sin(Math.toRadians(var13 * 360.0F / var8));
    int var18 = (int)this.worldToScreenX((float)var9);
    int var19 = (int)this.worldToScreenY((float)var11);
    int var20 = (int)this.worldToScreenX((float)var14);
    int var21 = (int)this.worldToScreenY((float)var16);
         SpriteRenderer.instance.renderline(nullptr, var18, var19, var20, var21, var4, var5, var6, var7);
         var9 = var14;
         var11 = var16;
      }
   }

    void renderZombie(float var1, float var2, float var3, float var4, float var5) {
    float var6 = 1.0F / this.zoom + 0.5F;
      this.renderRect(var1 - var6 / 2.0F, var2 - var6 / 2.0F, var6, var6, var3, var4, var5, 1.0F);
   }

    void renderVehicle(int var1, float var2, float var3, float var4, float var5, float var6) {
    float var7 = 2.0F / this.zoom + 0.5F;
      this.renderRect(var2 - var7 / 2.0F, var3 - var7 / 2.0F, var7, var7, var4, var5, var6, 1.0F);
      this.renderString(var2, var3, std::string.format("%d", var1), var4, var5, var6, 1.0);
   }

    void outlineRect(float var1, float var2, float var3, float var4, float var5, float var6, float var7, float var8) {
      this.renderLine(var1, var2, var1 + var3, var2, var5, var6, var7, var8);
      this.renderLine(var1 + var3, var2, var1 + var3, var2 + var4, var5, var6, var7, var8);
      this.renderLine(var1, var2 + var4, var1 + var3, var2 + var4, var5, var6, var7, var8);
      this.renderLine(var1, var2, var1, var2 + var4, var5, var6, var7, var8);
   }

    void renderCellInfo(int var1, int var2, int var3, int var4, float var5) {
    float var6 = this.worldToScreenX(var1 * 300) + 4.0F;
    float var7 = this.worldToScreenY(var2 * 300) + 4.0F;
    std::string var8 = var3 + " / " + var4;
      if (var5 > 0.0F) {
         var8 = var8 + std::string.format(" %.2f", var5);
      }

      SpriteRenderer.instance
         .render(
            nullptr,
            var6 - 2.0F,
            var7 - 2.0F,
            TextManager.instance.MeasureStringX(UIFont.Small, var8) + 4,
            TextManager.instance.font.getLineHeight() + 4,
            0.0F,
            0.0F,
            0.0F,
            0.75F,
            nullptr
         );
      TextManager.instance.DrawString(var6, var7, var8, 1.0, 1.0, 1.0, 1.0);
   }

    void render(UIElement var1, float var2, float var3, float var4) {
      /* synchronized - TODO: add std::mutex */ (MapCollisionData.instance.renderLock) {
         this._render(var1, var2, var3, var4);
      }
   }

    void _render(UIElement var1, float var2, float var3, float var4) {
      this.draww = var1.getWidth().intValue();
      this.drawh = var1.getHeight().intValue();
      this.xPos = var3;
      this.yPos = var4;
      this.offx = var1.getAbsoluteX().intValue();
      this.offy = var1.getAbsoluteY().intValue();
      this.zoom = var2;
    IsoCell var5 = IsoWorld.instance.CurrentCell;
    IsoChunkMap var6 = IsoWorld.instance.CurrentCell.ChunkMap[0];
    IsoMetaGrid var7 = IsoWorld.instance.MetaGrid;
      IsoMetaCell[][] var8 = var7.Grid;
    int var9 = (int)(this.uiToWorldX(0.0F) / 300.0F) - var7.minX;
    int var10 = (int)(this.uiToWorldY(0.0F) / 300.0F) - var7.minY;
    int var11 = (int)(this.uiToWorldX(this.draww) / 300.0F) + 1 - var7.minX;
    int var12 = (int)(this.uiToWorldY(this.drawh) / 300.0F) + 1 - var7.minY;
      var9 = PZMath.clamp(var9, 0, var7.getWidth() - 1);
      var10 = PZMath.clamp(var10, 0, var7.getHeight() - 1);
      var11 = PZMath.clamp(var11, 0, var7.getWidth() - 1);
      var12 = PZMath.clamp(var12, 0, var7.getHeight() - 1);
      if (this.MetaGridBuildings.getValue()) {
         for (int var13 = var9; var13 <= var11; var13++) {
            for (int var14 = var10; var14 <= var12; var14++) {
    LotHeader var15 = var8[var13][var14].info;
               if (var15 != nullptr) {
                  for (int var16 = 0; var16 < var15.Buildings.size(); var16++) {
    BuildingDef var17 = (BuildingDef)var15.Buildings.get(var16);

                     for (int var18 = 0; var18 < var17.rooms.size(); var18++) {
                        if (((RoomDef)var17.rooms.get(var18)).level <= 0) {
    std::vector var19 = ((RoomDef)var17.rooms.get(var18)).getRects();

                           for (int var20 = 0; var20 < var19.size(); var20++) {
    RoomRect var21 = (RoomRect)var19.get(var20);
                              if (var17.bAlarmed) {
                                 this.renderRect(var21.getX(), var21.getY(), var21.getW(), var21.getH(), 0.8F, 0.8F, 0.5F, 0.3F);
                              } else {
                                 this.renderRect(var21.getX(), var21.getY(), var21.getW(), var21.getH(), 0.5F, 0.5F, 0.8F, 0.3F);
                              }
                           }
                        }
                     }
                  }
               }
            }
         }
      }

      if (this.CellGrid.getValue()) {
         for (int var26 = var10; var26 <= var12; var26++) {
            this.renderLine(var7.minX * 300, (var7.minY + var26) * 300, (var7.maxX + 1) * 300, (var7.minY + var26) * 300, 1.0F, 1.0F, 1.0F, 0.15F);
         }

         for (int var27 = var9; var27 <= var11; var27++) {
            this.renderLine((var7.minX + var27) * 300, var7.minY * 300, (var7.minX + var27) * 300, (var7.maxY + 1) * 300, 1.0F, 1.0F, 1.0F, 0.15F);
         }
      }

      for (int var28 = 0; var28 < IsoWorld.instance.CurrentCell.getZombieList().size(); var28++) {
    IsoZombie var30 = (IsoZombie)IsoWorld.instance.CurrentCell.getZombieList().get(var28);
    float var32 = 1.0F;
    float var33 = 1.0F;
    float var34 = 0.0F;
         if (var30.isReanimatedPlayer()) {
            var32 = 0.0F;
         }

         this.renderZombie(var30.x, var30.y, var32, var33, var34);
         if (var30.getCurrentState() == WalkTowardState.instance()) {
            this.renderLine(var30.x, var30.y, var30.getPathTargetX(), var30.getPathTargetY(), 1.0F, 1.0F, 1.0F, 0.5F);
         }
      }

      for (int var29 = 0; var29 < IsoPlayer.numPlayers; var29++) {
    IsoPlayer var31 = IsoPlayer.players[var29];
         if (var31 != nullptr) {
            this.renderZombie(var31.x, var31.y, 0.0F, 0.5F, 0.0F);
         }
      }

      if (GameClient.bClient) {
         MPDebugInfo.instance.render(this, var2);
      } else {
         if (this.Vehicles.getValue()) {
            VehiclesDB2.instance.renderDebug(this);
         }

         this.n_render(var2, (int)this.offx, (int)this.offy, var3, var4, (int)this.draww, (int)this.drawh);
      }
   }

    void setWallFollowerStart(int var1, int var2) {
      if (!GameClient.bClient) {
         this.n_setWallFollowerStart(var1, var2);
      }
   }

    void setWallFollowerEnd(int var1, int var2) {
      if (!GameClient.bClient) {
         this.n_setWallFollowerEnd(var1, var2);
      }
   }

    void wallFollowerMouseMove(int var1, int var2) {
      if (!GameClient.bClient) {
         this.n_wallFollowerMouseMove(var1, var2);
      }
   }

    ConfigOption getOptionByName(const std::string& var1) {
      for (int var2 = 0; var2 < this.options.size(); var2++) {
    ConfigOption var3 = this.options.get(var2);
         if (var3.getName() == var1)) {
    return var3;
         }
      }

    return nullptr;
   }

    int getOptionCount() {
      return this.options.size();
   }

    ConfigOption getOptionByIndex(int var1) {
      return this.options.get(var1);
   }

    void setBoolean(const std::string& var1, bool var2) {
    ConfigOption var3 = this.getOptionByName(var1);
      if (dynamic_cast<BooleanConfigOption*>(var3) != nullptr) {
         ((BooleanConfigOption)var3).setValue(var2);
      }
   }

    bool getBoolean(const std::string& var1) {
    ConfigOption var2 = this.getOptionByName(var1);
      return dynamic_cast<BooleanConfigOption*>(var2) != nullptr ? ((BooleanConfigOption)var2).getValue() : false;
   }

    void save() {
    std::string var1 = ZomboidFileSystem.instance.getCacheDir() + File.separator + "popman-options.ini";
    ConfigFile var2 = std::make_shared<ConfigFile>();
      var2.write(var1, 1, this.options);

      for (int var3 = 0; var3 < this.options.size(); var3++) {
    ConfigOption var4 = this.options.get(var3);
         this.n_setDebugOption(var4.getName(), var4.getValueAsString());
      }
   }

    void load() {
    std::string var1 = ZomboidFileSystem.instance.getCacheDir() + File.separator + "popman-options.ini";
    ConfigFile var2 = std::make_shared<ConfigFile>();
      if (var2.read(var1)) {
         for (int var3 = 0; var3 < var2.getOptions().size(); var3++) {
    ConfigOption var4 = (ConfigOption)var2.getOptions().get(var3);
    ConfigOption var5 = this.getOptionByName(var4.getName());
            if (var5 != nullptr) {
               var5.parse(var4.getValueAsString());
            }
         }
      }

      for (int var6 = 0; var6 < this.options.size(); var6++) {
    ConfigOption var7 = this.options.get(var6);
         this.n_setDebugOption(var7.getName(), var7.getValueAsString());
      }
   }
}
} // namespace popman
} // namespace zombie
