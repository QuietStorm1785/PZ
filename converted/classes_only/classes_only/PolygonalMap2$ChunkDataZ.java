package zombie.vehicles;

import java.nio.ByteBuffer;
import java.util.ArrayList;
import zombie.iso.IsoGridSquare;
import zombie.popman.ObjectPool;
import zombie.vehicles.PolygonalMap2.Chunk;
import zombie.vehicles.PolygonalMap2.Edge;
import zombie.vehicles.PolygonalMap2.EdgeRing;
import zombie.vehicles.PolygonalMap2.ImmutableRectF;
import zombie.vehicles.PolygonalMap2.Node;
import zombie.vehicles.PolygonalMap2.Obstacle;
import zombie.vehicles.PolygonalMap2.Square;
import zombie.vehicles.PolygonalMap2.Vehicle;
import zombie.vehicles.PolygonalMap2.VehiclePoly;

final class PolygonalMap2$ChunkDataZ {
   public Chunk chunk;
   public final ArrayList<Obstacle> obstacles = new ArrayList<>();
   public final ArrayList<Node> nodes = new ArrayList<>();
   public int z;
   static short EPOCH = 0;
   short epoch;
   public static final ObjectPool<PolygonalMap2$ChunkDataZ> pool = new ObjectPool(PolygonalMap2$ChunkDataZ::new);

   private PolygonalMap2$ChunkDataZ() {
   }

   public void init(Chunk var1, int var2) {
      this.chunk = var1;
      this.z = var2;
      this.epoch = EPOCH;
      if (PolygonalMap2.instance.clipperThread == null) {
         PolygonalMap2.instance.clipperThread = new Clipper();
      }

      Clipper var3 = PolygonalMap2.instance.clipperThread;
      var3.clear();
      int var4 = var1.wx * 10;
      int var5 = var1.wy * 10;

      for (int var6 = var5 - 2; var6 < var5 + 10 + 2; var6++) {
         for (int var7 = var4 - 2; var7 < var4 + 10 + 2; var7++) {
            Square var8 = PolygonalMap2.instance.getSquare(var7, var6, var2);
            if (var8 != null && var8.has(512)) {
               if (var8.isReallySolid() || var8.has(128) || var8.has(64) || var8.has(16) || var8.has(8)) {
                  var3.addAABBBevel(var7 - 0.3F, var6 - 0.3F, var7 + 1.0F + 0.3F, var6 + 1.0F + 0.3F, 0.19800001F);
               }

               if (var8.has(2) || var8.has(256)) {
                  var3.addAABBBevel(var7 - 0.3F, var6 - 0.3F, var7 + 0.3F, var6 + 1.0F + 0.3F, 0.19800001F);
               }

               if (var8.has(4) || var8.has(32)) {
                  var3.addAABBBevel(var7 - 0.3F, var6 - 0.3F, var7 + 1.0F + 0.3F, var6 + 0.3F, 0.19800001F);
               }

               if (var8.has(256)) {
                  Square var9 = PolygonalMap2.instance.getSquare(var7 + 1, var6, var2);
                  if (var9 != null) {
                     var3.addAABBBevel(var7 + 1 - 0.3F, var6 - 0.3F, var7 + 1 + 0.3F, var6 + 1.0F + 0.3F, 0.19800001F);
                  }
               }

               if (var8.has(32)) {
                  Square var26 = PolygonalMap2.instance.getSquare(var7, var6 + 1, var2);
                  if (var26 != null) {
                     var3.addAABBBevel(var7 - 0.3F, var6 + 1 - 0.3F, var7 + 1.0F + 0.3F, var6 + 1 + 0.3F, 0.19800001F);
                  }
               }
            } else {
               var3.addAABB(var7, var6, var7 + 1.0F, var6 + 1.0F);
            }
         }
      }

      ByteBuffer var21 = PolygonalMap2.instance.xyBufferThread;
      int var22 = var3.generatePolygons();

      for (int var23 = 0; var23 < var22; var23++) {
         var21.clear();
         var3.getPolygon(var23, var21);
         Obstacle var27 = Obstacle.alloc().init((IsoGridSquare)null);
         this.getEdgesFromBuffer(var21, var27, true);
         short var10 = var21.getShort();

         for (int var11 = 0; var11 < var10; var11++) {
            this.getEdgesFromBuffer(var21, var27, false);
         }

         var27.calcBounds();
         this.obstacles.add(var27);
      }

      int var24 = var1.wx * 10;
      int var28 = var1.wy * 10;
      int var30 = var24 + 10;
      int var32 = var28 + 10;
      var24 -= 2;
      var28 -= 2;
      var30 += 2;
      var32 += 2;
      ImmutableRectF var12 = ImmutableRectF.alloc();
      var12.init(var24, var28, var30 - var24, var32 - var28);
      ImmutableRectF var13 = ImmutableRectF.alloc();

      for (int var14 = 0; var14 < PolygonalMap2.instance.vehicles.size(); var14++) {
         Vehicle var15 = (Vehicle)PolygonalMap2.instance.vehicles.get(var14);
         VehiclePoly var16 = var15.polyPlusRadius;
         float var17 = Math.min(var16.x1, Math.min(var16.x2, Math.min(var16.x3, var16.x4)));
         float var18 = Math.min(var16.y1, Math.min(var16.y2, Math.min(var16.y3, var16.y4)));
         float var19 = Math.max(var16.x1, Math.max(var16.x2, Math.max(var16.x3, var16.x4)));
         float var20 = Math.max(var16.y1, Math.max(var16.y2, Math.max(var16.y3, var16.y4)));
         var13.init(var17, var18, var19 - var17, var20 - var18);
         if (var12.intersects(var13)) {
            this.addEdgesForVehicle(var15);
         }
      }

      var12.release();
      var13.release();
   }

