package zombie.vehicles;

import java.io.IOException;
import java.util.concurrent.ConcurrentLinkedQueue;
import zombie.core.logger.ExceptionLogger;
import zombie.debug.DebugLog;
import zombie.iso.IsoChunk;
import zombie.iso.IsoGridSquare;
import zombie.iso.IsoWorld;
import zombie.iso.IsoChunk.JobType;
import zombie.vehicles.VehiclesDB2.IVehicleStore;
import zombie.vehicles.VehiclesDB2.QueueItem;
import zombie.vehicles.VehiclesDB2.SQLStore;
import zombie.vehicles.VehiclesDB2.VehicleBuffer;

final class VehiclesDB2$WorldStreamerThread {
   final IVehicleStore m_store = new SQLStore();
   final ConcurrentLinkedQueue<QueueItem> m_queue = new ConcurrentLinkedQueue<>();
   final VehicleBuffer m_vehicleBuffer = new VehicleBuffer();

   private VehiclesDB2$WorldStreamerThread() {
   }

   void Reset() {
      this.m_store.Reset();
      if (!$assertionsDisabled && !this.m_queue.isEmpty()) {
         throw new AssertionError();
      } else {
         this.m_queue.clear();
      }
   }

   void update() {
      for (QueueItem var1 = this.m_queue.poll(); var1 != null; var1 = this.m_queue.poll()) {
         try {
            var1.processWorldStreamer();
         } finally {
            VehiclesDB2.instance.m_main.m_queue.add(var1);
         }
      }
   }

   void loadChunk(IsoChunk var1) throws IOException {
      this.m_store.loadChunk(var1, this::vehicleLoaded);
   }

   void vehicleLoaded(IsoChunk var1, VehicleBuffer var2) throws IOException {
      if (!$assertionsDisabled && var2.m_id < 1) {
         throw new AssertionError();
      } else {
         IsoGridSquare var3 = var1.getGridSquare((int)(var2.m_x - var1.wx * 10), (int)(var2.m_y - var1.wy * 10), 0);
         BaseVehicle var4 = new BaseVehicle(IsoWorld.instance.CurrentCell);
         var4.setSquare(var3);
         var4.setCurrent(var3);

         try {
            var4.load(var2.m_bb, var2.m_WorldVersion);
         } catch (Exception var6) {
            ExceptionLogger.logException(var6);
            DebugLog.General.error("vehicle %d is being deleted because an error occurred loading it", new Object[]{var2.m_id});
            this.m_store.removeVehicle(var2.m_id);
            return;
         }

         var4.sqlID = var2.m_id;
         var4.chunk = var1;
         if (var1.jobType == JobType.SoftReset) {
            var4.softReset();
         }

         var1.vehicles.add(var4);
      }
   }

   void unloadChunk(IsoChunk var1) {
      for (int var2 = 0; var2 < var1.vehicles.size(); var2++) {
         try {
            BaseVehicle var3 = (BaseVehicle)var1.vehicles.get(var2);
            this.m_vehicleBuffer.set(var3);
            this.m_store.updateVehicle(this.m_vehicleBuffer);
         } catch (Exception var4) {
            ExceptionLogger.logException(var4);
         }
      }
   }
}
