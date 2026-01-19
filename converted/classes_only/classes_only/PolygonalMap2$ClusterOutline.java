package zombie.vehicles;

import java.util.ArrayDeque;

final class PolygonalMap2$ClusterOutline {
   int x;
   int y;
   int z;
   boolean w;
   boolean n;
   boolean e;
   boolean s;
   boolean tw;
   boolean tn;
   boolean te;
   boolean ts;
   boolean inner;
   boolean innerCorner;
   boolean start;
   static final ArrayDeque<PolygonalMap2$ClusterOutline> pool = new ArrayDeque<>();

   private PolygonalMap2$ClusterOutline() {
   }

   PolygonalMap2$ClusterOutline init(int var1, int var2, int var3) {
      this.x = var1;
      this.y = var2;
      this.z = var3;
      this.w = this.n = this.e = this.s = false;
      this.tw = this.tn = this.te = this.ts = false;
      this.inner = this.innerCorner = this.start = false;
      return this;
   }

   static PolygonalMap2$ClusterOutline alloc() {
      return pool.isEmpty() ? new PolygonalMap2$ClusterOutline() : pool.pop();
   }

   void release() {
      if (!$assertionsDisabled && pool.contains(this)) {
         throw new AssertionError();
      } else {
         pool.push(this);
      }
   }
}
