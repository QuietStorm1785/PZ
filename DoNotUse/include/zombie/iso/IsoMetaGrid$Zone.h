#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/list/array/TIntArrayList.h"
#include "org/joml/Vector2f.h"
#include "zombie/GameTime.h"
#include "zombie/characters/IsoGameCharacter/Location.h"
#include "zombie/core/Rand.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/iso/IsoMetaGrid/Zone/PolygonHit.h"
#include "zombie/iso/IsoMetaGrid/ZoneGeometryType.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/PacketTypes/PacketType.h"
#include "zombie/randomizedWorld/randomizedZoneStory/RandomizedZoneStoryBase.h"
#include "zombie/vehicles/BaseVehicle.h"
#include "zombie/vehicles/Clipper.h"
#include "zombie/vehicles/ClipperOffset.h"
#include "zombie/vehicles/ClipperOffset/EndType.h"
#include "zombie/vehicles/ClipperOffset/JoinType.h"
#include "zombie/vehicles/PolygonalMap2/LiangBarsky.h"
#include <filesystem>

namespace zombie {
namespace iso {


class IsoMetaGrid {
public:
    double id = 0.0;
    int hourLastSeen = 0;
    int lastActionTimestamp = 0;
    bool haveConstruction = false;
   public const std::unordered_map<std::string, int> spawnedZombies = std::make_unique<std::unordered_map<>>();
    std::string zombiesTypeToSpawn = nullptr;
    bool spawnSpecialZombies = nullptr;
    std::string name;
    std::string type;
    int x;
    int y;
    int z;
    int w;
    int h;
    ZoneGeometryType geometryType = ZoneGeometryType.INVALID;
    const TIntArrayList points = std::make_shared<TIntArrayList>();
    bool bTriangulateFailed = false;
    int polylineWidth = 0;
   public float[] polylineOutlinePoints;
   public float[] triangles;
   public float[] triangleAreas;
    float totalArea = 0.0F;
    int pickedXForZoneStory;
    int pickedYForZoneStory;
    RandomizedZoneStoryBase pickedRZStory;
    std::string originalName;
    bool isPreferredZoneForSquare = false;
    static const LiangBarsky LIANG_BARSKY = std::make_shared<LiangBarsky>();
    static const Vector2 L_lineSegmentIntersects = std::make_shared<Vector2>();

