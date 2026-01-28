#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <vector>
#include <unordered_set>
#include "org/joml/Matrix4f.h"
#include "org/joml/Vector2f.h"
#include <GL/glew.h>
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Core.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/VBO/GLVertexBufferObject.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/opengl/PZGLUtil.h"
#include "zombie/core/skinnedmodel/ModelCamera.h"
#include "zombie/core/skinnedmodel/model/ModelSlotRenderData.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/core/textures/TextureDraw/GenericDrawer.h"
#include "zombie/core/textures/TextureID.h"
#include "zombie/iso/IsoCamera.h"
#include "zombie/iso/IsoMetaCell.h"
#include "zombie/iso/IsoMetaGrid/Zone.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/ui/UIManager.h"
#include "zombie/util/list/PZArrayUtil.h"
#include "zombie/worldMap/StrokeGeometry/Attrs.h"
#include "zombie/worldMap/StrokeGeometry/Point.h"
#include "zombie/worldMap/WorldMapGeometry/TrianglesPerZoom.h"
#include "zombie/worldMap/WorldMapGeometry/Type.h"
#include "zombie/worldMap/WorldMapRenderer/1.h"
#include "zombie/worldMap/WorldMapRenderer/PlayerRenderData.h"
#include "zombie/worldMap/styles/WorldMapStyle.h"
#include "zombie/worldMap/styles/WorldMapStyleLayer.h"
#include "zombie/worldMap/styles/WorldMapStyleLayer/FilterArgs.h"
#include "zombie/worldMap/styles/WorldMapStyleLayer/RGBAf.h"
#include "zombie/worldMap/styles/WorldMapStyleLayer/RenderArgs.h"
#include "zombie/worldMap/styles/WorldMapTextureStyleLayer.h"
#include <iterator>

namespace zombie {
namespace worldMap {


class WorldMapRenderer {
public:
    WorldMapRenderer m_renderer;
    const WorldMapStyle m_style = std::make_shared<WorldMapStyle>();
    WorldMap m_worldMap;
    int m_x;
    int m_y;
    int m_width;
    int m_height;
    float m_centerWorldX;
    float m_centerWorldY;
    int m_zoom = 0;
    float m_zoomF = 0.0F;
    float m_worldScale;
    float m_renderOriginX;
    float m_renderOriginY;
    float m_renderCellX;
    float m_renderCellY;
    const Matrix4f m_projection = std::make_shared<Matrix4f>();
    const Matrix4f m_modelView = std::make_shared<Matrix4f>();
   private const PlayerRenderData[] m_playerRenderData = new PlayerRenderData[4];
    const FilterArgs m_filterArgs = std::make_shared<FilterArgs>();
    const RenderArgs m_renderArgs = std::make_shared<RenderArgs>();
   const std::vector<WorldMapRenderLayer> m_renderLayers = std::make_unique<std::vector<>>();
   const std::vector<WorldMapFeature> m_features = std::make_unique<std::vector<>>();
   const std::vector<Zone> m_zones = std::make_unique<std::vector<>>();
   const std::unordered_set<Zone> m_zoneSet = std::make_unique<std::unordered_set<>>();
    RGBAf m_fill;
    int m_triangulationsThisFrame = 0;
   float[] m_floatArray;
    const Vector2f m_vector2f = std::make_shared<Vector2f>();
    const TIntArrayList m_rasterizeXY = std::make_shared<TIntArrayList>();
    const TIntSet m_rasterizeSet = std::make_shared<TIntHashSet>();
    float m_rasterizeMinTileX;
    float m_rasterizeMinTileY;
    float m_rasterizeMaxTileX;
    float m_rasterizeMaxTileY;
    const Rasterize m_rasterize = std::make_shared<Rasterize>();
   int[] m_rasterizeXY_ints;
    int m_rasterizeMult = 1;

   WorldMapRenderer$Drawer() {
      PZArrayUtil.arrayPopulate(this.m_playerRenderData, PlayerRenderData::new);
   }

    void init(WorldMapRenderer var1, UIWorldMap var2) {
      this.m_renderer = var1;
      this.m_style.copyFrom(this.m_renderer.m_style);
      this.m_worldMap = var1.m_worldMap;
      this.m_x = var1.m_x;
      this.m_y = var1.m_y;
      this.m_width = var1.m_width;
      this.m_height = var1.m_height;
      this.m_centerWorldX = var1.m_centerWorldX;
      this.m_centerWorldY = var1.m_centerWorldY;
      this.m_zoomF = var1.m_displayZoomF;
      this.m_zoom = (int)this.m_zoomF;
      this.m_worldScale = this.getWorldScale();
      this.m_renderOriginX = (this.m_renderer.m_worldMap.getMinXInSquares() - this.m_centerWorldX) * this.m_worldScale;
      this.m_renderOriginY = (this.m_renderer.m_worldMap.getMinYInSquares() - this.m_centerWorldY) * this.m_worldScale;
      this.m_projection.set(var1.m_projection);
      this.m_modelView.set(var1.m_modelView);
      this.m_fill = var2.m_color;
      this.m_triangulationsThisFrame = 0;
      if (this.m_renderer.m_visited != nullptr) {
         this.m_renderer.m_visited.renderMain();
      }

      for (int var3 = 0; var3 < 4; var3++) {
         this.m_playerRenderData[var3].m_modelSlotRenderData = nullptr;
      }

      if (this.m_renderer.Players.getValue() && this.m_zoomF >= 20.0F) {
         for (int var10 = 0; var10 < 4; var10++) {
    IsoPlayer var4 = IsoPlayer.players[var10];
            if (var4 != nullptr && !var4.isDead() && var4.legsSprite.hasActiveModel()) {
    float var5 = var4.x;
    float var6 = var4.y;
               if (var4.getVehicle() != nullptr) {
                  var5 = var4.getVehicle().getX();
                  var6 = var4.getVehicle().getY();
               }

    float var7 = this.m_renderer.worldToUIX(var5, var6, this.m_zoomF, this.m_centerWorldX, this.m_centerWorldY, this.m_projection, this.m_modelView);
    float var8 = this.m_renderer.worldToUIY(var5, var6, this.m_zoomF, this.m_centerWorldX, this.m_centerWorldY, this.m_projection, this.m_modelView);
               if (!(var7 < -100.0F) && !(var7 > this.m_width + 100) && !(var8 < -100.0F) && !(var8 > this.m_height + 100)) {
                  this.m_playerRenderData[var10].m_angle = var4.getVehicle() == nullptr ? var4.getAnimationPlayer().getAngle() : (float) (Math.PI * 3.0 / 2.0);
                  this.m_playerRenderData[var10].m_x = var5 - this.m_centerWorldX;
                  this.m_playerRenderData[var10].m_y = var6 - this.m_centerWorldY;
                  var4.legsSprite.modelSlot.model.updateLights();
    int var9 = IsoCamera.frameState.playerIndex;
                  IsoCamera.frameState.playerIndex = var10;
                  var4.checkUpdateModelTextures();
                  this.m_playerRenderData[var10].m_modelSlotRenderData = ModelSlotRenderData.alloc().init(var4.legsSprite.modelSlot);
                  this.m_playerRenderData[var10].m_modelSlotRenderData.centerOfMassY = 0.0F;
                  IsoCamera.frameState.playerIndex = var9;
                  var4.legsSprite.modelSlot.renderRefCount++;
               }
            }
         }
      }
   }

    int getAbsoluteX() {
      return this.m_x;
   }

    int getAbsoluteY() {
      return this.m_y;
   }

    int getWidth() {
      return this.m_width;
   }

    int getHeight() {
      return this.m_height;
   }

    float getWorldScale() {
      return this.m_renderer.getWorldScale(this.m_zoomF);
   }

    float uiToWorldX(float var1, float var2) {
      return this.m_renderer.uiToWorldX(var1, var2, this.m_zoomF, this.m_centerWorldX, this.m_centerWorldY, this.m_projection, this.m_modelView);
   }

    float uiToWorldY(float var1, float var2) {
      return this.m_renderer.uiToWorldY(var1, var2, this.m_zoomF, this.m_centerWorldX, this.m_centerWorldY, this.m_projection, this.m_modelView);
   }

    float worldOriginUIX(float var1) {
      return this.m_renderer.worldOriginUIX(this.m_zoomF, var1);
   }

    float worldOriginUIY(float var1) {
      return this.m_renderer.worldOriginUIY(this.m_zoomF, var1);
   }

    void renderCellFeatures() {
      for (byte var1 = 0; var1 < this.m_rasterizeXY.size() - 1; var1 += 2) {
    int var2 = this.m_rasterizeXY_ints[var1];
    int var3 = this.m_rasterizeXY_ints[var1 + 1];
         if (this.m_renderer.m_visited == nullptr || this.m_renderer.m_visited.isCellVisible(var2, var3)) {
            this.m_features.clear();

            for (int var4 = 0; var4 < this.m_worldMap.m_data.size(); var4++) {
    WorldMapData var5 = (WorldMapData)this.m_worldMap.m_data.get(var4);
               if (var5.isReady()) {
    WorldMapCell var6 = var5.getCell(var2, var3);
                  if (var6 != nullptr && !var6.m_features.empty()) {
                     this.m_features.addAll(var6.m_features);
                     if (this.m_worldMap.isLastDataInDirectory(var5)) {
                        break;
                     }
                  }
               }
            }

            if (this.m_features.empty()) {
               this.m_renderArgs.renderer = this.m_renderer;
               this.m_renderArgs.drawer = this;
               this.m_renderArgs.cellX = var2;
               this.m_renderArgs.cellY = var3;
               this.m_renderCellX = this.m_renderOriginX + (var2 * 300 - this.m_worldMap.getMinXInSquares()) * this.m_worldScale;
               this.m_renderCellY = this.m_renderOriginY + (var3 * 300 - this.m_worldMap.getMinYInSquares()) * this.m_worldScale;

               for (int var7 = 0; var7 < this.m_style.m_layers.size(); var7++) {
    WorldMapStyleLayer var8 = (WorldMapStyleLayer)this.m_style.m_layers.get(var7);
                  if (dynamic_cast<WorldMapTextureStyleLayer*>(var8) != nullptr) {
                     var8.renderCell(this.m_renderArgs);
                  }
               }
            } else {
               this.renderCell(var2, var3, this.m_features);
            }
         }
      }
   }

    void renderCell(int var1, int var2, std::vector<WorldMapFeature> var3) {
      this.m_renderCellX = this.m_renderOriginX + (var1 * 300 - this.m_worldMap.getMinXInSquares()) * this.m_worldScale;
      this.m_renderCellY = this.m_renderOriginY + (var2 * 300 - this.m_worldMap.getMinYInSquares()) * this.m_worldScale;
      WorldMapRenderLayer.s_pool.release(this.m_renderLayers);
      this.m_renderLayers.clear();
      this.m_filterArgs.renderer = this.m_renderer;
      this.filterFeatures(var3, this.m_filterArgs, this.m_renderLayers);
      this.m_renderArgs.renderer = this.m_renderer;
      this.m_renderArgs.drawer = this;
      this.m_renderArgs.cellX = var1;
      this.m_renderArgs.cellY = var2;

      for (int var4 = 0; var4 < this.m_renderLayers.size(); var4++) {
    WorldMapRenderLayer var5 = this.m_renderLayers.get(var4);
         var5.m_styleLayer.renderCell(this.m_renderArgs);

         for (int var6 = 0; var6 < var5.m_features.size(); var6++) {
    WorldMapFeature var7 = (WorldMapFeature)var5.m_features.get(var6);
            var5.m_styleLayer.render(var7, this.m_renderArgs);
         }
      }
   }

