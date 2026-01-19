package zombie.iso;

import java.io.IOException;
import java.util.ArrayList;
import java.util.concurrent.ConcurrentLinkedQueue;
import zombie.core.Core;
import zombie.debug.DebugLog;
import zombie.network.GameServer;
import zombie.vehicles.BaseVehicle;
import zombie.vehicles.VehiclesDB2;

public class ChunkSaveWorker {
   public static ChunkSaveWorker instance = new ChunkSaveWorker();
   private final ArrayList<IsoChunk> tempList = new ArrayList<>();
   public ConcurrentLinkedQueue<IsoChunk> toSaveQueue = new ConcurrentLinkedQueue<>();
   public boolean bSaving;

   public void Update(IsoChunk var1) {
      if (!GameServer.bServer) {
         IsoChunk var2 = null;
         Object var3 = null;
         this.bSaving = !this.toSaveQueue.isEmpty();
         if (this.bSaving) {
            if (var1 != null) {
               for (IsoChunk var6 : this.toSaveQueue) {
                  if (var6.wx == var1.wx && var6.wy == var1.wy) {
                     var2 = var6;
                     break;
                  }
               }
            }

            if (var2 == null) {
               var2 = this.toSaveQueue.poll();
            } else {
               this.toSaveQueue.remove(var2);
            }

            if (var2 != null) {
               try {
                  var2.Save(false);
               } catch (Exception var5) {
                  var5.printStackTrace();
               }
            }
         }
      }
   }

   public void SaveNow(ArrayList<IsoChunk> var1) {
      this.tempList.clear();

      for (IsoChunk var2 = this.toSaveQueue.poll(); var2 != null; var2 = this.toSaveQueue.poll()) {
         boolean var3 = false;

         for (int var4 = 0; var4 < var1.size(); var4++) {
            IsoChunk var5 = (IsoChunk)var1.get(var4);
            if (var2.wx == var5.wx && var2.wy == var5.wy) {
               try {
                  var2.Save(false);
               } catch (IOException var7) {
                  var7.printStackTrace();
               }

               var3 = true;
               break;
            }
         }

         if (!var3) {
            this.tempList.add(var2);
         }
      }

      for (int var8 = 0; var8 < this.tempList.size(); var8++) {
         this.toSaveQueue.add(this.tempList.get(var8));
      }

      this.tempList.clear();
   }

   public void SaveNow() {
      DebugLog.log("EXITDEBUG: ChunkSaveWorker.SaveNow 1");

      for (IsoChunk var1 = this.toSaveQueue.poll(); var1 != null; var1 = this.toSaveQueue.poll()) {
         try {
            DebugLog.log("EXITDEBUG: ChunkSaveWorker.SaveNow 2 (ch=" + var1.wx + ", " + var1.wy + ")");
            var1.Save(false);
         } catch (Exception var3) {
            var3.printStackTrace();
         }
      }

      this.bSaving = false;
      DebugLog.log("EXITDEBUG: ChunkSaveWorker.SaveNow 3");
   }

   public void Add(IsoChunk var1) {
      if (Core.getInstance().isNoSave()) {
         for (int var2 = 0; var2 < var1.vehicles.size(); var2++) {
            VehiclesDB2.instance.updateVehicle((BaseVehicle)var1.vehicles.get(var2));
         }
      }

      if (!this.toSaveQueue.contains(var1)) {
         this.toSaveQueue.add(var1);
      }
   }
}
