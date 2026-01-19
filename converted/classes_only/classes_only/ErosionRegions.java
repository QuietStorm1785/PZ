package zombie.erosion;

import java.util.ArrayList;
import zombie.erosion.ErosionRegions.Region;
import zombie.erosion.categories.ErosionCategory;
import zombie.erosion.categories.Flowerbed;
import zombie.erosion.categories.NatureBush;
import zombie.erosion.categories.NatureGeneric;
import zombie.erosion.categories.NaturePlants;
import zombie.erosion.categories.NatureTrees;
import zombie.erosion.categories.StreetCracks;
import zombie.erosion.categories.WallCracks;
import zombie.erosion.categories.WallVines;

public final class ErosionRegions {
   public static final int REGION_NATURE = 0;
   public static final int CATEGORY_TREES = 0;
   public static final int CATEGORY_BUSH = 1;
   public static final int CATEGORY_PLANTS = 2;
   public static final int CATEGORY_GENERIC = 3;
   public static final int REGION_STREET = 1;
   public static final int CATEGORY_STREET_CRACKS = 0;
   public static final int REGION_WALL = 2;
   public static final int CATEGORY_WALL_VINES = 0;
   public static final int CATEGORY_WALL_CRACKS = 1;
   public static final int REGION_FLOWERBED = 3;
   public static final int CATEGORY_FLOWERBED = 0;
   public static final ArrayList<Region> regions = new ArrayList<>();

   private static void addRegion(Region var0) {
      var0.ID = regions.size();
      regions.add(var0);
   }

   public static ErosionCategory getCategory(int var0, int var1) {
      return (ErosionCategory)regions.get(var0).categories.get(var1);
   }

   public static void init() {
      regions.clear();
      addRegion(
         new Region(0, "blends_natural_01", true, true, false)
            .addCategory(0, new NatureTrees())
            .addCategory(1, new NatureBush())
            .addCategory(2, new NaturePlants())
            .addCategory(3, new NatureGeneric())
      );
      addRegion(new Region(1, "blends_street", true, true, false).addCategory(0, new StreetCracks()));
      addRegion(new Region(2, null, false, false, true).addCategory(0, new WallVines()).addCategory(1, new WallCracks()));
      addRegion(new Region(3, null, true, true, false).addCategory(0, new Flowerbed()));

      for (int var0 = 0; var0 < regions.size(); var0++) {
         regions.get(var0).init();
      }
   }

   public static void Reset() {
      for (int var0 = 0; var0 < regions.size(); var0++) {
         regions.get(var0).Reset();
      }

      regions.clear();
   }
}
