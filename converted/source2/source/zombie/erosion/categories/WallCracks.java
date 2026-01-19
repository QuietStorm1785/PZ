package zombie.erosion.categories;

import java.util.ArrayList;
import zombie.erosion.ErosionData.Chunk;
import zombie.erosion.ErosionData.Square;
import zombie.erosion.categories.ErosionCategory.Data;
import zombie.erosion.categories.WallCracks.CategoryData;
import zombie.erosion.obj.ErosionObjOverlay;
import zombie.erosion.obj.ErosionObjOverlaySprites;
import zombie.iso.IsoGridSquare;
import zombie.iso.IsoObject;
import zombie.iso.IsoWorld;

public final class WallCracks extends ErosionCategory {
   private ArrayList<ErosionObjOverlay> objs = new ArrayList<>();
   private static final int DIRNW = 0;
   private static final int DIRN = 1;
   private static final int DIRW = 2;
   private ArrayList<ArrayList<Integer>> objsRef = new ArrayList<>();
   private ArrayList<ArrayList<Integer>> botRef = new ArrayList<>();
   private ArrayList<ArrayList<Integer>> topRef = new ArrayList<>();
   private int[] spawnChance = new int[100];

   public boolean replaceExistingObject(IsoGridSquare var1, Square var2, Chunk var3, boolean var4, boolean var5) {
      return false;
   }

   public boolean validateSpawn(IsoGridSquare var1, Square var2, Chunk var3, boolean var4, boolean var5, boolean var6) {
      if (!var4) {
         return false;
      } else {
         int var7 = var2.noiseMainInt;
         int var8 = this.spawnChance[var7];
         if (var8 == 0) {
            return false;
         } else if (var2.rand(var1.x, var1.y, 101) >= var8) {
            return false;
         } else {
            byte var9 = -1;
            IsoObject var11 = this.validWall(var1, true, false);
            if (var11 != null) {
               String var10 = var11.getSprite().getName();
               if (var10 != null && var10.startsWith("fencing")) {
                  var11 = null;
               }
            }

            IsoObject var12 = this.validWall(var1, false, false);
            if (var12 != null) {
               String var20 = var12.getSprite().getName();
               if (var20 != null && var20.startsWith("fencing")) {
                  var12 = null;
               }
            }

            if (var11 != null && var12 != null) {
               var9 = 0;
            } else if (var11 != null) {
               var9 = 1;
            } else {
               if (var12 == null) {
                  return false;
               }

               var9 = 2;
            }

            boolean var13 = var7 < 35 && var2.magicNum > 0.3F;
            CategoryData var14 = (CategoryData)this.setCatModData(var2);
            var14.gameObj = this.objsRef.get(var9).get(var2.rand(var1.x, var1.y, this.objsRef.get(var9).size()));
            var14.alpha = 0.0F;
            var14.spawnTime = var7;
            if (var13) {
               IsoGridSquare var15 = IsoWorld.instance.CurrentCell.getGridSquare(var1.getX(), var1.getY(), var1.getZ() + 1);
               if (var15 != null) {
                  IsoObject var16 = this.validWall(var15, var9 == 1, false);
                  if (var16 != null) {
                     int var17 = var2.rand(var1.x, var1.y, this.botRef.get(var9).size());
                     var14.gameObj = this.botRef.get(var9).get(var17);
                     CategoryData var18 = new CategoryData();
                     var18.gameObj = this.topRef.get(var9).get(var17);
                     var18.alpha = 0.0F;
                     var18.spawnTime = var14.spawnTime;
                     var14.hasTop = var18;
                  }
               }
            }

            return true;
         }
      }
   }

   public void update(IsoGridSquare var1, Square var2, Data var3, Chunk var4, int var5) {
      CategoryData var6 = (CategoryData)var3;
      if (var5 >= var6.spawnTime && !var6.doNothing) {
         if (var6.gameObj >= 0 && var6.gameObj < this.objs.size()) {
            ErosionObjOverlay var7 = this.objs.get(var6.gameObj);
            float var8 = var6.alpha;
            float var9 = (var5 - var6.spawnTime) / 100.0F;
            if (var9 > 1.0F) {
               var9 = 1.0F;
            }

            if (var9 < 0.0F) {
               var9 = 0.0F;
            }

            if (var9 != var8) {
               IsoObject var10 = null;
               IsoObject var11 = this.validWall(var1, true, false);
               IsoObject var12 = this.validWall(var1, false, false);
               if (var11 != null && var12 != null) {
                  var10 = var11;
               } else if (var11 != null) {
                  var10 = var11;
               } else if (var12 != null) {
                  var10 = var12;
               }

               if (var10 != null) {
                  int var13 = var6.curID;
                  byte var14 = 0;
                  int var15 = var7.setOverlay(var10, var13, var14, 0, var9);
                  if (var15 >= 0) {
                     var6.alpha = var9;
                     var6.curID = var15;
                  }
               } else {
                  var6.doNothing = true;
               }

               if (var6.hasTop != null) {
                  IsoGridSquare var16 = IsoWorld.instance.CurrentCell.getGridSquare(var1.getX(), var1.getY(), var1.getZ() + 1);
                  if (var16 != null) {
                     this.update(var16, var2, var6.hasTop, var4, var5);
                  }
               }
            }
         } else {
            var6.doNothing = true;
         }
      }
   }

   public void init() {
      for (int var1 = 0; var1 < 100; var1++) {
         this.spawnChance[var1] = var1 <= 50 ? 100 : 0;
      }

      String var7 = "d_wallcracks_1_";
      int[] var2 = new int[]{2, 2, 2, 1, 1, 1, 0, 0, 0};

      for (int var3 = 0; var3 < 3; var3++) {
         this.objsRef.add(new ArrayList<>());
         this.topRef.add(new ArrayList<>());
         this.botRef.add(new ArrayList<>());
      }

      for (int var8 = 0; var8 < var2.length; var8++) {
         for (int var4 = 0; var4 <= 7; var4++) {
            int var5 = var4 * 9 + var8;
            ErosionObjOverlaySprites var6 = new ErosionObjOverlaySprites(1, "WallCracks");
            var6.setSprite(0, var7 + var5, 0);
            this.objs.add(new ErosionObjOverlay(var6, 60, true));
            this.objsRef.get(var2[var8]).add(this.objs.size() - 1);
            if (var4 == 0) {
               this.botRef.get(var2[var8]).add(this.objs.size() - 1);
            } else if (var4 == 1) {
               this.topRef.get(var2[var8]).add(this.objs.size() - 1);
            }
         }
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
