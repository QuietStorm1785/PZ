#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/iso/sprite/IsoSpriteInstance.h"

namespace zombie {
namespace erosion {
namespace obj {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class ErosionObjOverlay {
public:
 const ErosionObjOverlaySprites sprites;
 std::string name;
 int stages;
 bool applyAlpha;
 int cycleTime;

 public ErosionObjOverlay(ErosionObjOverlaySprites erosionObjOverlaySprites, int int0, bool boolean0) {
 this->sprites = erosionObjOverlaySprites;
 this->name = erosionObjOverlaySprites.name;
 this->stages = erosionObjOverlaySprites.stages;
 this->applyAlpha = boolean0;
 this->cycleTime = int0;
 }

 int setOverlay(IsoObject object, int int1, int int0, int int2, float var5) {
 if (int0 >= 0 && int0 < this->stages && object != nullptr) {
 if (int1 >= 0) {
 this->removeOverlay(object, int1);
 }

 IsoSprite sprite = this->sprites.getSprite(int0, int2);
 IsoSpriteInstance spriteInstance = sprite.newInstance();
 if (object.AttachedAnimSprite == nullptr) {
 object.AttachedAnimSprite = std::make_unique<ArrayList<>>();
 }

 object.AttachedAnimSprite.add(spriteInstance);
 return spriteInstance.getID();
 } else {
 return -1;
 }
 }

 bool removeOverlay(IsoObject object, int int1) {
 if (object == nullptr) {
 return false;
 } else {
 std::vector arrayList = object.AttachedAnimSprite;
 if (arrayList != nullptr && !arrayList.empty()) {
 for (int int0 = 0; int0 < object.AttachedAnimSprite.size(); int0++) {
 if (object.AttachedAnimSprite.get(int0).parentSprite.ID == int1) {
 object.AttachedAnimSprite.remove(int0--);
 }
 }

 for (int int2 = arrayList.size() - 1; int2 >= 0; int2--) {
 if (((IsoSpriteInstance)arrayList.get(int2).getID() == int1) {
 arrayList.remove(int2);
 return true;
 }
 }

 return false;
 } else {
 return false;
 }
 }
 }
}
} // namespace obj
} // namespace erosion
} // namespace zombie
