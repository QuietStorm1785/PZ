#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/textures/Texture.h"

namespace zombie {
namespace chat {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


/**
 * Turbo
 */
class NineGridTexture {
public:
 Texture topLeft;
 Texture topMid;
 Texture topRight;
 Texture left;
 Texture mid;
 Texture right;
 Texture botLeft;
 Texture botMid;
 Texture botRight;
 int outer;

 public NineGridTexture(const std::string& base, int _outer) {
 this->outer = _outer;
 this->topLeft = Texture.getSharedTexture(base + "_topleft");
 this->topMid = Texture.getSharedTexture(base + "_topmid");
 this->topRight = Texture.getSharedTexture(base + "_topright");
 this->left = Texture.getSharedTexture(base + "_left");
 this->mid = Texture.getSharedTexture(base + "_mid");
 this->right = Texture.getSharedTexture(base + "_right");
 this->botLeft = Texture.getSharedTexture(base + "_botleft");
 this->botMid = Texture.getSharedTexture(base + "_botmid");
 this->botRight = Texture.getSharedTexture(base + "_botright");
 }

 void renderInnerBased(int x, int y, int w, int h, float r, float g, float b, float a) {
 y += 5;
 h -= 7;
 SpriteRenderer.instance.renderi(this->topLeft, x - this->outer, y - this->outer, this->outer, this->outer, r, g, b, a, nullptr);
 SpriteRenderer.instance.renderi(this->topMid, x, y - this->outer, w, this->outer, r, g, b, a, nullptr);
 SpriteRenderer.instance.renderi(this->topRight, x + w, y - this->outer, this->outer, this->outer, r, g, b, a, nullptr);
 SpriteRenderer.instance.renderi(this->left, x - this->outer, y, this->outer, h, r, g, b, a, nullptr);
 SpriteRenderer.instance.renderi(this->mid, x, y, w, h, r, g, b, a, nullptr);
 SpriteRenderer.instance.renderi(this->right, x + w, y, this->outer, h, r, g, b, a, nullptr);
 SpriteRenderer.instance.renderi(this->botLeft, x - this->outer, y + h, this->outer, this->outer, r, g, b, a, nullptr);
 SpriteRenderer.instance.renderi(this->botMid, x, y + h, w, this->outer, r, g, b, a, nullptr);
 SpriteRenderer.instance.renderi(this->botRight, x + w, y + h, this->outer, this->outer, r, g, b, a, nullptr);
 }
}
} // namespace chat
} // namespace zombie
