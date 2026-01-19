package zombie.iso.weather;

class ClimateManager$ClimateNetInfo {
   public boolean IsStopWeather = false;
   public boolean IsTrigger = false;
   public boolean IsGenerate = false;
   public float TriggerDuration = 0.0F;
   public boolean TriggerStorm = false;
   public boolean TriggerTropical = false;
   public boolean TriggerBlizzard = false;
   public float GenerateStrength = 0.0F;
   public int GenerateFront = 0;

   private ClimateManager$ClimateNetInfo() {
   }

   private void reset() {
      this.IsStopWeather = false;
      this.IsTrigger = false;
      this.IsGenerate = false;
      this.TriggerDuration = 0.0F;
      this.TriggerStorm = false;
      this.TriggerTropical = false;
      this.TriggerBlizzard = false;
      this.GenerateStrength = 0.0F;
      this.GenerateFront = 0;
   }
}
