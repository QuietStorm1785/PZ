package zombie.network;

import zombie.network.MPStatistic.ThreadStatistic;

public class MPStatistic$MainThreadStatistic extends ThreadStatistic {
   private long timeStartSleep;

   public MPStatistic$MainThreadStatistic(MPStatistic var1) {
      this.this$0 = var1;
      this.timeStartSleep = 0L;
   }

   public void Start() {
      if (this.timeStart == 0L) {
         this.timeStart = System.currentTimeMillis();
      } else {
         long var1 = System.currentTimeMillis() - this.timeStart;
         this.timeStart = System.currentTimeMillis();
         this.timeWork += var1;
         if (this.timeMax < var1) {
            this.timeMax = var1;
         }

         this.timeCount++;
      }
   }

   public void End() {
   }

   public void StartSleep() {
      this.timeStartSleep = System.currentTimeMillis();
   }

   public void EndSleep() {
      long var1 = System.currentTimeMillis() - this.timeStartSleep;
      this.timeSleep += var1;
      this.timeStart += var1;
   }
}
