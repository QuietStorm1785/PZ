package zombie.vehicles;

import java.util.ArrayDeque;
import zombie.vehicles.PolygonalMap2.Node;

final class PolygonalMap2$Connection {
   Node node1;
   Node node2;
   int flags;
   static final ArrayDeque<PolygonalMap2$Connection> pool = new ArrayDeque<>();

   private PolygonalMap2$Connection() {
   }

   PolygonalMap2$Connection init(Node var1, Node var2, int var3) {
      this.node1 = var1;
      this.node2 = var2;
      this.flags = var3;
      return this;
   }

   Node otherNode(Node var1) {
      if (!$assertionsDisabled && var1 != this.node1 && var1 != this.node2) {
         throw new AssertionError();
      } else {
         return var1 == this.node1 ? this.node2 : this.node1;
      }
   }

   boolean has(int var1) {
      return (this.flags & var1) != 0;
   }

   static PolygonalMap2$Connection alloc() {
      if (pool.isEmpty()) {
         boolean var0 = false;
      } else {
         boolean var1 = false;
      }

      return pool.isEmpty() ? new PolygonalMap2$Connection() : pool.pop();
   }

   void release() {
      if (!$assertionsDisabled && pool.contains(this)) {
         throw new AssertionError();
      } else {
         pool.push(this);
      }
   }
}
