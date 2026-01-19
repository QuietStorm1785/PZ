package zombie.iso;

import gnu.trove.list.array.TIntArrayList;
import java.nio.ByteBuffer;
import java.util.ArrayList;
import java.util.HashMap;
import org.joml.Vector2f;
import zombie.GameTime;
import zombie.characters.IsoGameCharacter.Location;
import zombie.core.Rand;
import zombie.core.network.ByteBufferWriter;
import zombie.debug.DebugLog;
import zombie.iso.IsoMetaGrid.ZoneGeometryType;
import zombie.iso.IsoMetaGrid.Zone.PolygonHit;
import zombie.network.GameClient;
import zombie.network.PacketTypes.PacketType;
import zombie.randomizedWorld.randomizedZoneStory.RandomizedZoneStoryBase;
import zombie.vehicles.BaseVehicle;
import zombie.vehicles.Clipper;
import zombie.vehicles.ClipperOffset;
import zombie.vehicles.ClipperOffset.EndType;
import zombie.vehicles.ClipperOffset.JoinType;
import zombie.vehicles.PolygonalMap2.LiangBarsky;

public class IsoMetaGrid$Zone {
   public Double id = 0.0;
   public int hourLastSeen = 0;
   public int lastActionTimestamp = 0;
   public boolean haveConstruction = false;
   public final HashMap<String, Integer> spawnedZombies = new HashMap<>();
   public String zombiesTypeToSpawn = null;
   public Boolean spawnSpecialZombies = null;
   public String name;
   public String type;
   public int x;
   public int y;
   public int z;
   public int w;
   public int h;
   public ZoneGeometryType geometryType = ZoneGeometryType.INVALID;
   public final TIntArrayList points = new TIntArrayList();
   private boolean bTriangulateFailed = false;
   public int polylineWidth = 0;
   public float[] polylineOutlinePoints;
   public float[] triangles;
   public float[] triangleAreas;
   public float totalArea = 0.0F;
   public int pickedXForZoneStory;
   public int pickedYForZoneStory;
   public RandomizedZoneStoryBase pickedRZStory;
   private String originalName;
   public boolean isPreferredZoneForSquare = false;
   static final LiangBarsky LIANG_BARSKY = new LiangBarsky();
   static final Vector2 L_lineSegmentIntersects = new Vector2();

   public IsoMetaGrid$Zone(String var1, String var2, int var3, int var4, int var5, int var6, int var7) {
      this.id = Rand.Next(9999999) + 100000.0;
      this.originalName = var1;
      this.name = var1;
      this.type = var2;
      this.x = var3;
      this.y = var4;
      this.z = var5;
      this.w = var6;
      this.h = var7;
   }

   public void setX(int var1) {
      this.x = var1;
   }

   public void setY(int var1) {
      this.y = var1;
   }

   public void setW(int var1) {
      this.w = var1;
   }

   public void setH(int var1) {
      this.h = var1;
   }

   public boolean isPoint() {
      return this.geometryType == ZoneGeometryType.Point;
   }

   public boolean isPolygon() {
      return this.geometryType == ZoneGeometryType.Polygon;
   }

   public boolean isPolyline() {
      return this.geometryType == ZoneGeometryType.Polyline;
   }

   public boolean isRectangle() {
      return this.geometryType == ZoneGeometryType.INVALID;
   }

   public void setPickedXForZoneStory(int var1) {
      this.pickedXForZoneStory = var1;
   }

   public void setPickedYForZoneStory(int var1) {
      this.pickedYForZoneStory = var1;
   }

   public float getHoursSinceLastSeen() {
      return (float)GameTime.instance.getWorldAgeHours() - this.hourLastSeen;
   }

   public void setHourSeenToCurrent() {
      this.hourLastSeen = (int)GameTime.instance.getWorldAgeHours();
   }

   public void setHaveConstruction(boolean var1) {
      this.haveConstruction = var1;
      if (GameClient.bClient) {
         ByteBufferWriter var2 = GameClient.connection.startPacket();
         PacketType.ConstructedZone.doPacket(var2);
         var2.putInt(this.x);
         var2.putInt(this.y);
         var2.putInt(this.z);
         PacketType.ConstructedZone.send(GameClient.connection);
      }
   }

