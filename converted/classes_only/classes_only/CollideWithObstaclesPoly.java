package zombie.vehicles;

import java.nio.ByteBuffer;
import java.util.ArrayList;
import org.joml.Vector2f;
import zombie.characters.IsoGameCharacter;
import zombie.characters.IsoPlayer;
import zombie.core.Core;
import zombie.debug.DebugOptions;
import zombie.debug.LineDrawer;
import zombie.iso.IsoChunk;
import zombie.iso.IsoWorld;
import zombie.iso.Vector2;
import zombie.network.GameServer;
import zombie.network.ServerMap;
import zombie.vehicles.CollideWithObstaclesPoly.CCEdge;
import zombie.vehicles.CollideWithObstaclesPoly.CCNode;
import zombie.vehicles.CollideWithObstaclesPoly.CCObstacle;
import zombie.vehicles.CollideWithObstaclesPoly.ChunkDataZ;
import zombie.vehicles.CollideWithObstaclesPoly.ClosestPointOnEdge;
import zombie.vehicles.CollideWithObstaclesPoly.ImmutableRectF;
import zombie.vehicles.PolygonalMap2.VehiclePoly;

public class CollideWithObstaclesPoly {
   static final float RADIUS = 0.3F;
   private final ArrayList<CCObstacle> obstacles = new ArrayList<>();
   private final ArrayList<CCNode> nodes = new ArrayList<>();
   private final ImmutableRectF moveBounds = new ImmutableRectF();
   private final ImmutableRectF vehicleBounds = new ImmutableRectF();
   private static final Vector2 move = new Vector2();
   private static final Vector2 nodeNormal = new Vector2();
   private static final Vector2 edgeVec = new Vector2();
   private final ArrayList<BaseVehicle> vehicles = new ArrayList<>();
   private Clipper clipper;
   private final ByteBuffer xyBuffer = ByteBuffer.allocateDirect(8192);
   private final ClosestPointOnEdge closestPointOnEdge = new ClosestPointOnEdge();

   void getVehiclesInRect(float var1, float var2, float var3, float var4, int var5) {
      this.vehicles.clear();
      int var6 = (int)(var1 / 10.0F);
      int var7 = (int)(var2 / 10.0F);
      int var8 = (int)Math.ceil(var3 / 10.0F);
      int var9 = (int)Math.ceil(var4 / 10.0F);

      for (int var10 = var7; var10 < var9; var10++) {
         for (int var11 = var6; var11 < var8; var11++) {
            IsoChunk var12 = GameServer.bServer
               ? ServerMap.instance.getChunk(var11, var10)
               : IsoWorld.instance.CurrentCell.getChunkForGridSquare(var11 * 10, var10 * 10, 0);
            if (var12 != null) {
               for (int var13 = 0; var13 < var12.vehicles.size(); var13++) {
                  BaseVehicle var14 = (BaseVehicle)var12.vehicles.get(var13);
                  if (var14.getScript() != null && (int)var14.z == var5) {
                     this.vehicles.add(var14);
                  }
               }
            }
         }
      }
   }

   void getObstaclesInRect(float var1, float var2, float var3, float var4, int var5, int var6, int var7, boolean var8) {
      if (this.clipper == null) {
         this.clipper = new Clipper();
      }

      this.clipper.clear();
      this.moveBounds.init(var1 - 2.0F, var2 - 2.0F, var3 - var1 + 4.0F, var4 - var2 + 4.0F);
      int var9 = (int)(this.moveBounds.x / 10.0F);
      int var10 = (int)(this.moveBounds.y / 10.0F);
      int var11 = (int)Math.ceil(this.moveBounds.right() / 10.0F);
      int var12 = (int)Math.ceil(this.moveBounds.bottom() / 10.0F);
      if (Math.abs(var3 - var1) < 2.0F && Math.abs(var4 - var2) < 2.0F) {
         var9 = var5 / 10;
         var10 = var6 / 10;
         var11 = var9 + 1;
         var12 = var10 + 1;
      }

      for (int var13 = var10; var13 < var12; var13++) {
         for (int var14 = var9; var14 < var11; var14++) {
            IsoChunk var15 = GameServer.bServer ? ServerMap.instance.getChunk(var14, var13) : IsoWorld.instance.CurrentCell.getChunk(var14, var13);
            if (var15 != null) {
               ChunkDataZ var16 = var15.collision.init(var15, var7, this);
               ArrayList var17 = var8 ? var16.worldVehicleUnion : var16.worldVehicleSeparate;

               for (int var18 = 0; var18 < var17.size(); var18++) {
                  CCObstacle var19 = (CCObstacle)var17.get(var18);
                  if (var19.bounds.intersects(this.moveBounds)) {
                     this.obstacles.add(var19);
                  }
               }

               this.nodes.addAll(var16.nodes);
            }
         }
      }
   }

