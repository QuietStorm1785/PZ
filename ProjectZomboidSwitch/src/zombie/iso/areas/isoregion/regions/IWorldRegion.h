#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace iso {
namespace areas {
namespace isoregion {
namespace regions {


class IWorldRegion {
public:
    virtual ~IWorldRegion() = default;
   std::vector<IsoWorldRegion> getDebugConnectedNeighborCopy();

   std::vector<IsoWorldRegion> getNeighbors();

    bool isFogMask();

    bool isPlayerRoom();

    bool isFullyRoofed();

    int getRoofCnt();

    int getSquareSize();

   std::vector<IsoChunkRegion> getDebugIsoChunkRegionCopy();
}
} // namespace regions
} // namespace isoregion
} // namespace areas
} // namespace iso
} // namespace zombie