    void filterFeatures(std::vector<WorldMapFeature> var1, FilterArgs var2, std::vector<WorldMapRenderLayer> var3) {
      for (int var4 = 0; var4 < this.m_style.m_layers.size(); var4++) {
    WorldMapStyleLayer var5 = (WorldMapStyleLayer)this.m_style.m_layers.get(var4);
         if (!(var5.m_minZoom > this.m_zoomF)) {
            if (var5.m_id == "mylayer")) {
    bool var6 = true;
            }

    WorldMapRenderLayer var9 = nullptr;
            if (dynamic_cast<WorldMapTextureStyleLayer*>(var5) != nullptr) {
               var9 = (WorldMapRenderLayer)WorldMapRenderLayer.s_pool.alloc();
               var9.m_styleLayer = var5;
               var9.m_features.clear();
               var3.push_back(var9);
            } else {
               for (int var7 = 0; var7 < var1.size(); var7++) {
    WorldMapFeature var8 = (WorldMapFeature)var1.get(var7);
                  if (var5.filter(var8, var2)) {
                     if (var9 == nullptr) {
                        var9 = (WorldMapRenderLayer)WorldMapRenderLayer.s_pool.alloc();
                        var9.m_styleLayer = var5;
                        var9.m_features.clear();
                        var3.push_back(var9);
                     }

                     var9.m_features.push_back(var8);
                  }
               }
            }
         }
      }
   }

    void renderCellGrid(int var1, int var2, int var3, int var4) {
    float var5 = this.m_renderOriginX + (var1 * 300 - this.m_worldMap.getMinXInSquares()) * this.m_worldScale;
    float var6 = this.m_renderOriginY + (var2 * 300 - this.m_worldMap.getMinYInSquares()) * this.m_worldScale;
    float var7 = var5 + (var3 - var1 + 1) * 300 * this.m_worldScale;
    float var8 = var6 + (var4 - var2 + 1) * 300 * this.m_worldScale;
      WorldMapRenderer.m_vboLines.setMode(1);
      WorldMapRenderer.m_vboLines.setLineWidth(1.0F);

      for (int var9 = var1; var9 <= var3 + 1; var9++) {
         WorldMapRenderer.m_vboLines
            .addLine(
               this.m_renderOriginX + (var9 * 300 - this.m_worldMap.getMinXInSquares()) * this.m_worldScale,
               var6,
               0.0F,
               this.m_renderOriginX + (var9 * 300 - this.m_worldMap.getMinXInSquares()) * this.m_worldScale,
               var8,
               0.0F,
               0.25F,
               0.25F,
               0.25F,
               1.0F
            );
      }

      for (int var10 = var2; var10 <= var4 + 1; var10++) {
         WorldMapRenderer.m_vboLines
            .addLine(
               var5,
               this.m_renderOriginY + (var10 * 300 - this.m_worldMap.getMinYInSquares()) * this.m_worldScale,
               0.0F,
               var7,
               this.m_renderOriginY + (var10 * 300 - this.m_worldMap.getMinYInSquares()) * this.m_worldScale,
               0.0F,
               0.25F,
               0.25F,
               0.25F,
               1.0F
            );
      }

      WorldMapRenderer.m_vboLines.flush();
   }

