package zombie.iso;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.function.BiConsumer;
import java.util.function.Predicate;
import org.joml.Vector2f;
import zombie.iso.RoomDef.RoomRect;
import zombie.iso.areas.IsoRoom;
import zombie.network.GameServer;
import zombie.network.ServerMap;
import zombie.util.list.PZArrayUtil;

public final class RoomDef {
   private static final ArrayList<IsoGridSquare> squareChoices = new ArrayList<>();
   public boolean bExplored = false;
   public boolean bDoneSpawn = false;
   public int IndoorZombies = 0;
   public int spawnCount = -1;
   public boolean bLightsActive = false;
   public String name;
   public int level;
   public BuildingDef building;
   public int ID = -1;
   public final ArrayList<RoomRect> rects = new ArrayList<>(1);
   public final ArrayList<MetaObject> objects = new ArrayList<>(0);
   public int x = 100000;
   public int y = 100000;
   public int x2 = -10000;
   public int y2 = -10000;
   public int area;
   private final HashMap<String, Integer> proceduralSpawnedContainer = new HashMap<>();
   private boolean roofFixed = false;
   public long metaID;

   public RoomDef(int var1, String var2) {
      this.ID = var1;
      this.name = var2;
   }

   public int getID() {
      return this.ID;
   }

   public boolean isExplored() {
      return this.bExplored;
   }

   public boolean isInside(int var1, int var2, int var3) {
      int var4 = this.building.x;
      int var5 = this.building.y;

      for (int var6 = 0; var6 < this.rects.size(); var6++) {
         int var7 = this.rects.get(var6).x;
         int var8 = this.rects.get(var6).y;
         int var9 = this.rects.get(var6).getX2();
         int var10 = this.rects.get(var6).getY2();
         if (var1 >= var7 && var2 >= var8 && var1 < var9 && var2 < var10 && var3 == this.level) {
            return true;
         }
      }

      return false;
   }

   public boolean intersects(int var1, int var2, int var3, int var4) {
      for (int var5 = 0; var5 < this.rects.size(); var5++) {
         RoomRect var6 = this.rects.get(var5);
         if (var1 + var3 > var6.getX() && var1 < var6.getX2() && var2 + var4 > var6.getY() && var2 < var6.getY2()) {
            return true;
         }
      }

      return false;
   }

   public float getAreaOverlapping(IsoChunk var1) {
      return this.getAreaOverlapping(var1.wx * 10, var1.wy * 10, 10, 10);
   }

   public float getAreaOverlapping(int var1, int var2, int var3, int var4) {
      int var5 = 0;
      int var6 = 0;

      for (int var7 = 0; var7 < this.rects.size(); var7++) {
         RoomRect var8 = this.rects.get(var7);
         var5 += var8.w * var8.h;
         int var9 = Math.max(var1, var8.x);
         int var10 = Math.max(var2, var8.y);
         int var11 = Math.min(var1 + var3, var8.x + var8.w);
         int var12 = Math.min(var2 + var4, var8.y + var8.h);
         if (var11 >= var9 && var12 >= var10) {
            var6 += (var11 - var9) * (var12 - var10);
         }
      }

      return var6 <= 0 ? 0.0F : (float)var6 / var5;
   }

   public void forEachChunk(BiConsumer<RoomDef, IsoChunk> var1) {
      HashSet var2 = new HashSet();

      for (int var3 = 0; var3 < this.rects.size(); var3++) {
         RoomRect var4 = this.rects.get(var3);
         int var5 = var4.x / 10;
         int var6 = var4.y / 10;
         int var7 = (var4.x + var4.w) / 10;
         int var8 = (var4.y + var4.h) / 10;
         if ((var4.x + var4.w) % 10 == 0) {
            var7--;
         }

         if ((var4.y + var4.h) % 10 == 0) {
            var8--;
         }

         for (int var9 = var6; var9 <= var8; var9++) {
            for (int var10 = var5; var10 <= var7; var10++) {
               IsoChunk var11 = GameServer.bServer ? ServerMap.instance.getChunk(var10, var9) : IsoWorld.instance.CurrentCell.getChunk(var10, var9);
               if (var11 != null) {
                  var2.add(var11);
               }
            }
         }
      }

      var2.forEach(var2x -> var1.accept(this, var2x));
      var2.clear();
   }

