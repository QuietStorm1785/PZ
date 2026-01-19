package zombie.util;

class ExecuteTimeAnalyse$TimeStamp {
   long time;
   String comment;

   public ExecuteTimeAnalyse$TimeStamp(String var1) {
      this.comment = var1;
      this.time = System.nanoTime();
   }

   public ExecuteTimeAnalyse$TimeStamp() {
   }
}
