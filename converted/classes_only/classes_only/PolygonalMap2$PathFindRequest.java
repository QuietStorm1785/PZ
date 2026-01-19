package zombie.vehicles;

import gnu.trove.list.array.TFloatArrayList;
import java.util.ArrayDeque;
import java.util.ArrayList;
import zombie.ai.KnownBlockedEdges;
import zombie.ai.astar.Mover;
import zombie.characters.IsoGameCharacter;
import zombie.characters.IsoZombie;
import zombie.util.Type;
import zombie.vehicles.PolygonalMap2.IPathfinder;
import zombie.vehicles.PolygonalMap2.Path;

final class PolygonalMap2$PathFindRequest {
   IPathfinder finder;
   Mover mover;
   boolean bCanCrawl;
   boolean bIgnoreCrawlCost;
   boolean bCanThump;
   final ArrayList<KnownBlockedEdges> knownBlockedEdges = new ArrayList<>();
   float startX;
   float startY;
   float startZ;
   float targetX;
   float targetY;
   float targetZ;
   final TFloatArrayList targetXYZ = new TFloatArrayList();
   final Path path = new Path();
   boolean cancel = false;
   static final ArrayDeque<PolygonalMap2$PathFindRequest> pool = new ArrayDeque<>();

   PolygonalMap2$PathFindRequest init(IPathfinder var1, Mover var2, float var3, float var4, float var5, float var6, float var7, float var8) {
      this.finder = var1;
      this.mover = var2;
      this.bCanCrawl = false;
      this.bIgnoreCrawlCost = false;
      this.bCanThump = false;
      IsoZombie var9 = (IsoZombie)Type.tryCastTo(var2, IsoZombie.class);
      if (var9 != null) {
         this.bCanCrawl = var9.isCrawling() || var9.isCanCrawlUnderVehicle();
         this.bIgnoreCrawlCost = var9.isCrawling() && !var9.isCanWalk();
         this.bCanThump = true;
      }

      this.startX = var3;
      this.startY = var4;
      this.startZ = var5;
      this.targetX = var6;
      this.targetY = var7;
      this.targetZ = var8;
      this.targetXYZ.resetQuick();
      this.path.clear();
      this.cancel = false;
      IsoGameCharacter var10 = (IsoGameCharacter)Type.tryCastTo(var2, IsoGameCharacter.class);
      if (var10 != null) {
         ArrayList var11 = var10.getMapKnowledge().getKnownBlockedEdges();

         for (int var12 = 0; var12 < var11.size(); var12++) {
            KnownBlockedEdges var13 = (KnownBlockedEdges)var11.get(var12);
            this.knownBlockedEdges.add(KnownBlockedEdges.alloc().init(var13));
         }
      }

      return this;
   }

   void addTargetXYZ(float var1, float var2, float var3) {
      this.targetXYZ.add(var1);
      this.targetXYZ.add(var2);
      this.targetXYZ.add(var3);
   }

   static PolygonalMap2$PathFindRequest alloc() {
      return pool.isEmpty() ? new PolygonalMap2$PathFindRequest() : pool.pop();
   }

   public void release() {
      KnownBlockedEdges.releaseAll(this.knownBlockedEdges);
      this.knownBlockedEdges.clear();
      if (!$assertionsDisabled && pool.contains(this)) {
         throw new AssertionError();
      } else {
         pool.push(this);
      }
   }
}
