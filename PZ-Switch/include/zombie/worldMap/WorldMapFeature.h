#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace worldMap {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class WorldMapFeature {
public:
 const WorldMapCell m_cell;
public
 ArrayList<WorldMapGeometry> m_geometries =
 std::make_unique<ArrayList<>>();
 WorldMapProperties m_properties = nullptr;

 WorldMapFeature(WorldMapCell worldMapCell) { this->m_cell = worldMapCell; }

 bool hasLineString() {
 for (int int0 = 0; int0 < this->m_geometries.size(); int0++) {
 if (this->m_geometries.get(int0).m_type ==
 WorldMapGeometry.Type.LineString) {
 return true;
 }
 }

 return false;
 }

 bool hasPoint() {
 for (int int0 = 0; int0 < this->m_geometries.size(); int0++) {
 if (this->m_geometries.get(int0).m_type == WorldMapGeometry.Type.Point) {
 return true;
 }
 }

 return false;
 }

 bool hasPolygon() {
 for (int int0 = 0; int0 < this->m_geometries.size(); int0++) {
 if (this->m_geometries.get(int0).m_type == WorldMapGeometry.Type.Polygon) {
 return true;
 }
 }

 return false;
 }

 bool containsPoint(float x, float y) {
 for (int int0 = 0; int0 < this->m_geometries.size(); int0++) {
 WorldMapGeometry worldMapGeometry = this->m_geometries.get(int0);
 if (worldMapGeometry.containsPoint(x, y) {
 return true;
 }
 }

 return false;
 }

 void dispose() {
 for (WorldMapGeometry worldMapGeometry : this->m_geometries) {
 worldMapGeometry.dispose();
 }

 this->m_properties.clear();
 }
}
} // namespace worldMap
} // namespace zombie
