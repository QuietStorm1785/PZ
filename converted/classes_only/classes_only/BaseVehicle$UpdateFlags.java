package zombie.vehicles;

public class BaseVehicle$UpdateFlags {
   public static final short Full = 1;
   public static final short PositionOrientation = 2;
   public static final short Engine = 4;
   public static final short Lights = 8;
   public static final short PartModData = 16;
   public static final short PartUsedDelta = 32;
   public static final short PartModels = 64;
   public static final short PartItem = 128;
   public static final short PartWindow = 256;
   public static final short PartDoor = 512;
   public static final short Sounds = 1024;
   public static final short PartCondition = 2048;
   public static final short UpdateCarProperties = 4096;
   public static final short Authorization = 16384;
   public static final short AllPartFlags = 19440;

   protected BaseVehicle$UpdateFlags() {
   }
}