    void renderPlayers() {
    bool var1 = true;

      for (int var2 = 0; var2 < this.m_playerRenderData.length; var2++) {
    PlayerRenderData var3 = this.m_playerRenderData[var2];
         if (var3.m_modelSlotRenderData != nullptr) {
            if (var1) {
               GL11.glClear(256);
               var1 = false;
            }

            this.m_renderer.m_CharacterModelCamera.m_worldScale = this.m_worldScale;
            this.m_renderer.m_CharacterModelCamera.m_bUseWorldIso = true;
            this.m_renderer.m_CharacterModelCamera.m_angle = var3.m_angle;
            this.m_renderer.m_CharacterModelCamera.m_playerX = var3.m_x;
            this.m_renderer.m_CharacterModelCamera.m_playerY = var3.m_y;
            this.m_renderer.m_CharacterModelCamera.m_bVehicle = var3.m_modelSlotRenderData.bInVehicle;
            ModelCamera.instance = this.m_renderer.m_CharacterModelCamera;
            var3.m_modelSlotRenderData.render();
         }
      }

      if (UIManager.useUIFBO) {
         GL14.glBlendFuncSeparate(770, 771, 1, 771);
      }
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    void drawLineStringXXX(RenderArgs var1, WorldMapFeature var2, RGBAf var3, float var4) {
    float var5 = this.m_renderCellX;
    float var6 = this.m_renderCellY;
    float var7 = this.m_worldScale;
    float var8 = var3.r;
    float var9 = var3.g;
    float var10 = var3.b;
    float var11 = var3.a;

      for (int var12 = 0; var12 < var2.m_geometries.size(); var12++) {
    WorldMapGeometry var13 = (WorldMapGeometry)var2.m_geometries.get(var12);
         switch (1.$SwitchMap$zombie$worldMap$WorldMapGeometry$Type[var13.m_type.ordinal()]) {
            case 1:
               WorldMapRenderer.m_vboLines.setMode(1);
               WorldMapRenderer.m_vboLines.setLineWidth(var4);

               for (int var14 = 0; var14 < var13.m_points.size(); var14++) {
    WorldMapPoints var15 = (WorldMapPoints)var13.m_points.get(var14);

                  for (int var16 = 0; var16 < var15.numPoints() - 1; var16++) {
    float var17 = var15.getX(var16);
    float var18 = var15.getY(var16);
    float var19 = var15.getX(var16 + 1);
    float var20 = var15.getY(var16 + 1);
                     WorldMapRenderer.m_vboLines
                        .addLine(var5 + var17 * var7, var6 + var18 * var7, 0.0F, var5 + var19 * var7, var6 + var20 * var7, 0.0F, var8, var9, var10, var11);
                  }
               }
         }
      }
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    void drawLineStringYYY(RenderArgs var1, WorldMapFeature var2, RGBAf var3, float var4) {
    float var5 = this.m_renderCellX;
    float var6 = this.m_renderCellY;
    float var7 = this.m_worldScale;
    float var8 = var3.r;
    float var9 = var3.g;
    float var10 = var3.b;
    float var11 = var3.a;

      for (int var12 = 0; var12 < var2.m_geometries.size(); var12++) {
    WorldMapGeometry var13 = (WorldMapGeometry)var2.m_geometries.get(var12);
         switch (1.$SwitchMap$zombie$worldMap$WorldMapGeometry$Type[var13.m_type.ordinal()]) {
            case 1:
               Point[] var14 = new Point[var13.m_points.size()];
    WorldMapPoints var15 = (WorldMapPoints)var13.m_points.get(0);

               for (int var16 = 0; var16 < var15.numPoints(); var16++) {
    float var17 = var15.getX(var16);
    float var18 = var15.getY(var16);
                  var14[var16] = StrokeGeometry.newPoint(var5 + var17 * var7, var6 + var18 * var7);
               }

    Attrs var21 = std::make_shared<Attrs>();
               var21.join = "miter";
               var21.width = var4;
    std::vector var22 = StrokeGeometry.getStrokeGeometry(var14, var21);
               if (var22 != nullptr) {
                  WorldMapRenderer.m_vboLines.setMode(4);

                  for (int var23 = 0; var23 < var22.size(); var23++) {
    float var19 = (float)((Point)var22.get(var23)).x;
    float var20 = (float)((Point)var22.get(var23)).y;
                     WorldMapRenderer.m_vboLines.addElement(var19, var20, 0.0F, var8, var9, var10, var11);
                  }

                  StrokeGeometry.release(var22);
               }
         }
      }
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    void drawLineString(RenderArgs var1, WorldMapFeature var2, RGBAf var3, float var4) {
      if (this.m_renderer.LineString.getValue()) {
    float var5 = this.m_renderCellX;
    float var6 = this.m_renderCellY;
    float var7 = this.m_worldScale;
    float var8 = var3.r;
    float var9 = var3.g;
    float var10 = var3.b;
    float var11 = var3.a;
         WorldMapRenderer.m_vboLines.flush();
         WorldMapRenderer.m_vboLinesUV.flush();

         for (int var12 = 0; var12 < var2.m_geometries.size(); var12++) {
    WorldMapGeometry var13 = (WorldMapGeometry)var2.m_geometries.get(var12);
            switch (1.$SwitchMap$zombie$worldMap$WorldMapGeometry$Type[var13.m_type.ordinal()]) {
               case 1:
    WorldMapPoints var14 = (WorldMapPoints)var13.m_points.get(0);
                  if (this.m_floatArray == nullptr || this.m_floatArray.length < var14.numPoints() * 2) {
                     this.m_floatArray = new float[var14.numPoints() * 2];
                  }

                  for (int var15 = 0; var15 < var14.numPoints(); var15++) {
    float var16 = var14.getX(var15);
    float var17 = var14.getY(var15);
                     this.m_floatArray[var15 * 2] = var5 + var16 * var7;
                     this.m_floatArray[var15 * 2 + 1] = var6 + var17 * var7;
                  }

                  GL13.glActiveTexture(33984);
                  GL11.glDisable(3553);
                  GL11.glEnable(3042);
            }
         }
      }
   }

    void drawLineStringTexture(RenderArgs var1, WorldMapFeature var2, RGBAf var3, float var4, Texture var5) {
    float var6 = this.m_renderCellX;
    float var7 = this.m_renderCellY;
    float var8 = this.m_worldScale;
      if (var5 != nullptr && var5.isReady()) {
         if (var5.getID() == -1) {
            var5.bind();
         }

         for (int var9 = 0; var9 < var2.m_geometries.size(); var9++) {
    WorldMapGeometry var10 = (WorldMapGeometry)var2.m_geometries.get(var9);
            if (var10.m_type == Type.LineString) {
               WorldMapRenderer.m_vboLinesUV.setMode(7);
               WorldMapRenderer.m_vboLinesUV.startRun(var5.getTextureId());
    float var11 = var4;
    WorldMapPoints var12 = (WorldMapPoints)var10.m_points.get(0);

               for (int var13 = 0; var13 < var12.numPoints() - 1; var13++) {
    float var14 = var6 + var12.getX(var13) * var8;
    float var15 = var7 + var12.getY(var13) * var8;
    float var16 = var6 + var12.getX(var13 + 1) * var8;
    float var17 = var7 + var12.getY(var13 + 1) * var8;
    float var18 = var17 - var15;
    float var19 = -(var16 - var14);
    Vector2f var20 = this.m_vector2f.set(var18, var19);
                  var20.normalize();
    float var21 = var14 + var20.x * var11 / 2.0F;
    float var22 = var15 + var20.y * var11 / 2.0F;
    float var23 = var16 + var20.x * var11 / 2.0F;
    float var24 = var17 + var20.y * var11 / 2.0F;
    float var25 = var16 - var20.x * var11 / 2.0F;
    float var26 = var17 - var20.y * var11 / 2.0F;
    float var27 = var14 - var20.x * var11 / 2.0F;
    float var28 = var15 - var20.y * var11 / 2.0F;
    float var29 = Vector2f.length(var16 - var14, var17 - var15);
    float var30 = 0.0F;
    float var31 = var29 / (var11 * ((float)var5.getHeight() / var5.getWidth()));
    float var32 = 0.0F;
    float var33 = 0.0F;
    float var34 = 1.0F;
    float var35 = 0.0F;
    float var36 = 1.0F;
    float var37 = var29 / (var11 * ((float)var5.getHeight() / var5.getWidth()));
                  WorldMapRenderer.m_vboLinesUV
                     .addQuad(
                        var21,
                        var22,
                        var30,
                        var31,
                        var23,
                        var24,
                        var32,
                        var33,
                        var25,
                        var26,
                        var34,
                        var35,
                        var27,
                        var28,
                        var36,
                        var37,
                        0.0F,
                        var3.r,
                        var3.g,
                        var3.b,
                        var3.a
                     );
               }
            }
         }
      }
   }

    void fillPolygon(RenderArgs var1, WorldMapFeature var2, RGBAf var3) {
      WorldMapRenderer.m_vboLinesUV.flush();
    float var4 = this.m_renderCellX;
    float var5 = this.m_renderCellY;
    float var6 = this.m_worldScale;
    float var7 = var3.r;
    float var8 = var3.g;
    float var9 = var3.b;
    float var10 = var3.a;

      for (int var11 = 0; var11 < var2.m_geometries.size(); var11++) {
    WorldMapGeometry var12 = (WorldMapGeometry)var2.m_geometries.get(var11);
         if (var12.m_type == Type.Polygon) {
    bool var13 = false;
            if (var12.m_triangles == nullptr) {
               if (this.m_triangulationsThisFrame > 500) {
                  continue;
               }

               this.m_triangulationsThisFrame++;
               double[] var14 = var2.m_properties.containsKey("highway") ? new double[]{1.0, 2.0, 4.0, 8.0, 12.0, 18.0} : nullptr;
               var12.triangulate(var14);
               if (var12.m_triangles == nullptr) {
                  if (!Core.bDebug) {
                     continue;
                  }

                  WorldMapRenderer.m_vboLines.setMode(1);
                  var7 = 1.0F;
                  var9 = 0.0F;
                  var8 = 0.0F;
                  WorldMapRenderer.m_vboLines.setLineWidth(4.0F);

                  for (int var15 = 0; var15 < var12.m_points.size(); var15++) {
    WorldMapPoints var29 = (WorldMapPoints)var12.m_points.get(var15);

                     for (int var31 = 0; var31 < var29.numPoints(); var31++) {
    int var33 = var29.getX(var31);
    int var35 = var29.getY(var31);
    int var37 = var29.getX((var31 + 1) % var29.numPoints());
    int var39 = var29.getY((var31 + 1) % var29.numPoints());
                        WorldMapRenderer.m_vboLines.reserve(2);
                        WorldMapRenderer.m_vboLines.addElement(var4 + var33 * var6, var5 + var35 * var6, 0.0F, var7, var8, var9, var10);
                        WorldMapRenderer.m_vboLines.addElement(var4 + var37 * var6, var5 + var39 * var6, 0.0F, var7, var8, var9, var10);
                     }
                  }

                  WorldMapRenderer.m_vboLines.setLineWidth(1.0F);
                  continue;
               }

               if (var13) {
                  this.uploadTrianglesToVBO(var12);
               }
            }

            if (var13) {
               GL11.glTranslatef(var4, var5, 0.0F);
               GL11.glScalef(var6, var6, var6);
               GL11.glColor4f(var7, var8, var9, var10);
               if (var12.m_triangles.length / 2 > 2340) {
    int var28 = PZMath.min(var12.m_triangles.length / 2, 2340);
                  WorldMapVBOs.getInstance().drawElements(4, var12.m_vboIndex1, var12.m_vboIndex2, var28);
                  WorldMapVBOs.getInstance().drawElements(4, var12.m_vboIndex3, var12.m_vboIndex4, var12.m_triangles.length / 2 - var28);
               } else {
                  WorldMapVBOs.getInstance().drawElements(4, var12.m_vboIndex1, var12.m_vboIndex2, var12.m_triangles.length / 2);
               }

               GL11.glScalef(1.0F / var6, 1.0F / var6, 1.0F / var6);
               GL11.glTranslatef(-var4, -var5, 0.0F);
            } else {
               WorldMapRenderer.m_vboLines.setMode(4);
    double var27 = 0.0;
               if (this.m_zoomF <= 11.5) {
                  var27 = 18.0;
               } else if (this.m_zoomF <= 12.0) {
                  var27 = 12.0;
               } else if (this.m_zoomF <= 12.5) {
                  var27 = 8.0;
               } else if (this.m_zoomF <= 13.0) {
                  var27 = 4.0;
               } else if (this.m_zoomF <= 13.5) {
                  var27 = 2.0;
               } else if (this.m_zoomF <= 14.0) {
                  var27 = 1.0;
               }

    TrianglesPerZoom var16 = var27 == 0.0 ? nullptr : var12.findTriangles(var27);
               if (var16 != nullptr) {
                  float[] var30 = var16.m_triangles;

                  for (byte var32 = 0; var32 < var30.length; var32 += 6) {
    float var34 = var30[var32];
    float var36 = var30[var32 + 1];
    float var38 = var30[var32 + 2];
    float var40 = var30[var32 + 3];
    float var41 = var30[var32 + 4];
    float var42 = var30[var32 + 5];
                     WorldMapRenderer.m_vboLines.reserve(3);
    float var25 = 1.0F;
                     WorldMapRenderer.m_vboLines.addElement(var4 + var34 * var6, var5 + var36 * var6, 0.0F, var7 * var25, var8 * var25, var9 * var25, var10);
                     WorldMapRenderer.m_vboLines.addElement(var4 + var38 * var6, var5 + var40 * var6, 0.0F, var7 * var25, var8 * var25, var9 * var25, var10);
                     WorldMapRenderer.m_vboLines.addElement(var4 + var41 * var6, var5 + var42 * var6, 0.0F, var7 * var25, var8 * var25, var9 * var25, var10);
                  }
               } else {
                  float[] var17 = var12.m_triangles;

                  for (byte var18 = 0; var18 < var17.length; var18 += 6) {
    float var19 = var17[var18];
    float var20 = var17[var18 + 1];
    float var21 = var17[var18 + 2];
    float var22 = var17[var18 + 3];
    float var23 = var17[var18 + 4];
    float var24 = var17[var18 + 5];
                     WorldMapRenderer.m_vboLines.reserve(3);
                     WorldMapRenderer.m_vboLines.addElement(var4 + var19 * var6, var5 + var20 * var6, 0.0F, var7, var8, var9, var10);
                     WorldMapRenderer.m_vboLines.addElement(var4 + var21 * var6, var5 + var22 * var6, 0.0F, var7, var8, var9, var10);
                     WorldMapRenderer.m_vboLines.addElement(var4 + var23 * var6, var5 + var24 * var6, 0.0F, var7, var8, var9, var10);
                  }
               }
            }
         }
      }
   }

    void fillPolygon(RenderArgs var1, WorldMapFeature var2, RGBAf var3, Texture var4, float var5) {
      WorldMapRenderer.m_vboLines.flush();
    float var6 = this.m_renderCellX;
    float var7 = this.m_renderCellY;
    float var8 = this.m_worldScale;
    float var9 = var3.r;
    float var10 = var3.g;
    float var11 = var3.b;
    float var12 = var3.a;

      for (int var13 = 0; var13 < var2.m_geometries.size(); var13++) {
    WorldMapGeometry var14 = (WorldMapGeometry)var2.m_geometries.get(var13);
         if (var14.m_type == Type.Polygon) {
            if (var14.m_triangles == nullptr) {
               var14.triangulate(nullptr);
               if (var14.m_triangles == nullptr) {
                  continue;
               }
            }

            GL11.glEnable(3553);
            GL11.glTexParameteri(3553, 10241, 9728);
            GL11.glTexParameteri(3553, 10240, 9728);
            WorldMapRenderer.m_vboLinesUV.setMode(4);
            WorldMapRenderer.m_vboLinesUV.startRun(var4.getTextureId());
            float[] var15 = var14.m_triangles;
    float var16 = var1.cellX * 300 + var14.m_minX;
    float var17 = var1.cellY * 300 + var14.m_minY;
    float var18 = var4.getWidth() * var5;
    float var19 = var4.getHeight() * var5;
    float var20 = var4.getWidthHW();
    float var21 = var4.getHeightHW();
    float var22 = PZMath.floor(var16 / var18) * var18;
    float var23 = PZMath.floor(var17 / var19) * var19;

            for (byte var24 = 0; var24 < var15.length; var24 += 6) {
    float var25 = var15[var24];
    float var26 = var15[var24 + 1];
    float var27 = var15[var24 + 2];
    float var28 = var15[var24 + 3];
    float var29 = var15[var24 + 4];
    float var30 = var15[var24 + 5];
    float var31 = (var25 + var1.cellX * 300 - var22) / var5;
    float var32 = (var26 + var1.cellY * 300 - var23) / var5;
    float var33 = (var27 + var1.cellX * 300 - var22) / var5;
    float var34 = (var28 + var1.cellY * 300 - var23) / var5;
    float var35 = (var29 + var1.cellX * 300 - var22) / var5;
    float var36 = (var30 + var1.cellY * 300 - var23) / var5;
               var25 = var6 + var25 * var8;
               var26 = var7 + var26 * var8;
               var27 = var6 + var27 * var8;
               var28 = var7 + var28 * var8;
               var29 = var6 + var29 * var8;
               var30 = var7 + var30 * var8;
    float var37 = var31 / var20;
    float var38 = var32 / var21;
    float var39 = var33 / var20;
    float var40 = var34 / var21;
    float var41 = var35 / var20;
    float var42 = var36 / var21;
               WorldMapRenderer.m_vboLinesUV.reserve(3);
               WorldMapRenderer.m_vboLinesUV.addElement(var25, var26, 0.0F, var37, var38, var9, var10, var11, var12);
               WorldMapRenderer.m_vboLinesUV.addElement(var27, var28, 0.0F, var39, var40, var9, var10, var11, var12);
               WorldMapRenderer.m_vboLinesUV.addElement(var29, var30, 0.0F, var41, var42, var9, var10, var11, var12);
            }

            GL11.glDisable(3553);
         }
      }
   }

    void uploadTrianglesToVBO(WorldMapGeometry var1) {
      int[] var2 = new int[2];
    int var3 = var1.m_triangles.length / 2;
      if (var3 > 2340) {
    int var4 = 0;

         while (var3 > 0) {
    int var5 = PZMath.min(var3 / 3, 780);
            WorldMapVBOs.getInstance().reserveVertices(var5 * 3, var2);
            if (var1.m_vboIndex1 == -1) {
               var1.m_vboIndex1 = var2[0];
               var1.m_vboIndex2 = var2[1];
            } else {
               var1.m_vboIndex3 = var2[0];
               var1.m_vboIndex4 = var2[1];
            }

            float[] var6 = var1.m_triangles;
    int var7 = var4 * 3 * 2;

            for (int var8 = (var4 + var5) * 3 * 2; var7 < var8; var7 += 6) {
    float var9 = var6[var7];
    float var10 = var6[var7 + 1];
    float var11 = var6[var7 + 2];
    float var12 = var6[var7 + 3];
    float var13 = var6[var7 + 4];
    float var14 = var6[var7 + 5];
               WorldMapVBOs.getInstance().addElement(var9, var10, 0.0F, 1.0F, 1.0F, 1.0F, 1.0F);
               WorldMapVBOs.getInstance().addElement(var11, var12, 0.0F, 1.0F, 1.0F, 1.0F, 1.0F);
               WorldMapVBOs.getInstance().addElement(var13, var14, 0.0F, 1.0F, 1.0F, 1.0F, 1.0F);
            }

            var4 += var5;
            var3 -= var5 * 3;
         }
      } else {
         WorldMapVBOs.getInstance().reserveVertices(var3, var2);
         var1.m_vboIndex1 = var2[0];
         var1.m_vboIndex2 = var2[1];
         float[] var15 = var1.m_triangles;

         for (byte var16 = 0; var16 < var15.length; var16 += 6) {
    float var17 = var15[var16];
    float var18 = var15[var16 + 1];
    float var19 = var15[var16 + 2];
    float var20 = var15[var16 + 3];
    float var21 = var15[var16 + 4];
    float var22 = var15[var16 + 5];
            WorldMapVBOs.getInstance().addElement(var17, var18, 0.0F, 1.0F, 1.0F, 1.0F, 1.0F);
            WorldMapVBOs.getInstance().addElement(var19, var20, 0.0F, 1.0F, 1.0F, 1.0F, 1.0F);
            WorldMapVBOs.getInstance().addElement(var21, var22, 0.0F, 1.0F, 1.0F, 1.0F, 1.0F);
         }
      }
   }

    void outlineTriangles(WorldMapGeometry var1, float var2, float var3, float var4) {
      WorldMapRenderer.m_vboLines.setMode(1);
    float var8 = 1.0F;
    float var5 = 1.0F;
    float var7 = 0.0F;
    float var6 = 0.0F;
      float[] var9 = var1.m_triangles;

      for (byte var10 = 0; var10 < var9.length; var10 += 6) {
    float var11 = var9[var10];
    float var12 = var9[var10 + 1];
    float var13 = var9[var10 + 2];
    float var14 = var9[var10 + 3];
    float var15 = var9[var10 + 4];
    float var16 = var9[var10 + 5];
         WorldMapRenderer.m_vboLines.addElement(var2 + var11 * var4, var3 + var12 * var4, 0.0F, var5, var6, var7, var8);
         WorldMapRenderer.m_vboLines.addElement(var2 + var13 * var4, var3 + var14 * var4, 0.0F, var5, var6, var7, var8);
         WorldMapRenderer.m_vboLines.addElement(var2 + var13 * var4, var3 + var14 * var4, 0.0F, var5, var6, var7, var8);
         WorldMapRenderer.m_vboLines.addElement(var2 + var15 * var4, var3 + var16 * var4, 0.0F, var5, var6, var7, var8);
         WorldMapRenderer.m_vboLines.addElement(var2 + var15 * var4, var3 + var16 * var4, 0.0F, var5, var6, var7, var8);
         WorldMapRenderer.m_vboLines.addElement(var2 + var11 * var4, var3 + var12 * var4, 0.0F, var5, var6, var7, var8);
      }
   }

    void outlinePolygon(WorldMapGeometry var1, float var2, float var3, float var4) {
      WorldMapRenderer.m_vboLines.setMode(1);
    float var8 = 1.0F;
    float var7 = 0.8F;
    float var6 = 0.8F;
    float var5 = 0.8F;
      WorldMapRenderer.m_vboLines.setLineWidth(4.0F);

      for (int var9 = 0; var9 < var1.m_points.size(); var9++) {
    WorldMapPoints var10 = (WorldMapPoints)var1.m_points.get(var9);

         for (int var11 = 0; var11 < var10.numPoints(); var11++) {
    int var12 = var10.getX(var11);
    int var13 = var10.getY(var11);
    int var14 = var10.getX((var11 + 1) % var10.numPoints());
    int var15 = var10.getY((var11 + 1) % var10.numPoints());
            WorldMapRenderer.m_vboLines.addElement(var2 + var12 * var4, var3 + var13 * var4, 0.0F, var5, var6, var7, var8);
            WorldMapRenderer.m_vboLines.addElement(var2 + var14 * var4, var3 + var15 * var4, 0.0F, var5, var6, var7, var8);
         }
      }

      WorldMapRenderer.m_vboLines.setLineWidth(1.0F);
   }

    void drawTexture(Texture var1, RGBAf var2, int var3, int var4, int var5, int var6) {
      if (var1 != nullptr && var1.isReady()) {
         WorldMapRenderer.m_vboLines.flush();
         WorldMapRenderer.m_vboLinesUV.flush();
    float var7 = this.m_worldScale;
    float var8 = (var3 - this.m_centerWorldX) * var7;
    float var9 = (var4 - this.m_centerWorldY) * var7;
    float var10 = var8 + (var5 - var3) * var7;
    float var11 = var9 + (var6 - var4) * var7;
    float var12 = PZMath.clamp(var8, this.m_renderCellX, this.m_renderCellX + 300.0F * var7);
    float var13 = PZMath.clamp(var9, this.m_renderCellY, this.m_renderCellY + 300.0F * var7);
    float var14 = PZMath.clamp(var10, this.m_renderCellX, this.m_renderCellX + 300.0F * var7);
    float var15 = PZMath.clamp(var11, this.m_renderCellY, this.m_renderCellY + 300.0F * var7);
         if (!(var12 >= var14) && !(var13 >= var15)) {
    float var16 = (float)var1.getWidth() / (var5 - var3);
    float var17 = (float)var1.getHeight() / (var6 - var4);
            GL11.glEnable(3553);
            GL11.glEnable(3042);
            GL11.glDisable(2929);
            if (var1.getID() == -1) {
               var1.bind();
            } else {
               GL11.glBindTexture(3553, Texture.lastTextureID = var1.getID());
               GL11.glTexParameteri(3553, 10241, 9728);
               GL11.glTexParameteri(3553, 10240, 9728);
            }

    float var18 = (var12 - var8) / (var1.getWidthHW() * var7) * var16;
    float var19 = (var13 - var9) / (var1.getHeightHW() * var7) * var17;
    float var20 = (var14 - var8) / (var1.getWidthHW() * var7) * var16;
    float var21 = (var15 - var9) / (var1.getHeightHW() * var7) * var17;
            WorldMapRenderer.m_vboLinesUV.setMode(7);
            WorldMapRenderer.m_vboLinesUV.startRun(var1.getTextureId());
            WorldMapRenderer.m_vboLinesUV.addQuad(var12, var13, var18, var19, var14, var15, var20, var21, 0.0F, var2.r, var2.g, var2.b, var2.a);
         }
      }
   }

    void drawTextureTiled(Texture var1, RGBAf var2, int var3, int var4, int var5, int var6, int var7, int var8) {
      if (var1 != nullptr && var1.isReady()) {
         if (var7 * 300 < var5 && (var7 + 1) * 300 > var3) {
            if (var8 * 300 < var6 && (var8 + 1) * 300 > var4) {
               WorldMapRenderer.m_vboLines.flush();
    float var9 = this.m_worldScale;
    int var10 = var1.getWidth();
    int var11 = var1.getHeight();
    int var12 = (int)(PZMath.floor(var7 * 300.0F / var10) * var10);
    int var13 = (int)(PZMath.floor(var8 * 300.0F / var11) * var11);
    int var14 = var12 + (int)Math.ceil(((var7 + 1) * 300.0F - var12) / var10) * var10;
    int var15 = var13 + (int)Math.ceil(((var8 + 1) * 300.0F - var13) / var11) * var11;
    float var16 = PZMath.clamp(var12, var7 * 300, (var7 + 1) * 300);
    float var17 = PZMath.clamp(var13, var8 * 300, (var8 + 1) * 300);
    float var18 = PZMath.clamp(var14, var7 * 300, (var7 + 1) * 300);
    float var19 = PZMath.clamp(var15, var8 * 300, (var8 + 1) * 300);
               var16 = PZMath.clamp(var16, var3, var5);
               var17 = PZMath.clamp(var17, var4, var6);
               var18 = PZMath.clamp(var18, var3, var5);
               var19 = PZMath.clamp(var19, var4, var6);
    float var20 = (var16 - var3) / var10;
    float var21 = (var17 - var4) / var11;
    float var22 = (var18 - var3) / var10;
    float var23 = (var19 - var4) / var11;
               var16 = (var16 - this.m_centerWorldX) * var9;
               var17 = (var17 - this.m_centerWorldY) * var9;
               var18 = (var18 - this.m_centerWorldX) * var9;
               var19 = (var19 - this.m_centerWorldY) * var9;
    float var24 = var20 * var1.xEnd;
    float var25 = var21 * var1.yEnd;
    float var26 = (int)var22 + (var22 - (int)var22) * var1.xEnd;
    float var27 = (int)var23 + (var23 - (int)var23) * var1.yEnd;
               GL11.glEnable(3553);
               if (var1.getID() == -1) {
                  var1.bind();
               } else {
                  GL11.glBindTexture(3553, Texture.lastTextureID = var1.getID());
                  GL11.glTexParameteri(3553, 10241, 9728);
                  GL11.glTexParameteri(3553, 10240, 9728);
                  GL11.glTexParameteri(3553, 10242, 10497);
                  GL11.glTexParameteri(3553, 10243, 10497);
               }

               WorldMapRenderer.m_vboLinesUV.setMode(7);
               WorldMapRenderer.m_vboLinesUV.startRun(var1.getTextureId());
               WorldMapRenderer.m_vboLinesUV.addQuad(var16, var17, var24, var25, var18, var19, var26, var27, 0.0F, var2.r, var2.g, var2.b, var2.a);
               GL11.glDisable(3553);
            }
         }
      }
   }

    void drawTextureTiled(Texture var1, RGBAf var2, int var3, int var4, int var5, int var6, int var7, int var8, int var9, int var10) {
      if (var1 != nullptr && var1.isReady()) {
         WorldMapRenderer.m_vboLines.flush();
         WorldMapRenderer.m_vboLinesUV.flush();
    float var11 = this.m_worldScale;
    float var12 = var3;
    float var13 = var4;
    float var14 = var5;
    float var15 = var6;
    float var16 = PZMath.clamp(var12, var9 * 300, (var9 + 1) * 300);
    float var17 = PZMath.clamp(var13, var10 * 300, (var10 + 1) * 300);
    float var18 = PZMath.clamp(var14, var9 * 300, (var9 + 1) * 300);
    float var19 = PZMath.clamp(var15, var10 * 300, (var10 + 1) * 300);
    float var20 = (var16 - var3) / var7;
    float var21 = (var17 - var4) / var8;
    float var22 = (var18 - var3) / var7;
    float var23 = (var19 - var4) / var8;
         var16 = (var16 - this.m_centerWorldX) * var11;
         var17 = (var17 - this.m_centerWorldY) * var11;
         var18 = (var18 - this.m_centerWorldX) * var11;
         var19 = (var19 - this.m_centerWorldY) * var11;
    float var24 = var20 * var1.xEnd;
    float var25 = var21 * var1.yEnd;
    float var26 = (int)var22 + (var22 - (int)var22) * var1.xEnd;
    float var27 = (int)var23 + (var23 - (int)var23) * var1.yEnd;
         GL11.glEnable(3553);
         if (var1.getID() == -1) {
            var1.bind();
         } else {
            GL11.glBindTexture(3553, Texture.lastTextureID = var1.getID());
            GL11.glTexParameteri(3553, 10241, 9728);
            GL11.glTexParameteri(3553, 10240, 9728);
            GL11.glTexParameteri(3553, 10242, 10497);
            GL11.glTexParameteri(3553, 10243, 10497);
         }

         GL11.glColor4f(var2.r, var2.g, var2.b, var2.a);
         GL11.glBegin(7);
         GL11.glTexCoord2f(var24, var25);
         GL11.glVertex2f(var16, var17);
         GL11.glTexCoord2f(var26, var25);
         GL11.glVertex2f(var18, var17);
         GL11.glTexCoord2f(var26, var27);
         GL11.glVertex2f(var18, var19);
         GL11.glTexCoord2f(var24, var27);
         GL11.glVertex2f(var16, var19);
         GL11.glEnd();
         GL11.glColor4f(1.0F, 1.0F, 1.0F, 1.0F);
         GL11.glDisable(3553);
      }
   }

    void renderZones() {
      this.m_zoneSet.clear();

      for (byte var1 = 0; var1 < this.m_rasterizeXY.size() - 1; var1 += 2) {
    int var2 = this.m_rasterizeXY_ints[var1];
    int var3 = this.m_rasterizeXY_ints[var1 + 1];
         if (this.m_renderer.m_visited == nullptr || this.m_renderer.m_visited.isCellVisible(var2, var3)) {
    IsoMetaCell var4 = IsoWorld.instance.MetaGrid.getCellData(var2, var3);
            if (var4 != nullptr) {
               var4.getZonesUnique(this.m_zoneSet);
            }
         }
      }

      this.m_zones.clear();
      this.m_zones.addAll(this.m_zoneSet);
      this.renderZones(this.m_zones, "Forest", 0.0F, 1.0F, 0.0F, 0.25F);
      this.renderZones(this.m_zones, "DeepForest", 0.0F, 0.5F, 0.0F, 0.25F);
      this.renderZones(this.m_zones, "Nav", 0.0F, 0.0F, 1.0F, 0.25F);
      this.renderZones(this.m_zones, "Vegitation", 1.0F, 1.0F, 0.0F, 0.25F);
   }

    void renderZones(std::vector<Zone> var1, const std::string& var2, float var3, float var4, float var5, float var6) {
      WorldMapRenderer.m_vboLinesUV.flush();
    float var7 = this.m_worldScale;
      WorldMapRenderer.m_vboLines.setMode(4);
    Iterator var8 = var1.iterator();

      while (true) {
    Zone var9;
         label89:
         while (true) {
            if (!var8.hasNext()) {
               WorldMapRenderer.m_vboLines.setMode(1);
               WorldMapRenderer.m_vboLines.setLineWidth(2.0F);

    for (auto& var19 : var1)                  if (var2 == var19.type)) {
                     if (var19.isRectangle()) {
    float var21 = (var19.x - this.m_centerWorldX) * var7;
    float var25 = (var19.y - this.m_centerWorldY) * var7;
    float var29 = (var19.x + var19.w - this.m_centerWorldX) * var7;
    float var33 = (var19.y + var19.h - this.m_centerWorldY) * var7;
                        WorldMapRenderer.m_vboLines.addLine(var21, var25, 0.0F, var29, var25, 0.0F, var3, var4, var5, 1.0F);
                        WorldMapRenderer.m_vboLines.addLine(var29, var25, 0.0F, var29, var33, 0.0F, var3, var4, var5, 1.0F);
                        WorldMapRenderer.m_vboLines.addLine(var29, var33, 0.0F, var21, var33, 0.0F, var3, var4, var5, 1.0F);
                        WorldMapRenderer.m_vboLines.addLine(var21, var33, 0.0F, var21, var25, 0.0F, var3, var4, var5, 1.0F);
                     }

                     if (var19.isPolygon()) {
                        for (byte var22 = 0; var22 < var19.points.size(); var22 += 2) {
    float var26 = (var19.points.getQuick(var22) - this.m_centerWorldX) * var7;
    float var30 = (var19.points.getQuick(var22 + 1) - this.m_centerWorldY) * var7;
    float var34 = (var19.points.getQuick((var22 + 2) % var19.points.size()) - this.m_centerWorldX) * var7;
    float var37 = (var19.points.getQuick((var22 + 3) % var19.points.size()) - this.m_centerWorldY) * var7;
                           WorldMapRenderer.m_vboLines.addLine(var26, var30, 0.0F, var34, var37, 0.0F, var3, var4, var5, 1.0F);
                        }
                     }

                     if (var19.isPolyline()) {
                        float[] var23 = var19.polylineOutlinePoints;
                        if (var23 != nullptr) {
                           for (byte var27 = 0; var27 < var23.length; var27 += 2) {
    float var31 = (var23[var27] - this.m_centerWorldX) * var7;
    float var35 = (var23[var27 + 1] - this.m_centerWorldY) * var7;
    float var38 = (var23[(var27 + 2) % var23.length] - this.m_centerWorldX) * var7;
    float var40 = (var23[(var27 + 3) % var23.length] - this.m_centerWorldY) * var7;
                              WorldMapRenderer.m_vboLines.addLine(var31, var35, 0.0F, var38, var40, 0.0F, var3, var4, var5, 1.0F);
                           }
                        }
                     }
                  }
               }

               return;
            }

            var9 = (Zone)var8.next();
            if (var2 == var9.type)) {
               if (var9.isRectangle()) {
                  WorldMapRenderer.m_vboLines
                     .addQuad(
                        (var9.x - this.m_centerWorldX) * var7,
                        (var9.y - this.m_centerWorldY) * var7,
                        (var9.x + var9.w - this.m_centerWorldX) * var7,
                        (var9.y + var9.h - this.m_centerWorldY) * var7,
                        0.0F,
                        var3,
                        var4,
                        var5,
                        var6
                     );
               }

               if (!var9.isPolygon()) {
                  break;
               }

               float[] var10 = var9.getPolygonTriangles();
               if (var10 != nullptr) {
    uint8_t var11 = 0;

                  while (true) {
                     if (var11 >= var10.length) {
    break label89;
                     }

    float var12 = (var10[var11] - this.m_centerWorldX) * var7;
    float var13 = (var10[var11 + 1] - this.m_centerWorldY) * var7;
    float var14 = (var10[var11 + 2] - this.m_centerWorldX) * var7;
    float var15 = (var10[var11 + 3] - this.m_centerWorldY) * var7;
    float var16 = (var10[var11 + 4] - this.m_centerWorldX) * var7;
    float var17 = (var10[var11 + 5] - this.m_centerWorldY) * var7;
                     WorldMapRenderer.m_vboLines.addTriangle(var12, var13, 0.0F, var14, var15, 0.0F, var16, var17, 0.0F, var3, var4, var5, var6);
                     var11 += 6;
                  }
               }
            }
         }

         if (var9.isPolyline()) {
            float[] var20 = var9.getPolylineOutlineTriangles();
            if (var20 != nullptr) {
               for (byte var24 = 0; var24 < var20.length; var24 += 6) {
    float var28 = (var20[var24] - this.m_centerWorldX) * var7;
    float var32 = (var20[var24 + 1] - this.m_centerWorldY) * var7;
    float var36 = (var20[var24 + 2] - this.m_centerWorldX) * var7;
    float var39 = (var20[var24 + 3] - this.m_centerWorldY) * var7;
    float var41 = (var20[var24 + 4] - this.m_centerWorldX) * var7;
    float var42 = (var20[var24 + 5] - this.m_centerWorldY) * var7;
                  WorldMapRenderer.m_vboLines.addTriangle(var28, var32, 0.0F, var36, var39, 0.0F, var41, var42, 0.0F, var3, var4, var5, var6);
               }
            }
         }
      }
   }