   public boolean haveCons() {
      return this.haveConstruction;
   }

   public int getZombieDensity() {
      IsoMetaChunk var1 = IsoWorld.instance.MetaGrid.getChunkDataFromTile(this.x, this.y);
      return var1 != null ? var1.getUnadjustedZombieIntensity() : 0;
   }

   public boolean contains(int var1, int var2, int var3) {
      if (var3 != this.z) {
         return false;
      } else if (var1 < this.x || var1 >= this.x + this.w) {
         return false;
      } else if (var2 < this.y || var2 >= this.y + this.h) {
         return false;
      } else if (this.isPoint()) {
         return false;
      } else if (this.isPolyline()) {
         if (this.polylineWidth > 0) {
            this.checkPolylineOutline();
            return this.isPointInPolyline_WindingNumber(var1 + 0.5F, var2 + 0.5F, 0) == PolygonHit.Inside;
         } else {
            return false;
         }
      } else {
         return this.isPolygon() ? this.isPointInPolygon_WindingNumber(var1 + 0.5F, var2 + 0.5F, 0) == PolygonHit.Inside : true;
      }
   }

   public boolean intersects(int var1, int var2, int var3, int var4, int var5) {
      if (this.z != var3) {
         return false;
      } else if (var1 + var4 > this.x && var1 < this.x + this.w) {
         if (var2 + var5 <= this.y || var2 >= this.y + this.h) {
            return false;
         } else if (this.isPolygon()) {
            return this.polygonRectIntersect(var1, var2, var4, var5);
         } else if (this.isPolyline()) {
            if (this.polylineWidth > 0) {
               this.checkPolylineOutline();
               return this.polylineOutlineRectIntersect(var1, var2, var4, var5);
            } else {
               for (byte var6 = 0; var6 < this.points.size() - 2; var6 += 2) {
                  int var7 = this.points.getQuick(var6);
                  int var8 = this.points.getQuick(var6 + 1);
                  int var9 = this.points.getQuick(var6 + 2);
                  int var10 = this.points.getQuick(var6 + 3);
                  if (LIANG_BARSKY.lineRectIntersect(var7, var8, var9 - var7, var10 - var8, var1, var2, var1 + var4, var2 + var5)) {
                     return true;
                  }
               }

               return false;
            }
         } else {
            return true;
         }
      } else {
         return false;
      }
   }

   public boolean difference(int var1, int var2, int var3, int var4, int var5, ArrayList<IsoMetaGrid$Zone> var6) {
      var6.clear();
      if (!this.intersects(var1, var2, var3, var4, var5)) {
         return false;
      } else if (this.isRectangle()) {
         if (this.x < var1) {
            int var14 = Math.max(var2, this.y);
            int var16 = Math.min(var2 + var5, this.y + this.h);
            var6.add(new IsoMetaGrid$Zone(this.name, this.type, this.x, var14, var3, var1 - this.x, var16 - var14));
         }

         if (var1 + var4 < this.x + this.w) {
            int var15 = Math.max(var2, this.y);
            int var17 = Math.min(var2 + var5, this.y + this.h);
            var6.add(new IsoMetaGrid$Zone(this.name, this.type, var1 + var4, var15, var3, this.x + this.w - (var1 + var4), var17 - var15));
         }

         if (this.y < var2) {
            var6.add(new IsoMetaGrid$Zone(this.name, this.type, this.x, this.y, var3, this.w, var2 - this.y));
         }

         if (var2 + var5 < this.y + this.h) {
            var6.add(new IsoMetaGrid$Zone(this.name, this.type, this.x, var2 + var5, var3, this.w, this.y + this.h - (var2 + var5)));
         }

         return true;
      } else {
         if (this.isPolygon()) {
            if (IsoMetaGrid.s_clipper == null) {
               IsoMetaGrid.s_clipper = new Clipper();
               IsoMetaGrid.s_clipperBuffer = ByteBuffer.allocateDirect(3072);
            }

            Clipper var7 = IsoMetaGrid.s_clipper;
            ByteBuffer var8 = IsoMetaGrid.s_clipperBuffer;
            var8.clear();

            for (byte var9 = 0; var9 < this.points.size(); var9 += 2) {
               var8.putFloat(this.points.getQuick(var9));
               var8.putFloat(this.points.getQuick(var9 + 1));
            }

            var7.clear();
            var7.addPath(this.points.size() / 2, var8, false);
            var7.clipAABB(var1, var2, var1 + var4, var2 + var5);
            int var18 = var7.generatePolygons();

            for (int var10 = 0; var10 < var18; var10++) {
               var8.clear();
               var7.getPolygon(var10, var8);
               short var11 = var8.getShort();
               if (var11 < 3) {
                  var8.position(var8.position() + var11 * 4 * 2);
               } else {
                  IsoMetaGrid$Zone var12 = new IsoMetaGrid$Zone(this.name, this.type, this.x, this.y, this.z, this.w, this.h);
                  var12.geometryType = ZoneGeometryType.Polygon;

                  for (int var13 = 0; var13 < var11; var13++) {
                     var12.points.add((int)var8.getFloat());
                     var12.points.add((int)var8.getFloat());
                  }

                  var6.add(var12);
               }
            }
         }

         if (this.isPolyline()) {
         }

         return true;
      }
   }

