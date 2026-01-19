#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/Lua/LuaManager/Exposer.h"
#include "zombie/characters/Faction.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Core.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/input/GameKeyboard.h"
#include "zombie/inventory/types/MapItem.h"
#include "zombie/iso/BuildingDef.h"
#include "zombie/iso/IsoMetaGrid.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/RoomDef.h"
#include "zombie/iso/RoomDef/RoomRect.h"
#include "zombie/iso/areas/SafeHouse.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/ServerOptions.h"
#include "zombie/ui/TextManager.h"
#include "zombie/ui/UIElement.h"
#include "zombie/ui/UIFont.h"
#include "zombie/util/StringUtils.h"
#include "zombie/worldMap/WorldMapRenderer/WorldMapBooleanOption.h"
#include "zombie/worldMap/WorldMapRenderer/WorldMapDoubleOption.h"
#include "zombie/worldMap/editor/WorldMapEditorState.h"
#include "zombie/worldMap/markers/WorldMapGridSquareMarker.h"
#include "zombie/worldMap/markers/WorldMapMarkers.h"
#include "zombie/worldMap/markers/WorldMapMarkersV1.h"
#include "zombie/worldMap/styles/WorldMapStyle.h"
#include "zombie/worldMap/styles/WorldMapStyleLayer/RGBAf.h"
#include "zombie/worldMap/styles/WorldMapStyleV1.h"
#include "zombie/worldMap/symbols/MapSymbolDefinitions.h"
#include "zombie/worldMap/symbols/MapSymbolDefinitions/MapSymbolDefinition.h"
#include "zombie/worldMap/symbols/WorldMapSymbols.h"
#include "zombie/worldMap/symbols/WorldMapSymbolsV1.h"

namespace zombie {
namespace worldMap {


class UIWorldMap : public UIElement {
public:
   static final ArrayList<WorldMapFeature> s_tempFeatures = std::make_unique<ArrayList<>>();
    auto m_worldMap = std::make_shared<WorldMap>();
    auto m_style = std::make_shared<WorldMapStyle>();
    auto m_renderer = std::make_shared<WorldMapRenderer>();
    auto m_markers = std::make_shared<WorldMapMarkers>();
    WorldMapSymbols m_symbols = null;
    auto m_color = std::make_shared<RGBAf>().init(0.85882354F, 0.84313726F, 0.7529412F, 1.0F);
    auto m_APIv1 = std::make_shared<UIWorldMapV1>(this);
    bool m_dataWasReady = false;
   private final ArrayList<BuildingDef> m_buildingsWithoutFeatures = std::make_unique<ArrayList<>>();
    bool m_bBuildingsWithoutFeatures = false;

    public UIWorldMap(KahluaTable var1) {
      super(var1);
   }

    UIWorldMapV1 getAPI() {
      return this.m_APIv1;
   }

    UIWorldMapV1 getAPIv1() {
      return this.m_APIv1;
   }

    void setMapItem(MapItem var1) {
      this.m_symbols = var1.getSymbols();
   }

