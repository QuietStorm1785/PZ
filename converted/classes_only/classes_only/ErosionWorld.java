package zombie.erosion;

import zombie.erosion.ErosionData.Chunk;
import zombie.erosion.ErosionData.Square;
import zombie.erosion.ErosionRegions.Region;
import zombie.erosion.categories.ErosionCategory;
import zombie.erosion.categories.ErosionCategory.Data;
import zombie.iso.IsoGridSquare;
import zombie.iso.IsoObject;
import zombie.iso.SpriteDetails.IsoFlagType;
import zombie.iso.SpriteDetails.IsoObjectType;

public final class ErosionWorld {
   public boolean init() {
      ErosionRegions.init();
      return true;
   }

   public void validateSpawn(IsoGridSquare var1, Square var2, Chunk var3) {
      boolean var4 = var1.Is(IsoFlagType.exterior);
      boolean var5 = var1.Has(IsoObjectType.wall);
      IsoObject var6 = var1.getFloor();
      String var7 = var6 != null && var6.getSprite() != null ? var6.getSprite().getName() : null;
      if (var7 == null) {
         var2.doNothing = true;
      } else {
         boolean var8 = false;

         for (int var9 = 0; var9 < ErosionRegions.regions.size(); var9++) {
            Region var10 = (Region)ErosionRegions.regions.get(var9);
            String var11 = var10.tileNameMatch;
            if ((var11 == null || var7.startsWith(var11)) && (!var10.checkExterior || var10.isExterior == var4) && (!var10.hasWall || var10.hasWall == var5)) {
               for (int var12 = 0; var12 < var10.categories.size(); var12++) {
                  ErosionCategory var13 = (ErosionCategory)var10.categories.get(var12);
                  boolean var14 = var13.replaceExistingObject(var1, var2, var3, var4, var5);
                  if (!var14) {
                     var14 = var13.validateSpawn(var1, var2, var3, var4, var5, false);
                  }

                  if (var14) {
                     var8 = true;
                     break;
                  }
               }
            }
         }

         if (!var8) {
            var2.doNothing = true;
         }
      }
   }

   public void update(IsoGridSquare var1, Square var2, Chunk var3, int var4) {
      if (var2.regions != null) {
         for (int var5 = 0; var5 < var2.regions.size(); var5++) {
            Data var6 = (Data)var2.regions.get(var5);
            ErosionCategory var7 = ErosionRegions.getCategory(var6.regionID, var6.categoryID);
            int var8 = var2.regions.size();
            var7.update(var1, var2, var6, var3, var4);
            if (var8 > var2.regions.size()) {
               var5--;
            }
         }
      }
   }
}
