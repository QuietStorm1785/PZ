package zombie.network;

public class MPStatistic$ServerCellStatistic {
   protected long added = 0L;
   protected long canceled = 0L;

   public void Clear() {
      this.added = 0L;
      this.canceled = 0L;
   }

   public String PrintTitle(String var1) {
      return var1 + "Added; " + var1 + "Canceled; ";
   }

   public String Print() {
      return this.added + "; " + this.canceled + "; ";
   }

   public void Added() {
      this.added++;
   }

   public void Added(int var1) {
      this.added += var1;
   }

   public void Canceled() {
      this.canceled++;
   }
}