   public Vector2f resolveCollision(IsoGameCharacter var1, float var2, float var3, Vector2f var4) {
      var4.set(var2, var3);
      boolean var5 = Core.bDebug && DebugOptions.instance.CollideWithObstaclesRenderObstacles.getValue();
      float var6 = var1.x;
      float var7 = var1.y;
      float var8 = var2;
      float var9 = var3;
      if (var5) {
         LineDrawer.addLine(var6, var7, (int)var1.z, var2, var3, (int)var1.z, 1.0F, 1.0F, 1.0F, null, true);
      }

      if (var6 == var2 && var7 == var3) {
         return var4;
      } else {
         move.set(var2 - var1.x, var3 - var1.y);
         move.normalize();
         this.nodes.clear();
         this.obstacles.clear();
         this.getObstaclesInRect(
            Math.min(var6, var2), Math.min(var7, var3), Math.max(var6, var2), Math.max(var7, var3), (int)var1.x, (int)var1.y, (int)var1.z, true
         );
         this.closestPointOnEdge.edge = null;
         this.closestPointOnEdge.node = null;
         this.closestPointOnEdge.distSq = Double.MAX_VALUE;

         for (int var10 = 0; var10 < this.obstacles.size(); var10++) {
            CCObstacle var11 = this.obstacles.get(var10);
            byte var12 = 0;
            if (var11.isPointInside(var1.x, var1.y, var12)) {
               var11.getClosestPointOnEdge(var1.x, var1.y, this.closestPointOnEdge);
            }
         }

         CCEdge var16 = this.closestPointOnEdge.edge;
         CCNode var17 = this.closestPointOnEdge.node;
         if (var16 != null) {
            float var18 = var16.normal.dot(move);
            if (var18 >= 0.01F) {
               var16 = null;
            }
         }

         if (var17 != null && var17.getNormalAndEdgeVectors(nodeNormal, edgeVec) && nodeNormal.dot(move) + 0.05F >= nodeNormal.dot(edgeVec)) {
            var17 = null;
            var16 = null;
         }

         if (var16 == null) {
            this.closestPointOnEdge.edge = null;
            this.closestPointOnEdge.node = null;
            this.closestPointOnEdge.distSq = Double.MAX_VALUE;

            for (int var19 = 0; var19 < this.obstacles.size(); var19++) {
               CCObstacle var13 = this.obstacles.get(var19);
               var13.lineSegmentIntersect(var6, var7, var8, var9, this.closestPointOnEdge, var5);
            }

            var16 = this.closestPointOnEdge.edge;
            var17 = this.closestPointOnEdge.node;
         }

         if (var17 != null) {
            move.set(var2 - var1.x, var3 - var1.y);
            move.normalize();
            CCEdge var20 = var16;
            CCEdge var22 = null;

            for (int var14 = 0; var14 < var17.edges.size(); var14++) {
               CCEdge var15 = (CCEdge)var17.edges.get(var14);
               if (var15 != var16
                  && (var20.node1.x != var15.node1.x || var20.node1.y != var15.node1.y || var20.node2.x != var15.node2.x || var20.node2.y != var15.node2.y)
                  && (var20.node1.x != var15.node2.x || var20.node1.y != var15.node2.y || var20.node2.x != var15.node1.x || var20.node2.y != var15.node1.y)
                  && (!var20.hasNode(var15.node1) || !var20.hasNode(var15.node2))) {
                  var22 = var15;
               }
            }

            if (var20 != null && var22 != null) {
               if (var16 == var20) {
                  CCNode var24 = var17 == var22.node1 ? var22.node2 : var22.node1;
                  edgeVec.set(var24.x - var17.x, var24.y - var17.y);
                  edgeVec.normalize();
                  if (move.dot(edgeVec) >= 0.0F) {
                     var16 = var22;
                  }
               } else if (var16 == var22) {
                  CCNode var25 = var17 == var20.node1 ? var20.node2 : var20.node1;
                  edgeVec.set(var25.x - var17.x, var25.y - var17.y);
                  edgeVec.normalize();
                  if (move.dot(edgeVec) >= 0.0F) {
                     var16 = var20;
                  }
               }
            }
         }

         if (var16 != null) {
            if (var5) {
               float var21 = var16.node1.x;
               float var23 = var16.node1.y;
               float var26 = var16.node2.x;
               float var27 = var16.node2.y;
               LineDrawer.addLine(var21, var23, var16.node1.z, var26, var27, var16.node1.z, 0.0F, 1.0F, 1.0F, null, true);
            }

            this.closestPointOnEdge.distSq = Double.MAX_VALUE;
            var16.getClosestPointOnEdge(var2, var3, this.closestPointOnEdge);
            var4.set(this.closestPointOnEdge.point.x, this.closestPointOnEdge.point.y);
         }

         return var4;
      }
   }

