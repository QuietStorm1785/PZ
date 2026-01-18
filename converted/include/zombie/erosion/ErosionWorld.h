#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/erosion/categories/ErosionCategory.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/SpriteDetails/IsoFlagType.h"
#include "zombie/iso/SpriteDetails/IsoObjectType.h"

namespace zombie {
namespace erosion {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class ErosionWorld {
public:
 bool init() {
 ErosionRegions.init();
 return true;
 }

 void validateSpawn(IsoGridSquare _sq, ErosionData.Square _sqErosionData, ErosionData.Chunk _chunkData) {
 bool boolean0 = _sq.Is(IsoFlagType.exterior);
 bool boolean1 = _sq.Has(IsoObjectType.wall);
 IsoObject object = _sq.getFloor();
 std::string string0 = object != nullptr && object.getSprite() != nullptr ? object.getSprite().getName() : nullptr;
 if (string0.empty()) {
 _sqErosionData.doNothing = true;
 } else {
 bool boolean2 = false;

 for (int int0 = 0; int0 < ErosionRegions.regions.size(); int0++) {
 ErosionRegions.Region region = ErosionRegions.regions.get(int0);
 std::string string1 = region.tileNameMatch;
 if ((string1.empty() || string0.startsWith(string1)
 && (!region.checkExterior || region.isExterior == boolean0)
 && (!region.hasWall || region.hasWall == boolean1) {
 for (int int1 = 0; int1 < region.categories.size(); int1++) {
 ErosionCategory erosionCategory = region.categories.get(int1);
 bool boolean3 = erosionCategory.replaceExistingObject(_sq, _sqErosionData, _chunkData, boolean0, boolean1);
 if (!boolean3) {
 boolean3 = erosionCategory.validateSpawn(_sq, _sqErosionData, _chunkData, boolean0, boolean1, false);
 }

 if (boolean3) {
 boolean2 = true;
 break;
 }
 }
 }
 }

 if (!boolean2) {
 _sqErosionData.doNothing = true;
 }
 }
 }

 void update(IsoGridSquare _sq, ErosionData.Square _sqErosionData, ErosionData.Chunk _chunkData, int _eTick) {
 if (_sqErosionData.regions != nullptr) {
 for (int int0 = 0; int0 < _sqErosionData.regions.size(); int0++) {
 ErosionCategory.Data data = _sqErosionData.regions.get(int0);
 ErosionCategory erosionCategory = ErosionRegions.getCategory(data.regionID, data.categoryID);
 int int1 = _sqErosionData.regions.size();
 erosionCategory.update(_sq, _sqErosionData, data, _chunkData, _eTick);
 if (int1 > _sqErosionData.regions.size()) {
 int0--;
 }
 }
 }
 }
}
} // namespace erosion
} // namespace zombie
