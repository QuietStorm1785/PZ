#pragma once
#include "zombie/util/Pool.h"
#include "zombie/worldMap/UIWorldMap.h"
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

class WorldMapMarkers {
public:
private
 static Pool<WorldMapGridSquareMarker> s_gridSquareMarkerPool =
 new Pool<>(WorldMapGridSquareMarker::new);
private
 ArrayList<WorldMapMarker> m_markers = std::make_unique<ArrayList<>>();

 WorldMapGridSquareMarker addGridSquareMarker(int worldX, int worldY,
 int radius, float r, float g,
 float b, float a) {
 WorldMapGridSquareMarker worldMapGridSquareMarker =
 s_gridSquareMarkerPool.alloc().init(worldX, worldY, radius, r, g, b, a);
 this->m_markers.add(worldMapGridSquareMarker);
 return worldMapGridSquareMarker;
 }

 void removeMarker(WorldMapMarker marker) {
 if (this->m_markers.contains(marker) {
 this->m_markers.remove(marker);
 marker.release();
 }
 }

 void clear() {
 for (int int0 = 0; int0 < this->m_markers.size(); int0++) {
 this->m_markers.get(int0).release();
 }

 this->m_markers.clear();
 }

 void render(UIWorldMap ui) {
 for (int int0 = 0; int0 < this->m_markers.size(); int0++) {
 this->m_markers.get(int0).render(ui);
 }
 }
}
} // namespace markers
} // namespace worldMap
} // namespace zombie
