#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/math/PZMath.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/worldMap/WorldMapFeature.h"
#include "zombie/worldMap/styles/WorldMapStyleLayer/ColorStop.h"
#include "zombie/worldMap/styles/WorldMapStyleLayer/FilterArgs.h"
#include "zombie/worldMap/styles/WorldMapStyleLayer/FloatStop.h"
#include "zombie/worldMap/styles/WorldMapStyleLayer/IWorldMapStyleFilter.h"
#include "zombie/worldMap/styles/WorldMapStyleLayer/RGBAf.h"
#include "zombie/worldMap/styles/WorldMapStyleLayer/RenderArgs.h"
#include "zombie/worldMap/styles/WorldMapStyleLayer/Stop.h"
#include "zombie/worldMap/styles/WorldMapStyleLayer/TextureStop.h"

namespace zombie {
namespace worldMap {
namespace styles {


class WorldMapStyleLayer {
public:
    std::string m_id;
    float m_minZoom = 0.0F;
    IWorldMapStyleFilter m_filter;
    std::string m_filterKey;
    std::string m_filterValue;

    public WorldMapStyleLayer(const std::string& var1) {
      this.m_id = var1;
   }

   public abstract std::string getTypeString();

   static <S : public Stop> int findStop(float var0, std::vector<S> var1) {
      if (var1.empty()) {
         return -2;
      } else if (var0 <= ((Stop)var1.get(0)).m_zoom) {
         return -1;
      } else {
         for (int var2 = 0; var2 < var1.size() - 1; var2++) {
            if (var0 <= ((Stop)var1.get(var2 + 1)).m_zoom) {
    return var2;
            }
         }

         return var1.size() - 1;
      }
   }

    RGBAf evalColor(RenderArgs var1, std::vector<ColorStop> var2) {
      if (var2.empty()) {
         return ((RGBAf)RGBAf.s_pool.alloc()).init(1.0F, 1.0F, 1.0F, 1.0F);
      } else {
    float var3 = var1.drawer.m_zoomF;
    int var4 = findStop(var3, var2);
    int var5 = var4 == -1 ? 0 : var4;
    int var6 = PZMath.min(var4 + 1, var2.size() - 1);
    ColorStop var7 = (ColorStop)var2.get(var5);
    ColorStop var8 = (ColorStop)var2.get(var6);
    float var9 = var5 == var6 ? 1.0F : (PZMath.clamp(var3, var7.m_zoom, var8.m_zoom) - var7.m_zoom) / (var8.m_zoom - var7.m_zoom);
    float var10 = PZMath.lerp(var7.r, var8.r, var9) / 255.0F;
    float var11 = PZMath.lerp(var7.g, var8.g, var9) / 255.0F;
    float var12 = PZMath.lerp(var7.b, var8.b, var9) / 255.0F;
    float var13 = PZMath.lerp(var7.a, var8.a, var9) / 255.0F;
         return ((RGBAf)RGBAf.s_pool.alloc()).init(var10, var11, var12, var13);
      }
   }

    float evalFloat(RenderArgs var1, std::vector<FloatStop> var2) {
      if (var2.empty()) {
         return 1.0F;
      } else {
    float var3 = var1.drawer.m_zoomF;
    int var4 = findStop(var3, var2);
    int var5 = var4 == -1 ? 0 : var4;
    int var6 = PZMath.min(var4 + 1, var2.size() - 1);
    FloatStop var7 = (FloatStop)var2.get(var5);
    FloatStop var8 = (FloatStop)var2.get(var6);
    float var9 = var5 == var6 ? 1.0F : (PZMath.clamp(var3, var7.m_zoom, var8.m_zoom) - var7.m_zoom) / (var8.m_zoom - var7.m_zoom);
         return PZMath.lerp(var7.f, var8.f, var9);
      }
   }

    Texture evalTexture(RenderArgs var1, std::vector<TextureStop> var2) {
      if (var2.empty()) {
    return nullptr;
      } else {
    float var3 = var1.drawer.m_zoomF;
    int var4 = findStop(var3, var2);
    int var5 = var4 == -1 ? 0 : var4;
    int var6 = PZMath.min(var4 + 1, var2.size() - 1);
    TextureStop var7 = (TextureStop)var2.get(var5);
    TextureStop var8 = (TextureStop)var2.get(var6);
         if (var7 == var8) {
            return var3 < var7.m_zoom ? nullptr : var7.texture;
         } else if (!(var3 < var7.m_zoom) && !(var3 > var8.m_zoom)) {
    float var9 = var5 == var6 ? 1.0F : (PZMath.clamp(var3, var7.m_zoom, var8.m_zoom) - var7.m_zoom) / (var8.m_zoom - var7.m_zoom);
            return var9 < 0.5F ? var7.texture : var8.texture;
         } else {
    return nullptr;
         }
      }
   }

    bool filter(WorldMapFeature var1, FilterArgs var2) {
      return this.m_filter == nullptr ? false : this.m_filter.filter(var1, var2);
   }

   public abstract void render(WorldMapFeature var1, RenderArgs var2);

    void renderCell(RenderArgs var1) {
   }
}
} // namespace styles
} // namespace worldMap
} // namespace zombie
