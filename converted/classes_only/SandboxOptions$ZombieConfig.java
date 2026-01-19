package zombie;

import zombie.SandboxOptions.DoubleSandboxOption;
import zombie.SandboxOptions.IntegerSandboxOption;

public final class SandboxOptions$ZombieConfig {
   public final DoubleSandboxOption PopulationMultiplier;
   public final DoubleSandboxOption PopulationStartMultiplier;
   public final DoubleSandboxOption PopulationPeakMultiplier;
   public final IntegerSandboxOption PopulationPeakDay;
   public final DoubleSandboxOption RespawnHours;
   public final DoubleSandboxOption RespawnUnseenHours;
   public final DoubleSandboxOption RespawnMultiplier;
   public final DoubleSandboxOption RedistributeHours;
   public final IntegerSandboxOption FollowSoundDistance;
   public final IntegerSandboxOption RallyGroupSize;
   public final IntegerSandboxOption RallyTravelDistance;
   public final IntegerSandboxOption RallyGroupSeparation;
   public final IntegerSandboxOption RallyGroupRadius;

   private SandboxOptions$ZombieConfig(SandboxOptions var1) {
      this.this$0 = var1;
      this.PopulationMultiplier = var1.newDoubleOption("ZombieConfig.PopulationMultiplier", 0.0, 4.0, 1.0);
      this.PopulationStartMultiplier = var1.newDoubleOption("ZombieConfig.PopulationStartMultiplier", 0.0, 4.0, 1.0);
      this.PopulationPeakMultiplier = var1.newDoubleOption("ZombieConfig.PopulationPeakMultiplier", 0.0, 4.0, 1.5);
      this.PopulationPeakDay = var1.newIntegerOption("ZombieConfig.PopulationPeakDay", 1, 365, 28);
      this.RespawnHours = var1.newDoubleOption("ZombieConfig.RespawnHours", 0.0, 8760.0, 72.0);
      this.RespawnUnseenHours = var1.newDoubleOption("ZombieConfig.RespawnUnseenHours", 0.0, 8760.0, 16.0);
      this.RespawnMultiplier = var1.newDoubleOption("ZombieConfig.RespawnMultiplier", 0.0, 1.0, 0.1);
      this.RedistributeHours = var1.newDoubleOption("ZombieConfig.RedistributeHours", 0.0, 8760.0, 12.0);
      this.FollowSoundDistance = var1.newIntegerOption("ZombieConfig.FollowSoundDistance", 10, 1000, 100);
      this.RallyGroupSize = var1.newIntegerOption("ZombieConfig.RallyGroupSize", 0, 1000, 20);
      this.RallyTravelDistance = var1.newIntegerOption("ZombieConfig.RallyTravelDistance", 5, 50, 20);
      this.RallyGroupSeparation = var1.newIntegerOption("ZombieConfig.RallyGroupSeparation", 5, 25, 15);
      this.RallyGroupRadius = var1.newIntegerOption("ZombieConfig.RallyGroupRadius", 1, 10, 3);
   }
}
