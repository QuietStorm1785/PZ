#pragma once
#include "zombie/erosion/ErosionMain.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/iso/sprite/IsoSpriteInstance.h"
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace erosion {
namespace obj {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class ErosionObjOverlaySprites {
public:
 std::string name;
 int stages;
private
 ErosionObjOverlaySprites.Stage[] sprites;

public
 ErosionObjOverlaySprites(int int0, std::string_view string) {
 this->name = string;
 this->stages = int0;
 this->sprites = new ErosionObjOverlaySprites.Stage[this->stages];

 for (int int1 = 0; int1 < this->stages; int1++) {
 this->sprites[int1] = new ErosionObjOverlaySprites.Stage();
 }
 }

 IsoSprite getSprite(int int1, int int0) {
 return this->sprites[int1].seasons[int0].getSprite();
 }

 IsoSpriteInstance getSpriteInstance(int int1, int int0) {
 return this->sprites[int1].seasons[int0].getInstance();
 }

 void setSprite(int int1, std::string_view string, int int0) {
 this->sprites[int1].seasons[int0] =
 new ErosionObjOverlaySprites.Sprite(string);
 }

private
 static class Sprite {
 const std::string sprite;

 public
 Sprite(std::string_view string) { this->sprite = string; }

 IsoSprite getSprite() {
 return this->sprite != nullptr
 ? ErosionMain.getInstance().getSpriteManager().getSprite(
 this->sprite)
 : nullptr;
 }

 IsoSpriteInstance getInstance() {
 return this->sprite != nullptr ? ErosionMain.getInstance()
 .getSpriteManager()
 .getSprite(this->sprite)
 .newInstance()
 : nullptr;
 }
 }

 private static class Stage {
 public
 ErosionObjOverlaySprites.Sprite[] seasons =
 new ErosionObjOverlaySprites.Sprite[6];
 }
}
} // namespace obj
} // namespace erosion
} // namespace zombie