   boolean canStandAt(float var1, float var2, float var3, BaseVehicle var4, int var5) {
      boolean var6 = (var5 & 1) != 0;
      boolean var7 = (var5 & 2) != 0;
      float var8 = var1 - 0.3F;
      float var9 = var2 - 0.3F;
      float var10 = var1 + 0.3F;
      float var11 = var2 + 0.3F;
      this.nodes.clear();
      this.obstacles.clear();
      this.getObstaclesInRect(
         Math.min(var8, var10), Math.min(var9, var11), Math.max(var8, var10), Math.max(var9, var11), (int)var1, (int)var2, (int)var3, var4 == null
      );

      for (int var12 = 0; var12 < this.obstacles.size(); var12++) {
         CCObstacle var13 = this.obstacles.get(var12);
         if ((var4 == null || var13.vehicle != var4) && var13.isPointInside(var1, var2, var5)) {
            return false;
         }
      }

      return true;
   }

   public boolean isNotClear(float var1, float var2, float var3, float var4, int var5, boolean var6, BaseVehicle var7, boolean var8, boolean var9) {
      float var10 = var1;
      float var11 = var2;
      float var12 = var3;
      float var13 = var4;
      var1 /= 10.0F;
      var2 /= 10.0F;
      var3 /= 10.0F;
      var4 /= 10.0F;
      double var14 = Math.abs(var3 - var1);
      double var16 = Math.abs(var4 - var2);
      int var18 = (int)Math.floor(var1);
      int var19 = (int)Math.floor(var2);
      int var20 = 1;
      byte var21;
      double var23;
      if (var14 == 0.0) {
         var21 = 0;
         var23 = Double.POSITIVE_INFINITY;
      } else if (var3 > var1) {
         var21 = 1;
         var20 += (int)Math.floor(var3) - var18;
         var23 = (Math.floor(var1) + 1.0 - var1) * var16;
      } else {
         var21 = -1;
         var20 += var18 - (int)Math.floor(var3);
         var23 = (var1 - Math.floor(var1)) * var16;
      }

      byte var22;
      if (var16 == 0.0) {
         var22 = 0;
         var23 -= Double.POSITIVE_INFINITY;
      } else if (var4 > var2) {
         var22 = 1;
         var20 += (int)Math.floor(var4) - var19;
         var23 -= (Math.floor(var2) + 1.0 - var2) * var14;
      } else {
         var22 = -1;
         var20 += var19 - (int)Math.floor(var4);
         var23 -= (var2 - Math.floor(var2)) * var14;
      }

      for (; var20 > 0; var20--) {
         IsoChunk var25 = GameServer.bServer ? ServerMap.instance.getChunk(var18, var19) : IsoWorld.instance.CurrentCell.getChunk(var18, var19);
         if (var25 != null) {
            if (var6) {
               LineDrawer.addRect(var18 * 10, var19 * 10, var5, 10.0F, 10.0F, 1.0F, 1.0F, 1.0F);
            }

            ChunkDataZ var26 = var25.collision.init(var25, var5, this);
            ArrayList var27 = var7 == null ? var26.worldVehicleUnion : var26.worldVehicleSeparate;

            for (int var28 = 0; var28 < var27.size(); var28++) {
               CCObstacle var29 = (CCObstacle)var27.get(var28);
               if ((var7 == null || var29.vehicle != var7) && var29.lineSegmentIntersects(var10, var11, var12, var13, var6)) {
                  return true;
               }
            }
         }

         if (var23 > 0.0) {
            var19 += var22;
            var23 -= var14;
         } else {
            var18 += var21;
            var23 += var16;
         }
      }

      return false;
   }

