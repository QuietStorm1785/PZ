package zombie.characters;

import zombie.vehicles.BaseVehicle;

class IsoPlayer$VehicleContainer {
   BaseVehicle vehicle;
   int containerIndex;

   private IsoPlayer$VehicleContainer() {
   }

   public IsoPlayer$VehicleContainer set(BaseVehicle var1, int var2) {
      this.vehicle = var1;
      this.containerIndex = var2;
      return this;
   }

   @Override
   public boolean equals(Object var1) {
      return var1 instanceof IsoPlayer$VehicleContainer
         && this.vehicle == ((IsoPlayer$VehicleContainer)var1).vehicle
         && this.containerIndex == ((IsoPlayer$VehicleContainer)var1).containerIndex;
   }
}
