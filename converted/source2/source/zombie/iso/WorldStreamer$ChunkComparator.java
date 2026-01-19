package zombie.iso;

import java.util.Comparator;
import zombie.characters.IsoPlayer;

class WorldStreamer$ChunkComparator implements Comparator<IsoChunk> {
   private Vector2[] pos = new Vector2[4];

   public WorldStreamer$ChunkComparator() {
      for (int var1 = 0; var1 < 4; var1++) {
         this.pos[var1] = new Vector2();
      }
   }

   public void init() {
      for (int var1 = 0; var1 < 4; var1++) {
         Vector2 var2 = this.pos[var1];
         var2.x = var2.y = -1.0F;
         IsoPlayer var3 = IsoPlayer.players[var1];
         if (var3 != null) {
            if (var3.lx == var3.x && var3.ly == var3.y) {
               var2.x = var3.x;
               var2.y = var3.y;
            } else {
               var2.x = var3.x - var3.lx;
               var2.y = var3.y - var3.ly;
               var2.normalize();
               var2.setLength(10.0F);
               var2.x = var2.x + var3.x;
               var2.y = var2.y + var3.y;
            }
         }
      }
   }

   public int compare(IsoChunk var1, IsoChunk var2) {
      float var3 = Float.MAX_VALUE;
      float var4 = Float.MAX_VALUE;

      for (int var5 = 0; var5 < 4; var5++) {
         if (this.pos[var5].x != -1.0F || this.pos[var5].y != -1.0F) {
            float var6 = this.pos[var5].x;
            float var7 = this.pos[var5].y;
            var3 = Math.min(var3, IsoUtils.DistanceTo(var6, var7, var1.wx * 10 + 5, var1.wy * 10 + 5));
            var4 = Math.min(var4, IsoUtils.DistanceTo(var6, var7, var2.wx * 10 + 5, var2.wy * 10 + 5));
         }
      }

      if (var3 < var4) {
         return 1;
      } else {
         return var3 > var4 ? -1 : 0;
      }
   }
}
