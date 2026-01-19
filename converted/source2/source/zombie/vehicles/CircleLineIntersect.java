package zombie.vehicles;

import java.util.ArrayList;
import java.util.List;
import org.joml.Vector3f;
import org.lwjgl.util.vector.Vector2f;
import zombie.characters.IsoPlayer;
import zombie.core.physics.CarController;
import zombie.core.physics.WorldSimulation;
import zombie.debug.LineDrawer;
import zombie.vehicles.CircleLineIntersect.Collideclassindex;
import zombie.vehicles.CircleLineIntersect.Collider;
import zombie.vehicles.CircleLineIntersect.Collideresult;
import zombie.vehicles.CircleLineIntersect.ForceCircle;
import zombie.vehicles.CircleLineIntersect.Point;
import zombie.vehicles.CircleLineIntersect.PointVector;
import zombie.vehicles.CircleLineIntersect.RectVector;
import zombie.vehicles.CircleLineIntersect.StaticLine;
import zombie.vehicles.CircleLineIntersect.VectorMath;

public class CircleLineIntersect {
   public static Collideresult checkforcecirclescollidetime(List<ForceCircle> var0, ArrayList<StaticLine> var1, double[] var2, boolean[] var3, boolean var4) {
      PointVector[] var6 = new PointVector[var0.size()];
      double[] var7 = new double[var0.size()];
      Collideclassindex[] var8 = new Collideclassindex[var0.size()];
      double[] var9 = new double[var0.size()];

      for (int var10 = var0.size() - 1; var10 >= 0; var10--) {
         var7[var10] = -1.0;
         var8[var10] = new Collideclassindex();
         var6[var10] = (PointVector)var0.get(var10);
         var9[var10] = 1.0;
      }

      for (int var11 = Math.min(var0.size(), var2.length) - 1; var11 >= 0; var11--) {
         if (var4 || var3[var11]) {
            ForceCircle var5 = (ForceCircle)var0.get(var11);

            for (int var12 = var1.size() - 1; var12 >= 0; var12--) {
               StaticLine var76 = (StaticLine)var1.get(var12);
               Point var13 = VectorMath.closestpointonline(var76.getX1(), var76.getY1(), var76.getX2(), var76.getY2(), var5.getX(), var5.getY());
               double var14 = Point.distanceSq(var13.getX(), var13.getY(), var5.getX(), var5.getY());
               if (var14 < var5.getRadiusSq()) {
                  double var16 = 0.0;
                  double var18 = 0.0;
                  if (var14 == 0.0) {
                     Point var20 = Point.midpoint(var76.getP1(), var76.getP2());
                     double var21 = var76.getP1().distance(var76.getP2());
                     double var23 = var5.distanceSq(var20);
                     if (var23 < Math.pow(var5.getRadius() + var21 / 2.0, 2.0)) {
                        if (var23 != 0.0) {
                           double var25 = var5.distance(var20);
                           double var27 = (var5.getX() - var20.getX()) / var25;
                           double var29 = (var5.getY() - var20.getY()) / var25;
                           var16 = var20.getX() + (var5.getRadius() + var21 / 2.0) * var27;
                           var18 = var20.getY() + (var5.getRadius() + var21 / 2.0) * var29;
                        } else {
                           var16 = var5.getX();
                           var18 = var5.getY();
                        }

                        if (var7[var11] == -1.0) {
                           var6[var11] = new PointVector(var16, var18);
                        } else {
                           var6[var11].setPoint(var16, var18);
                        }

                        if (var7[var11] == 0.0) {
                           var8[var11].addCollided(var76, var12, var5.getVector());
                        } else {
                           var8[var11].setCollided(var76, var12, var5.getVector());
                        }

                        var7[var11] = 0.0;
                        continue;
                     }

                     if (var23 == Math.pow(var5.getRadius() + var21 / 2.0, 2.0) && var5.getLength() == 0.0) {
                        continue;
                     }
                  } else {
                     if (Math.min(var76.getX1(), var76.getX2()) <= var13.getX()
                        && var13.getX() <= Math.max(var76.getX1(), var76.getX2())
                        && Math.min(var76.getY1(), var76.getY2()) <= var13.getY()
                        && var13.getY() <= Math.max(var76.getY1(), var76.getY2())) {
                        double var95 = Math.sqrt(var14);
                        double var100 = (var5.getX() - var13.getX()) / var95;
                        double var103 = (var5.getY() - var13.getY()) / var95;
                        var16 = var13.getX() + var5.getRadius() * var100;
                        var18 = var13.getY() + var5.getRadius() * var103;
                        if (var7[var11] == -1.0) {
                           var6[var11] = new PointVector(var16, var18);
                        } else {
                           var6[var11].setPoint(var16, var18);
                        }

                        if (var7[var11] == 0.0) {
                           var8[var11].addCollided(var76, var12, var5.getVector());
                        } else {
                           var8[var11].setCollided(var76, var12, var5.getVector());
                        }

                        var7[var11] = 0.0;
                        continue;
                     }

                     if (Point.distanceSq(var5.getX(), var5.getY(), var76.getX1(), var76.getY1()) < var5.getRadiusSq()) {
                        double var94 = Point.distance(var5.getX(), var5.getY(), var76.getX1(), var76.getY1());
                        double var99 = (var5.getX() - var76.getX1()) / var94;
                        double var102 = (var5.getY() - var76.getY1()) / var94;
                        var16 = var76.getX1() + var5.getRadius() * var99;
                        var18 = var76.getY1() + var5.getRadius() * var102;
                        if (var7[var11] == -1.0) {
                           var6[var11] = new PointVector(var16, var18);
                        } else {
                           var6[var11].setPoint(var16, var18);
                        }

                        if (var7[var11] == 0.0) {
                           var8[var11].addCollided(var76, var12, var5.getVector());
                        } else {
                           var8[var11].setCollided(var76, var12, var5.getVector());
                        }

                        var7[var11] = 0.0;
                        continue;
                     }

                     if (Point.distanceSq(var5.getX(), var5.getY(), var76.getX2(), var76.getY2()) < var5.getRadiusSq()) {
                        double var93 = Point.distance(var5.getX(), var5.getY(), var76.getX2(), var76.getY2());
                        double var98 = (var5.getX() - var76.getX2()) / var93;
                        double var101 = (var5.getY() - var76.getY2()) / var93;
                        var16 = var76.getX2() + var5.getRadius() * var98;
                        var18 = var76.getY2() + var5.getRadius() * var101;
                        if (var7[var11] == -1.0) {
                           var6[var11] = new PointVector(var16, var18);
                        } else {
                           var6[var11].setPoint(var16, var18);
                        }

                        if (var7[var11] == 0.0) {
                           var8[var11].addCollided(var76, var12, var5.getVector());
                        } else {
                           var8[var11].setCollided(var76, var12, var5.getVector());
                        }

                        var7[var11] = 0.0;
                        continue;
                     }
                  }
               }

               double var81 = var76.getY2() - var76.getY1();
               double var86 = var76.getX1() - var76.getX2();
               double var92 = (var76.getY2() - var76.getY1()) * var76.getX1() + (var76.getX1() - var76.getX2()) * var76.getY1();
               double var22 = var5.getvy();
               double var24 = -var5.getvx();
               double var26 = var5.getvy() * var5.getX() + -var5.getvx() * var5.getY();
               double var28 = var81 * var24 - var22 * var86;
               double var30 = 0.0;
               double var32 = 0.0;
               if (var28 != 0.0) {
                  var30 = (var24 * var92 - var86 * var26) / var28;
                  var32 = (var81 * var26 - var22 * var92) / var28;
               }

               Point var34 = VectorMath.closestpointonline(var76.getX1(), var76.getY1(), var76.getX2(), var76.getY2(), var5.getX2(), var5.getY2());
               Point var35 = VectorMath.closestpointonline(var5.getX(), var5.getY(), var5.getX2(), var5.getY2(), var76.getX1(), var76.getY1());
               Point var36 = VectorMath.closestpointonline(var5.getX(), var5.getY(), var5.getX2(), var5.getY2(), var76.getX2(), var76.getY2());
               if (Point.distanceSq(var34.getX(), var34.getY(), var5.getX2(), var5.getY2()) < var5.getRadiusSq()
                     && Math.min(var76.getX1(), var76.getX2()) <= var34.getX()
                     && var34.getX() <= Math.max(var76.getX1(), var76.getX2())
                     && Math.min(var76.getY1(), var76.getY2()) <= var34.getY()
                     && var34.getY() <= Math.max(var76.getY1(), var76.getY2())
                  || Point.distanceSq(var35.getX(), var35.getY(), var76.getX1(), var76.getY1()) < var5.getRadiusSq()
                     && Math.min(var5.getX(), var5.getX() + var5.getvx()) <= var35.getX()
                     && var35.getX() <= Math.max(var5.getX(), var5.getX() + var5.getvx())
                     && Math.min(var5.getY(), var5.getY() + var5.getvy()) <= var35.getY()
                     && var35.getY() <= Math.max(var5.getY(), var5.getY() + var5.getvy())
                  || Point.distanceSq(var36.getX(), var36.getY(), var76.getX2(), var76.getY2()) < var5.getRadiusSq()
                     && Math.min(var5.getX(), var5.getX() + var5.getvx()) <= var36.getX()
                     && var36.getX() <= Math.max(var5.getX(), var5.getX() + var5.getvx())
                     && Math.min(var5.getY(), var5.getY() + var5.getvy()) <= var36.getY()
                     && var36.getY() <= Math.max(var5.getY(), var5.getY() + var5.getvy())
                  || Math.min(var5.getX(), var5.getX() + var5.getvx()) <= var30
                     && var30 <= Math.max(var5.getX(), var5.getX() + var5.getvx())
                     && Math.min(var5.getY(), var5.getY() + var5.getvy()) <= var32
                     && var32 <= Math.max(var5.getY(), var5.getY() + var5.getvy())
                     && Math.min(var76.getX1(), var76.getX2()) <= var30
                     && var30 <= Math.max(var76.getX1(), var76.getX2())
                     && Math.min(var76.getY1(), var76.getY2()) <= var32
                     && var32 <= Math.max(var76.getY1(), var76.getY2())
                  || Point.distanceSq(var76.getX1(), var76.getY1(), var5.getX2(), var5.getY2()) <= var5.getRadiusSq()
                  || Point.distanceSq(var76.getX2(), var76.getY2(), var5.getX2(), var5.getY2()) <= var5.getRadiusSq()) {
                  double var37 = -var86;
                  double var41 = var37 * var5.getX() + var81 * var5.getY();
                  double var43 = var81 * var81 - var37 * var86;
                  double var45 = 0.0;
                  double var47 = 0.0;
                  if (var43 != 0.0) {
                     var45 = (var81 * var92 - var86 * var41) / var43;
                     var47 = (var81 * var41 - var37 * var92) / var43;
                     double var49 = Point.distance(var30, var32, var5.getX(), var5.getY())
                        * var5.getRadius()
                        / Point.distance(var45, var47, var5.getX(), var5.getY());
                     var30 += -var49 * var5.getnormvx();
                     var32 += -var49 * var5.getnormvy();
                     double var51 = var37 * var30 + var81 * var32;
                     double var53 = (var81 * var92 - var86 * var51) / var43;
                     double var55 = (var81 * var51 - var37 * var92) / var43;
                     if (Math.min(var76.getX1(), var76.getX2()) <= var53
                        && var53 <= Math.max(var76.getX1(), var76.getX2())
                        && Math.min(var76.getY1(), var76.getY2()) <= var55
                        && var55 <= Math.max(var76.getY1(), var76.getY2())) {
                        var45 += var30 - var53;
                        var47 += var32 - var55;
                        double var61 = Math.pow(var30 - var5.getX(), 2.0) + Math.pow(var32 - var5.getY(), 2.0);
                        if (var61 <= var7[var11] || var7[var11] < 0.0) {
                           RectVector var63 = null;
                           if (!var8[var11].collided() || var7[var11] != var61) {
                              for (int var123 = 0; var123 < var8[var11].size(); var123++) {
                                 if (var8[var11].collided()
                                    && ((Collider)var8[var11].getColliders().get(var123)).getCollideobj() instanceof ForceCircle
                                    && var7[var11] > var61) {
                                    var6[((Collider)var8[var11].getColliders().get(var123)).getCollidewith()] = new PointVector(
                                       (PointVector)var0.get(((Collider)var8[var11].getColliders().get(var123)).getCollidewith())
                                    );
                                    var7[((Collider)var8[var11].getColliders().get(var123)).getCollidewith()] = -1.0;
                                 }
                              }
                           }

                           if (Point.distanceSq(var45, var47, var5.getX(), var5.getY()) < 1.0E-8) {
                              Point var124 = VectorMath.closestpointonline(
                                 var76.getX1() + (var30 - var45),
                                 var76.getY1() + (var32 - var47),
                                 var76.getX2() + (var30 - var45),
                                 var76.getY2() + (var32 - var47),
                                 var5.getX2(),
                                 var5.getY2()
                              );
                              var63 = new RectVector(
                                 var124.getX() + (var124.getX() - var5.getX2()) - var5.getX(), var124.getY() + (var124.getY() - var5.getY2()) - var5.getY()
                              );
                              var63 = (RectVector)var63.getUnitVector();
                              var63 = new RectVector(var63.getvx() * var5.getLength(), var63.getvy() * var5.getLength());
                           } else {
                              var63 = new RectVector(var5.getX() - 2.0 * (var45 - var30) - var30, var5.getY() - 2.0 * (var47 - var32) - var32);
                              var63 = (RectVector)var63.getUnitVector();
                              var63 = new RectVector(var63.getvx() * var5.getLength(), var63.getvy() * var5.getLength());
                           }

                           var63 = (RectVector)var63.getUnitVector();
                           var63 = new RectVector(var63.getvx() * var5.getLength(), var63.getvy() * var5.getLength());
                           if (var7[var11] == -1.0) {
                              var6[var11] = new PointVector(var30, var32);
                           } else {
                              var6[var11].setPoint(var30, var32);
                           }

                           if (var7[var11] == var61) {
                              var8[var11].addCollided(var76, var12, var63);
                           } else {
                              var8[var11].setCollided(var76, var12, var63);
                           }

                           var7[var11] = var61;
                        }
                     } else {
                        double var57 = var5.getRadius() * var5.getRadius();
                        Point var59 = VectorMath.closestpointonline(var5.getX(), var5.getY(), var5.getX2(), var5.getY2(), var76.getX1(), var76.getY1());
                        double var60 = Point.distanceSq(var59.getX(), var59.getY(), var76.getX1(), var76.getY1());
                        double var62 = Point.distanceSq(var59.getX(), var59.getY(), var5.getX(), var5.getY());
                        Point var64 = VectorMath.closestpointonline(var5.getX(), var5.getY(), var5.getX2(), var5.getY2(), var76.getX2(), var76.getY2());
                        double var65 = Point.distanceSq(var64.getX(), var64.getY(), var76.getX2(), var76.getY2());
                        double var67 = Point.distanceSq(var64.getX(), var64.getY(), var5.getX(), var5.getY());
                        double var69 = 0.0;
                        if (var62 < var67 && var60 <= var65) {
                           var69 = Math.sqrt(Math.abs(var57 - var60));
                           var30 = var59.getX() - var69 * var5.getnormvx();
                           var32 = var59.getY() - var69 * var5.getnormvy();
                           var45 = var76.getX1();
                           var47 = var76.getY1();
                        } else if (var62 > var67 && var60 >= var65) {
                           var69 = Math.sqrt(Math.abs(var57 - var65));
                           var30 = var64.getX() - var69 * var5.getnormvx();
                           var32 = var64.getY() - var69 * var5.getnormvy();
                           var45 = var76.getX2();
                           var47 = var76.getY2();
                        } else if (var60 < var65) {
                           if (!(var62 < var67) && !(Point.distanceSq(var53, var55, var76.getX1(), var76.getY1()) <= var57)) {
                              var69 = Math.sqrt(Math.abs(var57 - var65));
                              var30 = var64.getX() - var69 * var5.getnormvx();
                              var32 = var64.getY() - var69 * var5.getnormvy();
                              var45 = var76.getX2();
                              var47 = var76.getY2();
                           } else {
                              var69 = Math.sqrt(Math.abs(var57 - var60));
                              var30 = var59.getX() - var69 * var5.getnormvx();
                              var32 = var59.getY() - var69 * var5.getnormvy();
                              var45 = var76.getX1();
                              var47 = var76.getY1();
                           }
                        } else if (var60 > var65) {
                           if (!(var67 < var62) && !(Point.distanceSq(var53, var55, var76.getX2(), var76.getY2()) <= var57)) {
                              var69 = Math.sqrt(Math.abs(var57 - var60));
                              var30 = var59.getX() - var69 * var5.getnormvx();
                              var32 = var59.getY() - var69 * var5.getnormvy();
                              var45 = var76.getX1();
                              var47 = var76.getY1();
                           } else {
                              var69 = Math.sqrt(Math.abs(var57 - var65));
                              var30 = var64.getX() - var69 * var5.getnormvx();
                              var32 = var64.getY() - var69 * var5.getnormvy();
                              var45 = var76.getX2();
                              var47 = var76.getY2();
                           }
                        } else if ((
                              !(Math.min(var5.getX(), var5.getX2()) <= var64.getX())
                                 || !(var64.getX() <= Math.max(var5.getX(), var5.getX2()))
                                 || !(Math.min(var5.getY(), var5.getY2()) <= var64.getY())
                                 || !(var64.getY() <= Math.max(var5.getY(), var5.getY2()))
                           )
                           && !(Point.distanceSq(var64.getX(), var64.getY(), var5.getX2(), var5.getY2()) <= var5.getRadiusSq())) {
                           var69 = Math.sqrt(Math.abs(var57 - var60));
                           var30 = var59.getX() - var69 * var5.getnormvx();
                           var32 = var59.getY() - var69 * var5.getnormvy();
                           var45 = var76.getX1();
                           var47 = var76.getY1();
                        } else if ((
                              !(Math.min(var5.getX(), var5.getX2()) <= var59.getX())
                                 || !(var59.getX() <= Math.max(var5.getX(), var5.getX2()))
                                 || !(Math.min(var5.getY(), var5.getY2()) <= var59.getY())
                                 || !(var59.getY() <= Math.max(var5.getY(), var5.getY2()))
                           )
                           && !(Point.distanceSq(var64.getX(), var64.getY(), var5.getX2(), var5.getY2()) <= var5.getRadiusSq())) {
                           var69 = Math.sqrt(Math.abs(var57 - var65));
                           var30 = var64.getX() - var69 * var5.getnormvx();
                           var32 = var64.getY() - var69 * var5.getnormvy();
                           var45 = var76.getX2();
                           var47 = var76.getY2();
                        } else if (var62 < var67) {
                           var69 = Math.sqrt(Math.abs(var57 - var60));
                           var30 = var59.getX() - var69 * var5.getnormvx();
                           var32 = var59.getY() - var69 * var5.getnormvy();
                           var45 = var76.getX1();
                           var47 = var76.getY1();
                        } else {
                           var69 = Math.sqrt(Math.abs(var57 - var65));
                           var30 = var64.getX() - var69 * var5.getnormvx();
                           var32 = var64.getY() - var69 * var5.getnormvy();
                           var45 = var76.getX2();
                           var47 = var76.getY2();
                        }

                        double var71 = Math.pow(var30 - var5.getX(), 2.0) + Math.pow(var32 - var5.getY(), 2.0);
                        if (var71 <= var7[var11] || var7[var11] < 0.0) {
                           RectVector var73 = null;
                           if (!var8[var11].collided() || var7[var11] != var71) {
                              for (int var74 = 0; var74 < var8[var11].size(); var74++) {
                                 if (var8[var11].collided()
                                    && ((Collider)var8[var11].getColliders().get(var74)).getCollideobj() instanceof ForceCircle
                                    && var7[var11] > var71) {
                                    var6[((Collider)var8[var11].getColliders().get(var74)).getCollidewith()] = new PointVector(
                                       (PointVector)var0.get(((Collider)var8[var11].getColliders().get(var74)).getCollidewith())
                                    );
                                    var7[((Collider)var8[var11].getColliders().get(var74)).getCollidewith()] = -1.0;
                                 }
                              }
                           }

                           var73 = new RectVector(var30 - (var45 - var30) - var30, var32 - (var47 - var32) - var32);
                           var73 = (RectVector)var73.getUnitVector();
                           var73 = new RectVector(var73.getvx() * var5.getLength(), var73.getvy() * var5.getLength());
                           if (var7[var11] == -1.0) {
                              var6[var11] = new PointVector(var30, var32);
                           } else {
                              var6[var11].setPoint(var30, var32);
                           }

                           if (var7[var11] == var71) {
                              var8[var11].addCollided(var76, var12, var73);
                           } else {
                              var8[var11].setCollided(var76, var12, var73);
                           }

                           var7[var11] = var71;
                        }
                     }
                  }
               }
            }
         }
      }

      ArrayList var77 = new ArrayList((int)Math.ceil(var0.size() / 10));

      for (int var78 = 0; var78 < var6.length; var78++) {
         if (var8[var78].collided()) {
            ForceCircle var75 = (ForceCircle)var0.get(var78);
            if (var75.isFrozen()) {
               var6[var78].setRect(0.0, 0.0);
            } else {
               double var79 = 0.0;
               double var15 = 0.0;
               boolean var17 = false;
               double var90 = 0.0;

               for (int var96 = 0; var96 < var8[var78].size(); var96++) {
                  Object var97 = ((Collider)var8[var78].getColliders().get(var96)).getCollideobj();
                  var90 += ((ForceCircle)var0.get(var78)).getRestitution(((Collider)var8[var78].getColliders().get(var96)).getCollideobj());
                  if (var97 instanceof StaticLine && ((Collider)var8[var78].getColliders().get(var96)).getCollideforce() != null) {
                     var79 += ((Collider)var8[var78].getColliders().get(var96)).getCollideforce().getvx();
                     var15 += ((Collider)var8[var78].getColliders().get(var96)).getCollideforce().getvy();
                  }
               }

               var90 /= var8[var78].getColliders().size();
               if (var7[var78] == -1.0) {
                  var6[var78] = new PointVector(var6[var78].getX(), var6[var78].getY());
               }

               var6[var78].setRect(var79 * var90, var15 * var90);
               var77.add(var78);
               if (var9[var78] == 1.0 && ((ForceCircle)var0.get(var78)).getLength() != 0.0 && !var17) {
                  if (var7[var78] == 0.0) {
                     var9[var78] = 0.0;
                  } else if (var7[var78] > 0.0) {
                     var9[var78] = Math.sqrt(var7[var78]) / ((ForceCircle)var0.get(var78)).getLength();
                  } else {
                     var9[var78] = ((ForceCircle)var0.get(var78)).distance(var6[var78]) / ((ForceCircle)var0.get(var78)).getLength();
                  }
               }

               var2[var78] += var9[var78] * (1.0 - var2[var78]);
               if (!var6[var78].equals(var0.get(var78))) {
                  var3[var78] = true;
               }
            }
         }
      }

      return new Collideresult(var6, var8, var77, var2, var9, var3);
   }

