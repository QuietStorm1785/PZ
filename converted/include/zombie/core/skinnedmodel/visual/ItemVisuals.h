#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/skinnedmodel/population/ClothingItem.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace visual {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class ItemVisuals : public ArrayList {
public:
 void save(ByteBuffer output) {
 output.putShort((short)this->size());

 for (int int0 = 0; int0 < this->size(); int0++) {
 this->get(int0).save(output);
 }
 }

 void load(ByteBuffer input, int WorldVersion) {
 this->clear();
 short short0 = input.getShort();

 for (int int0 = 0; int0 < short0; int0++) {
 ItemVisual itemVisual = new ItemVisual();
 itemVisual.load(input, WorldVersion);
 this->add(itemVisual);
 }
 }

 ItemVisual findHat() {
 for (int int0 = 0; int0 < this->size(); int0++) {
 ItemVisual itemVisual = this->get(int0);
 ClothingItem clothingItem = itemVisual.getClothingItem();
 if (clothingItem != nullptr && clothingItem.isHat()) {
 return itemVisual;
 }
 }

 return nullptr;
 }

 ItemVisual findMask() {
 for (int int0 = 0; int0 < this->size(); int0++) {
 ItemVisual itemVisual = this->get(int0);
 ClothingItem clothingItem = itemVisual.getClothingItem();
 if (clothingItem != nullptr && clothingItem.isMask()) {
 return itemVisual;
 }
 }

 return nullptr;
 }
}
} // namespace visual
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