   public IsoRoom getIsoRoom() {
      return IsoWorld.instance.MetaGrid.getMetaGridFromTile(this.x, this.y).info.getRoom(this.ID);
   }

   public ArrayList<MetaObject> getObjects() {
      return this.objects;
   }

   public ArrayList<MetaObject> getMetaObjects() {
      return this.objects;
   }

   public void refreshSquares() {
      this.getIsoRoom().refreshSquares();
   }

   public BuildingDef getBuilding() {
      return this.building;
   }

   public void setBuilding(BuildingDef var1) {
      this.building = var1;
   }

   public String getName() {
      return this.name;
   }

   public ArrayList<RoomRect> getRects() {
      return this.rects;
   }

   public int getY() {
      return this.y;
   }

   public int getX() {
      return this.x;
   }

   public int getX2() {
      return this.x2;
   }

   public int getY2() {
      return this.y2;
   }

   public int getW() {
      return this.x2 - this.x;
   }

   public int getH() {
      return this.y2 - this.y;
   }

   public int getZ() {
      return this.level;
   }

   public void CalculateBounds() {
      for (int var1 = 0; var1 < this.rects.size(); var1++) {
         RoomRect var2 = this.rects.get(var1);
         if (var2.x < this.x) {
            this.x = var2.x;
         }

         if (var2.y < this.y) {
            this.y = var2.y;
         }

         if (var2.x + var2.w > this.x2) {
            this.x2 = var2.x + var2.w;
         }

         if (var2.y + var2.h > this.y2) {
            this.y2 = var2.y + var2.h;
         }

         this.area = this.area + var2.w * var2.h;
      }
   }

   public long calculateMetaID(int var1, int var2) {
      int var3 = Integer.MAX_VALUE;
      int var4 = Integer.MAX_VALUE;

      for (int var5 = 0; var5 < this.rects.size(); var5++) {
         RoomRect var6 = this.rects.get(var5);
         if (var6.x <= var3 && var6.y < var4) {
            var3 = var6.x;
            var4 = var6.y;
         }
      }

      var3 -= var1 * 300;
      var4 -= var2 * 300;
      return (long)this.level << 32 | (long)var4 << 16 | var3;
   }

   public int getArea() {
      return this.area;
   }

   public void setExplored(boolean var1) {
      this.bExplored = var1;
   }

   public IsoGridSquare getFreeSquare() {
      return this.getRandomSquare(var0 -> var0.isFree(false));
   }

   public IsoGridSquare getRandomSquare(Predicate<IsoGridSquare> var1) {
      squareChoices.clear();

      for (int var2 = 0; var2 < this.rects.size(); var2++) {
         RoomRect var3 = this.rects.get(var2);

         for (int var4 = var3.getX(); var4 < var3.getX2(); var4++) {
            for (int var5 = var3.getY(); var5 < var3.getY2(); var5++) {
               IsoGridSquare var6 = IsoWorld.instance.CurrentCell.getGridSquare(var4, var5, this.getZ());
               if (var6 != null && var1 != null && var1.test(var6) || var1 == null) {
                  squareChoices.add(var6);
               }
            }
         }
      }

      return (IsoGridSquare)PZArrayUtil.pickRandom(squareChoices);
   }

   public boolean isEmptyOutside() {
      return "emptyoutside".equalsIgnoreCase(this.name);
   }

   public HashMap<String, Integer> getProceduralSpawnedContainer() {
      return this.proceduralSpawnedContainer;
   }

   public boolean isRoofFixed() {
      return this.roofFixed;
   }

   public void setRoofFixed(boolean var1) {
      this.roofFixed = var1;
   }

   public float getClosestPoint(float var1, float var2, Vector2f var3) {
      float var4 = Float.MAX_VALUE;
      Vector2f var5 = new Vector2f();

      for (int var6 = 0; var6 < this.rects.size(); var6++) {
         RoomRect var7 = this.rects.get(var6);
         float var8 = var7.getClosestPoint(var1, var2, var5);
         if (var8 < var4) {
            var4 = var8;
            var3.set(var5);
         }
      }

      return var4;
   }

   public void Dispose() {
      this.building = null;
      this.rects.clear();
      this.objects.clear();
      this.proceduralSpawnedContainer.clear();
   }
}
