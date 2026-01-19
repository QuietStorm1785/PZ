package zombie.vehicles;

import java.util.ArrayDeque;
import zombie.vehicles.PolygonalMap2.Vehicle;
import zombie.vehicles.PolygonalMap2.VehicleCluster;

final class PolygonalMap2$VehicleRect {
   VehicleCluster cluster;
   Vehicle vehicle;
   int x;
   int y;
   int w;
   int h;
   int z;
   static final ArrayDeque<PolygonalMap2$VehicleRect> pool = new ArrayDeque<>();

   private PolygonalMap2$VehicleRect() {
   }

   PolygonalMap2$VehicleRect init(Vehicle var1, int var2, int var3, int var4, int var5, int var6) {
      this.cluster = null;
      this.vehicle = var1;
      this.x = var2;
      this.y = var3;
      this.w = var4;
      this.h = var5;
      this.z = var6;
      return this;
   }

   PolygonalMap2$VehicleRect init(int var1, int var2, int var3, int var4, int var5) {
      this.cluster = null;
      this.vehicle = null;
      this.x = var1;
      this.y = var2;
      this.w = var3;
      this.h = var4;
      this.z = var5;
      return this;
   }

   int left() {
      return this.x;
   }

   int top() {
      return this.y;
   }

   int right() {
      return this.x + this.w;
   }

   int bottom() {
      return this.y + this.h;
   }

   boolean containsPoint(float var1, float var2, float var3) {
      return var1 >= this.left() && var1 < this.right() && var2 >= this.top() && var2 < this.bottom() && (int)var3 == this.z;
   }

   boolean containsPoint(float var1, float var2, float var3, int var4) {
      int var5 = this.x - var4;
      int var6 = this.y - var4;
      int var7 = this.right() + var4;
      int var8 = this.bottom() + var4;
      return var1 >= var5 && var1 < var7 && var2 >= var6 && var2 < var8 && (int)var3 == this.z;
   }

   boolean intersects(PolygonalMap2$VehicleRect var1) {
      return this.left() < var1.right() && this.right() > var1.left() && this.top() < var1.bottom() && this.bottom() > var1.top();
   }

   boolean isAdjacent(PolygonalMap2$VehicleRect var1) {
      this.x--;
      this.y--;
      this.w += 2;
      this.h += 2;
      boolean var2 = this.intersects(var1);
      this.x++;
      this.y++;
      this.w -= 2;
      this.h -= 2;
      return var2;
   }

   static PolygonalMap2$VehicleRect alloc() {
      if (pool.isEmpty()) {
         boolean var0 = false;
      } else {
         boolean var1 = false;
      }

      return pool.isEmpty() ? new PolygonalMap2$VehicleRect() : pool.pop();
   }

   void release() {
      if (!$assertionsDisabled && pool.contains(this)) {
         throw new AssertionError();
      } else {
         pool.push(this);
      }
   }
}
