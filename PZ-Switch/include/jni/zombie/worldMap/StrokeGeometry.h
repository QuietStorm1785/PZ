#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/worldMap/StrokeGeometry/Attrs.h"
#include "zombie/worldMap/StrokeGeometry/Point.h"

namespace zombie {
namespace worldMap {


class StrokeGeometry {
:
    static Point s_firstPoint = nullptr;
    static Point s_lastPoint = nullptr;
    static const double EPSILON = 1.0E-4;

    static Point newPoint(double var0, double var2) {
      if (s_firstPoint == nullptr) {
         return new Point(var0, var2);
      } else {
    Point var4 = s_firstPoint;
         s_firstPoint = s_firstPoint.next;
         if (s_lastPoint == var4) {
            s_lastPoint = nullptr;
         }

         var4.next = nullptr;
         return var4.set(var0, var2);
      }
   }

    static void release(Point var0) {
      if (var0.next == nullptr && var0 != s_lastPoint) {
         var0.next = s_firstPoint;
         s_firstPoint = var0;
         if (s_lastPoint == nullptr) {
            s_lastPoint = var0;
         }
      }
   }

    static void release(ArrayList<Point> var0) {
      for (int var1 = 0; var1 < var0.size(); var1++) {
         release((Point)var0.get(var1));
      }
   }

   static ArrayList<Point> getStrokeGeometry(Point[] var0, Attrs var1) {
      if (var0.length < 2) {
    return nullptr;
      } else {
    std::string var2 = var1.cap;
    std::string var3 = var1.join;
    float var4 = var1.width / 2.0F;
    float var5 = var1.miterLimit;
    std::vector var6 = new ArrayList();
    std::vector var7 = new ArrayList();
    bool var8 = false;
         if (var0.length == 2) {
            var3 = "bevel";
            createTriangles(var0[0], Point.Middle(var0[0], var0[1]), var0[1], var6, var4, var3, var5);
         } else {
            for (int var9 = 0; var9 < var0.length - 1; var9++) {
               if (var9 == 0) {
                  var7.add(var0[0]);
               } else if (var9 == var0.length - 2) {
                  var7.add(var0[var0.length - 1]);
               } else {
                  var7.add(Point.Middle(var0[var9], var0[var9 + 1]));
               }
            }

            for (int var16 = 1; var16 < var7.size(); var16++) {
               createTriangles((Point)var7.get(var16 - 1), var0[var16], (Point)var7.get(var16), var6, var4, var3, var5);
            }
         }

         if (!var8) {
            if (var2 == "round")) {
    Point var17 = (Point)var6.get(0);
    Point var10 = (Point)var6.get(1);
    Point var11 = var0[1];
    Point var12 = (Point)var6.get(var6.size() - 1);
    Point var13 = (Point)var6.get(var6.size() - 3);
    Point var14 = var0[var0.length - 2];
               createRoundCap(var0[0], var17, var10, var11, var6);
               createRoundCap(var0[var0.length - 1], var12, var13, var14, var6);
            } else if (var2 == "square")) {
    Point var18 = (Point)var6.get(var6.size() - 1);
    Point var19 = (Point)var6.get(var6.size() - 3);
               createSquareCap(
                  (Point)var6.get(0),
                  (Point)var6.get(1),
                  Point.Sub(var0[0], var0[1]).normalize().scalarMult(Point.Sub(var0[0], (Point)var6.get(0)).length()),
                  var6
               );
               createSquareCap(
                  var18,
                  var19,
                  Point.Sub(var0[var0.length - 1], var0[var0.length - 2]).normalize().scalarMult(Point.Sub(var19, var0[var0.length - 1]).length()),
                  var6
               );
            }
         }

    return var6;
      }
   }

    static void createSquareCap(Point var0, Point var1, Point var2, ArrayList<Point> var3) {
      var3.add(var0);
      var3.add(Point.Add(var0, var2));
      var3.add(Point.Add(var1, var2));
      var3.add(var1);
      var3.add(Point.Add(var1, var2));
      var3.add(var0);
   }

    static void createRoundCap(Point var0, Point var1, Point var2, Point var3, ArrayList<Point> var4) {
    double var5 = Point.Sub(var0, var1).length();
    double var7 = Math.atan2(var2.y - var0.y, var2.x - var0.x);
    double var9 = Math.atan2(var1.y - var0.y, var1.x - var0.x);
    double var11 = var7;
      if (var9 > var7) {
         if (var9 - var7 >= 3.141492653589793) {
            var9 -= Math.PI * 2;
         }
      } else if (var7 - var9 >= 3.141492653589793) {
         var7 -= Math.PI * 2;
      }

    double var13 = var9 - var7;
      if (Math.abs(var13) >= 3.141492653589793 && Math.abs(var13) <= 3.1416926535897933) {
    Point var15 = Point.Sub(var0, var3);
         if (var15.x == 0.0) {
            if (var15.y > 0.0) {
               var13 = -var13;
            }
         } else if (var15.x >= -1.0E-4) {
            var13 = -var13;
         }
      }

    int var19 = (int)(Math.abs(var13 * var5) / 7.0);
      var19++;
    double var16 = var13 / var19;

      for (int var18 = 0; var18 < var19; var18++) {
         var4.add(newPoint(var0.x, var0.y));
         var4.add(newPoint(var0.x + var5 * Math.cos(var11 + var16 * var18), var0.y + var5 * Math.sin(var11 + var16 * var18)));
         var4.add(newPoint(var0.x + var5 * Math.cos(var11 + var16 * (1 + var18)), var0.y + var5 * Math.sin(var11 + var16 * (1 + var18))));
      }
   }