    void render() {
      try {
         PZGLUtil.pushAndLoadMatrix(5889, this.m_projection);
         PZGLUtil.pushAndLoadMatrix(5888, this.m_modelView);
         this.renderInternal();
      } catch (Exception var5) {
         ExceptionLogger.logException(var5);
      } finally {
         PZGLUtil.popMatrix(5889);
         PZGLUtil.popMatrix(5888);
      }
   }

    void renderInternal() {
    float var1 = this.m_worldScale;
    int var2 = (int)Math.max(this.uiToWorldX(0.0F, 0.0F), (float)this.m_worldMap.getMinXInSquares()) / 300;
    int var3 = (int)Math.max(this.uiToWorldY(0.0F, 0.0F), (float)this.m_worldMap.getMinYInSquares()) / 300;
    int var4 = (int)Math.min(this.uiToWorldX(this.getWidth(), this.getHeight()), (float)(this.m_worldMap.m_maxX * 300)) / 300;
    int var5 = (int)Math.min(this.uiToWorldY(this.getWidth(), this.getHeight()), (float)(this.m_worldMap.m_maxY * 300)) / 300;
      var2 = this.m_worldMap.getMinXInSquares();
      var3 = this.m_worldMap.getMinYInSquares();
      var4 = this.m_worldMap.m_maxX;
      var5 = this.m_worldMap.m_maxY;
      GL11.glViewport(this.m_x, Core.height - this.m_height - this.m_y, this.m_width, this.m_height);
      GLVertexBufferObject.funcs.glBindBuffer(GLVertexBufferObject.funcs.GL_ARRAY_BUFFER(), 0);
      GLVertexBufferObject.funcs.glBindBuffer(GLVertexBufferObject.funcs.GL_ELEMENT_ARRAY_BUFFER(), 0);
      GL11.glPolygonMode(1032, this.m_renderer.Wireframe.getValue() ? 6913 : 6914);
      if (this.m_renderer.ImagePyramid.getValue()) {
         this.renderImagePyramids();
      }

      this.calculateVisibleCells();
      if (this.m_renderer.Features.getValue()) {
         this.renderCellFeatures();
      }

      if (this.m_renderer.ForestZones.getValue()) {
         this.renderZones();
      }

      if (this.m_renderer.VisibleCells.getValue()) {
         this.renderVisibleCells();
      }

      WorldMapRenderer.m_vboLines.flush();
      WorldMapRenderer.m_vboLinesUV.flush();
      GL11.glEnableClientState(32884);
      GL11.glEnableClientState(32886);
      GL13.glActiveTexture(33984);
      GL13.glClientActiveTexture(33984);
      GL11.glEnableClientState(32888);
      GL11.glTexEnvi(8960, 8704, 8448);
      GL11.glPolygonMode(1032, 6914);
      GL11.glEnable(3042);
      SpriteRenderer.ringBuffer.restoreBoundTextures = true;
      SpriteRenderer.ringBuffer.restoreVBOs = true;
      if (this.m_renderer.m_visited != nullptr) {
         this.m_renderer
            .m_visited
            .render(
               this.m_renderOriginX - (this.m_worldMap.getMinXInSquares() - this.m_renderer.m_visited.getMinX() * 300) * var1,
               this.m_renderOriginY - (this.m_worldMap.getMinYInSquares() - this.m_renderer.m_visited.getMinY() * 300) * var1,
               var2 / 300,
               var3 / 300,
               var4 / 300,
               var5 / 300,
               var1,
               this.m_renderer.BlurUnvisited.getValue()
            );
         if (this.m_renderer.UnvisitedGrid.getValue()) {
            this.m_renderer
               .m_visited
               .renderGrid(
                  this.m_renderOriginX - (this.m_worldMap.getMinXInSquares() - this.m_renderer.m_visited.getMinX() * 300) * var1,
                  this.m_renderOriginY - (this.m_worldMap.getMinYInSquares() - this.m_renderer.m_visited.getMinY() * 300) * var1,
                  var2 / 300,
                  var3 / 300,
                  var4 / 300,
                  var5 / 300,
                  var1,
                  this.m_zoomF
               );
         }
      }

      this.renderPlayers();
      if (this.m_renderer.CellGrid.getValue()) {
         this.renderCellGrid(var2 / 300, var3 / 300, var4 / 300, var5 / 300);
      }

      if (Core.bDebug) {
      }

      this.paintAreasOutsideBounds(var2, var3, var4, var5, var1);
      if (this.m_renderer.WorldBounds.getValue()) {
         this.renderWorldBounds();
      }

      WorldMapRenderer.m_vboLines.flush();
      WorldMapRenderer.m_vboLinesUV.flush();
      GL11.glViewport(0, 0, Core.width, Core.height);
   }

