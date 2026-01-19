package zombie.vehicles;

import gnu.trove.map.hash.TIntObjectHashMap;
import gnu.trove.set.hash.TIntHashSet;
import java.io.IOException;
import java.util.ArrayList;
import zombie.iso.IsoChunk;
import zombie.vehicles.VehiclesDB2.IVehicleStore;
import zombie.vehicles.VehiclesDB2.ThrowingBiConsumer;
import zombie.vehicles.VehiclesDB2.ThrowingConsumer;
import zombie.vehicles.VehiclesDB2.VehicleBuffer;

class VehiclesDB2$MemoryStore extends IVehicleStore {
   final TIntObjectHashMap<VehicleBuffer> m_IDToVehicle = new TIntObjectHashMap();
   final TIntObjectHashMap<ArrayList<VehicleBuffer>> m_ChunkToVehicles = new TIntObjectHashMap();

   private VehiclesDB2$MemoryStore() {
   }

   void init(TIntHashSet var1, TIntHashSet var2) {
      var1.clear();
      var2.clear();
   }

   void Reset() {
      this.m_IDToVehicle.clear();
      this.m_ChunkToVehicles.clear();
   }

   void loadChunk(IsoChunk var1, ThrowingBiConsumer<IsoChunk, VehicleBuffer, IOException> var2) throws IOException {
      int var3 = var1.wy << 16 | var1.wx;
      ArrayList var4 = (ArrayList)this.m_ChunkToVehicles.get(var3);
      if (var4 != null) {
         for (int var5 = 0; var5 < var4.size(); var5++) {
            VehicleBuffer var6 = (VehicleBuffer)var4.get(var5);
            var6.m_bb.rewind();
            boolean var7 = var6.m_bb.get() == 1;
            int var8 = var6.m_bb.getInt();
            var2.accept(var1, var6);
         }
      }
   }

   void loadChunk(int var1, int var2, ThrowingConsumer<VehicleBuffer, IOException> var3) throws IOException {
      int var4 = var2 << 16 | var1;
      ArrayList var5 = (ArrayList)this.m_ChunkToVehicles.get(var4);
      if (var5 != null) {
         for (int var6 = 0; var6 < var5.size(); var6++) {
            VehicleBuffer var7 = (VehicleBuffer)var5.get(var6);
            var7.m_bb.rewind();
            boolean var8 = var7.m_bb.get() == 1;
            int var9 = var7.m_bb.getInt();
            var3.accept(var7);
         }
      }
   }

   void updateVehicle(VehicleBuffer var1) {
      if (!$assertionsDisabled && var1.m_id < 1) {
         throw new AssertionError();
      } else {
         synchronized (VehiclesDB2.instance.m_main.m_usedIDs) {
            if (!$assertionsDisabled && !VehiclesDB2.instance.m_main.m_usedIDs.contains(var1.m_id)) {
               throw new AssertionError();
            }
         }

         var1.m_bb.rewind();
         VehicleBuffer var5 = (VehicleBuffer)this.m_IDToVehicle.get(var1.m_id);
         if (var5 == null) {
            var5 = new VehicleBuffer();
            var5.m_id = var1.m_id;
            this.m_IDToVehicle.put(var1.m_id, var5);
         } else {
            int var3 = var5.m_wy << 16 | var5.m_wx;
            ((ArrayList)this.m_ChunkToVehicles.get(var3)).remove(var5);
         }

         var5.m_wx = var1.m_wx;
         var5.m_wy = var1.m_wy;
         var5.m_x = var1.m_x;
         var5.m_y = var1.m_y;
         var5.m_WorldVersion = var1.m_WorldVersion;
         var5.setBytes(var1.m_bb);
         int var6 = var5.m_wy << 16 | var5.m_wx;
         if (this.m_ChunkToVehicles.get(var6) == null) {
            this.m_ChunkToVehicles.put(var6, new ArrayList());
         }

         ((ArrayList)this.m_ChunkToVehicles.get(var6)).add(var5);
      }
   }

   void removeVehicle(int var1) {
      VehicleBuffer var2 = (VehicleBuffer)this.m_IDToVehicle.remove(var1);
      if (var2 != null) {
         int var3 = var2.m_wy << 16 | var2.m_wx;
         ((ArrayList)this.m_ChunkToVehicles.get(var3)).remove(var2);
      }
   }
}
