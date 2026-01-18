#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace worldMap {
namespace styles {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class WorldMapStyle {
public:
public
 ArrayList<WorldMapStyleLayer> m_layers =
 std::make_unique<ArrayList<>>();

 void copyFrom(WorldMapStyle other) {
 this->m_layers.clear();
 this->m_layers.addAll(other.m_layers);
 }
}
} // namespace styles
} // namespace worldMap
} // namespace zombie