   private int pickRandomTriangle() {
      float[] var1 = this.isPolygon() ? this.getPolygonTriangles() : (this.isPolyline() ? this.getPolylineOutlineTriangles() : null);
      if (var1 == null) {
         return -1;
      } else {
         int var2 = var1.length / 6;
         float var3 = Rand.Next(0.0F, this.totalArea);
         float var4 = 0.0F;

         for (int var5 = 0; var5 < this.triangleAreas.length; var5++) {
            var4 += this.triangleAreas[var5];
            if (var4 >= var3) {
               return var5;
            }
         }

         return Rand.Next(var2);
      }
   }

   private Vector2 pickRandomPointInTriangle(int var1, Vector2 var2) {
      float var3 = this.triangles[var1 * 3 * 2];
      float var4 = this.triangles[var1 * 3 * 2 + 1];
      float var5 = this.triangles[var1 * 3 * 2 + 2];
      float var6 = this.triangles[var1 * 3 * 2 + 3];
      float var7 = this.triangles[var1 * 3 * 2 + 4];
      float var8 = this.triangles[var1 * 3 * 2 + 5];
      float var9 = Rand.Next(0.0F, 1.0F);
      float var10 = Rand.Next(0.0F, 1.0F);
      boolean var13 = var9 + var10 <= 1.0F;
      float var11;
      float var12;
      if (var13) {
         var11 = var9 * (var5 - var3) + var10 * (var7 - var3);
         var12 = var9 * (var6 - var4) + var10 * (var8 - var4);
      } else {
         var11 = (1.0F - var9) * (var5 - var3) + (1.0F - var10) * (var7 - var3);
         var12 = (1.0F - var9) * (var6 - var4) + (1.0F - var10) * (var8 - var4);
      }

      var11 += var3;
      var12 += var4;
      return var2.set(var11, var12);
   }

   public Location pickRandomLocation(Location var1) {
      if (this.isPolygon() || this.isPolyline() && this.polylineWidth > 0) {
         int var2 = this.pickRandomTriangle();
         if (var2 == -1) {
            return null;
         } else {
            for (int var3 = 0; var3 < 20; var3++) {
               Vector2 var4 = this.pickRandomPointInTriangle(var2, BaseVehicle.allocVector2());
               if (this.contains((int)var4.x, (int)var4.y, this.z)) {
                  var1.set((int)var4.x, (int)var4.y, this.z);
                  BaseVehicle.releaseVector2(var4);
                  return var1;
               }
            }

            return null;
         }
      } else {
         return !this.isPoint() && !this.isPolyline() ? var1.set(Rand.Next(this.x, this.x + this.w), Rand.Next(this.y, this.y + this.h), this.z) : null;
      }
   }

   public IsoGridSquare getRandomSquareInZone() {
      Location var1 = this.pickRandomLocation((Location)IsoMetaGrid.TL_Location.get());
      return var1 == null ? null : IsoWorld.instance.CurrentCell.getGridSquare(var1.x, var1.y, var1.z);
   }