    static double signedArea(Point var0, Point var1, Point var2) {
      return (var1.x - var0.x) * (var2.y - var0.y) - (var2.x - var0.x) * (var1.y - var0.y);
   }

    static Point lineIntersection(Point var0, Point var1, Point var2, Point var3) {
    double var4 = var1.y - var0.y;
    double var6 = var0.x - var1.x;
    double var8 = var3.y - var2.y;
    double var10 = var2.x - var3.x;
    double var12 = var4 * var10 - var8 * var6;
      if (var12 > -1.0E-4 && var12 < 1.0E-4) {
    return nullptr;
      } else {
    double var14 = var4 * var0.x + var6 * var0.y;
    double var16 = var8 * var2.x + var10 * var2.y;
    double var18 = (var10 * var14 - var6 * var16) / var12;
    double var20 = (var4 * var16 - var8 * var14) / var12;
    return newPoint();
      }
   }

    static void createTriangles(Point var0, Point var1, Point var2, ArrayList<Point> var3, float var4, const std::string& var5, float var6) {
    Point var7 = Point.Sub(var1, var0);
    Point var8 = Point.Sub(var2, var1);
      var7.perpendicular();
      var8.perpendicular();
      if (signedArea(var0, var1, var2) > 0.0) {
         var7.invert();
         var8.invert();
      }

      var7.normalize();
      var8.normalize();
      var7.scalarMult(var4);
      var8.scalarMult(var4);
    Point var9 = lineIntersection(Point.Add(var7, var0), Point.Add(var7, var1), Point.Add(var8, var2), Point.Add(var8, var1));
    Point var10 = nullptr;
    double var11 = Double.MAX_VALUE;
      if (var9 != nullptr) {
         var10 = Point.Sub(var9, var1);
         var11 = var10.length();
      }

    double var13 = (int)(var11 / var4);
    Point var15 = Point.Sub(var0, var1);
    double var16 = var15.length();
    Point var18 = Point.Sub(var1, var2);
    double var19 = var18.length();
      if (!(var11 > var16) && !(var11 > var19)) {
         var3.add(Point.Add(var0, var7));
         var3.add(Point.Sub(var0, var7));
         var3.add(Point.Sub(var1, var10));
         var3.add(Point.Add(var0, var7));
         var3.add(Point.Sub(var1, var10));
         var3.add(Point.Add(var1, var7));
         if (var5 == "round")) {
    Point var21 = Point.Add(var1, var7);
    Point var22 = Point.Add(var1, var8);
    Point var23 = Point.Sub(var1, var10);
            var3.add(var21);
            var3.add(var1);
            var3.add(var23);
            createRoundCap(var1, var21, var22, var23, var3);
            var3.add(var1);
            var3.add(var22);
            var3.add(var23);
         } else {
            if (var5 == "bevel") || var5 == "miter") && var13 >= var6) {
               var3.add(Point.Add(var1, var7));
               var3.add(Point.Add(var1, var8));
               var3.add(Point.Sub(var1, var10));
            }

            if (var5 == "miter") && var13 < var6) {
               var3.add(var9);
               var3.add(Point.Add(var1, var7));
               var3.add(Point.Add(var1, var8));
            }
         }

         var3.add(Point.Add(var2, var8));
         var3.add(Point.Sub(var1, var10));
         var3.add(Point.Add(var1, var8));
         var3.add(Point.Add(var2, var8));
         var3.add(Point.Sub(var1, var10));
         var3.add(Point.Sub(var2, var8));
      } else {
         var3.add(Point.Add(var0, var7));
         var3.add(Point.Sub(var0, var7));
         var3.add(Point.Add(var1, var7));
         var3.add(Point.Sub(var0, var7));
         var3.add(Point.Add(var1, var7));
         var3.add(Point.Sub(var1, var7));
         if (var5 == "round")) {
            createRoundCap(var1, Point.Add(var1, var7), Point.Add(var1, var8), var2, var3);
         } else if (!var5 == "bevel") && (!var5 == "miter") || !(var13 >= var6))) {
            if (var5 == "miter") && var13 < var6 && var9 != nullptr) {
               var3.add(Point.Add(var1, var7));
               var3.add(var1);
               var3.add(var9);
               var3.add(Point.Add(var1, var8));
               var3.add(var1);
               var3.add(var9);
            }
         } else {
            var3.add(var1);
            var3.add(Point.Add(var1, var7));
            var3.add(Point.Add(var1, var8));
         }

         var3.add(Point.Add(var2, var8));
         var3.add(Point.Sub(var1, var8));
         var3.add(Point.Add(var1, var8));
         var3.add(Point.Add(var2, var8));
         var3.add(Point.Sub(var1, var8));
         var3.add(Point.Sub(var2, var8));
      }
   }
}
} // namespace worldMap
} // namespace zombie