   public static Collideresult checkforcecirclescollide(List<ForceCircle> var0, ArrayList<StaticLine> var1, double[] var2, boolean[] var3, boolean var4) {
      Collideresult var5 = checkforcecirclescollidetime(var0, var1, var2, var3, var4);
      new ArrayList();

      for (int var7 = var5.resultants.length - 1; var7 >= 0; var7--) {
         if (var5.collideinto[var7].collided()) {
            ((ForceCircle)var0.get(var7)).setPointVector(var5.resultants[var7]);
         }
      }

      return var5;
   }

   public static Collideresult checkforcecirclescollide(List<ForceCircle> var0, ArrayList<StaticLine> var1) {
      double[] var2 = new double[var0.size()];
      boolean[] var3 = new boolean[var0.size()];

      for (int var4 = var0.size() - 1; var4 >= 0; var4--) {
         var2[var4] = 1.0;
      }

      return checkforcecirclescollide(var0, var1, var2, var3, true);
   }

   public static boolean TEST(Vector3f var0, float var1, float var2, float var3, float var4, CarController var5) {
      Vector3f var6 = new Vector3f();
      var0.cross(new Vector3f(0.0F, 1.0F, 0.0F), var6);
      var0.x *= var4;
      var0.z *= var4;
      var6.x *= var3;
      var6.z *= var3;
      float var7 = var1 + var0.x;
      float var8 = var2 + var0.z;
      float var9 = var1 - var0.x;
      float var10 = var2 - var0.z;
      float var11 = var7 - var6.x / 2.0F;
      float var12 = var7 + var6.x / 2.0F;
      float var13 = var9 - var6.x / 2.0F;
      float var14 = var9 + var6.x / 2.0F;
      float var15 = var10 - var6.z / 2.0F;
      float var16 = var10 + var6.z / 2.0F;
      float var17 = var8 - var6.z / 2.0F;
      float var18 = var8 + var6.z / 2.0F;
      var11 += WorldSimulation.instance.offsetX;
      var17 += WorldSimulation.instance.offsetY;
      var12 += WorldSimulation.instance.offsetX;
      var18 += WorldSimulation.instance.offsetY;
      var13 += WorldSimulation.instance.offsetX;
      var15 += WorldSimulation.instance.offsetY;
      var14 += WorldSimulation.instance.offsetX;
      var16 += WorldSimulation.instance.offsetY;
      ArrayList var19 = new ArrayList();
      StaticLine var22;
      var19.add(var22 = new StaticLine(var11, var17, var12, var18));
      StaticLine var21;
      var19.add(var21 = new StaticLine(var12, var18, var14, var16));
      StaticLine var23;
      var19.add(var23 = new StaticLine(var14, var16, var13, var15));
      StaticLine var20;
      var19.add(var20 = new StaticLine(var13, var15, var11, var17));
      IsoPlayer var24 = IsoPlayer.getInstance();
      ArrayList var25 = new ArrayList();
      byte var26 = 8;
      ForceCircle var27 = new ForceCircle(var24.x, var24.y, var24.nx - var24.x, var24.ny - var24.y, 0.295);
      if (var5 != null) {
         var5.drawCircle((float)var27.getX2(), (float)var27.getY2(), 0.3F);
      }

      var25.add(var27);
      Collideresult var28 = checkforcecirclescollide(var25, var19);
      if (var5 != null) {
         var5.drawCircle((float)var27.getX(), (float)var27.getY(), (float)var27.getRadius());
      }

      if (var28.collidelist.isEmpty()) {
         return false;
      } else {
         int var30 = var28.collideinto.length;
         Vector2f var31 = new Vector2f(var24.nx - var24.x, var24.ny - var24.y);
         if (var31.length() > 0.0F) {
            var31.normalise();
         }

         for (int var32 = 0; var32 < var28.collideinto.length; var32++) {
            StaticLine var33 = (StaticLine)((Collider)var28.collideinto[var32].getColliders().get(0)).getCollideobj();
            if (var33 == var20 || var33 == var21) {
               LineDrawer.addLine(
                  var7 + WorldSimulation.instance.offsetX,
                  var8 + WorldSimulation.instance.offsetY,
                  0.0F,
                  var9 + WorldSimulation.instance.offsetX,
                  var10 + WorldSimulation.instance.offsetY,
                  0.0F,
                  1.0F,
                  1.0F,
                  1.0F,
                  null,
                  true
               );
               Point var34 = VectorMath.closestpointonline(
                  var7 + WorldSimulation.instance.offsetX,
                  var8 + WorldSimulation.instance.offsetY,
                  var9 + WorldSimulation.instance.offsetX,
                  var10 + WorldSimulation.instance.offsetY,
                  var27.getX(),
                  var27.getY()
               );
               var0.set((float)(var34.x - var24.x), (float)(var34.y - var24.y), 0.0F);
               var0.normalize();
               double var35 = VectorMath.dotproduct(var31.x, var31.y, var0.x, var0.y);
               if (var35 < 0.0) {
                  var30--;
               }
            }

            if (var33 == var22 || var33 == var23) {
               LineDrawer.addLine(
                  var1 - var6.x / 2.0F + WorldSimulation.instance.offsetX,
                  var2 - var6.z / 2.0F + WorldSimulation.instance.offsetY,
                  0.0F,
                  var1 + var6.x / 2.0F + WorldSimulation.instance.offsetX,
                  var2 + var6.z / 2.0F + WorldSimulation.instance.offsetY,
                  0.0F,
                  1.0F,
                  1.0F,
                  1.0F,
                  null,
                  true
               );
               Point var45 = VectorMath.closestpointonline(
                  var1 - var6.x / 2.0F + WorldSimulation.instance.offsetX,
                  var2 - var6.z / 2.0F + WorldSimulation.instance.offsetY,
                  var1 + var6.x / 2.0F + WorldSimulation.instance.offsetX,
                  var2 + var6.z / 2.0F + WorldSimulation.instance.offsetY,
                  var27.getX(),
                  var27.getY()
               );
               var0.set((float)(var45.x - var24.x), (float)(var45.y - var24.y), 0.0F);
               var0.normalize();
               double var46 = VectorMath.dotproduct(var31.x, var31.y, var0.x, var0.y);
               if (var46 < 0.0) {
                  var30--;
               }
            }
         }

         if (var30 == 0) {
            return false;
         } else {
            var0.set((float)var27.getX(), (float)var27.getY(), 0.0F);
            return true;
         }
      }
   }
}
