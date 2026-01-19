package zombie.vehicles;

public enum BaseVehicle$engineStateTypes {
   Idle,
   Starting,
   RetryingStarting,
   StartingSuccess,
   StartingFailed,
   Running,
   Stalling,
   ShutingDown,
   StartingFailedNoPower;

   public static final BaseVehicle$engineStateTypes[] Values = values();
}
