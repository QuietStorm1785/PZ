package zombie.vehicles;

import gnu.trove.set.hash.TIntHashSet;
import java.io.IOException;
import java.util.concurrent.ConcurrentLinkedQueue;
import zombie.characters.IsoPlayer;
import zombie.iso.IsoChunk;
import zombie.network.GameClient;
import zombie.network.GameServer;
import zombie.vehicles.VehiclesDB2.QueueAddVehicle;
import zombie.vehicles.VehiclesDB2.QueueItem;
import zombie.vehicles.VehiclesDB2.QueueLoadChunk;
import zombie.vehicles.VehiclesDB2.QueueRemoveVehicle;
import zombie.vehicles.VehiclesDB2.QueueUpdateVehicle;

final class VehiclesDB2$MainThread {
   final TIntHashSet m_seenChunks = new TIntHashSet();
   final TIntHashSet m_usedIDs = new TIntHashSet();
   final TIntHashSet m_loadedIDs = new TIntHashSet();
   boolean m_forceSave = false;
   final ConcurrentLinkedQueue<QueueItem> m_queue = new ConcurrentLinkedQueue<>();

   VehiclesDB2$MainThread() {
      this.m_seenChunks.setAutoCompactionFactor(0.0F);
      this.m_usedIDs.setAutoCompactionFactor(0.0F);
      this.m_loadedIDs.setAutoCompactionFactor(0.0F);
   }

   void Reset() {
      this.m_seenChunks.clear();
      this.m_usedIDs.clear();
      this.m_loadedIDs.clear();
      if (!$assertionsDisabled && !this.m_queue.isEmpty()) {
         throw new AssertionError();
      } else {
         this.m_queue.clear();
         this.m_forceSave = false;
      }
   }

   void update() throws IOException {
      if (!GameClient.bClient && !GameServer.bServer && this.m_forceSave) {
         this.m_forceSave = false;

         for (int var1 = 0; var1 < 4; var1++) {
            IsoPlayer var2 = IsoPlayer.players[var1];
            if (var2 != null && var2.getVehicle() != null && var2.getVehicle().isEngineRunning()) {
               this.updateVehicle(var2.getVehicle());
               BaseVehicle var3 = var2.getVehicle().getVehicleTowing();
               if (var3 != null) {
                  this.updateVehicle(var3);
               }
            }
         }
      }

      for (QueueItem var7 = this.m_queue.poll(); var7 != null; var7 = this.m_queue.poll()) {
         try {
            var7.processMain();
         } finally {
            var7.release();
         }
      }
   }

   void setChunkSeen(int var1, int var2) {
      int var3 = var2 << 16 | var1;
      this.m_seenChunks.add(var3);
   }

   boolean isChunkSeen(int var1, int var2) {
      int var3 = var2 << 16 | var1;
      return this.m_seenChunks.contains(var3);
   }

   int allocateID() {
      synchronized (this.m_usedIDs) {
         for (int var2 = 1; var2 < Integer.MAX_VALUE; var2++) {
            if (!this.m_usedIDs.contains(var2)) {
               this.m_usedIDs.add(var2);
               return var2;
            }
         }
      }

      throw new RuntimeException("ran out of unused vehicle ids");
   }

   void setVehicleLoaded(BaseVehicle var1) {
      if (var1.sqlID == -1) {
         var1.sqlID = this.allocateID();
      }

      if (!$assertionsDisabled && this.m_loadedIDs.contains(var1.sqlID)) {
         throw new AssertionError();
      } else {
         this.m_loadedIDs.add(var1.sqlID);
      }
   }

   void setVehicleUnloaded(BaseVehicle var1) {
      if (var1.sqlID != -1) {
         this.m_loadedIDs.remove(var1.sqlID);
      }
   }

   void addVehicle(BaseVehicle var1) throws IOException {
      if (var1.sqlID == -1) {
         var1.sqlID = this.allocateID();
      }

      QueueAddVehicle var2 = (QueueAddVehicle)QueueAddVehicle.s_pool.alloc();
      var2.init(var1);
      VehiclesDB2.instance.m_worldStreamer.m_queue.add(var2);
   }

   void removeVehicle(BaseVehicle var1) {
      QueueRemoveVehicle var2 = (QueueRemoveVehicle)QueueRemoveVehicle.s_pool.alloc();
      var2.init(var1);
      VehiclesDB2.instance.m_worldStreamer.m_queue.add(var2);
   }

   void updateVehicle(BaseVehicle var1) throws IOException {
      if (var1.sqlID == -1) {
         var1.sqlID = this.allocateID();
      }

      QueueUpdateVehicle var2 = (QueueUpdateVehicle)QueueUpdateVehicle.s_pool.alloc();
      var2.init(var1);
      VehiclesDB2.instance.m_worldStreamer.m_queue.add(var2);
   }

   void loadChunk(IsoChunk var1) {
      QueueLoadChunk var2 = (QueueLoadChunk)QueueLoadChunk.s_pool.alloc();
      var2.init(var1.wx, var1.wy);
      var1.m_loadVehiclesObject = var2;
      VehiclesDB2.instance.m_worldStreamer.m_queue.add(var2);
   }
}
