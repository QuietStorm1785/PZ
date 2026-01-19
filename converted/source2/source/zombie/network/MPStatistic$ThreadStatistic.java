package zombie.network;

public class MPStatistic$ThreadStatistic {
   protected boolean started = false;
   protected long timeStart = 0L;
   protected long timeWork = 0L;
   protected long timeMax = 0L;
   protected long timeSleep = 0L;
   protected long timeCount = 0L;

   public void Clear() {
      this.timeWork = 0L;
      this.timeMax = 0L;
      this.timeSleep = 0L;
      this.timeCount = 0L;
   }

   public String PrintTitle(String var1) {
      return var1 + "Work; " + var1 + "Max; " + var1 + "Sleep; " + var1 + "Count;";
   }

   public String Print() {
      return this.timeWork + "; " + this.timeMax + "; " + this.timeSleep + "; " + this.timeCount + "; ";
   }

   public void Start() {
      if (this.started) {
         this.End();
      }

      if (this.timeStart != 0L) {
         this.timeSleep = this.timeSleep + (System.currentTimeMillis() - this.timeStart);
      }

      this.timeStart = System.currentTimeMillis();
      this.timeCount++;
      this.started = true;
   }

   public void End() {
      if (this.timeStart != 0L && this.started) {
         long var1 = System.currentTimeMillis() - this.timeStart;
         this.timeStart = System.currentTimeMillis();
         this.timeWork += var1;
         if (this.timeMax < var1) {
            this.timeMax = var1;
         }

         this.started = false;
      }
   }
}