    void rasterizeCellsCallback(int var1, int var2) {
    int var3 = var1 + var2 * this.m_worldMap.getWidthInCells();
      if (!this.m_rasterizeSet.contains(var3)) {
         for (int var4 = var2 * this.m_rasterizeMult; var4 < var2 * this.m_rasterizeMult + this.m_rasterizeMult; var4++) {
            for (int var5 = var1 * this.m_rasterizeMult; var5 < var1 * this.m_rasterizeMult + this.m_rasterizeMult; var5++) {
               if (var5 >= this.m_worldMap.getMinXInCells()
                  && var5 <= this.m_worldMap.getMaxXInCells()
                  && var4 >= this.m_worldMap.getMinYInCells()
                  && var4 <= this.m_worldMap.getMaxYInCells()) {
                  this.m_rasterizeSet.push_back(var3);
                  this.m_rasterizeXY.push_back(var5);
                  this.m_rasterizeXY.push_back(var4);
               }
            }
         }
      }
   }

    void rasterizeTilesCallback(int var1, int var2) {
    int var3 = var1 + var2 * 1000;
      if (!this.m_rasterizeSet.contains(var3)) {
         if (!(var1 < this.m_rasterizeMinTileX)
            && !(var1 > this.m_rasterizeMaxTileX)
            && !(var2 < this.m_rasterizeMinTileY)
            && !(var2 > this.m_rasterizeMaxTileY)) {
            this.m_rasterizeSet.push_back(var3);
            this.m_rasterizeXY.push_back(var1);
            this.m_rasterizeXY.push_back(var2);
         }
      }
   }