   public IsoGridSquare getRandomUnseenSquareInZone() {
      return null;
   }

   public void addSquare(IsoGridSquare var1) {
   }

   public ArrayList<IsoGridSquare> getSquares() {
      return null;
   }

   public void removeSquare(IsoGridSquare var1) {
   }

   public String getName() {
      return this.name;
   }

   public void setName(String var1) {
      this.name = var1;
   }

   public String getType() {
      return this.type;
   }

   public void setType(String var1) {
      this.type = var1;
   }

   public int getLastActionTimestamp() {
      return this.lastActionTimestamp;
   }

   public void setLastActionTimestamp(int var1) {
      this.lastActionTimestamp = var1;
   }

   public int getX() {
      return this.x;
   }

   public int getY() {
      return this.y;
   }

   public int getZ() {
      return this.z;
   }

   public int getHeight() {
      return this.h;
   }

   public int getWidth() {
      return this.w;
   }

   public float getTotalArea() {
      if (!this.isRectangle() && !this.isPoint() && (!this.isPolyline() || this.polylineWidth > 0)) {
         this.getPolygonTriangles();
         this.getPolylineOutlineTriangles();
         return this.totalArea;
      } else {
         return this.getWidth() * this.getHeight();
      }
   }

   public void sendToServer() {
      if (GameClient.bClient) {
         GameClient.registerZone(this, true);
      }
   }

   public String getOriginalName() {
      return this.originalName;
   }

   public void setOriginalName(String var1) {
      this.originalName = var1;
   }

   public int getClippedSegmentOfPolyline(int var1, int var2, int var3, int var4, double[] var5) {
      if (!this.isPolyline()) {
         return -1;
      } else {
         float var6 = this.polylineWidth % 2 == 0 ? 0.0F : 0.5F;

         for (byte var7 = 0; var7 < this.points.size() - 2; var7 += 2) {
            int var8 = this.points.getQuick(var7);
            int var9 = this.points.getQuick(var7 + 1);
            int var10 = this.points.getQuick(var7 + 2);
            int var11 = this.points.getQuick(var7 + 3);
            if (LIANG_BARSKY.lineRectIntersect(var8 + var6, var9 + var6, var10 - var8, var11 - var9, var1, var2, var3, var4, var5)) {
               return var7 / 2;
            }
         }

         return -1;
      }
   }

   private void checkPolylineOutline() {
      if (this.polylineOutlinePoints == null) {
         if (this.isPolyline()) {
            if (this.polylineWidth > 0) {
               if (IsoMetaGrid.s_clipperOffset == null) {
                  IsoMetaGrid.s_clipperOffset = new ClipperOffset();
                  IsoMetaGrid.s_clipperBuffer = ByteBuffer.allocateDirect(3072);
               }

               ClipperOffset var1 = IsoMetaGrid.s_clipperOffset;
               ByteBuffer var2 = IsoMetaGrid.s_clipperBuffer;
               var1.clear();
               var2.clear();
               float var3 = this.polylineWidth % 2 == 0 ? 0.0F : 0.5F;

               for (byte var4 = 0; var4 < this.points.size(); var4 += 2) {
                  int var5 = this.points.get(var4);
                  int var6 = this.points.get(var4 + 1);
                  var2.putFloat(var5 + var3);
                  var2.putFloat(var6 + var3);
               }

               var2.flip();
               var1.addPath(this.points.size() / 2, var2, JoinType.jtMiter.ordinal(), EndType.etOpenButt.ordinal());
               var1.execute(this.polylineWidth / 2.0F);
               int var7 = var1.getPolygonCount();
               if (var7 < 1) {
                  DebugLog.General.warn("Failed to generate polyline outline");
               } else {
                  var2.clear();
                  var1.getPolygon(0, var2);
                  short var8 = var2.getShort();
                  this.polylineOutlinePoints = new float[var8 * 2];

                  for (int var9 = 0; var9 < var8; var9++) {
                     this.polylineOutlinePoints[var9 * 2] = var2.getFloat();
                     this.polylineOutlinePoints[var9 * 2 + 1] = var2.getFloat();
                  }
               }
            }
         }
      }
   }

