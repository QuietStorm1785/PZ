package zombie.vehicles;

import java.io.IOException;
import zombie.util.Pool;
import zombie.vehicles.VehiclesDB2.QueueItem;
import zombie.vehicles.VehiclesDB2.VehicleBuffer;

final class VehiclesDB2$QueueUpdateVehicle extends QueueItem {
   static final Pool<VehiclesDB2$QueueUpdateVehicle> s_pool = new Pool(VehiclesDB2$QueueUpdateVehicle::new);
   final VehicleBuffer m_vehicleBuffer = new VehicleBuffer();

   private VehiclesDB2$QueueUpdateVehicle() {
   }

   void init(BaseVehicle var1) throws IOException {
      this.m_vehicleBuffer.set(var1);
   }

   void processMain() {
   }

   void processWorldStreamer() {
      VehiclesDB2.instance.m_worldStreamer.m_store.updateVehicle(this.m_vehicleBuffer);
   }
}
