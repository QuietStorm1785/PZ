package zombie.erosion.categories;

import java.util.ArrayList;
import zombie.erosion.ErosionData.Chunk;
import zombie.erosion.ErosionData.Square;
import zombie.erosion.categories.ErosionCategory.Data;
import zombie.erosion.categories.StreetCracks.CategoryData;
import zombie.erosion.obj.ErosionObj;
import zombie.erosion.obj.ErosionObjOverlay;
import zombie.erosion.obj.ErosionObjOverlaySprites;
import zombie.erosion.obj.ErosionObjSprites;
import zombie.iso.IsoGridSquare;
import zombie.iso.IsoObject;

public final class StreetCracks extends ErosionCategory {
   private ArrayList<ErosionObj> objs = new ArrayList<>();
   private ArrayList<ErosionObjOverlay> crackObjs = new ArrayList<>();
   private int[] spawnChance = new int[100];

   public boolean replaceExistingObject(IsoGridSquare var1, Square var2, Chunk var3, boolean var4, boolean var5) {
      return false;
   }

   public boolean validateSpawn(IsoGridSquare var1, Square var2, Chunk var3, boolean var4, boolean var5, boolean var6) {
      int var7 = var2.noiseMainInt;
      int var8 = this.spawnChance[var7];
      if (var8 == 0) {
         return false;
      } else if (var2.rand(var1.x, var1.y, 101) >= var8) {
         return false;
      } else {
         CategoryData var9 = (CategoryData)this.setCatModData(var2);
         var9.gameObj = var2.rand(var1.x, var1.y, this.crackObjs.size());
         var9.maxStage = var7 > 65 ? 2 : (var7 > 55 ? 1 : 0);
         var9.stage = 0;
         var9.spawnTime = 50 + (100 - var7);
         if (var2.magicNum > 0.5F) {
            var9.hasGrass = true;
         }

         return true;
      }
   }

   public void update(IsoGridSquare var1, Square var2, Data var3, Chunk var4, int var5) {
      CategoryData var6 = (CategoryData)var3;
      if (var5 >= var6.spawnTime && !var6.doNothing) {
         IsoObject var7 = var1.getFloor();
         if (var6.gameObj >= 0 && var6.gameObj < this.crackObjs.size() && var7 != null) {
            ErosionObjOverlay var8 = this.crackObjs.get(var6.gameObj);
            int var9 = var6.maxStage;
            int var10 = (int)Math.floor((var5 - var6.spawnTime) / (var8.cycleTime / (var9 + 1.0F)));
            if (var10 < var6.stage) {
               var10 = var6.stage;
            }

            if (var10 >= var8.stages) {
               var10 = var8.stages - 1;
            }

            if (var10 != var6.stage) {
               int var11 = var6.curID;
               int var12 = var8.setOverlay(var7, var11, var10, 0, 0.0F);
               if (var12 >= 0) {
                  var6.curID = var12;
               }

               var6.stage = var10;
            } else if (!var6.hasGrass && var10 == var8.stages - 1) {
               var6.doNothing = true;
            }

            if (var6.hasGrass) {
               ErosionObj var15 = this.objs.get(var6.gameObj);
               if (var15 != null) {
                  int var16 = this.currentSeason(var2.magicNum, var15);
                  boolean var13 = false;
                  boolean var14 = false;
                  this.updateObj(var2, var3, var1, var15, var13, var10, var16, var14);
               }
            }
         } else {
            var6.doNothing = true;
         }
      }
   }

   public void init() {
      for (int var1 = 0; var1 < 100; var1++) {
         this.spawnChance[var1] = var1 >= 40 ? (int)this.clerp((var1 - 40) / 60.0F, 0.0F, 60.0F) : 0;
      }

      this.seasonDisp[5].season1 = 5;
      this.seasonDisp[5].season2 = 0;
      this.seasonDisp[5].split = false;
      this.seasonDisp[1].season1 = 1;
      this.seasonDisp[1].season2 = 0;
      this.seasonDisp[1].split = false;
      this.seasonDisp[2].season1 = 2;
      this.seasonDisp[2].season2 = 4;
      this.seasonDisp[2].split = true;
      this.seasonDisp[4].season1 = 4;
      this.seasonDisp[4].season2 = 5;
      this.seasonDisp[4].split = true;
      String var9 = "d_streetcracks_1_";
      int[] var2 = new int[]{5, 1, 2, 4};

      for (int var3 = 0; var3 <= 7; var3++) {
         ErosionObjOverlaySprites var4 = new ErosionObjOverlaySprites(3, "StreeCracks");
         ErosionObjSprites var5 = new ErosionObjSprites(3, "CrackGrass", false, false, false);

         for (int var6 = 0; var6 <= 2; var6++) {
            for (int var7 = 0; var7 <= var2.length; var7++) {
               int var8 = var7 * 24 + var6 * 8 + var3;
               if (var7 == 0) {
                  var4.setSprite(var6, var9 + var8, 0);
               } else {
                  var5.setBase(var6, var9 + var8, var2[var7 - 1]);
               }
            }
         }

         this.crackObjs.add(new ErosionObjOverlay(var4, 60, false));
         this.objs.add(new ErosionObj(var5, 60, 0.0F, 0.0F, false));
      }
   }

   protected Data allocData() {
      return new CategoryData();
   }

   public void getObjectNames(ArrayList<String> var1) {
      for (int var2 = 0; var2 < this.objs.size(); var2++) {
         if (this.objs.get(var2).name != null && !var1.contains(this.objs.get(var2).name)) {
            var1.add(this.objs.get(var2).name);
         }
      }
   }
}
