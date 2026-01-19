package zombie.vehicles;

import zombie.util.PooledObject;

abstract class VehiclesDB2$QueueItem extends PooledObject {
   private VehiclesDB2$QueueItem() {
   }

   abstract void processMain();

   abstract void processWorldStreamer();
}
