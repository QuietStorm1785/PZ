package zombie.scripting.objects;

public final class Recipe$Result {
   public String module = null;
   public String type;
   public int count = 1;
   public int drainableCount = 0;

   public String getType() {
      return this.type;
   }

   public void setType(String var1) {
      this.type = var1;
   }

   public int getCount() {
      return this.count;
   }

   public void setCount(int var1) {
      this.count = var1;
   }

   public String getModule() {
      return this.module;
   }

   public void setModule(String var1) {
      this.module = var1;
   }

   public String getFullType() {
      return this.module + "." + this.type;
   }

   public int getDrainableCount() {
      return this.drainableCount;
   }

   public void setDrainableCount(int var1) {
      this.drainableCount = var1;
   }
}
