package zombie.vehicles;

import zombie.util.Pool;
import zombie.vehicles.VehiclesDB2.QueueItem;

class VehiclesDB2$QueueRemoveVehicle extends QueueItem {
   static final Pool<VehiclesDB2$QueueRemoveVehicle> s_pool = new Pool(VehiclesDB2$QueueRemoveVehicle::new);
   int m_id;

   private VehiclesDB2$QueueRemoveVehicle() {
   }

   void init(BaseVehicle var1) {
      this.m_id = var1.sqlID;
   }

   void processMain() {
   }

   void processWorldStreamer() {
      VehiclesDB2.instance.m_worldStreamer.m_store.removeVehicle(this.m_id);
   }
}
