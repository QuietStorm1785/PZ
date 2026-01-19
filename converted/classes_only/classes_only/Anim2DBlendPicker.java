package zombie.core.skinnedmodel.advancedanimation;

import java.util.ArrayList;
import java.util.Comparator;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import zombie.core.Core;
import zombie.core.SpriteRenderer;
import zombie.core.skinnedmodel.advancedanimation.Anim2DBlendPicker.Counter;
import zombie.core.skinnedmodel.advancedanimation.Anim2DBlendPicker.Edge;
import zombie.core.skinnedmodel.advancedanimation.Anim2DBlendPicker.HullComparer;
import zombie.core.skinnedmodel.advancedanimation.Anim2DBlendPicker.PickResults;

public final class Anim2DBlendPicker {
   private List<Anim2DBlendTriangle> m_tris;
   private List<Anim2DBlend> m_hull;
   private HullComparer m_hullComparer;

   public void SetPickTriangles(List<Anim2DBlendTriangle> var1) {
      this.m_tris = var1;
      this.BuildHull();
   }

   private void BuildHull() {
      HashMap var1 = new HashMap();
      Counter var2 = new Counter();

      for (Anim2DBlendTriangle var4 : this.m_tris) {
         Counter var5 = var1.putIfAbsent(new Edge(var4.node1, var4.node2), var2);
         if (var5 == null) {
            var5 = var2;
            var2 = new Counter();
         }

         var5.Increment();
         var5 = var1.putIfAbsent(new Edge(var4.node2, var4.node3), var2);
         if (var5 == null) {
            var5 = var2;
            var2 = new Counter();
         }

         var5.Increment();
         var5 = var1.putIfAbsent(new Edge(var4.node3, var4.node1), var2);
         if (var5 == null) {
            var5 = var2;
            var2 = new Counter();
         }

         var5.Increment();
      }

      HashSet var9 = new HashSet();
      var1.forEach((var1x, var2x) -> {
         if (var2x.count == 1) {
            var9.add(var1x.a);
            var9.add(var1x.b);
         }
      });
      ArrayList var10 = new ArrayList(var9);
      float var13 = 0.0F;
      float var6 = 0.0F;

      for (Anim2DBlend var8 : var10) {
         var13 += var8.m_XPos;
         var6 += var8.m_YPos;
      }

      var13 /= var10.size();
      var6 /= var10.size();
      this.m_hullComparer = new HullComparer(var13, var6);
      var10.sort(this.m_hullComparer);
      this.m_hull = var10;
   }

   static <T> int LowerBoundIdx(List<T> var0, T var1, Comparator<? super T> var2) {
      int var3 = 0;
      int var4 = var0.size();

      while (var3 != var4) {
         int var5 = (var3 + var4) / 2;
         if (var2.compare(var1, var0.get(var5)) < 0) {
            var4 = var5;
         } else {
            var3 = var5 + 1;
         }
      }

      return var3;
   }

   private static float ProjectPointToLine(float var0, float var1, float var2, float var3, float var4, float var5) {
      float var6 = var0 - var2;
      float var7 = var1 - var3;
      float var8 = var4 - var2;
      float var9 = var5 - var3;
      return (var8 * var6 + var9 * var7) / (var8 * var8 + var9 * var9);
   }

   public PickResults Pick(float var1, float var2) {
      PickResults var3 = new PickResults();

      for (Anim2DBlendTriangle var5 : this.m_tris) {
         if (var5.Contains(var1, var2)) {
            var3.numNodes = 3;
            var3.node1 = var5.node1;
            var3.node2 = var5.node2;
            var3.node3 = var5.node3;
            float var6 = var3.node1.m_XPos;
            float var7 = var3.node1.m_YPos;
            float var8 = var3.node2.m_XPos;
            float var9 = var3.node2.m_YPos;
            float var10 = var3.node3.m_XPos;
            float var11 = var3.node3.m_YPos;
            var3.scale1 = ((var9 - var11) * (var1 - var10) + (var10 - var8) * (var2 - var11))
               / ((var9 - var11) * (var6 - var10) + (var10 - var8) * (var7 - var11));
            var3.scale2 = ((var11 - var7) * (var1 - var10) + (var6 - var10) * (var2 - var11))
               / ((var9 - var11) * (var6 - var10) + (var10 - var8) * (var7 - var11));
            var3.scale3 = 1.0F - var3.scale1 - var3.scale2;
            return var3;
         }
      }

      var1 *= 1.1F;
      var2 *= 1.1F;
      Anim2DBlend var14 = new Anim2DBlend();
      var14.m_XPos = var1;
      var14.m_YPos = var2;
      int var15 = LowerBoundIdx(this.m_hull, var14, this.m_hullComparer);
      if (var15 == this.m_hull.size()) {
         var15 = 0;
      }

      int var16 = var15 > 0 ? var15 - 1 : this.m_hull.size() - 1;
      Anim2DBlend var17 = this.m_hull.get(var15);
      Anim2DBlend var18 = this.m_hull.get(var16);
      float var19 = ProjectPointToLine(var1, var2, var17.m_XPos, var17.m_YPos, var18.m_XPos, var18.m_YPos);
      if (var19 < 0.0F) {
         var3.numNodes = 1;
         var3.node1 = var17;
         var3.scale1 = 1.0F;
      } else if (var19 > 1.0F) {
         var3.numNodes = 1;
         var3.node1 = var18;
         var3.scale1 = 1.0F;
      } else {
         var3.numNodes = 2;
         var3.node1 = var17;
         var3.node2 = var18;
         var3.scale1 = 1.0F - var19;
         var3.scale2 = var19;
      }

      return var3;
   }