    void render() {
      if (this.isVisible()) {
         if (this.Parent == nullptr || this.Parent.getMaxDrawHeight() == -1.0 || !(this.Parent.getMaxDrawHeight() <= this.getY())) {
            this.DrawTextureScaledColor(
               nullptr,
               0.0,
               0.0,
               this.getWidth(),
               this.getHeight(),
               (double)this.m_color.r,
               (double)this.m_color.g,
               (double)this.m_color.b,
               (double)this.m_color.a
            );
            if (!this.m_worldMap.hasData()) {
            }

            this.setStencilRect(0.0, 0.0, this.getWidth(), this.getHeight());
            this.m_renderer
               .setMap(this.m_worldMap, this.getAbsoluteX().intValue(), this.getAbsoluteY().intValue(), this.getWidth().intValue(), this.getHeight().intValue());
            this.m_renderer.updateView();
    float var1 = this.m_renderer.getDisplayZoomF();
    float var2 = this.m_renderer.getCenterWorldX();
    float var3 = this.m_renderer.getCenterWorldY();
    float var4 = this.m_APIv1.getWorldScale(var1);
            if (this.m_renderer.getBoolean("HideUnvisited") && WorldMapVisited.getInstance() != nullptr) {
               this.m_renderer.setVisited(WorldMapVisited.getInstance());
            } else {
               this.m_renderer.setVisited(nullptr);
            }

            this.m_renderer.render(this);
            if (this.m_renderer.getBoolean("Symbols")) {
               this.m_symbols.render(this);
            }

            this.m_markers.render(this);
            this.renderLocalPlayers();
            this.renderRemotePlayers();
    int var5 = TextManager.instance.getFontHeight(UIFont.Small);
            if (Core.bDebug && this.m_renderer.getBoolean("DebugInfo")) {
               this.DrawTextureScaledColor(nullptr, 0.0, 0.0, 200.0, var5 * 4.0, 1.0, 1.0, 1.0, 1.0);
    float var6 = this.m_APIv1.mouseToWorldX();
    float var7 = this.m_APIv1.mouseToWorldY();
    double var8 = 0.0;
    double var10 = 0.0;
    double var12 = 0.0;
    double var14 = 1.0;
    int var16 = 0;
               this.DrawText("SQUARE = " + (int)var6 + "," + (int)var7, 0.0, var16, var8, var10, var12, var14);
               var16 += var5;
               this.DrawText("CELL = " + (int)(var6 / 300.0F) + "," + (int)(var7 / 300.0F), 0.0, var5, var8, var10, var12, var14);
               var16 += var5;
               this.DrawText("ZOOM = " + this.m_renderer.getDisplayZoomF(), 0.0, var16, var8, var10, var12, var14);
               var16 += var5;
               this.DrawText("SCALE = " + this.m_renderer.getWorldScale(this.m_renderer.getZoomF()), 0.0, var16, var8, var10, var12, var14);
               var16 += var5;
            }

            this.clearStencilRect();
            this.repaintStencilRect(0.0, 0.0, this.width, this.height);
            if (Core.bDebug && DebugOptions.instance.UIRenderOutline.getValue()) {
    double var23 = -this.getXScroll();
    double var25 = -this.getYScroll();
    double var27 = this.isMouseOver() ? 0.0 : 1.0;
               this.DrawTextureScaledColor(nullptr, var23, var25, 1.0, (double)this.height, var27, 1.0, 1.0, 0.5);
               this.DrawTextureScaledColor(nullptr, var23 + 1.0, var25, this.width - 2.0, 1.0, var27, 1.0, 1.0, 0.5);
               this.DrawTextureScaledColor(nullptr, var23 + this.width - 1.0, var25, 1.0, (double)this.height, var27, 1.0, 1.0, 0.5);
               this.DrawTextureScaledColor(nullptr, var23 + 1.0, var25 + this.height - 1.0, this.width - 2.0, 1.0, var27, 1.0, 1.0, 0.5);
            }

            if (Core.bDebug && this.m_renderer.getBoolean("HitTest")) {
    float var24 = this.m_APIv1.mouseToWorldX();
    float var26 = this.m_APIv1.mouseToWorldY();
               s_tempFeatures.clear();

               for (WorldMapData var9 : this.m_worldMap.m_data) {
                  if (var9.isReady()) {
                     var9.hitTest(var24, var26, s_tempFeatures);
                  }
               }

               if (!s_tempFeatures.isEmpty()) {
    WorldMapFeature var29 = s_tempFeatures.get(s_tempFeatures.size() - 1);
    int var30 = var29.m_cell.m_x * 300;
    int var31 = var29.m_cell.m_y * 300;
    int var11 = this.getAbsoluteX().intValue();
    int var32 = this.getAbsoluteY().intValue();
    WorldMapPoints var13 = (WorldMapPoints)(static_cast<WorldMapGeometry>(var29).m_geometries.get(0)).m_points.get(0);

                  for (int var33 = 0; var33 < var13.numPoints(); var33++) {
    int var15 = var13.getX(var33);
    int var38 = var13.getY(var33);
    int var17 = var13.getX((var33 + 1) % var13.numPoints());
    int var18 = var13.getY((var33 + 1) % var13.numPoints());
    float var19 = this.m_APIv1.worldToUIX(var30 + var15, var31 + var38);
    float var20 = this.m_APIv1.worldToUIY(var30 + var15, var31 + var38);
    float var21 = this.m_APIv1.worldToUIX(var30 + var17, var31 + var18);
    float var22 = this.m_APIv1.worldToUIY(var30 + var17, var31 + var18);
                     SpriteRenderer.instance
                        .renderline(nullptr, var11 + (int)var19, var32 + (int)var20, var11 + (int)var21, var32 + (int)var22, 1.0F, 0.0F, 0.0F, 1.0F);
                  }
               }
            }

            if (Core.bDebug && this.m_renderer.getBoolean("BuildingsWithoutFeatures") && !this.m_renderer.getBoolean("Isometric")) {
               this.renderBuildingsWithoutFeatures();
            }

            super.render();
         }
      }
   }

    void renderLocalPlayers() {
      if (this.m_renderer.getBoolean("Players")) {
    float var1 = this.m_renderer.getDisplayZoomF();
         if (!(var1 >= 20.0F)) {
            for (int var2 = 0; var2 < IsoPlayer.numPlayers; var2++) {
    IsoPlayer var3 = IsoPlayer.players[var2];
               if (var3 != nullptr && !var3.isDead()) {
    float var4 = var3.x;
    float var5 = var3.y;
                  if (var3.getVehicle() != nullptr) {
                     var4 = var3.getVehicle().getX();
                     var5 = var3.getVehicle().getY();
                  }

                  this.renderPlayer(var4, var5);
                  if (GameClient.bClient) {
                     this.renderPlayerName(var4, var5, var3.getUsername());
                  }
               }
            }
         }
      }
   }

