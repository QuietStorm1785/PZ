package zombie.network;

public class MPStatistic$ProbeStatistic {
   protected boolean started = false;
   protected long timeStart = 0L;
   protected long timeWork = 0L;
   protected long timeMax = 0L;
   protected long timeCount = 0L;

   public void Clear() {
      this.timeWork = 0L;
      this.timeMax = 0L;
      this.timeCount = 0L;
   }

   public String PrintTitle(String var1) {
      return var1 + "Work; " + var1 + "Max; " + var1 + "Count;";
   }

   public String Print() {
      return this.timeWork / 1000000L + "; " + this.timeMax / 1000000L + "; " + this.timeCount + "; ";
   }

   public void Start() {
      this.timeStart = System.nanoTime();
      this.timeCount++;
      this.started = true;
   }

   public void End() {
      if (this.started) {
         long var1 = System.nanoTime() - this.timeStart;
         this.timeWork += var1;
         if (this.timeMax < var1) {
            this.timeMax = var1;
         }

         this.started = false;
      }
   }
}
