#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/math/PZMath.h"
#include "zombie/vehicles/Clipper.h"
#include "zombie/worldMap/WorldMapGeometry/PolygonHit.h"
#include "zombie/worldMap/WorldMapGeometry/TrianglesPerZoom.h"
#include "zombie/worldMap/WorldMapGeometry/Type.h"
#include <filesystem>

namespace zombie {
namespace worldMap {


class WorldMapGeometry {
public:
    Type m_type;
   public final ArrayList<WorldMapPoints> m_points = std::make_unique<ArrayList<>>();
    int m_minX;
    int m_minY;
    int m_maxX;
    int m_maxY;
   public std::vector<float> m_triangles = nullptr;
   public ArrayList<TrianglesPerZoom> m_trianglesPerZoom = nullptr;
    int m_vboIndex1 = -1;
    int m_vboIndex2 = -1;
    int m_vboIndex3 = -1;
    int m_vboIndex4 = -1;
    static Clipper s_clipper = null;
    static ByteBuffer s_vertices = null;

    void calculateBounds() {
      this.m_minX = this.m_minY = Integer.MAX_VALUE;
      this.m_maxX = this.m_maxY = Integer.MIN_VALUE;

      for (int var1 = 0; var1 < this.m_points.size(); var1++) {
    WorldMapPoints var2 = this.m_points.get(var1);
         var2.calculateBounds();
         this.m_minX = PZMath.min(this.m_minX, var2.m_minX);
         this.m_minY = PZMath.min(this.m_minY, var2.m_minY);
         this.m_maxX = PZMath.max(this.m_maxX, var2.m_maxX);
         this.m_maxY = PZMath.max(this.m_maxY, var2.m_maxY);
      }
   }

    bool containsPoint(float var1, float var2) {
      return this.m_type == Type.Polygon && !this.m_points.isEmpty() ? this.isPointInPolygon_WindingNumber(var1, var2, 0) != PolygonHit.Outside : false;
   }