   private void getEdgesFromBuffer(ByteBuffer var1, Obstacle var2, boolean var3) {
      short var4 = var1.getShort();
      if (var4 < 3) {
         var1.position(var1.position() + var4 * 4 * 2);
      } else {
         EdgeRing var5 = var2.outer;
         if (!var3) {
            var5 = EdgeRing.alloc();
            var5.clear();
            var2.inner.add(var5);
         }

         int var6 = this.nodes.size();

         for (int var7 = 0; var7 < var4; var7++) {
            float var8 = var1.getFloat();
            float var9 = var1.getFloat();
            Node var10 = Node.alloc().init(var8, var9, this.z);
            var10.flags |= 4;
            this.nodes.add(var6, var10);
         }

         for (int var11 = var6; var11 < this.nodes.size() - 1; var11++) {
            Node var13 = this.nodes.get(var11);
            Node var15 = this.nodes.get(var11 + 1);
            Edge var17 = Edge.alloc().init(var13, var15, var2, var5);
            var5.add(var17);
         }

         Node var12 = this.nodes.get(this.nodes.size() - 1);
         Node var14 = this.nodes.get(var6);
         Edge var16 = Edge.alloc().init(var12, var14, var2, var5);
         var5.add(var16);
      }
   }

   private void addEdgesForVehicle(Vehicle var1) {
      VehiclePoly var2 = var1.polyPlusRadius;
      int var3 = (int)var2.z;
      Node var4 = Node.alloc().init(var2.x1, var2.y1, var3);
      Node var5 = Node.alloc().init(var2.x2, var2.y2, var3);
      Node var6 = Node.alloc().init(var2.x3, var2.y3, var3);
      Node var7 = Node.alloc().init(var2.x4, var2.y4, var3);
      var4.flags |= 4;
      var5.flags |= 4;
      var6.flags |= 4;
      var7.flags |= 4;
      Obstacle var8 = Obstacle.alloc().init(var1);
      this.obstacles.add(var8);
      Edge var9 = Edge.alloc().init(var4, var5, var8, var8.outer);
      Edge var10 = Edge.alloc().init(var5, var6, var8, var8.outer);
      Edge var11 = Edge.alloc().init(var6, var7, var8, var8.outer);
      Edge var12 = Edge.alloc().init(var7, var4, var8, var8.outer);
      var8.outer.add(var9);
      var8.outer.add(var10);
      var8.outer.add(var11);
      var8.outer.add(var12);
      var8.calcBounds();
      this.nodes.add(var4);
      this.nodes.add(var5);
      this.nodes.add(var6);
      this.nodes.add(var7);
   }

   public void clear() {
      Node.releaseAll(this.nodes);
      this.nodes.clear();
      Obstacle.releaseAll(this.obstacles);
      this.obstacles.clear();
   }
}
