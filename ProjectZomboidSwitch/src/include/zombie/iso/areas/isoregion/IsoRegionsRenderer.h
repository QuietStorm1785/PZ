#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/MapCollisionData.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/config/BooleanConfigOption.h"
#include "zombie/config/ConfigFile.h"
#include "zombie/config/ConfigOption.h"
#include "zombie/core/Color.h"
#include "zombie/core/Colors.h"
#include "zombie/core/Core.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/utils/Bits.h"
#include "zombie/iso/BuildingDef.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoMetaCell.h"
#include "zombie/iso/IsoMetaGrid.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/LotHeader.h"
#include "zombie/iso/RoomDef.h"
#include "zombie/iso/RoomDef/RoomRect.h"
#include "zombie/iso/areas/isoregion/IsoRegionsRenderer/BooleanDebugOption.h"
#include "zombie/iso/areas/isoregion/data/DataChunk.h"
#include "zombie/iso/areas/isoregion/data/DataRoot.h"
#include "zombie/iso/areas/isoregion/regions/IsoChunkRegion.h"
#include "zombie/iso/areas/isoregion/regions/IsoWorldRegion.h"
#include "zombie/iso/objects/IsoThumpable.h"
#include "zombie/ui/TextManager.h"
#include "zombie/ui/UIElement.h"
#include "zombie/ui/UIFont.h"
#include <fstream>
#include <iostream>

namespace zombie {
namespace iso {
namespace areas {
namespace isoregion {


class IsoRegionsRenderer {
public:
   private const List<DataChunk> tempChunkList = std::make_unique<std::vector<>>();
   private const List<std::string> debugLines = std::make_unique<std::vector<>>();
    float xPos;
    float yPos;
    float offx;
    float offy;
    float zoom;
    float draww;
    float drawh;
    bool hasSelected = false;
    bool validSelection = false;
    int selectedX;
    int selectedY;
    int selectedZ;
   private const std::unordered_set<int> drawnCells = std::make_unique<std::unordered_set<>>();
    bool editSquareInRange = false;
    int editSquareX;
    int editSquareY;
   private const std::vector<ConfigOption> editOptions = std::make_unique<std::vector<>>();
    bool EditingEnabled = false;
    const BooleanDebugOption EditWallN = std::make_shared<BooleanDebugOption>(this.editOptions, "Edit.WallN", false);
    const BooleanDebugOption EditWallW = std::make_shared<BooleanDebugOption>(this.editOptions, "Edit.WallW", false);
    const BooleanDebugOption EditDoorN = std::make_shared<BooleanDebugOption>(this.editOptions, "Edit.DoorN", false);
    const BooleanDebugOption EditDoorW = std::make_shared<BooleanDebugOption>(this.editOptions, "Edit.DoorW", false);
    const BooleanDebugOption EditFloor = std::make_shared<BooleanDebugOption>(this.editOptions, "Edit.Floor", false);
   private const std::vector<ConfigOption> zLevelOptions = std::make_unique<std::vector<>>();
    const BooleanDebugOption zLevelPlayer = std::make_shared<BooleanDebugOption>(this.zLevelOptions, "zLevel.Player", true);
    const BooleanDebugOption zLevel0 = std::make_shared<BooleanDebugOption>(this.zLevelOptions, "zLevel.0", false, 0);
    const BooleanDebugOption zLevel1 = std::make_shared<BooleanDebugOption>(this.zLevelOptions, "zLevel.1", false, 1);
    const BooleanDebugOption zLevel2 = std::make_shared<BooleanDebugOption>(this.zLevelOptions, "zLevel.2", false, 2);
    const BooleanDebugOption zLevel3 = std::make_shared<BooleanDebugOption>(this.zLevelOptions, "zLevel.3", false, 3);
    const BooleanDebugOption zLevel4 = std::make_shared<BooleanDebugOption>(this.zLevelOptions, "zLevel.4", false, 4);
    const BooleanDebugOption zLevel5 = std::make_shared<BooleanDebugOption>(this.zLevelOptions, "zLevel.5", false, 5);
    const BooleanDebugOption zLevel6 = std::make_shared<BooleanDebugOption>(this.zLevelOptions, "zLevel.6", false, 6);
    const BooleanDebugOption zLevel7 = std::make_shared<BooleanDebugOption>(this.zLevelOptions, "zLevel.7", false, 7);
    static const int VERSION = 1;
   private const std::vector<ConfigOption> options = std::make_unique<std::vector<>>();
    const BooleanDebugOption CellGrid = std::make_shared<BooleanDebugOption>(this.options, "CellGrid", true);
    const BooleanDebugOption MetaGridBuildings = std::make_shared<BooleanDebugOption>(this.options, "MetaGrid.Buildings", true);
    const BooleanDebugOption IsoRegionRender = std::make_shared<BooleanDebugOption>(this.options, "IsoRegion.Render", true);
    const BooleanDebugOption IsoRegionRenderChunks = std::make_shared<BooleanDebugOption>(this.options, "IsoRegion.RenderChunks", false);
    const BooleanDebugOption IsoRegionRenderChunksPlus = std::make_shared<BooleanDebugOption>(this.options, "IsoRegion.RenderChunksPlus", false);

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

