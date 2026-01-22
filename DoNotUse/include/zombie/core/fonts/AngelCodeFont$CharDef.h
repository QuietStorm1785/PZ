#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/fonts/AngelCodeFont/CharDefTexture.h"
#include "zombie/core/textures/Texture.h"

namespace zombie {
namespace core {
namespace fonts {


class AngelCodeFont {
public:
    short dlIndex;
    short height;
    int id;
    Texture image;
   public short[] kerningSecond;
   public short[] kerningAmount;
    short width;
    short x;
    short xadvance;
    short xoffset;
    short y;
    short yoffset;
    short page;

   public AngelCodeFont$CharDef(AngelCodeFont var1) {
      this.this$0 = var1;
   }

    void draw(float var1, float var2) {
    Texture var3 = this.image;
      if (AngelCodeFont.s_scale > 0.0F) {
         SpriteRenderer.instance
            .m_states
            .getPopulatingActiveState()
            .render(
               var3,
               var1 + this.xoffset * AngelCodeFont.s_scale + AngelCodeFont.xoff,
               var2 + this.yoffset * AngelCodeFont.s_scale + AngelCodeFont.yoff,
               this.width * AngelCodeFont.s_scale,
               this.height * AngelCodeFont.s_scale,
               AngelCodeFont.curR,
               AngelCodeFont.curG,
               AngelCodeFont.curB,
               AngelCodeFont.curA,
               nullptr
            );
      } else {
         SpriteRenderer.instance
            .renderi(
               var3,
               (int)(var1 + this.xoffset + AngelCodeFont.xoff),
               (int)(var2 + this.yoffset + AngelCodeFont.yoff),
               this.width,
               this.height,
               AngelCodeFont.curR,
               AngelCodeFont.curG,
               AngelCodeFont.curB,
               AngelCodeFont.curA,
               nullptr
            );
      }
   }

    int getKerning(int var1) {
      if (this.kerningSecond == nullptr) {
    return 0;
      } else {
    int var2 = 0;
    int var3 = this.kerningSecond.length - 1;

         while (var2 <= var3) {
    int var4 = var2 + var3 >>> 1;
            if (this.kerningSecond[var4] < var1) {
               var2 = var4 + 1;
            } else {
               if (this.kerningSecond[var4] <= var1) {
                  return this.kerningAmount[var4];
               }

               var3 = var4 - 1;
            }
         }

    return 0;
      }
   }

    void init() {
    Texture var1 = this.this$0.fontImage;
      if (this.this$0.pages.containsKey(this.page)) {
         var1 = (Texture)this.this$0.pages.get(this.page);
      }

      this.image = std::make_shared<CharDefTexture>(var1.getTextureId(), var1.getName() + "_" + this.x + "_" + this.y);
      this.image.setRegion(this.x + (int)(var1.xStart * var1.getWidthHW()), this.y + (int)(var1.yStart * var1.getHeightHW()), this.width, this.height);
   }

    void destroy() {
      if (this.image != nullptr && this.image.getTextureId() != nullptr) {
         ((CharDefTexture)this.image).releaseCharDef();
         this.image = nullptr;
      }
   }

    std::string toString() {
      return "[CharDef id=" + this.id + " x=" + this.x + " y=" + this.y + "]";
   }
}
} // namespace fonts
} // namespace core
} // namespace zombie
