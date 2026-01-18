#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace ai {
namespace astar {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

/**
 * A tagging interface for an object representing the entity in the game that is
 * going to moving along the path. This allows us to pass around entity/state
 * information to determine whether a particular tile is blocked, or how much
 * cost to apply on a particular tile.   For instance, a Mover might represent a
 * tank or plane on a game map. Passing round  this entity allows us to
 * determine whether rough ground on a map should effect  the unit's cost for
 * moving through the tile.
 */
class Mover {
public:
  virtual ~Mover() = default;
  int getID();

  int getPathFindIndex();
}
} // namespace astar
} // namespace ai
} // namespace zombie