   float isLeft(float var1, float var2, float var3, float var4, float var5, float var6) {
      return (var3 - var1) * (var6 - var2) - (var5 - var1) * (var4 - var2);
   }

   PolygonHit isPointInPolygon_WindingNumber(float var1, float var2, int var3) {
      int var4 = 0;

      for (byte var5 = 0; var5 < this.points.size(); var5 += 2) {
         int var6 = this.points.getQuick(var5);
         int var7 = this.points.getQuick(var5 + 1);
         int var8 = this.points.getQuick((var5 + 2) % this.points.size());
         int var9 = this.points.getQuick((var5 + 3) % this.points.size());
         if (var7 <= var2) {
            if (var9 > var2 && this.isLeft(var6, var7, var8, var9, var1, var2) > 0.0F) {
               var4++;
            }
         } else if (var9 <= var2 && this.isLeft(var6, var7, var8, var9, var1, var2) < 0.0F) {
            var4--;
         }
      }

      return var4 == 0 ? PolygonHit.Outside : PolygonHit.Inside;
   }

   PolygonHit isPointInPolyline_WindingNumber(float var1, float var2, int var3) {
      int var4 = 0;
      float[] var5 = this.polylineOutlinePoints;
      if (var5 == null) {
         return PolygonHit.Outside;
      } else {
         for (byte var6 = 0; var6 < var5.length; var6 += 2) {
            float var7 = var5[var6];
            float var8 = var5[var6 + 1];
            float var9 = var5[(var6 + 2) % var5.length];
            float var10 = var5[(var6 + 3) % var5.length];
            if (var8 <= var2) {
               if (var10 > var2 && this.isLeft(var7, var8, var9, var10, var1, var2) > 0.0F) {
                  var4++;
               }
            } else if (var10 <= var2 && this.isLeft(var7, var8, var9, var10, var1, var2) < 0.0F) {
               var4--;
            }
         }

         return var4 == 0 ? PolygonHit.Outside : PolygonHit.Inside;
      }
   }

   boolean polygonRectIntersect(int var1, int var2, int var3, int var4) {
      return this.x >= var1 && this.x + this.w <= var1 + var3 && this.y >= var2 && this.y + this.h <= var2 + var4
         ? true
         : this.lineSegmentIntersects(var1, var2, var1 + var3, var2)
            || this.lineSegmentIntersects(var1 + var3, var2, var1 + var3, var2 + var4)
            || this.lineSegmentIntersects(var1 + var3, var2 + var4, var1, var2 + var4)
            || this.lineSegmentIntersects(var1, var2 + var4, var1, var2);
   }

   boolean lineSegmentIntersects(float var1, float var2, float var3, float var4) {
      L_lineSegmentIntersects.set(var3 - var1, var4 - var2);
      float var5 = L_lineSegmentIntersects.getLength();
      L_lineSegmentIntersects.normalize();
      float var6 = L_lineSegmentIntersects.x;
      float var7 = L_lineSegmentIntersects.y;

      for (byte var8 = 0; var8 < this.points.size(); var8 += 2) {
         float var9 = this.points.getQuick(var8);
         float var10 = this.points.getQuick(var8 + 1);
         float var11 = this.points.getQuick((var8 + 2) % this.points.size());
         float var12 = this.points.getQuick((var8 + 3) % this.points.size());
         float var17 = var1 - var9;
         float var18 = var2 - var10;
         float var19 = var11 - var9;
         float var20 = var12 - var10;
         float var21 = 1.0F / (var20 * var6 - var19 * var7);
         float var22 = (var19 * var18 - var20 * var17) * var21;
         if (var22 >= 0.0F && var22 <= var5) {
            float var23 = (var18 * var6 - var17 * var7) * var21;
            if (var23 >= 0.0F && var23 <= 1.0F) {
               return true;
            }
         }
      }

      return this.isPointInPolygon_WindingNumber((var1 + var3) / 2.0F, (var2 + var4) / 2.0F, 0) != PolygonHit.Outside;
   }

