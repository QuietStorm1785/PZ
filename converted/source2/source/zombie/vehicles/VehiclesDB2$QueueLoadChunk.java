package zombie.vehicles;

import java.io.IOException;
import java.util.ArrayList;
import zombie.core.logger.ExceptionLogger;
import zombie.debug.DebugLog;
import zombie.iso.IsoChunk;
import zombie.iso.IsoGridSquare;
import zombie.iso.IsoWorld;
import zombie.iso.IsoChunk.JobType;
import zombie.network.ServerMap;
import zombie.util.Pool;
import zombie.vehicles.VehiclesDB2.QueueItem;
import zombie.vehicles.VehiclesDB2.VehicleBuffer;

class VehiclesDB2$QueueLoadChunk extends QueueItem {
   static final Pool<VehiclesDB2$QueueLoadChunk> s_pool = new Pool(VehiclesDB2$QueueLoadChunk::new);
   int m_wx;
   int m_wy;
   final ArrayList<BaseVehicle> m_vehicles = new ArrayList<>();
   IsoGridSquare m_dummySquare;

   private VehiclesDB2$QueueLoadChunk() {
   }

   void init(int var1, int var2) {
      this.m_wx = var1;
      this.m_wy = var2;
      this.m_vehicles.clear();
      if (this.m_dummySquare == null) {
         this.m_dummySquare = IsoGridSquare.getNew(IsoWorld.instance.CurrentCell, null, 0, 0, 0);
      }
   }

   void processMain() {
      IsoChunk var1 = ServerMap.instance.getChunk(this.m_wx, this.m_wy);
      if (var1 == null) {
         this.m_vehicles.clear();
      } else if (var1.m_loadVehiclesObject != this) {
         this.m_vehicles.clear();
      } else {
         var1.m_loadVehiclesObject = null;

         for (int var2 = 0; var2 < this.m_vehicles.size(); var2++) {
            BaseVehicle var3 = this.m_vehicles.get(var2);
            IsoGridSquare var4 = var1.getGridSquare((int)(var3.x - var1.wx * 10), (int)(var3.y - var1.wy * 10), 0);
            var3.setSquare(var4);
            var3.setCurrent(var4);
            var3.chunk = var1;
            if (var1.jobType == JobType.SoftReset) {
               var3.softReset();
            }

            if (!var3.addedToWorld && VehiclesDB2.instance.isVehicleLoaded(var3)) {
               var3.removeFromSquare();
               this.m_vehicles.remove(var2);
               var2--;
            } else {
               var1.vehicles.add(var3);
               if (!var3.addedToWorld) {
                  var3.addToWorld();
               }
            }
         }

         this.m_vehicles.clear();
      }
   }

   void processWorldStreamer() {
      try {
         VehiclesDB2.instance.m_worldStreamer.m_store.loadChunk(this.m_wx, this.m_wy, this::vehicleLoaded);
      } catch (Exception var2) {
         ExceptionLogger.logException(var2);
      }
   }

   void vehicleLoaded(VehicleBuffer var1) throws IOException {
      if (!$assertionsDisabled && var1.m_id < 1) {
         throw new AssertionError();
      } else {
         int var2 = (int)(var1.m_x - this.m_wx * 10);
         int var3 = (int)(var1.m_y - this.m_wy * 10);
         this.m_dummySquare.x = var2;
         this.m_dummySquare.y = var3;
         IsoGridSquare var4 = this.m_dummySquare;
         BaseVehicle var5 = new BaseVehicle(IsoWorld.instance.CurrentCell);
         var5.setSquare(var4);
         var5.setCurrent(var4);

         try {
            var5.load(var1.m_bb, var1.m_WorldVersion);
         } catch (Exception var7) {
            ExceptionLogger.logException(var7);
            DebugLog.General.error("vehicle %d is being deleted because an error occurred loading it", new Object[]{var1.m_id});
            VehiclesDB2.instance.m_worldStreamer.m_store.removeVehicle(var1.m_id);
            return;
         }

         var5.sqlID = var1.m_id;
         this.m_vehicles.add(var5);
      }
   }
}