    void renderRemotePlayers() {
      if (GameClient.bClient) {
         if (this.m_renderer.getBoolean("Players")) {
            if (this.m_renderer.getBoolean("RemotePlayers")) {
    std::vector var1 = WorldMapRemotePlayers.instance.getPlayers();

               for (int var2 = 0; var2 < var1.size(); var2++) {
    WorldMapRemotePlayer var3 = static_cast<WorldMapRemotePlayer>(var1).get(var2);
                  if (this.shouldShowRemotePlayer(var3)) {
                     this.renderPlayer(var3.getX(), var3.getY());
                     this.renderPlayerName(var3.getX(), var3.getY(), var3.getUsername());
                  }
               }
            }
         }
      }
   }

    bool shouldShowRemotePlayer(WorldMapRemotePlayer var1) {
      if (!var1.hasFullData()) {
    return false;
      } else if (var1.isInvisible()) {
         return this.isAdminSeeRemotePlayers();
      } else if (ServerOptions.getInstance().MapRemotePlayerVisibility.getValue() == 3) {
    return true;
      } else if (this.isAdminSeeRemotePlayers()) {
    return true;
      } else if (ServerOptions.getInstance().MapRemotePlayerVisibility.getValue() == 1) {
    return false;
      } else {
         for (int var2 = 0; var2 < IsoPlayer.numPlayers; var2++) {
    IsoPlayer var3 = IsoPlayer.players[var2];
            if (var3 != nullptr) {
               if (this.isInSameFaction(var3, var1)) {
    return true;
               }

               if (this.isInSameSafehouse(var3, var1)) {
    return true;
               }
            }
         }

    return false;
      }
   }

    bool isAdminSeeRemotePlayers() {
      for (int var1 = 0; var1 < IsoPlayer.numPlayers; var1++) {
    IsoPlayer var2 = IsoPlayer.players[var1];
         if (var2 != nullptr && !var2.isAccessLevel("none")) {
    return true;
         }
      }

    return false;
   }

    bool isInSameFaction(IsoPlayer var1, WorldMapRemotePlayer var2) {
    Faction var3 = Faction.getPlayerFaction(var1);
    Faction var4 = Faction.getPlayerFaction(var2.getUsername());
      return var3 != nullptr && var3 == var4;
   }

    bool isInSameSafehouse(IsoPlayer var1, WorldMapRemotePlayer var2) {
    std::vector var3 = SafeHouse.getSafehouseList();

      for (int var4 = 0; var4 < var3.size(); var4++) {
    SafeHouse var5 = static_cast<SafeHouse>(var3).get(var4);
         if (var5.playerAllowed(var1.getUsername()) && var5.playerAllowed(var2.getUsername())) {
    return true;
         }
      }

    return false;
   }

    void renderPlayer(float var1, float var2) {
    float var3 = this.m_renderer.getDisplayZoomF();
    float var4 = this.m_renderer.getCenterWorldX();
    float var5 = this.m_renderer.getCenterWorldY();
    float var6 = this.m_APIv1.worldToUIX(var1, var2, var3, var4, var5, this.m_renderer.getProjectionMatrix(), this.m_renderer.getModelViewMatrix());
    float var7 = this.m_APIv1.worldToUIY(var1, var2, var3, var4, var5, this.m_renderer.getProjectionMatrix(), this.m_renderer.getModelViewMatrix());
      var6 = PZMath.floor(var6);
      var7 = PZMath.floor(var7);
      this.DrawTextureScaledColor(nullptr, var6 - 3.0, var7 - 3.0, 6.0, 6.0, 1.0, 0.0, 0.0, 1.0);
   }

    void renderPlayerName(float var1, float var2, const std::string& var3) {
      if (this.m_renderer.getBoolean("PlayerNames")) {
         if (!StringUtils.isNullOrWhitespace(var3)) {
    float var4 = this.m_renderer.getDisplayZoomF();
    float var5 = this.m_renderer.getCenterWorldX();
    float var6 = this.m_renderer.getCenterWorldY();
    float var7 = this.m_APIv1.worldToUIX(var1, var2, var4, var5, var6, this.m_renderer.getProjectionMatrix(), this.m_renderer.getModelViewMatrix());
    float var8 = this.m_APIv1.worldToUIY(var1, var2, var4, var5, var6, this.m_renderer.getProjectionMatrix(), this.m_renderer.getModelViewMatrix());
            var7 = PZMath.floor(var7);
            var8 = PZMath.floor(var8);
    int var9 = TextManager.instance.MeasureStringX(UIFont.Small, var3) + 16;
    int var10 = TextManager.instance.font.getLineHeight();
    int var11 = (int)Math.ceil(var10 * 1.25);
            this.DrawTextureScaledColor(nullptr, var7 - var9 / 2.0, var8 + 4.0, (double)var9, (double)var11, 0.5, 0.5, 0.5, 0.5);
            this.DrawTextCentre(var3, var7, var8 + 4.0F + (var11 - var10) / 2.0, 0.0, 0.0, 0.0, 1.0);
         }
      }
   }