   private void vehicleMoved(VehiclePoly var1) {
      byte var2 = 2;
      int var3 = (int)Math.min(var1.x1, Math.min(var1.x2, Math.min(var1.x3, var1.x4)));
      int var4 = (int)Math.min(var1.y1, Math.min(var1.y2, Math.min(var1.y3, var1.y4)));
      int var5 = (int)Math.max(var1.x1, Math.max(var1.x2, Math.max(var1.x3, var1.x4)));
      int var6 = (int)Math.max(var1.y1, Math.max(var1.y2, Math.max(var1.y3, var1.y4)));
      int var7 = (int)var1.z;
      int var8 = (var3 - var2) / 10;
      int var9 = (var4 - var2) / 10;
      int var10 = (int)Math.ceil((var5 + var2 - 1.0F) / 10.0F);
      int var11 = (int)Math.ceil((var6 + var2 - 1.0F) / 10.0F);

      for (int var12 = var9; var12 <= var11; var12++) {
         for (int var13 = var8; var13 <= var10; var13++) {
            IsoChunk var14 = IsoWorld.instance.CurrentCell.getChunk(var13, var12);
            if (var14 != null && var14.collision.data[var7] != null) {
               ChunkDataZ var15 = var14.collision.data[var7];
               var14.collision.data[var7] = null;
               var15.clear();
               ChunkDataZ.pool.release(var15);
            }
         }
      }
   }

   public void vehicleMoved(VehiclePoly var1, VehiclePoly var2) {
      this.vehicleMoved(var1);
      this.vehicleMoved(var2);
   }

   public void render() {
      boolean var1 = Core.bDebug && DebugOptions.instance.CollideWithObstaclesRenderObstacles.getValue();
      if (var1) {
         IsoPlayer var2 = IsoPlayer.getInstance();
         if (var2 == null) {
            return;
         }

         this.nodes.clear();
         this.obstacles.clear();
         this.getObstaclesInRect(var2.x, var2.y, var2.x, var2.y, (int)var2.x, (int)var2.y, (int)var2.z, true);
         if (DebugOptions.instance.CollideWithObstaclesRenderNormals.getValue()) {
            for (CCNode var4 : this.nodes) {
               if (var4.getNormalAndEdgeVectors(nodeNormal, edgeVec)) {
                  LineDrawer.addLine(var4.x, var4.y, var4.z, var4.x + nodeNormal.x, var4.y + nodeNormal.y, var4.z, 0.0F, 0.0F, 1.0F, null, true);
               }
            }
         }

         for (CCObstacle var6 : this.obstacles) {
            var6.render();
         }
      }
   }
}
