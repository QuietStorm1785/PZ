package zombie.iso.areas.isoregion.jobs;

import java.util.concurrent.ConcurrentLinkedQueue;
import zombie.core.Core;
import zombie.core.raknet.UdpConnection;
import zombie.iso.areas.isoregion.jobs.RegionJobManager.1;

public final class RegionJobManager {
   private static final ConcurrentLinkedQueue<JobSquareUpdate> poolSquareUpdate = new ConcurrentLinkedQueue<>();
   private static final ConcurrentLinkedQueue<JobChunkUpdate> poolChunkUpdate = new ConcurrentLinkedQueue<>();
   private static final ConcurrentLinkedQueue<JobApplyChanges> poolApplyChanges = new ConcurrentLinkedQueue<>();
   private static final ConcurrentLinkedQueue<JobServerSendFullData> poolServerSendFullData = new ConcurrentLinkedQueue<>();
   private static final ConcurrentLinkedQueue<JobDebugResetAllData> poolDebugResetAllData = new ConcurrentLinkedQueue<>();

   public static JobSquareUpdate allocSquareUpdate(int var0, int var1, int var2, byte var3) {
      JobSquareUpdate var4 = poolSquareUpdate.poll();
      if (var4 == null) {
         var4 = new JobSquareUpdate();
      }

      var4.worldSquareX = var0;
      var4.worldSquareY = var1;
      var4.worldSquareZ = var2;
      var4.newSquareFlags = var3;
      return var4;
   }

   public static JobChunkUpdate allocChunkUpdate() {
      JobChunkUpdate var0 = poolChunkUpdate.poll();
      if (var0 == null) {
         var0 = new JobChunkUpdate();
      }

      return var0;
   }

   public static JobApplyChanges allocApplyChanges(boolean var0) {
      JobApplyChanges var1 = poolApplyChanges.poll();
      if (var1 == null) {
         var1 = new JobApplyChanges();
      }

      var1.saveToDisk = var0;
      return var1;
   }

   public static JobServerSendFullData allocServerSendFullData(UdpConnection var0) {
      JobServerSendFullData var1 = poolServerSendFullData.poll();
      if (var1 == null) {
         var1 = new JobServerSendFullData();
      }

      var1.targetConn = var0;
      return var1;
   }

   public static JobDebugResetAllData allocDebugResetAllData() {
      JobDebugResetAllData var0 = poolDebugResetAllData.poll();
      if (var0 == null) {
         var0 = new JobDebugResetAllData();
      }

      return var0;
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
   public static void release(RegionJob var0) {
      var0.reset();
      switch (1.$SwitchMap$zombie$iso$areas$isoregion$jobs$RegionJobType[var0.getJobType().ordinal()]) {
         case 1:
            poolSquareUpdate.add((JobSquareUpdate)var0);
            break;
         case 2:
            poolApplyChanges.add((JobApplyChanges)var0);
            break;
         case 3:
            poolChunkUpdate.add((JobChunkUpdate)var0);
            break;
         case 4:
            poolServerSendFullData.add((JobServerSendFullData)var0);
            break;
         case 5:
            poolDebugResetAllData.add((JobDebugResetAllData)var0);
            break;
         default:
            if (Core.bDebug) {
               throw new RuntimeException("No pooling for this job type?");
            }
      }
   }
}
