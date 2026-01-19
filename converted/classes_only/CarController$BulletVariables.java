package zombie.core.physics;

import zombie.vehicles.BaseVehicle;

public final class CarController$BulletVariables {
   float engineForce;
   float brakingForce;
   float vehicleSteering;
   BaseVehicle vehicle;

   CarController$BulletVariables set(BaseVehicle var1, float var2, float var3, float var4) {
      this.vehicle = var1;
      this.engineForce = var2;
      this.brakingForce = var3;
      this.vehicleSteering = var4;
      return this;
   }
}