    void triangulate(double[] var1) {
      if (s_clipper == nullptr) {
         s_clipper = std::make_unique<Clipper>();
      }

      s_clipper.clear();
    WorldMapPoints var2 = this.m_points.get(0);
      if (s_vertices == nullptr || s_vertices.capacity() < var2.size() * 50 * 4) {
         s_vertices = ByteBuffer.allocateDirect(var2.size() * 50 * 4);
      }

      s_vertices.clear();
      if (var2.isClockwise()) {
         for (int var3 = var2.numPoints() - 1; var3 >= 0; var3--) {
            s_vertices.putFloat(var2.getX(var3));
            s_vertices.putFloat(var2.getY(var3));
         }
      } else {
         for (int var24 = 0; var24 < var2.numPoints(); var24++) {
            s_vertices.putFloat(var2.getX(var24));
            s_vertices.putFloat(var2.getY(var24));
         }
      }

      s_clipper.addPath(var2.numPoints(), s_vertices, false);

      for (int var25 = 1; var25 < this.m_points.size(); var25++) {
         s_vertices.clear();
    WorldMapPoints var4 = this.m_points.get(var25);
         if (var4.isClockwise()) {
            for (int var32 = var4.numPoints() - 1; var32 >= 0; var32--) {
               s_vertices.putFloat(var4.getX(var32));
               s_vertices.putFloat(var4.getY(var32));
            }
         } else {
            for (int var5 = 0; var5 < var4.numPoints(); var5++) {
               s_vertices.putFloat(var4.getX(var5));
               s_vertices.putFloat(var4.getY(var5));
            }
         }

         s_clipper.addPath(var4.numPoints(), s_vertices, true);
      }

      if (this.m_minX < 0 || this.m_minY < 0 || this.m_maxX > 300 || this.m_maxY > 300) {
    short var26 = 900;
    float var29 = -var26;
    float var33 = -var26;
    float var6 = 300 + var26;
    float var7 = -var26;
    float var8 = 300 + var26;
    float var9 = 300 + var26;
    float var10 = -var26;
    float var11 = 300 + var26;
    float var12 = -var26;
    float var13 = 0.0F;
    float var14 = 0.0F;
    float var15 = 0.0F;
    float var16 = 0.0F;
    float var17 = 300.0F;
    float var18 = 300.0F;
    float var19 = 300.0F;
    float var20 = 300.0F;
    float var21 = 0.0F;
    float var22 = -var26;
    float var23 = 0.0F;
         s_vertices.clear();
         s_vertices.putFloat(var29).putFloat(var33);
         s_vertices.putFloat(var6).putFloat(var7);
         s_vertices.putFloat(var8).putFloat(var9);
         s_vertices.putFloat(var10).putFloat(var11);
         s_vertices.putFloat(var12).putFloat(var13);
         s_vertices.putFloat(var14).putFloat(var15);
         s_vertices.putFloat(var16).putFloat(var17);
         s_vertices.putFloat(var18).putFloat(var19);
         s_vertices.putFloat(var20).putFloat(var21);
         s_vertices.putFloat(var22).putFloat(var23);
         s_clipper.addPath(10, s_vertices, true);
      }

    int var27 = s_clipper.generatePolygons(0.0);
      if (var27 > 0) {
         s_vertices.clear();
    int var30 = s_clipper.triangulate(0, s_vertices);
         this.m_triangles = new float[var30 * 2];

         for (int var34 = 0; var34 < var30; var34++) {
            this.m_triangles[var34 * 2] = s_vertices.getFloat();
            this.m_triangles[var34 * 2 + 1] = s_vertices.getFloat();
         }

         if (var1 != nullptr) {
            for (int var35 = 0; var35 < var1.length; var35++) {
    double var36 = var1[var35] - (var35 == 0 ? 0.0 : var1[var35 - 1]);
               var27 = s_clipper.generatePolygons(var36);
               if (var27 > 0) {
                  s_vertices.clear();
                  var30 = s_clipper.triangulate(0, s_vertices);
    auto var37 = std::make_shared<TrianglesPerZoom>();
                  var37.m_triangles = new float[var30 * 2];
                  var37.m_delta = var1[var35];

                  for (int var38 = 0; var38 < var30; var38++) {
                     var37.m_triangles[var38 * 2] = s_vertices.getFloat();
                     var37.m_triangles[var38 * 2 + 1] = s_vertices.getFloat();
                  }

                  if (this.m_trianglesPerZoom == nullptr) {
                     this.m_trianglesPerZoom = std::make_unique<ArrayList<>>();
                  }

                  this.m_trianglesPerZoom.add(var37);
               }
            }
         }
      }
   }

    TrianglesPerZoom findTriangles(double var1) {
      if (this.m_trianglesPerZoom == nullptr) {
    return null;
      } else {
         for (int var3 = 0; var3 < this.m_trianglesPerZoom.size(); var3++) {
    TrianglesPerZoom var4 = this.m_trianglesPerZoom.get(var3);
            if (var4.m_delta == var1) {
    return var4;
            }
         }

    return null;
      }
   }

    void dispose() {
      this.m_points.clear();
      this.m_triangles = nullptr;
   }

    float isLeft(float var1, float var2, float var3, float var4, float var5, float var6) {
      return (var3 - var1) * (var6 - var2) - (var5 - var1) * (var4 - var2);
   }

    PolygonHit isPointInPolygon_WindingNumber(float var1, float var2, int var3) {
    int var4 = 0;
    WorldMapPoints var5 = this.m_points.get(0);

      for (int var6 = 0; var6 < var5.numPoints(); var6++) {
    int var7 = var5.getX(var6);
    int var8 = var5.getY(var6);
    int var9 = var5.getX((var6 + 1) % var5.numPoints());
    int var10 = var5.getY((var6 + 1) % var5.numPoints());
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
} // namespace worldMap
} // namespace zombie