   void render(float var1, float var2) {
      short var3 = 200;
      int var4 = Core.getInstance().getScreenWidth() - var3 - 100;
      int var5 = Core.getInstance().getScreenHeight() - var3 - 100;
      SpriteRenderer.instance.renderi(null, var4 - 20, var5 - 20, var3 + 40, var3 + 40, 1.0F, 1.0F, 1.0F, 1.0F, null);

      for (int var6 = 0; var6 < this.m_tris.size(); var6++) {
         Anim2DBlendTriangle var7 = this.m_tris.get(var6);
         SpriteRenderer.instance
            .renderline(
               null,
               (int)(var4 + var3 / 2 + var7.node1.m_XPos * var3 / 2.0F),
               (int)(var5 + var3 / 2 - var7.node1.m_YPos * var3 / 2.0F),
               (int)(var4 + var3 / 2 + var7.node2.m_XPos * var3 / 2.0F),
               (int)(var5 + var3 / 2 - var7.node2.m_YPos * var3 / 2.0F),
               0.5F,
               0.5F,
               0.5F,
               1.0F
            );
         SpriteRenderer.instance
            .renderline(
               null,
               (int)(var4 + var3 / 2 + var7.node2.m_XPos * var3 / 2.0F),
               (int)(var5 + var3 / 2 - var7.node2.m_YPos * var3 / 2.0F),
               (int)(var4 + var3 / 2 + var7.node3.m_XPos * var3 / 2.0F),
               (int)(var5 + var3 / 2 - var7.node3.m_YPos * var3 / 2.0F),
               0.5F,
               0.5F,
               0.5F,
               1.0F
            );
         SpriteRenderer.instance
            .renderline(
               null,
               (int)(var4 + var3 / 2 + var7.node3.m_XPos * var3 / 2.0F),
               (int)(var5 + var3 / 2 - var7.node3.m_YPos * var3 / 2.0F),
               (int)(var4 + var3 / 2 + var7.node1.m_XPos * var3 / 2.0F),
               (int)(var5 + var3 / 2 - var7.node1.m_YPos * var3 / 2.0F),
               0.5F,
               0.5F,
               0.5F,
               1.0F
            );
      }

      float var8 = 8.0F;
      PickResults var10 = this.Pick(var1, var2);
      if (var10.node1 != null) {
         SpriteRenderer.instance
            .render(
               null,
               var4 + var3 / 2 + var10.node1.m_XPos * var3 / 2.0F - var8 / 2.0F,
               var5 + var3 / 2 - var10.node1.m_YPos * var3 / 2.0F - var8 / 2.0F,
               var8,
               var8,
               0.0F,
               1.0F,
               0.0F,
               1.0F,
               null
            );
      }

      if (var10.node2 != null) {
         SpriteRenderer.instance
            .render(
               null,
               var4 + var3 / 2 + var10.node2.m_XPos * var3 / 2.0F - var8 / 2.0F,
               var5 + var3 / 2 - var10.node2.m_YPos * var3 / 2.0F - var8 / 2.0F,
               var8,
               var8,
               0.0F,
               1.0F,
               0.0F,
               1.0F,
               null
            );
      }

      if (var10.node3 != null) {
         SpriteRenderer.instance
            .render(
               null,
               var4 + var3 / 2 + var10.node3.m_XPos * var3 / 2.0F - var8 / 2.0F,
               var5 + var3 / 2 - var10.node3.m_YPos * var3 / 2.0F - var8 / 2.0F,
               var8,
               var8,
               0.0F,
               1.0F,
               0.0F,
               1.0F,
               null
            );
      }

      var8 = 4.0F;
      SpriteRenderer.instance
         .render(
            null,
            var4 + var3 / 2 + var1 * var3 / 2.0F - var8 / 2.0F,
            var5 + var3 / 2 - var2 * var3 / 2.0F - var8 / 2.0F,
            var8,
            var8,
            0.0F,
            0.0F,
            1.0F,
            1.0F,
            null
         );
   }
}