    void calculateVisibleCells() {
    bool var1 = Core.bDebug && this.m_renderer.VisibleCells.getValue();
    int var2 = var1 ? 200 : 0;
    float var3 = this.m_worldScale;
      if (1.0F / var3 > 100.0F) {
         this.m_rasterizeXY.clear();

         for (int var13 = this.m_worldMap.getMinYInCells(); var13 <= this.m_worldMap.getMaxYInCells(); var13++) {
            for (int var14 = this.m_worldMap.getMinXInCells(); var14 <= this.m_worldMap.getMaxYInCells(); var14++) {
               this.m_rasterizeXY.push_back(var14);
               this.m_rasterizeXY.push_back(var13);
            }
         }

         if (this.m_rasterizeXY_ints == nullptr || this.m_rasterizeXY_ints.length < this.m_rasterizeXY.size()) {
            this.m_rasterizeXY_ints = new int[this.m_rasterizeXY.size()];
         }

         this.m_rasterizeXY_ints = this.m_rasterizeXY.toArray(this.m_rasterizeXY_ints);
      } else {
    float var4 = this.uiToWorldX(var2 + 0.0F, var2 + 0.0F) / 300.0F;
    float var5 = this.uiToWorldY(var2 + 0.0F, var2 + 0.0F) / 300.0F;
    float var6 = this.uiToWorldX(this.getWidth() - var2, 0.0F + var2) / 300.0F;
    float var7 = this.uiToWorldY(this.getWidth() - var2, 0.0F + var2) / 300.0F;
    float var8 = this.uiToWorldX(this.getWidth() - var2, this.getHeight() - var2) / 300.0F;
    float var9 = this.uiToWorldY(this.getWidth() - var2, this.getHeight() - var2) / 300.0F;
    float var10 = this.uiToWorldX(0.0F + var2, this.getHeight() - var2) / 300.0F;
    float var11 = this.uiToWorldY(0.0F + var2, this.getHeight() - var2) / 300.0F;
    int var12 = 1;

         while (
            this.triangleArea(var10 / var12, var11 / var12, var8 / var12, var9 / var12, var6 / var12, var7 / var12)
                  + this.triangleArea(var6 / var12, var7 / var12, var4 / var12, var5 / var12, var10 / var12, var11 / var12)
               > 80.0F
         ) {
            var12++;
         }

         this.m_rasterizeMult = var12;
         this.m_rasterizeXY.clear();
         this.m_rasterizeSet.clear();
         this.m_rasterize
            .scanTriangle(var10 / var12, var11 / var12, var8 / var12, var9 / var12, var6 / var12, var7 / var12, 0, 1000, this::rasterizeCellsCallback);
         this.m_rasterize
            .scanTriangle(var6 / var12, var7 / var12, var4 / var12, var5 / var12, var10 / var12, var11 / var12, 0, 1000, this::rasterizeCellsCallback);
         if (this.m_rasterizeXY_ints == nullptr || this.m_rasterizeXY_ints.length < this.m_rasterizeXY.size()) {
            this.m_rasterizeXY_ints = new int[this.m_rasterizeXY.size()];
         }

         this.m_rasterizeXY_ints = this.m_rasterizeXY.toArray(this.m_rasterizeXY_ints);
      }
   }

    void renderVisibleCells() {
    bool var1 = Core.bDebug && this.m_renderer.VisibleCells.getValue();
    int var2 = var1 ? 200 : 0;
    float var3 = this.m_worldScale;
      if (!(1.0F / var3 > 100.0F)) {
         WorldMapRenderer.m_vboLines.setMode(4);

         for (byte var4 = 0; var4 < this.m_rasterizeXY.size(); var4 += 2) {
    int var5 = this.m_rasterizeXY.get(var4);
    int var6 = this.m_rasterizeXY.get(var4 + 1);
    float var7 = this.m_renderOriginX + (var5 * 300 - this.m_worldMap.getMinXInSquares()) * var3;
    float var8 = this.m_renderOriginY + (var6 * 300 - this.m_worldMap.getMinYInSquares()) * var3;
    float var9 = this.m_renderOriginX + ((var5 + 1) * 300 - this.m_worldMap.getMinXInSquares()) * var3;
    float var10 = this.m_renderOriginY + ((var6 + 1) * 300 - this.m_worldMap.getMinYInSquares()) * var3;
            WorldMapRenderer.m_vboLines.addElement(var7, var8, 0.0F, 0.0F, 1.0F, 0.0F, 0.2F);
            WorldMapRenderer.m_vboLines.addElement(var9, var8, 0.0F, 0.0F, 1.0F, 0.0F, 0.2F);
            WorldMapRenderer.m_vboLines.addElement(var7, var10, 0.0F, 0.0F, 1.0F, 0.0F, 0.2F);
            WorldMapRenderer.m_vboLines.addElement(var9, var8, 0.0F, 0.0F, 0.0F, 1.0F, 0.2F);
            WorldMapRenderer.m_vboLines.addElement(var9, var10, 0.0F, 0.0F, 0.0F, 1.0F, 0.2F);
            WorldMapRenderer.m_vboLines.addElement(var7, var10, 0.0F, 0.0F, 0.0F, 1.0F, 0.2F);
         }

         WorldMapRenderer.m_vboLines.flush();
    float var12 = this.uiToWorldX(var2 + 0.0F, var2 + 0.0F) / 300.0F;
    float var13 = this.uiToWorldY(var2 + 0.0F, var2 + 0.0F) / 300.0F;
    float var14 = this.uiToWorldX(this.getWidth() - var2, 0.0F + var2) / 300.0F;
    float var15 = this.uiToWorldY(this.getWidth() - var2, 0.0F + var2) / 300.0F;
    float var16 = this.uiToWorldX(this.getWidth() - var2, this.getHeight() - var2) / 300.0F;
    float var17 = this.uiToWorldY(this.getWidth() - var2, this.getHeight() - var2) / 300.0F;
    float var18 = this.uiToWorldX(0.0F + var2, this.getHeight() - var2) / 300.0F;
    float var11 = this.uiToWorldY(0.0F + var2, this.getHeight() - var2) / 300.0F;
         WorldMapRenderer.m_vboLines.setMode(1);
         WorldMapRenderer.m_vboLines.setLineWidth(4.0F);
         WorldMapRenderer.m_vboLines
            .addLine(
               this.m_renderOriginX + (var18 * 300.0F - this.m_worldMap.getMinXInSquares()) * var3,
               this.m_renderOriginY + (var11 * 300.0F - this.m_worldMap.getMinYInSquares()) * var3,
               0.0F,
               this.m_renderOriginX + (var16 * 300.0F - this.m_worldMap.getMinXInSquares()) * var3,
               this.m_renderOriginY + (var17 * 300.0F - this.m_worldMap.getMinYInSquares()) * var3,
               0.0F,
               1.0F,
               0.0F,
               0.0F,
               1.0F
            );
         WorldMapRenderer.m_vboLines
            .addLine(
               this.m_renderOriginX + (var16 * 300.0F - this.m_worldMap.getMinXInSquares()) * var3,
               this.m_renderOriginY + (var17 * 300.0F - this.m_worldMap.getMinYInSquares()) * var3,
               0.0F,
               this.m_renderOriginX + (var14 * 300.0F - this.m_worldMap.getMinXInSquares()) * var3,
               this.m_renderOriginY + (var15 * 300.0F - this.m_worldMap.getMinYInSquares()) * var3,
               0.0F,
               1.0F,
               0.0F,
               0.0F,
               1.0F
            );
         WorldMapRenderer.m_vboLines
            .addLine(
               this.m_renderOriginX + (var14 * 300.0F - this.m_worldMap.getMinXInSquares()) * var3,
               this.m_renderOriginY + (var15 * 300.0F - this.m_worldMap.getMinYInSquares()) * var3,
               0.0F,
               this.m_renderOriginX + (var18 * 300.0F - this.m_worldMap.getMinXInSquares()) * var3,
               this.m_renderOriginY + (var11 * 300.0F - this.m_worldMap.getMinYInSquares()) * var3,
               0.0F,
               0.5F,
               0.5F,
               0.5F,
               1.0F
            );
         WorldMapRenderer.m_vboLines
            .addLine(
               this.m_renderOriginX + (var14 * 300.0F - this.m_worldMap.getMinXInSquares()) * var3,
               this.m_renderOriginY + (var15 * 300.0F - this.m_worldMap.getMinYInSquares()) * var3,
               0.0F,
               this.m_renderOriginX + (var12 * 300.0F - this.m_worldMap.getMinXInSquares()) * var3,
               this.m_renderOriginY + (var13 * 300.0F - this.m_worldMap.getMinYInSquares()) * var3,
               0.0F,
               0.0F,
               0.0F,
               1.0F,
               1.0F
            );
         WorldMapRenderer.m_vboLines
            .addLine(
               this.m_renderOriginX + (var12 * 300.0F - this.m_worldMap.getMinXInSquares()) * var3,
               this.m_renderOriginY + (var13 * 300.0F - this.m_worldMap.getMinYInSquares()) * var3,
               0.0F,
               this.m_renderOriginX + (var18 * 300.0F - this.m_worldMap.getMinXInSquares()) * var3,
               this.m_renderOriginY + (var11 * 300.0F - this.m_worldMap.getMinYInSquares()) * var3,
               0.0F,
               0.0F,
               0.0F,
               1.0F,
               1.0F
            );
      }
   }

