package zombie.network;

public class MPStatistic$TasksStatistic {
   protected long added = 0L;
   protected long processed = 0L;

   public void Clear() {
      this.added = 0L;
      this.processed = 0L;
   }

   public String PrintTitle(String var1) {
      return var1 + "Added; " + var1 + "Processed; ";
   }

   public String Print() {
      return this.added + "; " + this.processed + "; ";
   }

   public void Added() {
      this.added++;
   }

   public void Processed() {
      this.processed++;
   }
}
