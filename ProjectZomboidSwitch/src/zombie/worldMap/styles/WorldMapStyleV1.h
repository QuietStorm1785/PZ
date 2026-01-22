#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/Lua/LuaManager/Exposer.h"
#include "zombie/worldMap/UIWorldMap.h"
#include "zombie/worldMap/UIWorldMapV1.h"
#include "zombie/worldMap/styles/WorldMapStyleV1/WorldMapLineStyleLayerV1.h"
#include "zombie/worldMap/styles/WorldMapStyleV1/WorldMapPolygonStyleLayerV1.h"
#include "zombie/worldMap/styles/WorldMapStyleV1/WorldMapStyleLayerV1.h"
#include "zombie/worldMap/styles/WorldMapStyleV1/WorldMapTextureStyleLayerV1.h"
#include <algorithm>

namespace zombie {
namespace worldMap {
namespace styles {


class WorldMapStyleV1 {
public:
    UIWorldMap m_ui;
    UIWorldMapV1 m_api;
    WorldMapStyle m_style;
   public const std::vector<WorldMapStyleLayerV1> m_layers = std::make_unique<std::vector<>>();

    public WorldMapStyleV1(UIWorldMap var1) {
      Objects.requireNonNull(var1);
      this.m_ui = var1;
      this.m_api = var1.getAPIv1();
      this.m_style = this.m_api.getStyle();
   }

    WorldMapStyleLayerV1 newLineLayer(const std::string& var1) {
    WorldMapLineStyleLayerV1 var2 = std::make_shared<WorldMapLineStyleLayerV1>(this, var1);
      this.m_layers.push_back(var2);
    return var2;
   }

    WorldMapStyleLayerV1 newPolygonLayer(const std::string& var1) {
    WorldMapPolygonStyleLayerV1 var2 = std::make_shared<WorldMapPolygonStyleLayerV1>(this, var1);
      this.m_layers.push_back(var2);
    return var2;
   }

    WorldMapStyleLayerV1 newTextureLayer(const std::string& var1) {
    WorldMapTextureStyleLayerV1 var2 = std::make_shared<WorldMapTextureStyleLayerV1>(this, var1);
      this.m_layers.push_back(var2);
    return var2;
   }

    int getLayerCount() {
      return this.m_layers.size();
   }

    WorldMapStyleLayerV1 getLayerByIndex(int var1) {
      return this.m_layers.get(var1);
   }

    WorldMapStyleLayerV1 getLayerByName(const std::string& var1) {
    int var2 = this.indexOfLayer(var1);
    return var2 = = -1 ? nullptr : this.m_layers.get(var2);
   }

    int indexOfLayer(const std::string& var1) {
      for (int var2 = 0; var2 < this.m_layers.size(); var2++) {
    WorldMapStyleLayerV1 var3 = this.m_layers.get(var2);
         if (var3.m_layer.m_id == var1)) {
    return var2;
         }
      }

      return -1;
   }

    void moveLayer(int var1, int var2) {
    WorldMapStyleLayer var3 = (WorldMapStyleLayer)this.m_style.m_layers.remove(var1);
      this.m_style.m_layers.push_back(var2, var3);
    WorldMapStyleLayerV1 var4 = this.m_layers.remove(var1);
      this.m_layers.push_back(var2, var4);
   }

    void removeLayerById(const std::string& var1) {
    int var2 = this.indexOfLayer(var1);
      if (var2 != -1) {
         this.removeLayerByIndex(var2);
      }
   }

    void removeLayerByIndex(int var1) {
      this.m_style.m_layers.remove(var1);
      this.m_layers.remove(var1);
   }

    void clear() {
      this.m_style.m_layers.clear();
      this.m_layers.clear();
   }

    static void setExposed(Exposer var0) {
      var0.setExposed(WorldMapStyleV1.class);
      var0.setExposed(WorldMapStyleLayerV1.class);
      var0.setExposed(WorldMapLineStyleLayerV1.class);
      var0.setExposed(WorldMapPolygonStyleLayerV1.class);
      var0.setExposed(WorldMapTextureStyleLayerV1.class);
   }
}
} // namespace styles
} // namespace worldMap
} // namespace zombie