    void calcVisiblePyramidTiles(WorldMapImages var1) {
      if (Core.bDebug) {
      }

    bool var2 = false;
    int var3 = var2 ? 200 : 0;
    float var4 = this.m_worldScale;
    int var5 = var1.getZoom(this.m_zoomF);
    short var6 = 256;
    float var7 = var6 * (1 << var5);
    int var8 = var1.getMinX();
    int var9 = var1.getMinY();
    float var10 = (this.uiToWorldX(var3 + 0.0F, var3 + 0.0F) - var8) / var7;
    float var11 = (this.uiToWorldY(var3 + 0.0F, var3 + 0.0F) - var9) / var7;
    float var12 = (this.uiToWorldX(this.getWidth() - var3, 0.0F + var3) - var8) / var7;
    float var13 = (this.uiToWorldY(this.getWidth() - var3, 0.0F + var3) - var9) / var7;
    float var14 = (this.uiToWorldX(this.getWidth() - var3, this.getHeight() - var3) - var8) / var7;
    float var15 = (this.uiToWorldY(this.getWidth() - var3, this.getHeight() - var3) - var9) / var7;
    float var16 = (this.uiToWorldX(0.0F + var3, this.getHeight() - var3) - var8) / var7;
    float var17 = (this.uiToWorldY(0.0F + var3, this.getHeight() - var3) - var9) / var7;
      if (var2) {
         WorldMapRenderer.m_vboLines.setMode(1);
         WorldMapRenderer.m_vboLines.setLineWidth(4.0F);
         WorldMapRenderer.m_vboLines
            .addLine(
               this.m_renderOriginX + var16 * var7 * var4,
               this.m_renderOriginY + var17 * var7 * var4,
               0.0F,
               this.m_renderOriginX + var14 * var7 * var4,
               this.m_renderOriginY + var15 * var7 * var4,
               0.0F,
               1.0F,
               0.0F,
               0.0F,
               1.0F
            );
         WorldMapRenderer.m_vboLines
            .addLine(
               this.m_renderOriginX + var14 * var7 * var4,
               this.m_renderOriginY + var15 * var7 * var4,
               0.0F,
               this.m_renderOriginX + var12 * var7 * var4,
               this.m_renderOriginY + var13 * var7 * var4,
               0.0F,
               1.0F,
               0.0F,
               0.0F,
               1.0F
            );
         WorldMapRenderer.m_vboLines
            .addLine(
               this.m_renderOriginX + var12 * var7 * var4,
               this.m_renderOriginY + var13 * var7 * var4,
               0.0F,
               this.m_renderOriginX + var16 * var7 * var4,
               this.m_renderOriginY + var17 * var7 * var4,
               0.0F,
               0.5F,
               0.5F,
               0.5F,
               1.0F
            );
         WorldMapRenderer.m_vboLines
            .addLine(
               this.m_renderOriginX + var12 * var7 * var4,
               this.m_renderOriginY + var13 * var7 * var4,
               0.0F,
               this.m_renderOriginX + var10 * var7 * var4,
               this.m_renderOriginY + var11 * var7 * var4,
               0.0F,
               0.0F,
               0.0F,
               1.0F,
               1.0F
            );
         WorldMapRenderer.m_vboLines
            .addLine(
               this.m_renderOriginX + var10 * var7 * var4,
               this.m_renderOriginY + var11 * var7 * var4,
               0.0F,
               this.m_renderOriginX + var16 * var7 * var4,
               this.m_renderOriginY + var17 * var7 * var4,
               0.0F,
               0.0F,
               0.0F,
               1.0F,
               1.0F
            );
      }

      this.m_rasterizeXY.clear();
      this.m_rasterizeSet.clear();
      this.m_rasterizeMinTileX = (int)((this.m_worldMap.getMinXInSquares() - var1.getMinX()) / var7);
      this.m_rasterizeMinTileY = (int)((this.m_worldMap.getMinYInSquares() - var1.getMinY()) / var7);
      this.m_rasterizeMaxTileX = (this.m_worldMap.getMaxXInSquares() - var1.getMinX()) / var7;
      this.m_rasterizeMaxTileY = (this.m_worldMap.getMaxYInSquares() - var1.getMinY()) / var7;
      this.m_rasterize.scanTriangle(var16, var17, var14, var15, var12, var13, 0, 1000, this::rasterizeTilesCallback);
      this.m_rasterize.scanTriangle(var12, var13, var10, var11, var16, var17, 0, 1000, this::rasterizeTilesCallback);
      if (this.m_rasterizeXY_ints == nullptr || this.m_rasterizeXY_ints.length < this.m_rasterizeXY.size()) {
         this.m_rasterizeXY_ints = new int[this.m_rasterizeXY.size()];
      }

      this.m_rasterizeXY_ints = this.m_rasterizeXY.toArray(this.m_rasterizeXY_ints);
      if (var2) {
         WorldMapRenderer.m_vboLines.setMode(4);

         for (byte var18 = 0; var18 < this.m_rasterizeXY.size(); var18 += 2) {
    int var19 = this.m_rasterizeXY.get(var18);
    int var20 = this.m_rasterizeXY.get(var18 + 1);
    float var21 = this.m_renderOriginX + var19 * var7 * var4;
    float var22 = this.m_renderOriginY + var20 * var7 * var4;
    float var23 = this.m_renderOriginX + (var19 + 1) * var7 * var4;
    float var24 = this.m_renderOriginY + (var20 + 1) * var7 * var4;
            WorldMapRenderer.m_vboLines.addElement(var21, var22, 0.0F, 0.0F, 1.0F, 0.0F, 0.2F);
            WorldMapRenderer.m_vboLines.addElement(var23, var22, 0.0F, 0.0F, 1.0F, 0.0F, 0.2F);
            WorldMapRenderer.m_vboLines.addElement(var21, var24, 0.0F, 0.0F, 1.0F, 0.0F, 0.2F);
            WorldMapRenderer.m_vboLines.addElement(var23, var22, 0.0F, 0.0F, 0.0F, 1.0F, 0.2F);
            WorldMapRenderer.m_vboLines.addElement(var23, var24, 0.0F, 0.0F, 0.0F, 1.0F, 0.2F);
            WorldMapRenderer.m_vboLines.addElement(var21, var24, 0.0F, 0.0F, 0.0F, 1.0F, 0.2F);
         }

         WorldMapRenderer.m_vboLines.flush();
      }
   }

    void renderImagePyramids() {
      for (int var1 = this.m_worldMap.getImagesCount() - 1; var1 >= 0; var1--) {
    WorldMapImages var2 = this.m_worldMap.getImagesByIndex(var1);
         this.renderImagePyramid(var2);
         GL11.glDisable(3553);
      }
   }

