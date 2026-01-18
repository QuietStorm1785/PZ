#include "zombie/iso/areas/isoregion/regions/IsoRegionManager.h"

namespace zombie {
namespace iso {
namespace areas {
namespace isoregion {
namespace regions {

public
IsoRegionManager::IsoRegionManager(DataRoot _dataRoot) {
 // TODO: Implement IsoRegionManager
 return nullptr;
}

IsoWorldRegion IsoRegionManager::allocIsoWorldRegion() {
 // TODO: Implement allocIsoWorldRegion
 return nullptr;
}

void IsoRegionManager::releaseIsoWorldRegion(IsoWorldRegion worldRegion) {
 // TODO: Implement releaseIsoWorldRegion
}

IsoChunkRegion IsoRegionManager::allocIsoChunkRegion(int zLayer) {
 // TODO: Implement allocIsoChunkRegion
 return nullptr;
}

void IsoRegionManager::releaseIsoChunkRegion(IsoChunkRegion chunkRegion) {
 // TODO: Implement releaseIsoChunkRegion
}

Color IsoRegionManager::getColor() {
 // TODO: Implement getColor
 return nullptr;
}

int IsoRegionManager::getWorldRegionCount() {
 // TODO: Implement getWorldRegionCount
 return 0;
}

int IsoRegionManager::getChunkRegionCount() {
 // TODO: Implement getChunkRegionCount
 return 0;
}

} // namespace regions
} // namespace isoregion
} // namespace areas
} // namespace iso
} // namespace zombie
