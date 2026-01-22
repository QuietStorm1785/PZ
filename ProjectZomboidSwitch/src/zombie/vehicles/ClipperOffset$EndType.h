#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace vehicles {

enum class ClipperOffset {
   etClosedPolygon,
   etClosedLine,
   etOpenButt,
   etOpenSquare,
   etOpenRound;
}
} // namespace vehicles
} // namespace zombie
