package zombie.erosion;

import java.util.ArrayList;
import zombie.erosion.categories.ErosionCategory;

public final class ErosionRegions$Region {
   public int ID;
   public String tileNameMatch;
   public boolean checkExterior;
   public boolean isExterior;
   public boolean hasWall;
   public final ArrayList<ErosionCategory> categories = new ArrayList<>();

   public ErosionRegions$Region(int var1, String var2, boolean var3, boolean var4, boolean var5) {
      this.ID = var1;
      this.tileNameMatch = var2;
      this.checkExterior = var3;
      this.isExterior = var4;
      this.hasWall = var5;
   }

   public ErosionRegions$Region addCategory(int var1, ErosionCategory var2) {
      var2.ID = var1;
      var2.region = this;
      this.categories.add(var2);
      return this;
   }

   public void init() {
      for (int var1 = 0; var1 < this.categories.size(); var1++) {
         this.categories.get(var1).init();
      }
   }

   public void Reset() {
      this.categories.clear();
   }
}
