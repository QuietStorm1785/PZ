package zombie.scripting.objects;

import java.util.ArrayList;

public final class Recipe$Source {
   public boolean keep = false;
   private final ArrayList<String> items = new ArrayList<>();
   public boolean destroy = false;
   public float count = 1.0F;
   public float use = 0.0F;

   public boolean isDestroy() {
      return this.destroy;
   }

   public void setDestroy(boolean var1) {
      this.destroy = var1;
   }

   public boolean isKeep() {
      return this.keep;
   }

   public void setKeep(boolean var1) {
      this.keep = var1;
   }

   public float getCount() {
      return this.count;
   }

   public void setCount(float var1) {
      this.count = var1;
   }

   public float getUse() {
      return this.use;
   }

   public void setUse(float var1) {
      this.use = var1;
   }

   public ArrayList<String> getItems() {
      return this.items;
   }

   public String getOnlyItem() {
      if (this.items.size() != 1) {
         throw new RuntimeException("items.size() == " + this.items.size());
      } else {
         return this.items.get(0);
      }
   }
}
