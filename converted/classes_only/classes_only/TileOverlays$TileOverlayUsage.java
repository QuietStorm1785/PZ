package zombie.iso;

import zombie.core.math.PZMath;
import zombie.util.StringUtils;

final class TileOverlays$TileOverlayUsage {
   String usage;
   int zOnly = -1;
   int zGreaterThan = -1;
   float alpha = -1.0F;
   boolean bTableTop = false;

   private TileOverlays$TileOverlayUsage() {
   }

   boolean parse(String var1) {
      this.usage = var1.trim();
      if (StringUtils.isNullOrWhitespace(this.usage)) {
         return true;
      } else {
         String[] var2 = var1.split(";");

         for (int var3 = 0; var3 < var2.length; var3++) {
            String var4 = var2[var3];
            if (var4.startsWith("z=")) {
               this.zOnly = Integer.parseInt(var4.substring(2));
            } else if (var4.startsWith("z>")) {
               this.zGreaterThan = Integer.parseInt(var4.substring(2));
            } else if (var4.startsWith("alpha=")) {
               this.alpha = Float.parseFloat(var4.substring(6));
               this.alpha = PZMath.clamp(this.alpha, 0.0F, 1.0F);
            } else {
               if (!var4.startsWith("tabletop")) {
                  return false;
               }

               this.bTableTop = true;
            }
         }

         return true;
      }
   }

   boolean match(IsoGridSquare var1) {
      return this.zOnly != -1 && var1.z != this.zOnly ? false : this.zGreaterThan == -1 || var1.z > this.zGreaterThan;
   }
}