    void update() {
      super.update();
   }

    bool onMouseDown(double var1, double var3) {
      if (GameKeyboard.isKeyDown(42)) {
         this.m_renderer.resetView();
      }

      return super.onMouseDown(var1, var3);
   }

    bool onMouseUp(double var1, double var3) {
      return super.onMouseUp(var1, var3);
   }

    void onMouseUpOutside(double var1, double var3) {
      super.onMouseUpOutside(var1, var3);
   }

    bool onMouseMove(double var1, double var3) {
      return super.onMouseMove(var1, var3);
   }

    bool onMouseWheel(double var1) {
      return super.onMouseWheel(var1);
   }

    static void setExposed(Exposer var0) {
      var0.setExposed(MapItem.class);
      var0.setExposed(MapSymbolDefinitions.class);
      var0.setExposed(MapSymbolDefinition.class);
      var0.setExposed(UIWorldMap.class);
      var0.setExposed(UIWorldMapV1.class);
      var0.setExposed(WorldMapGridSquareMarker.class);
      var0.setExposed(WorldMapMarkers.class);
      var0.setExposed(WorldMapBooleanOption.class);
      var0.setExposed(WorldMapDoubleOption.class);
      var0.setExposed(WorldMapVisited.class);
      WorldMapMarkersV1.setExposed(var0);
      WorldMapStyleV1.setExposed(var0);
      WorldMapSymbolsV1.setExposed(var0);
      var0.setExposed(WorldMapEditorState.class);
      var0.setExposed(WorldMapSettings.class);
   }

    void renderBuildingsWithoutFeatures() {
      if (this.m_bBuildingsWithoutFeatures) {
         for (BuildingDef var13 : this.m_buildingsWithoutFeatures) {
            this.debugRenderBuilding(var13, 1.0F, 0.0F, 0.0F, 1.0F);
         }
      } else {
         this.m_bBuildingsWithoutFeatures = true;
         this.m_buildingsWithoutFeatures.clear();
    IsoMetaGrid var1 = IsoWorld.instance.MetaGrid;

         for (int var2 = 0; var2 < var1.Buildings.size(); var2++) {
    BuildingDef var3 = static_cast<BuildingDef>(var1).Buildings.get(var2);
    bool var4 = false;

            for (int var5 = 0; var5 < var3.rooms.size(); var5++) {
    RoomDef var6 = static_cast<RoomDef>(var3).rooms.get(var5);
               if (var6.level <= 0) {
    std::vector var7 = var6.getRects();

                  for (int var8 = 0; var8 < var7.size(); var8++) {
    RoomRect var9 = static_cast<RoomRect>(var7).get(var8);
                     s_tempFeatures.clear();

                     for (WorldMapData var11 : this.m_worldMap.m_data) {
                        if (var11.isReady()) {
                           var11.hitTest(var9.x + var9.w / 2.0F, var9.y + var9.h / 2.0F, s_tempFeatures);
                        }
                     }

                     if (!s_tempFeatures.isEmpty()) {
                        var4 = true;
                        break;
                     }
                  }

                  if (var4) {
                     break;
                  }
               }
            }

            if (!var4) {
               this.m_buildingsWithoutFeatures.add(var3);
            }
         }
      }
   }

    void debugRenderBuilding(BuildingDef var1, float var2, float var3, float var4, float var5) {
      for (int var6 = 0; var6 < var1.rooms.size(); var6++) {
    std::vector var7 = (static_cast<RoomDef>(var1).rooms.get(var6)).getRects();

         for (int var8 = 0; var8 < var7.size(); var8++) {
    RoomRect var9 = static_cast<RoomRect>(var7).get(var8);
    float var10 = this.m_APIv1.worldToUIX(var9.x, var9.y);
    float var11 = this.m_APIv1.worldToUIY(var9.x, var9.y);
    float var12 = this.m_APIv1.worldToUIX(var9.getX2(), var9.getY2());
    float var13 = this.m_APIv1.worldToUIY(var9.getX2(), var9.getY2());
            this.DrawTextureScaledColor(
               nullptr, (double)var10, (double)var11, (double)(var12 - var10), (double)(var13 - var11), (double)var2, (double)var3, (double)var4, (double)var5
            );
         }
      }
   }
}
} // namespace worldMap
} // namespace zombie
