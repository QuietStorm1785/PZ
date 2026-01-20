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

    public NineGridTexture(const std::string& var1, int var2) {
      this.outer = var2;
      this.topLeft = Texture.getSharedTexture(var1 + "_topleft");
      this.topMid = Texture.getSharedTexture(var1 + "_topmid");
      this.topRight = Texture.getSharedTexture(var1 + "_topright");
      this.left = Texture.getSharedTexture(var1 + "_left");
      this.mid = Texture.getSharedTexture(var1 + "_mid");
      this.right = Texture.getSharedTexture(var1 + "_right");
      this.botLeft = Texture.getSharedTexture(var1 + "_botleft");
      this.botMid = Texture.getSharedTexture(var1 + "_botmid");
      this.botRight = Texture.getSharedTexture(var1 + "_botright");
   }

    void renderInnerBased(int var1, int var2, int var3, int var4, float var5, float var6, float var7, float var8) {
      var2 += 5;
      var4 -= 7;
      SpriteRenderer.instance.renderi(this.topLeft, var1 - this.outer, var2 - this.outer, this.outer, this.outer, var5, var6, var7, var8, nullptr);
      SpriteRenderer.instance.renderi(this.topMid, var1, var2 - this.outer, var3, this.outer, var5, var6, var7, var8, nullptr);
      SpriteRenderer.instance.renderi(this.topRight, var1 + var3, var2 - this.outer, this.outer, this.outer, var5, var6, var7, var8, nullptr);
      SpriteRenderer.instance.renderi(this.left, var1 - this.outer, var2, this.outer, var4, var5, var6, var7, var8, nullptr);
      SpriteRenderer.instance.renderi(this.mid, var1, var2, var3, var4, var5, var6, var7, var8, nullptr);
      SpriteRenderer.instance.renderi(this.right, var1 + var3, var2, this.outer, var4, var5, var6, var7, var8, nullptr);
      SpriteRenderer.instance.renderi(this.botLeft, var1 - this.outer, var2 + var4, this.outer, this.outer, var5, var6, var7, var8, nullptr);
      SpriteRenderer.instance.renderi(this.botMid, var1, var2 + var4, var3, this.outer, var5, var6, var7, var8, nullptr);
      SpriteRenderer.instance.renderi(this.botRight, var1 + var3, var2 + var4, this.outer, this.outer, var5, var6, var7, var8, nullptr);
   }
}
} // namespace chat
} // namespace zombie