   boolean polylineOutlineRectIntersect(int var1, int var2, int var3, int var4) {
      if (this.polylineOutlinePoints == null) {
         return false;
      } else {
         return this.x >= var1 && this.x + this.w <= var1 + var3 && this.y >= var2 && this.y + this.h <= var2 + var4
            ? true
            : this.polylineOutlineSegmentIntersects(var1, var2, var1 + var3, var2)
               || this.polylineOutlineSegmentIntersects(var1 + var3, var2, var1 + var3, var2 + var4)
               || this.polylineOutlineSegmentIntersects(var1 + var3, var2 + var4, var1, var2 + var4)
               || this.polylineOutlineSegmentIntersects(var1, var2 + var4, var1, var2);
      }
   }

   boolean polylineOutlineSegmentIntersects(float var1, float var2, float var3, float var4) {
      L_lineSegmentIntersects.set(var3 - var1, var4 - var2);
      float var5 = L_lineSegmentIntersects.getLength();
      L_lineSegmentIntersects.normalize();
      float var6 = L_lineSegmentIntersects.x;
      float var7 = L_lineSegmentIntersects.y;
      float[] var8 = this.polylineOutlinePoints;

      for (byte var9 = 0; var9 < var8.length; var9 += 2) {
         float var10 = var8[var9];
         float var11 = var8[var9 + 1];
         float var12 = var8[(var9 + 2) % var8.length];
         float var13 = var8[(var9 + 3) % var8.length];
         float var18 = var1 - var10;
         float var19 = var2 - var11;
         float var20 = var12 - var10;
         float var21 = var13 - var11;
         float var22 = 1.0F / (var21 * var6 - var20 * var7);
         float var23 = (var20 * var19 - var21 * var18) * var22;
         if (var23 >= 0.0F && var23 <= var5) {
            float var24 = (var19 * var6 - var18 * var7) * var22;
            if (var24 >= 0.0F && var24 <= 1.0F) {
               return true;
            }
         }
      }

      return this.isPointInPolyline_WindingNumber((var1 + var3) / 2.0F, (var2 + var4) / 2.0F, 0) != PolygonHit.Outside;
   }

   private boolean isClockwise() {
      if (!this.isPolygon()) {
         return false;
      } else {
         float var1 = 0.0F;

         for (byte var2 = 0; var2 < this.points.size(); var2 += 2) {
            int var3 = this.points.getQuick(var2);
            int var4 = this.points.getQuick(var2 + 1);
            int var5 = this.points.getQuick((var2 + 2) % this.points.size());
            int var6 = this.points.getQuick((var2 + 3) % this.points.size());
            var1 += (var5 - var3) * (var6 + var4);
         }

         return var1 > 0.0;
      }
   }

   public float[] getPolygonTriangles() {
      if (this.triangles != null) {
         return this.triangles;
      } else if (this.bTriangulateFailed) {
         return null;
      } else if (!this.isPolygon()) {
         return null;
      } else {
         if (IsoMetaGrid.s_clipper == null) {
            IsoMetaGrid.s_clipper = new Clipper();
            IsoMetaGrid.s_clipperBuffer = ByteBuffer.allocateDirect(3072);
         }

         Clipper var1 = IsoMetaGrid.s_clipper;
         ByteBuffer var2 = IsoMetaGrid.s_clipperBuffer;
         var2.clear();
         if (this.isClockwise()) {
            for (int var3 = this.points.size() - 1; var3 > 0; var3 -= 2) {
               var2.putFloat(this.points.getQuick(var3 - 1));
               var2.putFloat(this.points.getQuick(var3));
            }
         } else {
            for (byte var6 = 0; var6 < this.points.size(); var6 += 2) {
               var2.putFloat(this.points.getQuick(var6));
               var2.putFloat(this.points.getQuick(var6 + 1));
            }
         }

         var1.clear();
         var1.addPath(this.points.size() / 2, var2, false);
         int var7 = var1.generatePolygons();
         if (var7 < 1) {
            this.bTriangulateFailed = true;
            return null;
         } else {
            var2.clear();
            int var4 = var1.triangulate(0, var2);
            this.triangles = new float[var4 * 2];

            for (int var5 = 0; var5 < var4; var5++) {
               this.triangles[var5 * 2] = var2.getFloat();
               this.triangles[var5 * 2 + 1] = var2.getFloat();
            }

            this.initTriangleAreas();
            return this.triangles;
         }
      }
   }