    void renderStringUI(float var1, float var2, const std::string& var3, Color var4) {
      this.renderStringUI(var1, var2, var3, var4.r, var4.g, var4.b, var4.a);
   }

    void renderStringUI(float var1, float var2, const std::string& var3, double var4, double var6, double var8, double var10) {
    float var12 = this.offx + var1;
    float var13 = this.offy + var2;
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

    void renderZombie(float var1, float var2, float var3, float var4, float var5) {
    float var6 = 1.0F / this.zoom + 0.5F;
      this.renderRect(var1 - var6 / 2.0F, var2 - var6 / 2.0F, var6, var6, var3, var4, var5, 1.0F);
   }

    void renderSquare(float var1, float var2, float var3, float var4, float var5, float var6) {
    float var7 = 1.0F;
      this.renderRect(var1, var2, var7, var7, var3, var4, var5, var6);
   }

    void renderEntity(float var1, float var2, float var3, float var4, float var5, float var6, float var7) {
    float var8 = var1 / this.zoom + 0.5F;
      this.renderRect(var2 - var8 / 2.0F, var3 - var8 / 2.0F, var8, var8, var4, var5, var6, var7);
   }

    void render(UIElement var1, float var2, float var3, float var4) {
      /* synchronized - TODO: add std::mutex */ (MapCollisionData.instance.renderLock) {
         this._render(var1, var2, var3, var4);
      }
   }

    void debugLine(const std::string& var1) {
      this.debugLines.push_back(var1);
   }

    void recalcSurroundings() {
      IsoRegions.forceRecalcSurroundingChunks();
   }

    bool hasChunkRegion(int var1, int var2) {
    int var3 = this.getZLevel();
    DataRoot var4 = IsoRegions.getDataRoot();
      return var4.getIsoChunkRegion(var1, var2, var3) != nullptr;
   }

    IsoChunkRegion getChunkRegion(int var1, int var2) {
    int var3 = this.getZLevel();
    DataRoot var4 = IsoRegions.getDataRoot();
      return var4.getIsoChunkRegion(var1, var2, var3);
   }

    void setSelected(int var1, int var2) {
      this.setSelectedWorld((int)this.uiToWorldX(var1), (int)this.uiToWorldY(var2));
   }

    void setSelectedWorld(int var1, int var2) {
      this.selectedZ = this.getZLevel();
      this.hasSelected = true;
      this.selectedX = var1;
      this.selectedY = var2;
   }

    void unsetSelected() {
      this.hasSelected = false;
   }

    bool isHasSelected() {
      return this.hasSelected;
   }

    void _render(UIElement var1, float var2, float var3, float var4) {
      this.debugLines.clear();
      this.drawnCells.clear();
      this.draww = var1.getWidth().intValue();
      this.drawh = var1.getHeight().intValue();
      this.xPos = var3;
      this.yPos = var4;
      this.offx = var1.getAbsoluteX().intValue();
      this.offy = var1.getAbsoluteY().intValue();
      this.zoom = var2;
      this.debugLine("Zoom: " + var2);
      this.debugLine("zLevel: " + this.getZLevel());
    IsoMetaGrid var5 = IsoWorld.instance.MetaGrid;
      IsoMetaCell[][] var6 = var5.Grid;
    int var7 = (int)(this.uiToWorldX(0.0F) / 300.0F) - var5.minX;
    int var8 = (int)(this.uiToWorldY(0.0F) / 300.0F) - var5.minY;
    int var9 = (int)(this.uiToWorldX(this.draww) / 300.0F) + 1 - var5.minX;
    int var10 = (int)(this.uiToWorldY(this.drawh) / 300.0F) + 1 - var5.minY;
      var7 = PZMath.clamp(var7, 0, var5.getWidth() - 1);
      var8 = PZMath.clamp(var8, 0, var5.getHeight() - 1);
      var9 = PZMath.clamp(var9, 0, var5.getWidth() - 1);
      var10 = PZMath.clamp(var10, 0, var5.getHeight() - 1);
    float var11 = Math.max(1.0F - var2 / 2.0F, 0.1F);
    IsoChunkRegion var12 = nullptr;
    IsoWorldRegion var13 = nullptr;
      this.validSelection = false;
      if (this.IsoRegionRender.getValue()) {
    IsoPlayer var14 = IsoPlayer.getInstance();
    DataRoot var15 = IsoRegions.getDataRoot();
         this.tempChunkList.clear();
         var15.getAllChunks(this.tempChunkList);
         this.debugLine("DataChunks: " + this.tempChunkList.size());
         this.debugLine("IsoChunkRegions: " + var15.regionManager.getChunkRegionCount());
         this.debugLine("IsoWorldRegions: " + var15.regionManager.getWorldRegionCount());
         if (this.hasSelected) {
            var12 = var15.getIsoChunkRegion(this.selectedX, this.selectedY, this.selectedZ);
            var13 = var15.getIsoWorldRegion(this.selectedX, this.selectedY, this.selectedZ);
            if (var13 != nullptr && !var13.isEnclosed() && (!this.IsoRegionRenderChunks.getValue() || !this.IsoRegionRenderChunksPlus.getValue())) {
               var13 = nullptr;
               var12 = nullptr;
            }

            if (var12 != nullptr) {
               this.validSelection = true;
            }
         }

         for (int var23 = 0; var23 < this.tempChunkList.size(); var23++) {
    DataChunk var16 = this.tempChunkList.get(var23);
    int var17 = var16.getChunkX() * 10;
    int var18 = var16.getChunkY() * 10;
            if (var2 > 0.1F) {
    float var19 = this.worldToScreenX(var17);
    float var21 = this.worldToScreenY(var18);
    float var20 = this.worldToScreenX(var17 + 10);
    float var22 = this.worldToScreenY(var18 + 10);
               if (!(var19 >= this.offx + this.draww) && !(var20 < this.offx) && !(var21 >= this.offy + this.drawh) && !(var22 < this.offy)) {
                  this.renderRect(var17, var18, 10.0F, 10.0F, 0.0F, var11, 0.0F, 1.0F);
               }
            }
         }
      }

      if (this.MetaGridBuildings.getValue()) {
    float var39 = PZMath.clamp(0.3F * (var2 / 5.0F), 0.15F, 0.3F);

         for (int var45 = var7; var45 < var9; var45++) {
            for (int var52 = var8; var52 < var10; var52++) {
    LotHeader var56 = var6[var45][var52].info;
               if (var56 != nullptr) {
                  for (int var58 = 0; var58 < var56.Buildings.size(); var58++) {
    BuildingDef var60 = (BuildingDef)var56.Buildings.get(var58);

                     for (int var63 = 0; var63 < var60.rooms.size(); var63++) {
                        if (((RoomDef)var60.rooms.get(var63)).level <= 0) {
    std::vector var66 = ((RoomDef)var60.rooms.get(var63)).getRects();

                           for (int var69 = 0; var69 < var66.size(); var69++) {
    RoomRect var71 = (RoomRect)var66.get(var69);
                              if (var60.bAlarmed) {
                                 this.renderRect(var71.getX(), var71.getY(), var71.getW(), var71.getH(), 0.8F * var39, 0.8F * var39, 0.5F * var39, 1.0F);
                              } else {
                                 this.renderRect(var71.getX(), var71.getY(), var71.getW(), var71.getH(), 0.5F * var39, 0.5F * var39, 0.8F * var39, 1.0F);
                              }
                           }
                        }
                     }
                  }
               }
            }
         }
      }

      if (this.IsoRegionRender.getValue()) {
    int var40 = this.getZLevel();
    DataRoot var46 = IsoRegions.getDataRoot();
         this.tempChunkList.clear();
         var46.getAllChunks(this.tempChunkList);
    float var27 = 1.0F;

         for (int var28 = 0; var28 < this.tempChunkList.size(); var28++) {
    DataChunk var53 = this.tempChunkList.get(var28);
    int var57 = var53.getChunkX() * 10;
    int var59 = var53.getChunkY() * 10;
            if (var2 <= 0.1F) {
    int var75 = var57 / 300;
    int var76 = var59 / 300;
    int var77 = IsoRegions.hash(var75, var76);
               if (!this.drawnCells.contains(var77)) {
                  this.drawnCells.push_back(var77);
                  this.renderRect(var75 * 300, var76 * 300, 300.0F, 300.0F, 0.0F, var11, 0.0F, 1.0F);
               }
            } else if (!(var2 < 1.0F)) {
    float var70 = this.worldToScreenX(var57);
    float var24 = this.worldToScreenY(var59);
    float var72 = this.worldToScreenX(var57 + 10);
    float var25 = this.worldToScreenY(var59 + 10);
               if (!(var70 >= this.offx + this.draww) && !(var72 < this.offx) && !(var24 >= this.offy + this.drawh) && !(var25 < this.offy)) {
                  for (int var29 = 0; var29 < 10; var29++) {
                     for (int var30 = 0; var30 < 10; var30++) {
    int var31 = var40 > 0 ? var40 - 1 : var40;

                        for (int var32 = var31; var32 <= var40; var32++) {
    float var33 = var32 < var40 ? 0.25F : 1.0F;
    uint8_t var26 = var53.getSquare(var29, var30, var32);
                           if (var26 >= 0) {
    IsoChunkRegion var61 = var53.getIsoChunkRegion(var29, var30, var32);
                              if (var61 != nullptr) {
                                 if (var2 > 6.0F && this.IsoRegionRenderChunks.getValue() && this.IsoRegionRenderChunksPlus.getValue()) {
    Color var68 = var61.getColor();
                                    var27 = 1.0F;
                                    if (var12 != nullptr && var61 != var12) {
                                       var27 = 0.25F;
                                    }

                                    this.renderSquare(var57 + var29, var59 + var30, var68.r, var68.g, var68.b, var27 * var33);
                                 } else {
    IsoWorldRegion var64 = var61.getIsoWorldRegion();
                                    if (var64 != nullptr && var64.isEnclosed()) {
                                       var27 = 1.0F;
    Color var67;
                                       if (this.IsoRegionRenderChunks.getValue()) {
                                          var67 = var61.getColor();
                                          if (var12 != nullptr && var61 != var12) {
                                             var27 = 0.25F;
                                          }
                                       } else {
                                          var67 = var64.getColor();
                                          if (var13 != nullptr && var64 != var13) {
                                             var27 = 0.25F;
                                          }
                                       }

                                       this.renderSquare(var57 + var29, var59 + var30, var67.r, var67.g, var67.b, var27 * var33);
                                    }
                                 }
                              }

                              if (var32 > 0 && var32 == var40) {
                                 var61 = var53.getIsoChunkRegion(var29, var30, var32);
    IsoWorldRegion var65 = var61 != nullptr ? var61.getIsoWorldRegion() : nullptr;
    bool var34 = var61 == nullptr || var65 == nullptr || !var65.isEnclosed();
                                 if (var34 && Bits.hasFlags(var26, 16)) {
                                    this.renderSquare(var57 + var29, var59 + var30, 0.5F, 0.5F, 0.5F, 1.0F);
                                 }
                              }

                              if (Bits.hasFlags(var26, 1) || Bits.hasFlags(var26, 4)) {
                                 this.renderRect(var57 + var29, var59 + var30, 1.0F, 0.1F, 1.0F, 1.0F, 1.0F, 1.0F * var33);
                              }

                              if (Bits.hasFlags(var26, 2) || Bits.hasFlags(var26, 8)) {
                                 this.renderRect(var57 + var29, var59 + var30, 0.1F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F * var33);
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
    float var41 = 1.0F;
         if (var2 < 0.1F) {
            var41 = Math.max(var2 / 0.1F, 0.25F);
         }

         for (int var47 = var8; var47 <= var10; var47++) {
            this.renderLine(var5.minX * 300, (var5.minY + var47) * 300, (var5.maxX + 1) * 300, (var5.minY + var47) * 300, 1.0F, 1.0F, 1.0F, 0.15F * var41);
            if (var2 > 1.0F) {
               for (int var54 = 1; var54 < 30; var54++) {
                  this.renderLine(
                     var5.minX * 300,
                     (var5.minY + var47) * 300 + var54 * 10,
                     (var5.maxX + 1) * 300,
                     (var5.minY + var47) * 300 + var54 * 10,
                     1.0F,
                     1.0F,
                     1.0F,
                     0.0325F
                  );
               }
            } else if (var2 > 0.15F) {
               this.renderLine(
                  var5.minX * 300, (var5.minY + var47) * 300 + 100, (var5.maxX + 1) * 300, (var5.minY + var47) * 300 + 100, 1.0F, 1.0F, 1.0F, 0.075F
               );
               this.renderLine(
                  var5.minX * 300, (var5.minY + var47) * 300 + 200, (var5.maxX + 1) * 300, (var5.minY + var47) * 300 + 200, 1.0F, 1.0F, 1.0F, 0.075F
               );
            }
         }

         for (int var48 = var7; var48 <= var9; var48++) {
            this.renderLine((var5.minX + var48) * 300, var5.minY * 300, (var5.minX + var48) * 300, (var5.maxY + 1) * 300, 1.0F, 1.0F, 1.0F, 0.15F * var41);
            if (var2 > 1.0F) {
               for (int var55 = 1; var55 < 30; var55++) {
                  this.renderLine(
                     (var5.minX + var48) * 300 + var55 * 10,
                     var5.minY * 300,
                     (var5.minX + var48) * 300 + var55 * 10,
                     (var5.maxY + 1) * 300,
                     1.0F,
                     1.0F,
                     1.0F,
                     0.0325F
                  );
               }
            } else if (var2 > 0.15F) {
               this.renderLine(
                  (var5.minX + var48) * 300 + 100, var5.minY * 300, (var5.minX + var48) * 300 + 100, (var5.maxY + 1) * 300, 1.0F, 1.0F, 1.0F, 0.075F
               );
               this.renderLine(
                  (var5.minX + var48) * 300 + 200, var5.minY * 300, (var5.minX + var48) * 300 + 200, (var5.maxY + 1) * 300, 1.0F, 1.0F, 1.0F, 0.075F
               );
            }
         }
      }

      for (int var42 = 0; var42 < IsoPlayer.numPlayers; var42++) {
    IsoPlayer var49 = IsoPlayer.players[var42];
         if (var49 != nullptr) {
            this.renderZombie(var49.x, var49.y, 0.0F, 0.5F, 0.0F);
         }
      }

      if (this.isEditingEnabled()) {
    float var43 = this.editSquareInRange ? 0.0F : 1.0F;
    float var50 = this.editSquareInRange ? 1.0F : 0.0F;
         if (this.EditWallN.getValue() || this.EditDoorN.getValue()) {
            this.renderRect(this.editSquareX, this.editSquareY, 1.0F, 0.25F, var43, var50, 0.0F, 0.5F);
            this.renderRect(this.editSquareX, this.editSquareY, 1.0F, 0.05F, var43, var50, 0.0F, 1.0F);
            this.renderRect(this.editSquareX, this.editSquareY, 0.05F, 0.25F, var43, var50, 0.0F, 1.0F);
            this.renderRect(this.editSquareX, this.editSquareY + 0.2F, 1.0F, 0.05F, var43, var50, 0.0F, 1.0F);
            this.renderRect(this.editSquareX + 0.95F, this.editSquareY, 0.05F, 0.25F, var43, var50, 0.0F, 1.0F);
         } else if (!this.EditWallW.getValue() && !this.EditDoorW.getValue()) {
            this.renderRect(this.editSquareX, this.editSquareY, 1.0F, 1.0F, var43, var50, 0.0F, 0.5F);
            this.renderRect(this.editSquareX, this.editSquareY, 1.0F, 0.05F, var43, var50, 0.0F, 1.0F);
            this.renderRect(this.editSquareX, this.editSquareY, 0.05F, 1.0F, var43, var50, 0.0F, 1.0F);
            this.renderRect(this.editSquareX, this.editSquareY + 0.95F, 1.0F, 0.05F, var43, var50, 0.0F, 1.0F);
            this.renderRect(this.editSquareX + 0.95F, this.editSquareY, 0.05F, 1.0F, var43, var50, 0.0F, 1.0F);
         } else {
            this.renderRect(this.editSquareX, this.editSquareY, 0.25F, 1.0F, var43, var50, 0.0F, 0.5F);
            this.renderRect(this.editSquareX, this.editSquareY, 0.25F, 0.05F, var43, var50, 0.0F, 1.0F);
            this.renderRect(this.editSquareX, this.editSquareY, 0.05F, 1.0F, var43, var50, 0.0F, 1.0F);
            this.renderRect(this.editSquareX, this.editSquareY + 0.95F, 0.25F, 0.05F, var43, var50, 0.0F, 1.0F);
            this.renderRect(this.editSquareX + 0.2F, this.editSquareY, 0.05F, 1.0F, var43, var50, 0.0F, 1.0F);
         }
      }

      if (var12 != nullptr) {
         this.debugLine("- ChunkRegion -");
         this.debugLine("ID: " + var12.getID());
         this.debugLine("Squares: " + var12.getSquareSize());
         this.debugLine("Roofs: " + var12.getRoofCnt());
         this.debugLine("Neighbors: " + var12.getNeighborCount());
         this.debugLine("ConnectedNeighbors: " + var12.getConnectedNeighbors().size());
         this.debugLine("FullyEnclosed: " + var12.getIsEnclosed());
      }

      if (var13 != nullptr) {
         this.debugLine("- WorldRegion -");
         this.debugLine("ID: " + var13.getID());
         this.debugLine("Squares: " + var13.getSquareSize());
         this.debugLine("Roofs: " + var13.getRoofCnt());
         this.debugLine("IsFullyRoofed: " + var13.isFullyRoofed());
         this.debugLine("RoofPercentage: " + var13.getRoofedPercentage());
         this.debugLine("IsEnclosed: " + var13.isEnclosed());
         this.debugLine("Neighbors: " + var13.getNeighbors().size());
         this.debugLine("ChunkRegionCount: " + var13.size());
      }

    uint8_t var44 = 15;

      for (int var51 = 0; var51 < this.debugLines.size(); var51++) {
         this.renderStringUI(10.0F, var44, this.debugLines.get(var51), Colors.CornFlowerBlue);
         var44 += 18;
      }
   }

    void setEditSquareCoord(int var1, int var2) {
      this.editSquareX = var1;
      this.editSquareY = var2;
      this.editSquareInRange = false;
      if (this.editCoordInRange(var1, var2)) {
         this.editSquareInRange = true;
      }
   }

    bool editCoordInRange(int var1, int var2) {
    IsoGridSquare var3 = IsoWorld.instance.getCell().getGridSquare(var1, var2, 0);
      return var3 != nullptr;
   }

    void editSquare(int var1, int var2) {
      if (this.isEditingEnabled()) {
    int var3 = this.getZLevel();
    IsoGridSquare var4 = IsoWorld.instance.getCell().getGridSquare(var1, var2, var3);
    DataRoot var5 = IsoRegions.getDataRoot();
    uint8_t var6 = var5.getSquareFlags(var1, var2, var3);
         if (this.editCoordInRange(var1, var2)) {
            if (var4 == nullptr) {
               var4 = IsoWorld.instance.getCell().createNewGridSquare(var1, var2, var3, true);
               if (var4 == nullptr) {
                  return;
               }
            }

            this.editSquareInRange = true;

            for (int var7 = 0; var7 < this.editOptions.size(); var7++) {
    BooleanDebugOption var8 = (BooleanDebugOption)this.editOptions.get(var7);
               if (var8.getValue()) {
    std::string var9 = var8.getName();
                  switch (var9) {
                     case "Edit.WallW":
                     case "Edit.WallN":
    IsoThumpable var12;
                        if (var8.getName() == "Edit.WallN")) {
                           if (var6 > 0 && Bits.hasFlags(var6, 1)) {
                              return;
                           }

                           var12 = std::make_shared<IsoThumpable>(IsoWorld.instance.getCell(), var4, "walls_exterior_wooden_01_25", true, nullptr);
                        } else {
                           if (var6 > 0 && Bits.hasFlags(var6, 2)) {
                              return;
                           }

                           var12 = std::make_shared<IsoThumpable>(IsoWorld.instance.getCell(), var4, "walls_exterior_wooden_01_24", true, nullptr);
                        }

                        var12.setMaxHealth(100);
                        var12.setName("Wall Debug");
                        var12.setBreakSound("BreakObject");
                        var4.AddSpecialObject(var12);
                        var4.RecalcAllWithNeighbours(true);
                        var12.transmitCompleteItemToServer();
                        if (var4.getZone() != nullptr) {
                           var4.getZone().setHaveConstruction(true);
                        }
                        break;
                     case "Edit.DoorW":
                     case "Edit.DoorN":
    IsoThumpable var11;
                        if (var8.getName() == "Edit.DoorN")) {
                           if (var6 > 0 && Bits.hasFlags(var6, 1)) {
                              return;
                           }

                           var11 = std::make_shared<IsoThumpable>(IsoWorld.instance.getCell(), var4, "walls_exterior_wooden_01_35", true, nullptr);
                        } else {
                           if (var6 > 0 && Bits.hasFlags(var6, 2)) {
                              return;
                           }

                           var11 = std::make_shared<IsoThumpable>(IsoWorld.instance.getCell(), var4, "walls_exterior_wooden_01_34", true, nullptr);
                        }

                        var11.setMaxHealth(100);
                        var11.setName("Door Frame Debug");
                        var11.setBreakSound("BreakObject");
                        var4.AddSpecialObject(var11);
                        var4.RecalcAllWithNeighbours(true);
                        var11.transmitCompleteItemToServer();
                        if (var4.getZone() != nullptr) {
                           var4.getZone().setHaveConstruction(true);
                        }
                        break;
                     case "Edit.Floor":
                        if (var6 > 0 && Bits.hasFlags(var6, 16)) {
                           return;
                        }

                        if (var3 == 0) {
                           return;
                        }

                        var4.addFloor("carpentry_02_56");
                        if (var4.getZone() != nullptr) {
                           var4.getZone().setHaveConstruction(true);
                        }
                  }
               }
            }
         } else {
            this.editSquareInRange = false;
         }
      }
   }

    bool isEditingEnabled() {
      return this.EditingEnabled;
   }

    void editRotate() {
      if (this.EditWallN.getValue()) {
         this.EditWallN.setValue(false);
         this.EditWallW.setValue(true);
      } else if (this.EditWallW.getValue()) {
         this.EditWallW.setValue(false);
         this.EditWallN.setValue(true);
      }

      if (this.EditDoorN.getValue()) {
         this.EditDoorN.setValue(false);
         this.EditDoorW.setValue(true);
      } else if (this.EditDoorW.getValue()) {
         this.EditDoorW.setValue(false);
         this.EditDoorN.setValue(true);
      }
   }

    ConfigOption getEditOptionByName(const std::string& var1) {
      for (int var2 = 0; var2 < this.editOptions.size(); var2++) {
    ConfigOption var3 = this.editOptions.get(var2);
         if (var3.getName() == var1)) {
    return var3;
         }
      }

    return nullptr;
   }

    int getEditOptionCount() {
      return this.editOptions.size();
   }

    ConfigOption getEditOptionByIndex(int var1) {
      return this.editOptions.get(var1);
   }

    void setEditOption(int var1, bool var2) {
      for (int var3 = 0; var3 < this.editOptions.size(); var3++) {
    BooleanDebugOption var4 = (BooleanDebugOption)this.editOptions.get(var3);
         if (var3 != var1) {
            var4.setValue(false);
         } else {
            var4.setValue(var2);
            this.EditingEnabled = var2;
         }
      }
   }

    int getZLevel() {
      if (this.zLevelPlayer.getValue()) {
         return (int)IsoPlayer.getInstance().getZ();
      } else {
         for (int var1 = 0; var1 < this.zLevelOptions.size(); var1++) {
    BooleanDebugOption var2 = (BooleanDebugOption)this.zLevelOptions.get(var1);
            if (var2.getValue()) {
               return var2.zLevel;
            }
         }

    return 0;
      }
   }

    ConfigOption getZLevelOptionByName(const std::string& var1) {
      for (int var2 = 0; var2 < this.zLevelOptions.size(); var2++) {
    ConfigOption var3 = this.zLevelOptions.get(var2);
         if (var3.getName() == var1)) {
    return var3;
         }
      }

    return nullptr;
   }

    int getZLevelOptionCount() {
      return this.zLevelOptions.size();
   }

    ConfigOption getZLevelOptionByIndex(int var1) {
      return this.zLevelOptions.get(var1);
   }

    void setZLevelOption(int var1, bool var2) {
      for (int var3 = 0; var3 < this.zLevelOptions.size(); var3++) {
    BooleanDebugOption var4 = (BooleanDebugOption)this.zLevelOptions.get(var3);
         if (var3 != var1) {
            var4.setValue(false);
         } else {
            var4.setValue(var2);
         }
      }

      if (!var2) {
         this.zLevelPlayer.setValue(true);
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
    std::string var1 = ZomboidFileSystem.instance.getCacheDir() + File.separator + "isoregions-options.ini";
    ConfigFile var2 = std::make_shared<ConfigFile>();
      var2.write(var1, 1, this.options);
   }

    void load() {
    std::string var1 = ZomboidFileSystem.instance.getCacheDir() + File.separator + "isoregions-options.ini";
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
   }
}
} // namespace isoregion
} // namespace areas
} // namespace iso
} // namespace zombie
