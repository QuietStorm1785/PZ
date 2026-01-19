package zombie.vehicles;

import java.util.ArrayDeque;

final class PolygonalMap2$Square {
   static int nextID = 1;
   Integer ID = nextID++;
   int x;
   int y;
   int z;
   int bits;
   short cost;
   static final ArrayDeque<PolygonalMap2$Square> pool = new ArrayDeque<>();

   PolygonalMap2$Square init(int var1, int var2, int var3) {
      this.x = var1;
      this.y = var2;
      this.z = var3;
      return this;
   }

   boolean has(int var1) {
      return (this.bits & var1) != 0;
   }

   boolean isReallySolid() {
      return this.has(1) || this.has(1024) && !this.isAdjacentToWindow();
   }

   boolean isNonThumpableSolid() {
      return this.isReallySolid() && !this.has(131072);
   }

   boolean isCanPathW() {
      if (this.has(8192)) {
         return true;
      } else {
         PolygonalMap2$Square var1 = PolygonalMap2.instance.getSquare(this.x - 1, this.y, this.z);
         return var1 != null && (var1.has(131072) || var1.has(262144));
      }
   }

   boolean isCanPathN() {
      if (this.has(16384)) {
         return true;
      } else {
         PolygonalMap2$Square var1 = PolygonalMap2.instance.getSquare(this.x, this.y - 1, this.z);
         return var1 != null && (var1.has(131072) || var1.has(524288));
      }
   }

   boolean isCollideW() {
      if (this.has(2)) {
         return true;
      } else {
         PolygonalMap2$Square var1 = PolygonalMap2.instance.getSquare(this.x - 1, this.y, this.z);
         return var1 != null && (var1.has(262144) || var1.has(448) || var1.isReallySolid());
      }
   }

   boolean isCollideN() {
      if (this.has(4)) {
         return true;
      } else {
         PolygonalMap2$Square var1 = PolygonalMap2.instance.getSquare(this.x, this.y - 1, this.z);
         return var1 != null && (var1.has(524288) || var1.has(56) || var1.isReallySolid());
      }
   }

   boolean isThumpW() {
      if (this.has(32768)) {
         return true;
      } else {
         PolygonalMap2$Square var1 = PolygonalMap2.instance.getSquare(this.x - 1, this.y, this.z);
         return var1 != null && var1.has(131072);
      }
   }

   boolean isThumpN() {
      if (this.has(65536)) {
         return true;
      } else {
         PolygonalMap2$Square var1 = PolygonalMap2.instance.getSquare(this.x, this.y - 1, this.z);
         return var1 != null && var1.has(131072);
      }
   }

   boolean isAdjacentToWindow() {
      if (!this.has(2048) && !this.has(4096)) {
         PolygonalMap2$Square var1 = PolygonalMap2.instance.getSquare(this.x, this.y + 1, this.z);
         if (var1 != null && var1.has(4096)) {
            return true;
         } else {
            PolygonalMap2$Square var2 = PolygonalMap2.instance.getSquare(this.x + 1, this.y, this.z);
            return var2 != null && var2.has(2048);
         }
      } else {
         return true;
      }
   }

   static PolygonalMap2$Square alloc() {
      return pool.isEmpty() ? new PolygonalMap2$Square() : pool.pop();
   }

   void release() {
      if (!$assertionsDisabled && pool.contains(this)) {
         throw new AssertionError();
      } else {
         pool.push(this);
      }
   }
}
