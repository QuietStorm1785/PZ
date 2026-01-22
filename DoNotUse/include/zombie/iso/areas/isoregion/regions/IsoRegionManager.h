#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Color.h"
#include "zombie/core/Colors.h"
#include "zombie/iso/areas/isoregion/IsoRegions.h"
#include "zombie/iso/areas/isoregion/data/DataRoot.h"
#include <algorithm>

namespace zombie {
namespace iso {
namespace areas {
namespace isoregion {
namespace regions {


class IsoRegionManager {
public:
   private const ArrayDeque<IsoWorldRegion> poolIsoWorldRegion = std::make_unique<ArrayDeque<>>();
   private const ArrayDeque<IsoChunkRegion> poolIsoChunkRegion = std::make_unique<ArrayDeque<>>();
    const DataRoot dataRoot;
   private const ArrayDeque<int> regionIdStack = std::make_unique<ArrayDeque<>>();
    int nextID = 0;
    int colorIndex = 0;
    int worldRegionCount = 0;
    int chunkRegionCount = 0;

    public IsoRegionManager(DataRoot var1) {
      this.dataRoot = var1;
   }

    IsoWorldRegion allocIsoWorldRegion() {
    IsoWorldRegion var1 = !this.poolIsoWorldRegion.empty() ? this.poolIsoWorldRegion.pop() : std::make_shared<IsoWorldRegion>(this);
    int var2 = this.regionIdStack.empty() ? this.nextID++ : this.regionIdStack.pop();
      var1.init(var2);
      this.worldRegionCount++;
    return var1;
   }

    void releaseIsoWorldRegion(IsoWorldRegion var1) {
      this.dataRoot.DequeueDirtyIsoWorldRegion(var1);
      if (!var1.isInPool()) {
         this.regionIdStack.push(var1.getID());
         var1.reset();
         this.poolIsoWorldRegion.push(var1);
         this.worldRegionCount--;
      } else {
         IsoRegions.warn("IsoRegionManager -> Trying to release a MasterRegion twice.");
      }
   }

    IsoChunkRegion allocIsoChunkRegion(int var1) {
    IsoChunkRegion var2 = !this.poolIsoChunkRegion.empty() ? this.poolIsoChunkRegion.pop() : std::make_shared<IsoChunkRegion>(this);
    int var3 = this.regionIdStack.empty() ? this.nextID++ : this.regionIdStack.pop();
      var2.init(var3, var1);
      this.chunkRegionCount++;
    return var2;
   }

    void releaseIsoChunkRegion(IsoChunkRegion var1) {
      if (!var1.isInPool()) {
         this.regionIdStack.push(var1.getID());
         var1.reset();
         this.poolIsoChunkRegion.push(var1);
         this.chunkRegionCount--;
      } else {
         IsoRegions.warn("IsoRegionManager -> Trying to release a ChunkRegion twice.");
      }
   }

    Color getColor() {
    Color var1 = Colors.GetColorFromIndex(this.colorIndex++);
      if (this.colorIndex >= Colors.GetColorsCount()) {
         this.colorIndex = 0;
      }

    return var1;
   }

    int getWorldRegionCount() {
      return this.worldRegionCount;
   }

    int getChunkRegionCount() {
      return this.chunkRegionCount;
   }
}
} // namespace regions
} // namespace isoregion
} // namespace areas
} // namespace iso
} // namespace zombie
