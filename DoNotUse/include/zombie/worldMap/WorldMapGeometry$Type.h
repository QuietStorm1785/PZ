#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace worldMap {

enum class WorldMapGeometry {
   LineString,
   Point,
   Polygon;
}
} // namespace worldMap
} // namespace zombie