   public IsoMetaGrid$Zone(std::string var1, std::string var2, int var3, int var4, int var5, int var6, int var7) {
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

    void setX(int var1) {
      this.x = var1;
   }

    void setY(int var1) {
      this.y = var1;
   }

    void setW(int var1) {
      this.w = var1;
   }

    void setH(int var1) {
      this.h = var1;
   }

    bool isPoint() {
      return this.geometryType == ZoneGeometryType.Point;
   }

    bool isPolygon() {
      return this.geometryType == ZoneGeometryType.Polygon;
   }

    bool isPolyline() {
      return this.geometryType == ZoneGeometryType.Polyline;
   }

    bool isRectangle() {
      return this.geometryType == ZoneGeometryType.INVALID;
   }

    void setPickedXForZoneStory(int var1) {
      this.pickedXForZoneStory = var1;
   }

    void setPickedYForZoneStory(int var1) {
      this.pickedYForZoneStory = var1;
   }

    float getHoursSinceLastSeen() {
      return (float)GameTime.instance.getWorldAgeHours() - this.hourLastSeen;
   }

    void setHourSeenToCurrent() {
      this.hourLastSeen = (int)GameTime.instance.getWorldAgeHours();
   }

    void setHaveConstruction(bool var1) {
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

    bool haveCons() {
      return this.haveConstruction;
   }

    int getZombieDensity() {
    IsoMetaChunk var1 = IsoWorld.instance.MetaGrid.getChunkDataFromTile(this.x, this.y);
      return var1 != nullptr ? var1.getUnadjustedZombieIntensity() : 0;
   }

    bool contains(int var1, int var2, int var3) {
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

    bool intersects(int var1, int var2, int var3, int var4, int var5) {
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

    bool difference(int var1, int var2, int var3, int var4, int var5, std::vector<IsoMetaGrid$Zone> var6) {
      var6.clear();
      if (!this.intersects(var1, var2, var3, var4, var5)) {
    return false;
      } else if (this.isRectangle()) {
         if (this.x < var1) {
    int var14 = Math.max(var2, this.y);
    int var16 = Math.min(var2 + var5, this.y + this.h);
            var6.push_back(new IsoMetaGrid$Zone(this.name, this.type, this.x, var14, var3, var1 - this.x, var16 - var14));
         }

         if (var1 + var4 < this.x + this.w) {
    int var15 = Math.max(var2, this.y);
    int var17 = Math.min(var2 + var5, this.y + this.h);
            var6.push_back(new IsoMetaGrid$Zone(this.name, this.type, var1 + var4, var15, var3, this.x + this.w - (var1 + var4), var17 - var15));
         }

         if (this.y < var2) {
            var6.push_back(new IsoMetaGrid$Zone(this.name, this.type, this.x, this.y, var3, this.w, var2 - this.y));
         }

         if (var2 + var5 < this.y + this.h) {
            var6.push_back(new IsoMetaGrid$Zone(this.name, this.type, this.x, var2 + var5, var3, this.w, this.y + this.h - (var2 + var5)));
         }

    return true;
      } else {
         if (this.isPolygon()) {
            if (IsoMetaGrid.s_clipper == nullptr) {
               IsoMetaGrid.s_clipper = std::make_unique<Clipper>();
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
                     var12.points.push_back((int)var8.getFloat());
                     var12.points.push_back((int)var8.getFloat());
                  }

                  var6.push_back(var12);
               }
            }
         }

         if (this.isPolyline()) {
         }

    return true;
      }
   }

    int pickRandomTriangle() {
      float[] var1 = this.isPolygon() ? this.getPolygonTriangles() : (this.isPolyline() ? this.getPolylineOutlineTriangles() : nullptr);
      if (var1 == nullptr) {
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

    Vector2 pickRandomPointInTriangle(int var1, Vector2 var2) {
    float var3 = this.triangles[var1 * 3 * 2];
    float var4 = this.triangles[var1 * 3 * 2 + 1];
    float var5 = this.triangles[var1 * 3 * 2 + 2];
    float var6 = this.triangles[var1 * 3 * 2 + 3];
    float var7 = this.triangles[var1 * 3 * 2 + 4];
    float var8 = this.triangles[var1 * 3 * 2 + 5];
    float var9 = Rand.Next(0.0F, 1.0F);
    float var10 = Rand.Next(0.0F, 1.0F);
    bool var13 = var9 + var10 <= 1.0F;
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

    Location pickRandomLocation(Location var1) {
      if (this.isPolygon() || this.isPolyline() && this.polylineWidth > 0) {
    int var2 = this.pickRandomTriangle();
         if (var2 == -1) {
    return nullptr;
         } else {
            for (int var3 = 0; var3 < 20; var3++) {
    Vector2 var4 = this.pickRandomPointInTriangle(var2, BaseVehicle.allocVector2());
               if (this.contains((int)var4.x, (int)var4.y, this.z)) {
                  var1.set((int)var4.x, (int)var4.y, this.z);
                  BaseVehicle.releaseVector2(var4);
    return var1;
               }
            }

    return nullptr;
         }
      } else {
         return !this.isPoint() && !this.isPolyline() ? var1.set(Rand.Next(this.x, this.x + this.w), Rand.Next(this.y, this.y + this.h), this.z) : nullptr;
      }
   }

    IsoGridSquare getRandomSquareInZone() {
    Location var1 = this.pickRandomLocation((Location)IsoMetaGrid.TL_Location.get());
    return var1 = = nullptr ? nullptr : IsoWorld.instance.CurrentCell.getGridSquare(var1.x, var1.y, var1.z);
   }

    IsoGridSquare getRandomUnseenSquareInZone() {
    return nullptr;
   }

    void addSquare(IsoGridSquare var1) {
   }

   public std::vector<IsoGridSquare> getSquares() {
    return nullptr;
   }

    void removeSquare(IsoGridSquare var1) {
   }

    std::string getName() {
      return this.name;
   }

    void setName(const std::string& var1) {
      this.name = var1;
   }

    std::string getType() {
      return this.type;
   }

    void setType(const std::string& var1) {
      this.type = var1;
   }

    int getLastActionTimestamp() {
      return this.lastActionTimestamp;
   }

    void setLastActionTimestamp(int var1) {
      this.lastActionTimestamp = var1;
   }

    int getX() {
      return this.x;
   }

    int getY() {
      return this.y;
   }

    int getZ() {
      return this.z;
   }

    int getHeight() {
      return this.h;
   }

    int getWidth() {
      return this.w;
   }

    float getTotalArea() {
      if (!this.isRectangle() && !this.isPoint() && (!this.isPolyline() || this.polylineWidth > 0)) {
         this.getPolygonTriangles();
         this.getPolylineOutlineTriangles();
         return this.totalArea;
      } else {
         return this.getWidth() * this.getHeight();
      }
   }

    void sendToServer() {
      if (GameClient.bClient) {
         GameClient.registerZone(this, true);
      }
   }

    std::string getOriginalName() {
      return this.originalName;
   }

    void setOriginalName(const std::string& var1) {
      this.originalName = var1;
   }

    int getClippedSegmentOfPolyline(int var1, int var2, int var3, int var4, double[] var5) {
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

    void checkPolylineOutline() {
      if (this.polylineOutlinePoints == nullptr) {
         if (this.isPolyline()) {
            if (this.polylineWidth > 0) {
               if (IsoMetaGrid.s_clipperOffset == nullptr) {
                  IsoMetaGrid.s_clipperOffset = std::make_unique<ClipperOffset>();
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

    return var4 = = 0 ? PolygonHit.Outside : PolygonHit.Inside;
   }

    PolygonHit isPointInPolyline_WindingNumber(float var1, float var2, int var3) {
    int var4 = 0;
      float[] var5 = this.polylineOutlinePoints;
      if (var5 == nullptr) {
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

    return var4 = = 0 ? PolygonHit.Outside : PolygonHit.Inside;
      }
   }

    bool polygonRectIntersect(int var1, int var2, int var3, int var4) {
      return this.x >= var1 && this.x + this.w <= var1 + var3 && this.y >= var2 && this.y + this.h <= var2 + var4
         ? true
         : this.lineSegmentIntersects(var1, var2, var1 + var3, var2)
            || this.lineSegmentIntersects(var1 + var3, var2, var1 + var3, var2 + var4)
            || this.lineSegmentIntersects(var1 + var3, var2 + var4, var1, var2 + var4)
            || this.lineSegmentIntersects(var1, var2 + var4, var1, var2);
   }

    bool lineSegmentIntersects(float var1, float var2, float var3, float var4) {
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

    bool polylineOutlineRectIntersect(int var1, int var2, int var3, int var4) {
      if (this.polylineOutlinePoints == nullptr) {
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

    bool polylineOutlineSegmentIntersects(float var1, float var2, float var3, float var4) {
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

    bool isClockwise() {
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
      if (this.triangles != nullptr) {
         return this.triangles;
      } else if (this.bTriangulateFailed) {
    return nullptr;
      } else if (!this.isPolygon()) {
    return nullptr;
      } else {
         if (IsoMetaGrid.s_clipper == nullptr) {
            IsoMetaGrid.s_clipper = std::make_unique<Clipper>();
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
    return nullptr;
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

    float triangleArea(float var1, float var2, float var3, float var4, float var5, float var6) {
    float var7 = Vector2f.length(var3 - var1, var4 - var2);
    float var8 = Vector2f.length(var5 - var3, var6 - var4);
    float var9 = Vector2f.length(var1 - var5, var2 - var6);
    float var10 = (var7 + var8 + var9) / 2.0F;
      return (float)Math.sqrt(var10 * (var10 - var7) * (var10 - var8) * (var10 - var9));
   }

    void initTriangleAreas() {
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
      if (this.triangles != nullptr) {
         return this.triangles;
      } else if (!this.isPolyline() || this.polylineWidth <= 0) {
    return nullptr;
      } else if (this.bTriangulateFailed) {
    return nullptr;
      } else {
         this.checkPolylineOutline();
         float[] var1 = this.polylineOutlinePoints;
         if (var1 == nullptr) {
            this.bTriangulateFailed = true;
    return nullptr;
         } else {
            if (IsoMetaGrid.s_clipper == nullptr) {
               IsoMetaGrid.s_clipper = std::make_unique<Clipper>();
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
    return nullptr;
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

    float getPolylineLength() {
      if (this.isPolyline() && !this.points.empty()) {
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

    void Dispose() {
      this.pickedRZStory = nullptr;
      this.points.clear();
      this.polylineOutlinePoints = nullptr;
      this.spawnedZombies.clear();
      this.triangles = nullptr;
   }
}
} // namespace iso
} // namespace zombie