   private float triangleArea(float var1, float var2, float var3, float var4, float var5, float var6) {
      float var7 = Vector2f.length(var3 - var1, var4 - var2);
      float var8 = Vector2f.length(var5 - var3, var6 - var4);
      float var9 = Vector2f.length(var1 - var5, var2 - var6);
      float var10 = (var7 + var8 + var9) / 2.0F;
      return (float)Math.sqrt(var10 * (var10 - var7) * (var10 - var8) * (var10 - var9));
   }

   private void initTriangleAreas() {
      int var1 = this.triangles.length / 6;
      this.triangleAreas = new float[var1];
      this.totalArea = 0.0F;

      for (byte var2 = 0; var2 < this.triangles.length; var2 += 6) {
         float var3 = this.triangles[var2];
         float var4 = this.triangles[var2 + 1];
         float var5 = this.triangles[var2 + 2];
         float var6 = this.triangles[var2 + 3];
         float var7 = this.triangles[var2 + 4];
         float var8 = this.triangles[var2 + 5];
         float var9 = this.triangleArea(var3, var4, var5, var6, var7, var8);
         this.triangleAreas[var2 / 6] = var9;
         this.totalArea += var9;
      }
   }

   public float[] getPolylineOutlineTriangles() {
      if (this.triangles != null) {
         return this.triangles;
      } else if (!this.isPolyline() || this.polylineWidth <= 0) {
         return null;
      } else if (this.bTriangulateFailed) {
         return null;
      } else {
         this.checkPolylineOutline();
         float[] var1 = this.polylineOutlinePoints;
         if (var1 == null) {
            this.bTriangulateFailed = true;
            return null;
         } else {
            if (IsoMetaGrid.s_clipper == null) {
               IsoMetaGrid.s_clipper = new Clipper();
               IsoMetaGrid.s_clipperBuffer = ByteBuffer.allocateDirect(3072);
            }

            Clipper var2 = IsoMetaGrid.s_clipper;
            ByteBuffer var3 = IsoMetaGrid.s_clipperBuffer;
            var3.clear();
            if (this.isClockwise()) {
               for (int var4 = var1.length - 1; var4 > 0; var4 -= 2) {
                  var3.putFloat(var1[var4 - 1]);
                  var3.putFloat(var1[var4]);
               }
            } else {
               for (byte var7 = 0; var7 < var1.length; var7 += 2) {
                  var3.putFloat(var1[var7]);
                  var3.putFloat(var1[var7 + 1]);
               }
            }

            var2.clear();
            var2.addPath(var1.length / 2, var3, false);
            int var8 = var2.generatePolygons();
            if (var8 < 1) {
               this.bTriangulateFailed = true;
               return null;
            } else {
               var3.clear();
               int var5 = var2.triangulate(0, var3);
               this.triangles = new float[var5 * 2];

               for (int var6 = 0; var6 < var5; var6++) {
                  this.triangles[var6 * 2] = var3.getFloat();
                  this.triangles[var6 * 2 + 1] = var3.getFloat();
               }

               this.initTriangleAreas();
               return this.triangles;
            }
         }
      }
   }

   public float getPolylineLength() {
      if (this.isPolyline() && !this.points.isEmpty()) {
         float var1 = 0.0F;

         for (byte var2 = 0; var2 < this.points.size() - 2; var2 += 2) {
            int var3 = this.points.get(var2);
            int var4 = this.points.get(var2 + 1);
            int var5 = this.points.get(var2 + 2);
            int var6 = this.points.get(var2 + 3);
            var1 += Vector2f.length(var5 - var3, var6 - var4);
         }

         return var1;
      } else {
         return 0.0F;
      }
   }

   public void Dispose() {
      this.pickedRZStory = null;
      this.points.clear();
      this.polylineOutlinePoints = null;
      this.spawnedZombies.clear();
      this.triangles = null;
   }
}
