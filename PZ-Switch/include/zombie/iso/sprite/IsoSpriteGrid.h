#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace iso {
namespace sprite {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

/**
 * Turbo
 */
class IsoSpriteGrid {
public:
private
 IsoSprite[] sprites;
 int width;
 int height;

public
 IsoSpriteGrid(int w, int h) {
 this->sprites = new IsoSprite[w * h];
 this->width = w;
 this->height = h;
 }

 IsoSprite getAnchorSprite() {
 return this->sprites.length > 0 ? this->sprites[0] : nullptr;
 }

 IsoSprite getSprite(int x, int y) {
 return this->getSpriteFromIndex(y * this->width + x);
 }

 void setSprite(int x, int y, IsoSprite sprite) {
 this->sprites[y * this->width + x] = sprite;
 }

 int getSpriteIndex(IsoSprite sprite) {
 for (int int0 = 0; int0 < this->sprites.length; int0++) {
 IsoSprite _sprite = this->sprites[int0];
 if (_sprite != nullptr && _sprite == sprite) {
 return int0;
 }
 }

 return -1;
 }

 int getSpriteGridPosX(IsoSprite sprite) {
 int int0 = this->getSpriteIndex(sprite);
 return int0 >= 0 ? int0 % this->width : -1;
 }

 int getSpriteGridPosY(IsoSprite sprite) {
 int int0 = this->getSpriteIndex(sprite);
 return int0 >= 0 ? int0 / this->width : -1;
 }

 IsoSprite getSpriteFromIndex(int index) {
 return index >= 0 && index < this->sprites.length ? this->sprites[index]
 : nullptr;
 }

 int getWidth() { return this->width; }

 int getHeight() { return this->height; }

 bool validate() {
 for (int int0 = 0; int0 < this->sprites.length; int0++) {
 if (this->sprites[int0] == nullptr) {
 return false;
 }
 }

 return true;
 }

 int getSpriteCount() { return this->sprites.length; }

public
 IsoSprite[] getSprites() { return this->sprites; }
}
} // namespace sprite
} // namespace iso
} // namespace zombie
