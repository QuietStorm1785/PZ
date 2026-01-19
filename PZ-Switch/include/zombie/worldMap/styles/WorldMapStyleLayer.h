#pragma once
#include "zombie/core/math/PZMath.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/popman/ObjectPool.h"
#include "zombie/worldMap/WorldMapFeature.h"
#include "zombie/worldMap/WorldMapRenderer.h"
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace worldMap {
namespace styles {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class WorldMapStyleLayer {
public:
 std::string m_id;
 float m_minZoom = 0.0F;
public
 WorldMapStyleLayer.IWorldMapStyleFilter m_filter;
 std::string m_filterKey;
 std::string m_filterValue;

public
 WorldMapStyleLayer(std::string_view id) { this->m_id = id; }

public
 String getTypeString();

 static<S extends WorldMapStyleLayer.Stop> int
 findStop(float float0, ArrayList<S> arrayList) {
 if (arrayList.empty()) {
 return -2;
 } else if (float0 <= ((WorldMapStyleLayer.Stop)arrayList.get(0).m_zoom) {
 return -1;
 } else {
 for (int int0 = 0; int0 < arrayList.size() - 1; int0++) {
 if (float0 <=
 ((WorldMapStyleLayer.Stop)arrayList.get(int0 + 1).m_zoom) {
 return int0;
 }
 }

 return arrayList.size() - 1;
 }
 }

protected
 WorldMapStyleLayer.RGBAf
 evalColor(WorldMapStyleLayer.RenderArgs renderArgs,
 ArrayList<WorldMapStyleLayer.ColorStop> arrayList) {
 if (arrayList.empty()) {
 return WorldMapStyleLayer.RGBAf.s_pool.alloc().init(1.0F, 1.0F, 1.0F,
 1.0F);
 } else {
 float float0 = renderArgs.drawer.m_zoomF;
 int int0 = findStop(float0, arrayList);
 int int1 = int0 == -1 ? 0 : int0;
 int int2 = PZMath.min(int0 + 1, arrayList.size() - 1);
 WorldMapStyleLayer.ColorStop colorStop0 =
 (WorldMapStyleLayer.ColorStop)arrayList.get(int1);
 WorldMapStyleLayer.ColorStop colorStop1 =
 (WorldMapStyleLayer.ColorStop)arrayList.get(int2);
 float float1 =
 int1 == int2
 ? 1.0F
 : (PZMath.clamp(float0, colorStop0.m_zoom, colorStop1.m_zoom) -
 colorStop0.m_zoom) /
 (colorStop1.m_zoom - colorStop0.m_zoom);
 float float2 = PZMath.lerp(colorStop0.r, colorStop1.r, float1) / 255.0F;
 float float3 = PZMath.lerp(colorStop0.g, colorStop1.g, float1) / 255.0F;
 float float4 = PZMath.lerp(colorStop0.b, colorStop1.b, float1) / 255.0F;
 float float5 = PZMath.lerp(colorStop0.a, colorStop1.a, float1) / 255.0F;
 return WorldMapStyleLayer.RGBAf.s_pool.alloc().init(float2, float3,
 float4, float5);
 }
 }

 float evalFloat(WorldMapStyleLayer.RenderArgs renderArgs,
 ArrayList<WorldMapStyleLayer.FloatStop> arrayList) {
 if (arrayList.empty()) {
 return 1.0F;
 } else {
 float float0 = renderArgs.drawer.m_zoomF;
 int int0 = findStop(float0, arrayList);
 int int1 = int0 == -1 ? 0 : int0;
 int int2 = PZMath.min(int0 + 1, arrayList.size() - 1);
 WorldMapStyleLayer.FloatStop floatStop0 =
 (WorldMapStyleLayer.FloatStop)arrayList.get(int1);
 WorldMapStyleLayer.FloatStop floatStop1 =
 (WorldMapStyleLayer.FloatStop)arrayList.get(int2);
 float float1 =
 int1 == int2
 ? 1.0F
 : (PZMath.clamp(float0, floatStop0.m_zoom, floatStop1.m_zoom) -
 floatStop0.m_zoom) /
 (floatStop1.m_zoom - floatStop0.m_zoom);
 return PZMath.lerp(floatStop0.f, floatStop1.f, float1);
 }
 }

 Texture evalTexture(WorldMapStyleLayer.RenderArgs renderArgs,
 ArrayList<WorldMapStyleLayer.TextureStop> arrayList) {
 if (arrayList.empty()) {
 return nullptr;
 } else {
 float float0 = renderArgs.drawer.m_zoomF;
 int int0 = findStop(float0, arrayList);
 int int1 = int0 == -1 ? 0 : int0;
 int int2 = PZMath.min(int0 + 1, arrayList.size() - 1);
 WorldMapStyleLayer.TextureStop textureStop0 =
 (WorldMapStyleLayer.TextureStop)arrayList.get(int1);
 WorldMapStyleLayer.TextureStop textureStop1 =
 (WorldMapStyleLayer.TextureStop)arrayList.get(int2);
 if (textureStop0 == textureStop1) {
 return float0 < textureStop0.m_zoom ? nullptr : textureStop0.texture;
 } else if (!(float0 < textureStop0.m_zoom) &&
 !(float0 > textureStop1.m_zoom) {
 float float1 = int1 == int2
 ? 1.0F
 : (PZMath.clamp(float0, textureStop0.m_zoom,
 textureStop1.m_zoom) -
 textureStop0.m_zoom) /
 (textureStop1.m_zoom - textureStop0.m_zoom);
 return float1 < 0.5F ? textureStop0.texture : textureStop1.texture;
 } else {
 return nullptr;
 }
 }
 }

 bool filter(WorldMapFeature feature, WorldMapStyleLayer.FilterArgs args) {
 return this->m_filter.empty() ? false
 : this->m_filter.filter(feature, args);
 }

public
 void render(WorldMapFeature feature,
 WorldMapStyleLayer.RenderArgs args);

 void renderCell(WorldMapStyleLayer.RenderArgs args) {}

public
 static class ColorStop extends WorldMapStyleLayer.Stop {
 int r;
 int g;
 int b;
 int a;

 public
 ColorStop(float float0, int int0, int int1, int int2, int int3) {
 super(float0);
 this->r = int0;
 this->g = int1;
 this->b = int2;
 this->a = int3;
 }
 }

public
 static class FilterArgs {
 WorldMapRenderer renderer;
 }

 public static class FloatStop extends WorldMapStyleLayer.Stop {
 float f;

 public
 FloatStop(float float0, float float1) {
 super(float0);
 this->f = float1;
 }
 }

public
 interface IWorldMapStyleFilter {
 bool filter(WorldMapFeature feature, WorldMapStyleLayer.FilterArgs args);
 }

public
 static class RGBAf {
 float r;
 float g;
 float b;
 float a;
 public
 static ObjectPool<WorldMapStyleLayer.RGBAf> s_pool =
 new ObjectPool<>(WorldMapStyleLayer.RGBAf::new);

 public
 RGBAf() { this->r = this->g = this->b = this->a = 1.0F; }

 public
 WorldMapStyleLayer.RGBAf init(float _r, float _g, float _b, float _a) {
 this->r = _r;
 this->g = _g;
 this->b = _b;
 this->a = _a;
 return this;
 }
 }

 public static class RenderArgs {
 WorldMapRenderer renderer;
 public
 WorldMapRenderer.Drawer drawer;
 int cellX;
 int cellY;
 }

 public static class Stop {
 float m_zoom;

 Stop(float float0) { this->m_zoom = float0; }
 }

 public static class TextureStop extends WorldMapStyleLayer.Stop {
 std::string texturePath;
 Texture texture;

 public
 TextureStop(float float0, std::string_view string) {
 super(float0);
 this->texturePath = string;
 this->texture = Texture.getTexture(string);
 }
 }
}
} // namespace styles
} // namespace worldMap
} // namespace zombie
