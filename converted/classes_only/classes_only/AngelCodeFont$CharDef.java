package zombie.core.fonts;

import zombie.core.SpriteRenderer;
import zombie.core.fonts.AngelCodeFont.CharDefTexture;
import zombie.core.textures.Texture;

public class AngelCodeFont$CharDef {
   public short dlIndex;
   public short height;
   public int id;
   public Texture image;
   public short[] kerningSecond;
   public short[] kerningAmount;
   public short width;
   public short x;
   public short xadvance;
   public short xoffset;
   public short y;
   public short yoffset;
   public short page;

   public AngelCodeFont$CharDef(AngelCodeFont var1) {
      this.this$0 = var1;
   }

   public void draw(float var1, float var2) {
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
               null
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
               null
            );
      }
   }

   public int getKerning(int var1) {
      if (this.kerningSecond == null) {
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

   public void init() {
      Texture var1 = this.this$0.fontImage;
      if (this.this$0.pages.containsKey(this.page)) {
         var1 = (Texture)this.this$0.pages.get(this.page);
      }

      this.image = new CharDefTexture(var1.getTextureId(), var1.getName() + "_" + this.x + "_" + this.y);
      this.image.setRegion(this.x + (int)(var1.xStart * var1.getWidthHW()), this.y + (int)(var1.yStart * var1.getHeightHW()), this.width, this.height);
   }

   public void destroy() {
      if (this.image != null && this.image.getTextureId() != null) {
         ((CharDefTexture)this.image).releaseCharDef();
         this.image = null;
      }
   }

   @Override
   public String toString() {
      return "[CharDef id=" + this.id + " x=" + this.x + " y=" + this.y + "]";
   }
}
