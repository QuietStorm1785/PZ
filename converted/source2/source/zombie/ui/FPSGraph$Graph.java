package zombie.ui;

import java.util.ArrayList;
import zombie.core.PerformanceSettings;
import zombie.core.SpriteRenderer;

final class FPSGraph$Graph {
   private final ArrayList<Long> times;
   private final ArrayList<Integer> bars;

   private FPSGraph$Graph(FPSGraph var1) {
      this.this$0 = var1;
      this.times = new ArrayList<>();
      this.bars = new ArrayList<>();
   }

   public void add(long var1) {
      this.times.add(var1);
      this.bars.clear();
      long var3 = this.times.get(0);
      int var5 = 1;

      for (int var6 = 1; var6 < this.times.size(); var6++) {
         if (var6 != this.times.size() - 1 && this.times.get(var6) - var3 <= 1000L) {
            var5++;
         } else {
            long var7 = (this.times.get(var6) - var3) / 1000L - 1L;

            for (int var9 = 0; var9 < var7; var9++) {
               this.bars.add(0);
            }

            this.bars.add(var5);
            var5 = 1;
            var3 = this.times.get(var6);
         }
      }

      while (this.bars.size() > 30) {
         int var10 = this.bars.get(0);

         for (int var11 = 0; var11 < var10; var11++) {
            this.times.remove(0);
         }

         this.bars.remove(0);
      }
   }

   public void render(float var1, float var2, float var3) {
      if (!this.bars.isEmpty()) {
         float var4 = this.this$0.getHeight().intValue() - 4;
         float var5 = this.this$0.getHeight().intValue() - 2;
         int var6 = Math.max(PerformanceSettings.getLockFPS(), PerformanceSettings.LightingFPS);
         byte var7 = 8;
         float var8 = var4 * ((float)Math.min(var6, this.bars.get(0)) / var6);

         for (int var9 = 1; var9 < this.bars.size() - 1; var9++) {
            float var10 = var4 * ((float)Math.min(var6, this.bars.get(var9)) / var6);
            SpriteRenderer.instance
               .renderline(
                  null,
                  this.this$0.getAbsoluteX().intValue() + var7 - 8 + 4,
                  this.this$0.getAbsoluteY().intValue() + (int)(var5 - var8),
                  this.this$0.getAbsoluteX().intValue() + var7 + 4,
                  this.this$0.getAbsoluteY().intValue() + (int)(var5 - var10),
                  var1,
                  var2,
                  var3,
                  0.35F,
                  1
               );
            var7 += 8;
            var8 = var10;
         }
      }
   }
}
