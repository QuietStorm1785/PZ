#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace iso {
namespace areas {
namespace isoregion {
namespace regions {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

/**
 * TurboTuTone.
 */
class IWorldRegion {
public:
  virtual ~IWorldRegion() = default;
  ArrayList<IsoWorldRegion> getDebugConnectedNeighborCopy();

  ArrayList<IsoWorldRegion> getNeighbors();

  bool isFogMask();

  bool isPlayerRoom();

  bool isFullyRoofed();

  int getRoofCnt();

  int getSquareSize();

  ArrayList<IsoChunkRegion> getDebugIsoChunkRegionCopy();
}
} // namespace regions
} // namespace isoregion
} // namespace areas
} // namespace iso
} // namespace zombie
