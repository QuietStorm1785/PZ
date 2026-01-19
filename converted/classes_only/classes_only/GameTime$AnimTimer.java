package zombie;

public class GameTime$AnimTimer {
   public float Elapsed;
   public float Duration;
   public boolean Finished = true;
   public int Ticks;

   public void init(int var1) {
      this.Ticks = var1;
      this.Elapsed = 0.0F;
      this.Duration = var1 * 1 / 30.0F;
      this.Finished = false;
   }

   public void update() {
      this.Elapsed = this.Elapsed + GameTime.instance.getMultipliedSecondsSinceLastUpdate() * 60.0F / 30.0F;
      if (this.Elapsed >= this.Duration) {
         this.Elapsed = this.Duration;
         this.Finished = true;
      }
   }

   public float ratio() {
      return this.Elapsed / this.Duration;
   }

   public boolean finished() {
      return this.Finished;
   }
}
