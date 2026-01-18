#pragma once
#include "zombie/core/Color.h"
#include "zombie/core/Colors.h"
#include "zombie/iso/areas/isoregion/IsoRegions.h"
#include "zombie/iso/areas/isoregion/data/DataRoot.h"
#include <algorithm>
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
class IsoRegionManager {
public:
private
  final ArrayDeque<IsoWorldRegion> poolIsoWorldRegion =
      std::make_unique<ArrayDeque<>>();
private
  final ArrayDeque<IsoChunkRegion> poolIsoChunkRegion =
      std::make_unique<ArrayDeque<>>();
  const DataRoot dataRoot;
private
  final ArrayDeque<Integer> regionIdStack = std::make_unique<ArrayDeque<>>();
  int nextID = 0;
  int colorIndex = 0;
  int worldRegionCount = 0;
  int chunkRegionCount = 0;

public
  IsoRegionManager(DataRoot _dataRoot) { this.dataRoot = _dataRoot; }

  IsoWorldRegion allocIsoWorldRegion() {
    IsoWorldRegion worldRegion = !this.poolIsoWorldRegion.isEmpty()
                                     ? this.poolIsoWorldRegion.pop()
                                     : new IsoWorldRegion(this);
    int int0 =
        this.regionIdStack.isEmpty() ? this.nextID++ : this.regionIdStack.pop();
    worldRegion.init(int0);
    this.worldRegionCount++;
    return worldRegion;
  }

  void releaseIsoWorldRegion(IsoWorldRegion worldRegion) {
    this.dataRoot.DequeueDirtyIsoWorldRegion(worldRegion);
    if (!worldRegion.isInPool()) {
      this.regionIdStack.push(worldRegion.getID());
      worldRegion.reset();
      this.poolIsoWorldRegion.push(worldRegion);
      this.worldRegionCount--;
    } else {
      IsoRegions.warn(
          "IsoRegionManager -> Trying to release a MasterRegion twice.");
    }
  }

  IsoChunkRegion allocIsoChunkRegion(int zLayer) {
    IsoChunkRegion chunkRegion = !this.poolIsoChunkRegion.isEmpty()
                                     ? this.poolIsoChunkRegion.pop()
                                     : new IsoChunkRegion(this);
    int int0 =
        this.regionIdStack.isEmpty() ? this.nextID++ : this.regionIdStack.pop();
    chunkRegion.init(int0, zLayer);
    this.chunkRegionCount++;
    return chunkRegion;
  }

  void releaseIsoChunkRegion(IsoChunkRegion chunkRegion) {
    if (!chunkRegion.isInPool()) {
      this.regionIdStack.push(chunkRegion.getID());
      chunkRegion.reset();
      this.poolIsoChunkRegion.push(chunkRegion);
      this.chunkRegionCount--;
    } else {
      IsoRegions.warn(
          "IsoRegionManager -> Trying to release a ChunkRegion twice.");
    }
  }

  Color getColor() {
    Color color = Colors.GetColorFromIndex(this.colorIndex++);
    if (this.colorIndex >= Colors.GetColorsCount()) {
      this.colorIndex = 0;
    }

    return color;
  }

  int getWorldRegionCount() { return this.worldRegionCount; }

  int getChunkRegionCount() { return this.chunkRegionCount; }
}
} // namespace regions
} // namespace isoregion
} // namespace areas
} // namespace iso
} // namespace zombie
