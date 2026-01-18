#pragma once
#include "zombie/Lua/LuaManager.h"
#include "zombie/worldMap/UIWorldMap.h"
#include <algorithm>
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace worldMap {
namespace markers {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class WorldMapMarkersV1 {
public:
 const UIWorldMap m_ui;
private
 ArrayList<WorldMapMarkersV1.WorldMapMarkerV1> m_markers =
 std::make_unique<ArrayList<>>();

public
 WorldMapMarkersV1(UIWorldMap ui) {
 Objects.requireNonNull(ui);
 this->m_ui = ui;
 }

public
 WorldMapMarkersV1.WorldMapGridSquareMarkerV1
 addGridSquareMarker(int worldX, int worldY, int radius, float r, float g,
 float b, float a) {
 WorldMapGridSquareMarker worldMapGridSquareMarker =
 this->m_ui.getAPIv1().getMarkers().addGridSquareMarker(
 worldX, worldY, radius, r, g, b, a);
 WorldMapMarkersV1.WorldMapGridSquareMarkerV1 worldMapGridSquareMarkerV1 =
 new WorldMapMarkersV1.WorldMapGridSquareMarkerV1(
 worldMapGridSquareMarker);
 this->m_markers.add(worldMapGridSquareMarkerV1);
 return worldMapGridSquareMarkerV1;
 }

 void removeMarker(WorldMapMarkersV1.WorldMapMarkerV1 marker) {
 if (this->m_markers.remove(marker) {
 this->m_ui.getAPIv1().getMarkers().removeMarker(marker.m_marker);
 }
 }

 void clear() {
 this->m_ui.getAPIv1().getMarkers().clear();
 this->m_markers.clear();
 }

 static void setExposed(LuaManager.Exposer exposer) {
 exposer.setExposed(WorldMapMarkersV1.class);
 exposer.setExposed(WorldMapMarkersV1.WorldMapMarkerV1.class);
 exposer.setExposed(WorldMapMarkersV1.WorldMapGridSquareMarkerV1.class);
 }

public
 static class WorldMapGridSquareMarkerV1 extends
 WorldMapMarkersV1.WorldMapMarkerV1 {
 const WorldMapGridSquareMarker m_gridSquareMarker;

 WorldMapGridSquareMarkerV1(
 WorldMapGridSquareMarker worldMapGridSquareMarker) {
 super(worldMapGridSquareMarker);
 this->m_gridSquareMarker = worldMapGridSquareMarker;
 }

 void setBlink(bool blink) { this->m_gridSquareMarker.setBlink(blink); }

 void setMinScreenRadius(int pixels) {
 this->m_gridSquareMarker.setMinScreenRadius(pixels);
 }
 }

public
 static class WorldMapMarkerV1 {
 const WorldMapMarker m_marker;

 WorldMapMarkerV1(WorldMapMarker worldMapMarker) {
 this->m_marker = worldMapMarker;
 }
 }
}
} // namespace markers
} // namespace worldMap
} // namespace zombie