    void renderImagePyramid(WorldMapImages var1) {
    float var2 = this.m_worldScale;
    short var3 = 256;
    int var4 = var1.getZoom(this.m_zoomF);
    float var5 = var3 * (1 << var4);
      this.calcVisiblePyramidTiles(var1);
      GL11.glEnable(3553);
      GL11.glEnable(3042);
      WorldMapRenderer.m_vboLinesUV.setMode(4);
    int var6 = PZMath.clamp(var1.getMinX(), this.m_worldMap.getMinXInSquares(), this.m_worldMap.getMaxXInSquares());
    int var7 = PZMath.clamp(var1.getMinY(), this.m_worldMap.getMinYInSquares(), this.m_worldMap.getMaxYInSquares());
    int var8 = PZMath.clamp(var1.getMaxX(), this.m_worldMap.getMinXInSquares(), this.m_worldMap.getMaxXInSquares() + 1);
    int var9 = PZMath.clamp(var1.getMaxY(), this.m_worldMap.getMinYInSquares(), this.m_worldMap.getMaxYInSquares() + 1);

      for (byte var10 = 0; var10 < this.m_rasterizeXY.size() - 1; var10 += 2) {
    int var11 = this.m_rasterizeXY_ints[var10];
    int var12 = this.m_rasterizeXY_ints[var10 + 1];
    TextureID var13 = var1.getPyramid().getTexture(var11, var12, var4);
         if (var13 != nullptr && var13.isReady()) {
            WorldMapRenderer.m_vboLinesUV.startRun(var13);
    float var14 = var1.getMinX() + var11 * var5;
    float var15 = var1.getMinY() + var12 * var5;
    float var16 = var14 + var5;
    float var17 = var15 + var5;
    float var18 = PZMath.clamp(var14, var6, var8);
    float var19 = PZMath.clamp(var15, var7, var9);
    float var20 = PZMath.clamp(var16, var6, var8);
    float var21 = PZMath.clamp(var17, var7, var9);
    float var22 = (var18 - this.m_centerWorldX) * var2;
    float var23 = (var19 - this.m_centerWorldY) * var2;
    float var24 = (var20 - this.m_centerWorldX) * var2;
    float var25 = (var19 - this.m_centerWorldY) * var2;
    float var26 = (var20 - this.m_centerWorldX) * var2;
    float var27 = (var21 - this.m_centerWorldY) * var2;
    float var28 = (var18 - this.m_centerWorldX) * var2;
    float var29 = (var21 - this.m_centerWorldY) * var2;
    float var30 = (var18 - var14) / var5;
    float var31 = (var19 - var15) / var5;
    float var32 = (var20 - var14) / var5;
    float var33 = (var19 - var15) / var5;
    float var34 = (var20 - var14) / var5;
    float var35 = (var21 - var15) / var5;
    float var36 = (var18 - var14) / var5;
    float var37 = (var21 - var15) / var5;
    float var38 = 1.0F;
    float var39 = 1.0F;
    float var40 = 1.0F;
    float var41 = 1.0F;
            WorldMapRenderer.m_vboLinesUV.addElement(var22, var23, 0.0F, var30, var31, var38, var39, var40, var41);
            WorldMapRenderer.m_vboLinesUV.addElement(var24, var25, 0.0F, var32, var33, var38, var39, var40, var41);
            WorldMapRenderer.m_vboLinesUV.addElement(var28, var29, 0.0F, var36, var37, var38, var39, var40, var41);
            WorldMapRenderer.m_vboLinesUV.addElement(var24, var25, 0.0F, var32, var33, var38, var39, var40, var41);
            WorldMapRenderer.m_vboLinesUV.addElement(var26, var27, 0.0F, var34, var35, var38, var39, var40, var41);
            WorldMapRenderer.m_vboLinesUV.addElement(var28, var29, 0.0F, var36, var37, var38, var39, var40, var41);
            if (this.m_renderer.TileGrid.getValue()) {
               WorldMapRenderer.m_vboLinesUV.flush();
               WorldMapRenderer.m_vboLines.setMode(1);
               WorldMapRenderer.m_vboLines.setLineWidth(2.0F);
               WorldMapRenderer.m_vboLines
                  .addLine(
                     (var14 - this.m_centerWorldX) * var2,
                     (var15 - this.m_centerWorldY) * var2,
                     0.0F,
                     (var16 - this.m_centerWorldX) * var2,
                     (var15 - this.m_centerWorldY) * var2,
                     0.0F,
                     1.0F,
                     0.0F,
                     0.0F,
                     0.5F
                  );
               WorldMapRenderer.m_vboLines
                  .addLine(
                     (var14 - this.m_centerWorldX) * var2,
                     (var17 - this.m_centerWorldY) * var2,
                     0.0F,
                     (var16 - this.m_centerWorldX) * var2,
                     (var17 - this.m_centerWorldY) * var2,
                     0.0F,
                     1.0F,
                     0.0F,
                     0.0F,
                     0.5F
                  );
               WorldMapRenderer.m_vboLines
                  .addLine(
                     (var16 - this.m_centerWorldX) * var2,
                     (var15 - this.m_centerWorldY) * var2,
                     0.0F,
                     (var16 - this.m_centerWorldX) * var2,
                     (var17 - this.m_centerWorldY) * var2,
                     0.0F,
                     1.0F,
                     0.0F,
                     0.0F,
                     0.5F
                  );
               WorldMapRenderer.m_vboLines
                  .addLine(
                     (var14 - this.m_centerWorldX) * var2,
                     (var15 - this.m_centerWorldY) * var2,
                     0.0F,
                     (var14 - this.m_centerWorldX) * var2,
                     (var17 - this.m_centerWorldY) * var2,
                     0.0F,
                     1.0F,
                     0.0F,
                     0.0F,
                     0.5F
                  );
               WorldMapRenderer.m_vboLines.flush();
            }
         }
      }
   }

    void renderImagePyramidGrid(WorldMapImages var1) {
    float var2 = this.m_worldScale;
    short var3 = 256;
    int var4 = var1.getZoom(this.m_zoomF);
    float var5 = var3 * (1 << var4);
    float var6 = (var1.getMinX() - this.m_centerWorldX) * var2;
    float var7 = (var1.getMinY() - this.m_centerWorldY) * var2;
    int var8 = (int)Math.ceil((var1.getMaxX() - var1.getMinX()) / var5);
    int var9 = (int)Math.ceil((var1.getMaxY() - var1.getMinY()) / var5);
    float var10 = var6;
    float var11 = var7;
    float var12 = var6 + var8 * var5 * var2;
    float var13 = var7 + var9 * var5 * var2;
      WorldMapRenderer.m_vboLines.setMode(1);
      WorldMapRenderer.m_vboLines.setLineWidth(2.0F);

      for (int var14 = 0; var14 < var8 + 1; var14++) {
         WorldMapRenderer.m_vboLines.addLine(var6 + var14 * var5 * var2, var11, 0.0F, var6 + var14 * var5 * var2, var13, 0.0F, 1.0F, 0.0F, 0.0F, 0.5F);
      }

      for (int var15 = 0; var15 < var9 + 1; var15++) {
         WorldMapRenderer.m_vboLines.addLine(var10, var7 + var15 * var5 * var2, 0.0F, var12, var7 + var15 * var5 * var2, 0.0F, 1.0F, 0.0F, 0.0F, 0.5F);
      }

      WorldMapRenderer.m_vboLines.flush();
   }

    float triangleArea(float var1, float var2, float var3, float var4, float var5, float var6) {
    float var7 = Vector2f.length(var3 - var1, var4 - var2);
    float var8 = Vector2f.length(var5 - var3, var6 - var4);
    float var9 = Vector2f.length(var1 - var5, var2 - var6);
    float var10 = (var7 + var8 + var9) / 2.0F;
      return (float)Math.sqrt(var10 * (var10 - var7) * (var10 - var8) * (var10 - var9));
   }

    void paintAreasOutsideBounds(int var1, int var2, int var3, int var4, float var5) {
    float var6 = this.m_renderOriginX - var1 % 300 * var5;
    float var7 = this.m_renderOriginY - var2 % 300 * var5;
    float var8 = this.m_renderOriginX + ((this.m_worldMap.getMaxXInCells() + 1) * 300 - var1) * var5;
    float var9 = this.m_renderOriginY + ((this.m_worldMap.getMaxYInCells() + 1) * 300 - var2) * var5;
    float var10 = 0.0F;
    RGBAf var11 = this.m_fill;
      if (var1 % 300 != 0) {
    float var14 = this.m_renderOriginX;
         WorldMapRenderer.m_vboLines.setMode(4);
         WorldMapRenderer.m_vboLines.addQuad(var6, var7, var14, var9, var10, var11.r, var11.g, var11.b, var11.a);
      }

      if (var2 % 300 != 0) {
    float var12 = this.m_renderOriginX;
    float var18 = var12 + this.m_worldMap.getWidthInSquares() * this.m_worldScale;
    float var15 = this.m_renderOriginY;
         WorldMapRenderer.m_vboLines.setMode(4);
         WorldMapRenderer.m_vboLines.addQuad(var12, var7, var18, var15, var10, var11.r, var11.g, var11.b, var11.a);
      }

      if (var3 + 1 != 0) {
    float var16 = this.m_renderOriginX + (var3 - var1 + 1) * var5;
         WorldMapRenderer.m_vboLines.setMode(4);
         WorldMapRenderer.m_vboLines.addQuad(var16, var7, var8, var9, var10, var11.r, var11.g, var11.b, var11.a);
      }

      if (var4 + 1 != 0) {
    float var17 = this.m_renderOriginX;
    float var13 = this.m_renderOriginY + this.m_worldMap.getHeightInSquares() * var5;
    float var19 = this.m_renderOriginX + this.m_worldMap.getWidthInSquares() * var5;
         WorldMapRenderer.m_vboLines.setMode(4);
         WorldMapRenderer.m_vboLines.addQuad(var17, var13, var19, var9, var10, var11.r, var11.g, var11.b, var11.a);
      }
   }

    void renderWorldBounds() {
    float var1 = this.m_renderOriginX;
    float var2 = this.m_renderOriginY;
    float var3 = var1 + this.m_worldMap.getWidthInSquares() * this.m_worldScale;
    float var4 = var2 + this.m_worldMap.getHeightInSquares() * this.m_worldScale;
      this.renderDropShadow();
      WorldMapRenderer.m_vboLines.setMode(1);
      WorldMapRenderer.m_vboLines.setLineWidth(2.0F);
    float var5 = 0.5F;
      WorldMapRenderer.m_vboLines.addLine(var1, var2, 0.0F, var3, var2, 0.0F, var5, var5, var5, 1.0F);
      WorldMapRenderer.m_vboLines.addLine(var3, var2, 0.0F, var3, var4, 0.0F, var5, var5, var5, 1.0F);
      WorldMapRenderer.m_vboLines.addLine(var3, var4, 0.0F, var1, var4, 0.0F, var5, var5, var5, 1.0F);
      WorldMapRenderer.m_vboLines.addLine(var1, var4, 0.0F, var1, var2, 0.0F, var5, var5, var5, 1.0F);
   }

    void renderDropShadow() {
      float var1 = this.m_renderer.m_dropShadowWidth
         * (this.m_renderer.getHeight() / 1080.0F)
         * this.m_worldScale
         / this.m_renderer.getWorldScale(this.m_renderer.getBaseZoom());
      if (!(var1 < 2.0F)) {
    float var2 = this.m_renderOriginX;
    float var3 = this.m_renderOriginY;
    float var4 = var2 + this.m_worldMap.getWidthInSquares() * this.m_worldScale;
    float var5 = var3 + this.m_worldMap.getHeightInSquares() * this.m_worldScale;
         WorldMapRenderer.m_vboLines.setMode(4);
         WorldMapRenderer.m_vboLines.addElement(var2 + var1, var5, 0.0F, 0.5F, 0.5F, 0.5F, 0.5F);
         WorldMapRenderer.m_vboLines.addElement(var4, var5, 0.0F, 0.5F, 0.5F, 0.5F, 0.5F);
         WorldMapRenderer.m_vboLines.addElement(var2 + var1, var5 + var1, 0.0F, 0.5F, 0.5F, 0.5F, 0.0F);
         WorldMapRenderer.m_vboLines.addElement(var4, var5, 0.0F, 0.5F, 0.5F, 0.5F, 0.5F);
         WorldMapRenderer.m_vboLines.addElement(var4 + var1, var5 + var1, 0.0F, 0.5F, 0.5F, 0.5F, 0.0F);
         WorldMapRenderer.m_vboLines.addElement(var2 + var1, var5 + var1, 0.0F, 0.5F, 0.5F, 0.5F, 0.0F);
         WorldMapRenderer.m_vboLines.addElement(var4, var3 + var1, 0.0F, 0.5F, 0.5F, 0.5F, 0.5F);
         WorldMapRenderer.m_vboLines.addElement(var4 + var1, var3 + var1, 0.0F, 0.5F, 0.5F, 0.5F, 0.0F);
         WorldMapRenderer.m_vboLines.addElement(var4, var5, 0.0F, 0.5F, 0.5F, 0.5F, 0.5F);
         WorldMapRenderer.m_vboLines.addElement(var4 + var1, var3 + var1, 0.0F, 0.5F, 0.5F, 0.5F, 0.0F);
         WorldMapRenderer.m_vboLines.addElement(var4 + var1, var5 + var1, 0.0F, 0.5F, 0.5F, 0.5F, 0.0F);
         WorldMapRenderer.m_vboLines.addElement(var4, var5, 0.0F, 0.5F, 0.5F, 0.5F, 0.5F);
      }
   }

    void postRender() {
      for (int var1 = 0; var1 < this.m_playerRenderData.length; var1++) {
    PlayerRenderData var2 = this.m_playerRenderData[var1];
         if (var2.m_modelSlotRenderData != nullptr) {
            var2.m_modelSlotRenderData.postRender();
         }
      }
   }
}
} // namespace worldMap
} // namespace zombie
