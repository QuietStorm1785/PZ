package zombie;

import zombie.SandboxOptions.BooleanSandboxOption;
import zombie.SandboxOptions.EnumSandboxOption;

public final class SandboxOptions$ZombieLore {
   public final EnumSandboxOption Speed;
   public final EnumSandboxOption Strength;
   public final EnumSandboxOption Toughness;
   public final EnumSandboxOption Transmission;
   public final EnumSandboxOption Mortality;
   public final EnumSandboxOption Reanimate;
   public final EnumSandboxOption Cognition;
   public final EnumSandboxOption CrawlUnderVehicle;
   public final EnumSandboxOption Memory;
   public final EnumSandboxOption Sight;
   public final EnumSandboxOption Hearing;
   public final BooleanSandboxOption ThumpNoChasing;
   public final BooleanSandboxOption ThumpOnConstruction;
   public final EnumSandboxOption ActiveOnly;
   public final BooleanSandboxOption TriggerHouseAlarm;
   public final BooleanSandboxOption ZombiesDragDown;
   public final BooleanSandboxOption ZombiesFenceLunge;
   public final EnumSandboxOption DisableFakeDead;

   private SandboxOptions$ZombieLore(SandboxOptions var1) {
      this.this$0 = var1;
      this.Speed = (EnumSandboxOption)var1.newEnumOption("ZombieLore.Speed", 4, 2).setTranslation("ZSpeed");
      this.Strength = (EnumSandboxOption)var1.newEnumOption("ZombieLore.Strength", 4, 2).setTranslation("ZStrength");
      this.Toughness = (EnumSandboxOption)var1.newEnumOption("ZombieLore.Toughness", 4, 2).setTranslation("ZToughness");
      this.Transmission = (EnumSandboxOption)var1.newEnumOption("ZombieLore.Transmission", 4, 1).setTranslation("ZTransmission");
      this.Mortality = (EnumSandboxOption)var1.newEnumOption("ZombieLore.Mortality", 7, 5).setTranslation("ZInfectionMortality");
      this.Reanimate = (EnumSandboxOption)var1.newEnumOption("ZombieLore.Reanimate", 6, 3).setTranslation("ZReanimateTime");
      this.Cognition = (EnumSandboxOption)var1.newEnumOption("ZombieLore.Cognition", 4, 3).setTranslation("ZCognition");
      this.CrawlUnderVehicle = (EnumSandboxOption)var1.newEnumOption("ZombieLore.CrawlUnderVehicle", 7, 5).setTranslation("ZCrawlUnderVehicle");
      this.Memory = (EnumSandboxOption)var1.newEnumOption("ZombieLore.Memory", 5, 2).setTranslation("ZMemory");
      this.Sight = (EnumSandboxOption)var1.newEnumOption("ZombieLore.Sight", 4, 2).setTranslation("ZSight");
      this.Hearing = (EnumSandboxOption)var1.newEnumOption("ZombieLore.Hearing", 4, 2).setTranslation("ZHearing");
      this.ThumpNoChasing = var1.newBooleanOption("ZombieLore.ThumpNoChasing", false);
      this.ThumpOnConstruction = var1.newBooleanOption("ZombieLore.ThumpOnConstruction", true);
      this.ActiveOnly = (EnumSandboxOption)var1.newEnumOption("ZombieLore.ActiveOnly", 3, 1).setTranslation("ActiveOnly");
      this.TriggerHouseAlarm = var1.newBooleanOption("ZombieLore.TriggerHouseAlarm", false);
      this.ZombiesDragDown = var1.newBooleanOption("ZombieLore.ZombiesDragDown", true);
      this.ZombiesFenceLunge = var1.newBooleanOption("ZombieLore.ZombiesFenceLunge", true);
      this.DisableFakeDead = var1.newEnumOption("ZombieLore.DisableFakeDead", 3, 1);
   }
}
