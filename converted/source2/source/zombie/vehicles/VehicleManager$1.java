package zombie.vehicles;

import zombie.vehicles.BaseVehicle.engineStateTypes;

// $VF: synthetic class
class VehicleManager$1 {
   static {
      try {
         $SwitchMap$zombie$vehicles$BaseVehicle$engineStateTypes[engineStateTypes.Idle.ordinal()] = 1;
      } catch (NoSuchFieldError var9) {
      }

      try {
         $SwitchMap$zombie$vehicles$BaseVehicle$engineStateTypes[engineStateTypes.Starting.ordinal()] = 2;
      } catch (NoSuchFieldError var8) {
      }

      try {
         $SwitchMap$zombie$vehicles$BaseVehicle$engineStateTypes[engineStateTypes.RetryingStarting.ordinal()] = 3;
      } catch (NoSuchFieldError var7) {
      }

      try {
         $SwitchMap$zombie$vehicles$BaseVehicle$engineStateTypes[engineStateTypes.StartingSuccess.ordinal()] = 4;
      } catch (NoSuchFieldError var6) {
      }

      try {
         $SwitchMap$zombie$vehicles$BaseVehicle$engineStateTypes[engineStateTypes.StartingFailed.ordinal()] = 5;
      } catch (NoSuchFieldError var5) {
      }

      try {
         $SwitchMap$zombie$vehicles$BaseVehicle$engineStateTypes[engineStateTypes.StartingFailedNoPower.ordinal()] = 6;
      } catch (NoSuchFieldError var4) {
      }

      try {
         $SwitchMap$zombie$vehicles$BaseVehicle$engineStateTypes[engineStateTypes.Running.ordinal()] = 7;
      } catch (NoSuchFieldError var3) {
      }

      try {
         $SwitchMap$zombie$vehicles$BaseVehicle$engineStateTypes[engineStateTypes.Stalling.ordinal()] = 8;
      } catch (NoSuchFieldError var2) {
      }

      try {
         $SwitchMap$zombie$vehicles$BaseVehicle$engineStateTypes[engineStateTypes.ShutingDown.ordinal()] = 9;
      } catch (NoSuchFieldError var1) {
      }
   }
}
