package zombie.meta;

import gnu.trove.set.hash.TIntHashSet;
import java.util.ArrayList;
import zombie.GameTime;
import zombie.iso.IsoGridSquare;
import zombie.iso.IsoMetaGrid.Zone;
import zombie.iso.areas.SafeHouse;
import zombie.network.GameClient;
import zombie.network.GameServer;

public final class Meta {
   public static final Meta instance = new Meta();
   final ArrayList<IsoGridSquare> SquaresProcessing = new ArrayList<>();
   private final ArrayList<IsoGridSquare> SquaresSeen = new ArrayList<>(2000);
   private final TIntHashSet SquaresSeenSet = new TIntHashSet();

   public void dealWithSquareSeen(IsoGridSquare var1) {
      if (!GameClient.bClient) {
         if (var1.hourLastSeen != (int)GameTime.getInstance().getWorldAgeHours()) {
            synchronized (this.SquaresSeen) {
               if (!this.SquaresSeenSet.contains(var1.getID())) {
                  this.SquaresSeen.add(var1);
                  this.SquaresSeenSet.add(var1.getID());
               }
            }
         }
      }
   }

   public void dealWithSquareSeenActual(IsoGridSquare var1) {
      if (!GameClient.bClient) {
         Zone var2 = var1.zone;
         if (var2 != null) {
            var2.setHourSeenToCurrent();
         }

         if (GameServer.bServer) {
            SafeHouse var3 = SafeHouse.getSafeHouse(var1);
            if (var3 != null) {
               var3.updateSafehouse(null);
            }
         }

         var1.setHourSeenToCurrent();
      }
   }

   public void update() {
      if (!GameClient.bClient) {
         this.SquaresProcessing.clear();
         synchronized (this.SquaresSeen) {
            this.SquaresProcessing.addAll(this.SquaresSeen);
            this.SquaresSeen.clear();
            this.SquaresSeenSet.clear();
         }

         for (int var4 = 0; var4 < this.SquaresProcessing.size(); var4++) {
            this.dealWithSquareSeenActual(this.SquaresProcessing.get(var4));
         }

         this.SquaresProcessing.clear();
      }
   }
}
