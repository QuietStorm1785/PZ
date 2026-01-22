#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/joml/Vector2f.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/core/Core.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/debug/LineDrawer.h"
#include "zombie/iso/IsoChunk.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoUtils.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/SpriteDetails/IsoFlagType.h"
#include "zombie/iso/SpriteDetails/IsoObjectType.h"
#include "zombie/iso/Vector2.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/ServerMap.h"
#include "zombie/vehicles/CollideWithObstacles/CCEdge.h"
#include "zombie/vehicles/CollideWithObstacles/CCIntersection.h"
#include "zombie/vehicles/CollideWithObstacles/CCNode.h"
#include "zombie/vehicles/CollideWithObstacles/CCObjectOutline.h"
#include "zombie/vehicles/CollideWithObstacles/CCObstacle.h"
#include "zombie/vehicles/CollideWithObstacles/CompareIntersection.h"
#include "zombie/vehicles/CollideWithObstacles/ImmutableRectF.h"
#include "zombie/vehicles/PolygonalMap2/VehiclePoly.h"

namespace zombie {
namespace vehicles {


class CollideWithObstacles {
public:
    static const float RADIUS = 0.3F;
   private const std::vector<CCObstacle> obstacles = std::make_unique<std::vector<>>();
   private const std::vector<CCNode> nodes = std::make_unique<std::vector<>>();
   private const std::vector<CCIntersection> intersections = std::make_unique<std::vector<>>();
    const ImmutableRectF moveBounds = std::make_shared<ImmutableRectF>();
    const ImmutableRectF vehicleBounds = std::make_shared<ImmutableRectF>();
    const Vector2 move = std::make_shared<Vector2>();
    const Vector2 closest = std::make_shared<Vector2>();
    const Vector2 nodeNormal = std::make_shared<Vector2>();
    const Vector2 edgeVec = std::make_shared<Vector2>();
   private const std::vector<BaseVehicle> vehicles = std::make_unique<std::vector<>>();
   CCObjectOutline[][] oo = new CCObjectOutline[5][5];
   std::vector<CCNode> obstacleTraceNodes = std::make_unique<std::vector<>>();
    CompareIntersection comparator = std::make_shared<CompareIntersection>();

    void getVehiclesInRect(float var1, float var2, float var3, float var4, int var5) {
      this.vehicles.clear();
    int var6 = (int)(var1 / 10.0F);
    int var7 = (int)(var2 / 10.0F);
    int var8 = (int)Math.ceil(var3 / 10.0F);
    int var9 = (int)Math.ceil(var4 / 10.0F);

      for (int var10 = var7; var10 < var9; var10++) {
         for (int var11 = var6; var11 < var8; var11++) {
            IsoChunk var12 = GameServer.bServer
               ? ServerMap.instance.getChunk(var11, var10)
               : IsoWorld.instance.CurrentCell.getChunkForGridSquare(var11 * 10, var10 * 10, 0);
            if (var12 != nullptr) {
               for (int var13 = 0; var13 < var12.vehicles.size(); var13++) {
    BaseVehicle var14 = (BaseVehicle)var12.vehicles.get(var13);
                  if (var14.getScript() != nullptr && (int)var14.z == var5) {
                     this.vehicles.push_back(var14);
                  }
               }
            }
         }
      }
   }

    void getObstaclesInRect(float var1, float var2, float var3, float var4, int var5, int var6, int var7) {
      this.nodes.clear();
      this.obstacles.clear();
      this.moveBounds.init(var1 - 1.0F, var2 - 1.0F, var3 - var1 + 2.0F, var4 - var2 + 2.0F);
      this.getVehiclesInRect(var1 - 1.0F - 4.0F, var2 - 1.0F - 4.0F, var3 + 2.0F + 8.0F, var4 + 2.0F + 8.0F, var7);

      for (int var8 = 0; var8 < this.vehicles.size(); var8++) {
    BaseVehicle var9 = this.vehicles.get(var8);
    VehiclePoly var10 = var9.getPolyPlusRadius();
    float var11 = Math.min(var10.x1, Math.min(var10.x2, Math.min(var10.x3, var10.x4)));
    float var12 = Math.min(var10.y1, Math.min(var10.y2, Math.min(var10.y3, var10.y4)));
    float var13 = Math.max(var10.x1, Math.max(var10.x2, Math.max(var10.x3, var10.x4)));
    float var14 = Math.max(var10.y1, Math.max(var10.y2, Math.max(var10.y3, var10.y4)));
         this.vehicleBounds.init(var11, var12, var13 - var11, var14 - var12);
         if (this.moveBounds.intersects(this.vehicleBounds)) {
    int var15 = (int)var10.z;
    CCNode var16 = CCNode.alloc().init(var10.x1, var10.y1, var15);
    CCNode var17 = CCNode.alloc().init(var10.x2, var10.y2, var15);
    CCNode var18 = CCNode.alloc().init(var10.x3, var10.y3, var15);
    CCNode var19 = CCNode.alloc().init(var10.x4, var10.y4, var15);
    CCObstacle var20 = CCObstacle.alloc().init();
    CCEdge var21 = CCEdge.alloc().init(var16, var17, var20);
    CCEdge var22 = CCEdge.alloc().init(var17, var18, var20);
    CCEdge var23 = CCEdge.alloc().init(var18, var19, var20);
    CCEdge var24 = CCEdge.alloc().init(var19, var16, var20);
            var20.edges.push_back(var21);
            var20.edges.push_back(var22);
            var20.edges.push_back(var23);
            var20.edges.push_back(var24);
            var20.calcBounds();
            this.obstacles.push_back(var20);
            this.nodes.push_back(var16);
            this.nodes.push_back(var17);
            this.nodes.push_back(var18);
            this.nodes.push_back(var19);
         }
      }

      if (!this.obstacles.empty()) {
    int var25 = var5 - 2;
    int var26 = var6 - 2;
    int var27 = var5 + 2 + 1;
    int var28 = var6 + 2 + 1;

         for (int var29 = var26; var29 < var28; var29++) {
            for (int var32 = var25; var32 < var27; var32++) {
               CCObjectOutline.get(var32 - var25, var29 - var26, var7, this.oo).init(var32 - var25, var29 - var26, var7);
            }
         }

         for (int var30 = var26; var30 < var28 - 1; var30++) {
            for (int var33 = var25; var33 < var27 - 1; var33++) {
    IsoGridSquare var35 = IsoWorld.instance.CurrentCell.getGridSquare(var33, var30, var7);
               if (var35 != nullptr) {
                  if (var35.isSolid()
                     || var35.isSolidTrans() && !var35.isAdjacentToWindow()
                     || var35.Has(IsoObjectType.stairsMN)
                     || var35.Has(IsoObjectType.stairsTN)
                     || var35.Has(IsoObjectType.stairsMW)
                     || var35.Has(IsoObjectType.stairsTW)) {
                     CCObjectOutline.setSolid(var33 - var25, var30 - var26, var7, this.oo);
                  }

    bool var39 = var35.Is(IsoFlagType.collideW);
                  if (var35.Is(IsoFlagType.windowW) || var35.Is(IsoFlagType.WindowW)) {
                     var39 = true;
                  }

                  if (var39 && var35.Is(IsoFlagType.doorW)) {
                     var39 = false;
                  }

    bool var41 = var35.Is(IsoFlagType.collideN);
                  if (var35.Is(IsoFlagType.windowN) || var35.Is(IsoFlagType.WindowN)) {
                     var41 = true;
                  }

                  if (var41 && var35.Is(IsoFlagType.doorN)) {
                     var41 = false;
                  }

                  if (var39 || var35.hasBlockedDoor(false) || var35.Has(IsoObjectType.stairsBN)) {
                     CCObjectOutline.setWest(var33 - var25, var30 - var26, var7, this.oo);
                  }

                  if (var41 || var35.hasBlockedDoor(true) || var35.Has(IsoObjectType.stairsBW)) {
                     CCObjectOutline.setNorth(var33 - var25, var30 - var26, var7, this.oo);
                  }

                  if (var35.Has(IsoObjectType.stairsBN) && var33 != var27 - 2) {
                     var35 = IsoWorld.instance.CurrentCell.getGridSquare(var33 + 1, var30, var7);
                     if (var35 != nullptr) {
                        CCObjectOutline.setWest(var33 + 1 - var25, var30 - var26, var7, this.oo);
                     }
                  } else if (var35.Has(IsoObjectType.stairsBW) && var30 != var28 - 2) {
                     var35 = IsoWorld.instance.CurrentCell.getGridSquare(var33, var30 + 1, var7);
                     if (var35 != nullptr) {
                        CCObjectOutline.setNorth(var33 - var25, var30 + 1 - var26, var7, this.oo);
                     }
                  }
               }
            }
         }

         for (int var31 = 0; var31 < var28 - var26; var31++) {
            for (int var34 = 0; var34 < var27 - var25; var34++) {
    CCObjectOutline var38 = CCObjectOutline.get(var34, var31, var7, this.oo);
               if (var38 != nullptr && var38.nw && var38.nw_w && var38.nw_n) {
                  var38.trace(this.oo, this.obstacleTraceNodes);
                  if (!var38.nodes.empty()) {
    CCObstacle var40 = CCObstacle.alloc().init();
    CCNode var42 = (CCNode)var38.nodes.get(var38.nodes.size() - 1);

                     for (int var43 = var38.nodes.size() - 1; var43 > 0; var43--) {
    CCNode var44 = (CCNode)var38.nodes.get(var43);
    CCNode var45 = (CCNode)var38.nodes.get(var43 - 1);
                        var44.x += var25;
                        var44.y += var26;
    CCEdge var46 = CCEdge.alloc().init(var44, var45, var40);
    float var47 = var45.x + (var45 != var42 ? var25 : 0.0F);
    float var48 = var45.y + (var45 != var42 ? var26 : 0.0F);
                        var46.normal.set(var47 - var44.x, var48 - var44.y);
                        var46.normal.normalize();
                        var46.normal.rotate((float)Math.toRadians(90.0));
                        var40.edges.push_back(var46);
                        this.nodes.push_back(var44);
                     }

                     var40.calcBounds();
                     this.obstacles.push_back(var40);
                  }
               }
            }
         }
      }
   }

    void checkEdgeIntersection() {
    bool var1 = Core.bDebug && DebugOptions.instance.CollideWithObstaclesRenderObstacles.getValue();

      for (int var2 = 0; var2 < this.obstacles.size(); var2++) {
    CCObstacle var3 = this.obstacles.get(var2);

         for (int var4 = var2 + 1; var4 < this.obstacles.size(); var4++) {
    CCObstacle var5 = this.obstacles.get(var4);
            if (var3.bounds.intersects(var5.bounds)) {
               for (int var6 = 0; var6 < var3.edges.size(); var6++) {
    CCEdge var7 = (CCEdge)var3.edges.get(var6);

                  for (int var8 = 0; var8 < var5.edges.size(); var8++) {
    CCEdge var9 = (CCEdge)var5.edges.get(var8);
    CCIntersection var10 = this.getIntersection(var7, var9);
                     if (var10 != nullptr) {
                        var7.intersections.push_back(var10);
                        var9.intersections.push_back(var10);
                        if (var1) {
                           LineDrawer.addLine(
                              var10.nodeSplit.x - 0.1F,
                              var10.nodeSplit.y - 0.1F,
                              var7.node1.z,
                              var10.nodeSplit.x + 0.1F,
                              var10.nodeSplit.y + 0.1F,
                              var7.node1.z,
                              1.0F,
                              0.0F,
                              0.0F,
                              nullptr,
                              false
                           );
                        }

                        if (!var7.hasNode(var10.nodeSplit) && !var9.hasNode(var10.nodeSplit)) {
                           this.nodes.push_back(var10.nodeSplit);
                        }

                        this.intersections.push_back(var10);
                     }
                  }
               }
            }
         }
      }

      for (int var11 = 0; var11 < this.obstacles.size(); var11++) {
    CCObstacle var12 = this.obstacles.get(var11);

         for (int var13 = var12.edges.size() - 1; var13 >= 0; var13--) {
    CCEdge var14 = (CCEdge)var12.edges.get(var13);
            if (!var14.intersections.empty()) {
               this.comparator.edge = var14;
               Collections.sort(var14.intersections, this.comparator);

               for (int var15 = var14.intersections.size() - 1; var15 >= 0; var15--) {
    CCIntersection var16 = (CCIntersection)var14.intersections.get(var15);
    CCEdge var17 = var16.split(var14);
               }
            }
         }
      }
   }

    bool collinear(float var1, float var2, float var3, float var4, float var5, float var6) {
    float var7 = (var3 - var1) * (var6 - var2) - (var5 - var1) * (var4 - var2);
      return var7 >= -0.05F && var7 < 0.05F;
   }

    bool within(float var1, float var2, float var3) {
      return var1 <= var2 && var2 <= var3 || var3 <= var2 && var2 <= var1;
   }

    bool is_on(float var1, float var2, float var3, float var4, float var5, float var6) {
      return this.collinear(var1, var2, var3, var4, var5, var6) && (var1 != var3 ? this.within(var1, var5, var3) : this.within(var2, var6, var4));
   }

    CCIntersection getIntersection(CCEdge var1, CCEdge var2) {
    float var3 = var1.node1.x;
    float var4 = var1.node1.y;
    float var5 = var1.node2.x;
    float var6 = var1.node2.y;
    float var7 = var2.node1.x;
    float var8 = var2.node1.y;
    float var9 = var2.node2.x;
    float var10 = var2.node2.y;
    double var11 = (var10 - var8) * (var5 - var3) - (var9 - var7) * (var6 - var4);
      if (var11 > -0.01 && var11 < 0.01) {
    return nullptr;
      } else {
    double var13 = ((var9 - var7) * (var4 - var8) - (var10 - var8) * (var3 - var7)) / var11;
    double var15 = ((var5 - var3) * (var4 - var8) - (var6 - var4) * (var3 - var7)) / var11;
         if (var13 >= 0.0 && var13 <= 1.0 && var15 >= 0.0 && var15 <= 1.0) {
    float var17 = (float)(var3 + var13 * (var5 - var3));
    float var18 = (float)(var4 + var13 * (var6 - var4));
    CCNode var19 = nullptr;
    CCNode var20 = nullptr;
            if (var13 < 0.01F) {
               var19 = var1.node1;
            } else if (var13 > 0.99F) {
               var19 = var1.node2;
            }

            if (var15 < 0.01F) {
               var20 = var2.node1;
            } else if (var15 > 0.99F) {
               var20 = var2.node2;
            }

            if (var19 != nullptr && var20 != nullptr) {
    CCIntersection var21 = CCIntersection.alloc().init(var1, var2, (float)var13, (float)var15, var19);
               var1.intersections.push_back(var21);
               this.intersections.push_back(var21);
               var21 = CCIntersection.alloc().init(var1, var2, (float)var13, (float)var15, var20);
               var2.intersections.push_back(var21);
               this.intersections.push_back(var21);
               LineDrawer.addLine(
                  var21.nodeSplit.x - 0.1F,
                  var21.nodeSplit.y - 0.1F,
                  var1.node1.z,
                  var21.nodeSplit.x + 0.1F,
                  var21.nodeSplit.y + 0.1F,
                  var1.node1.z,
                  1.0F,
                  0.0F,
                  0.0F,
                  nullptr,
                  false
               );
    return nullptr;
            } else {
               return var19 == nullptr && var20 == nullptr
                  ? CCIntersection.alloc().init(var1, var2, (float)var13, (float)var15, var17, var18)
                  : CCIntersection.alloc().init(var1, var2, (float)var13, (float)var15, var19 == nullptr ? var20 : var19);
            }
         } else {
    return nullptr;
         }
      }
   }

    void checkNodesInObstacles() {
      for (int var1 = 0; var1 < this.nodes.size(); var1++) {
    CCNode var2 = this.nodes.get(var1);

         for (int var3 = 0; var3 < this.obstacles.size(); var3++) {
    CCObstacle var4 = this.obstacles.get(var3);
    bool var5 = false;

            for (int var6 = 0; var6 < this.intersections.size(); var6++) {
    CCIntersection var7 = this.intersections.get(var6);
               if (var7.nodeSplit == var2) {
                  if (var7.edge1.obstacle == var4 || var7.edge2.obstacle == var4) {
                     var5 = true;
                  }
                  break;
               }
            }

            if (!var5 && var4.isNodeInsideOf(var2)) {
               var2.ignore = true;
               break;
            }
         }
      }
   }

    bool isVisible(CCNode var1, CCNode var2) {
      return var1.sharesEdge(var2) ? !var1.onSameShapeButDoesNotShareAnEdge(var2) : !var1.sharesShape(var2);
   }

    void calculateNodeVisibility() {
      for (int var1 = 0; var1 < this.obstacles.size(); var1++) {
    CCObstacle var2 = this.obstacles.get(var1);

         for (int var3 = 0; var3 < var2.edges.size(); var3++) {
    CCEdge var4 = (CCEdge)var2.edges.get(var3);
            if (!var4.node1.ignore && !var4.node2.ignore && this.isVisible(var4.node1, var4.node2)) {
               var4.node1.visible.push_back(var4.node2);
               var4.node2.visible.push_back(var4.node1);
            }
         }
      }
   }

    Vector2f resolveCollision(IsoGameCharacter var1, float var2, float var3, Vector2f var4) {
      var4.set(var2, var3);
      if (var1.getCurrentSquare() != nullptr && var1.getCurrentSquare().HasStairs()) {
    return var4;
      } else {
    bool var5 = Core.bDebug && DebugOptions.instance.CollideWithObstaclesRenderObstacles.getValue();
    float var6 = var1.x;
    float var7 = var1.y;
    float var8 = var2;
    float var9 = var3;
         if (var5) {
            LineDrawer.addLine(var6, var7, (int)var1.z, var2, var3, (int)var1.z, 1.0F, 1.0F, 1.0F, nullptr, true);
         }

         if (var6 == var2 && var7 == var3) {
    return var4;
         } else {
            this.move.set(var2 - var1.x, var3 - var1.y);
            this.move.normalize();

            for (int var10 = 0; var10 < this.nodes.size(); var10++) {
               this.nodes.get(var10).release();
            }

            for (int var37 = 0; var37 < this.obstacles.size(); var37++) {
    CCObstacle var11 = this.obstacles.get(var37);

               for (int var12 = 0; var12 < var11.edges.size(); var12++) {
                  ((CCEdge)var11.edges.get(var12)).release();
               }

               var11.release();
            }

            for (int var38 = 0; var38 < this.intersections.size(); var38++) {
               this.intersections.get(var38).release();
            }

            this.intersections.clear();
            this.getObstaclesInRect(
               Math.min(var6, var2), Math.min(var7, var3), Math.max(var6, var2), Math.max(var7, var3), (int)var1.x, (int)var1.y, (int)var1.z
            );
            this.checkEdgeIntersection();
            this.checkNodesInObstacles();
            this.calculateNodeVisibility();
            if (var5) {
               for (CCNode var41 : this.nodes) {
                  for (CCNode var13 : var41.visible) {
                     LineDrawer.addLine(var41.x, var41.y, var41.z, var13.x, var13.y, var13.z, 0.0F, 1.0F, 0.0F, nullptr, true);
                  }

                  if (DebugOptions.instance.CollideWithObstaclesRenderNormals.getValue() && var41.getNormalAndEdgeVectors(this.nodeNormal, this.edgeVec)) {
                     LineDrawer.addLine(
                        var41.x, var41.y, var41.z, var41.x + this.nodeNormal.x, var41.y + this.nodeNormal.y, var41.z, 0.0F, 0.0F, 1.0F, nullptr, true
                     );
                  }

                  if (var41.ignore) {
                     LineDrawer.addLine(var41.x - 0.05F, var41.y - 0.05F, var41.z, var41.x + 0.05F, var41.y + 0.05F, var41.z, 1.0F, 1.0F, 0.0F, nullptr, false);
                  }
               }
            }

    CCEdge var40 = nullptr;
    CCNode var42 = nullptr;
    double var44 = double.MAX_VALUE;

            for (int var14 = 0; var14 < this.obstacles.size(); var14++) {
    CCObstacle var15 = this.obstacles.get(var14);
    uint8_t var16 = 0;
               if (var15.isPointInside(var1.x, var1.y, var16)) {
                  for (int var17 = 0; var17 < var15.edges.size(); var17++) {
    CCEdge var18 = (CCEdge)var15.edges.get(var17);
                     if (var18.node1.visible.contains(var18.node2)) {
    CCNode var19 = var18.closestPoint(var1.x, var1.y, this.closest);
    double var20 = (var1.x - this.closest.x) * (var1.x - this.closest.x) + (var1.y - this.closest.y) * (var1.y - this.closest.y);
                        if (var20 < var44) {
                           var44 = var20;
                           var40 = var18;
                           var42 = var19;
                        }
                     }
                  }
               }
            }

            if (var40 != nullptr) {
    float var45 = var40.normal.dot(this.move);
               if (var45 >= 0.01F) {
                  var40 = nullptr;
               }
            }

            if (var42 != nullptr
               && var42.getNormalAndEdgeVectors(this.nodeNormal, this.edgeVec)
               && this.nodeNormal.dot(this.move) + 0.05F >= this.nodeNormal.dot(this.edgeVec)) {
               var42 = nullptr;
               var40 = nullptr;
            }

            if (var40 == nullptr) {
    double var46 = double.MAX_VALUE;
               var40 = nullptr;
               var42 = nullptr;

               for (int var51 = 0; var51 < this.obstacles.size(); var51++) {
    CCObstacle var56 = this.obstacles.get(var51);

                  for (int var59 = 0; var59 < var56.edges.size(); var59++) {
    CCEdge var60 = (CCEdge)var56.edges.get(var59);
                     if (var60.node1.visible.contains(var60.node2)) {
    float var61 = var60.node1.x;
    float var21 = var60.node1.y;
    float var22 = var60.node2.x;
    float var23 = var60.node2.y;
    float var24 = var61 + 0.5F * (var22 - var61);
    float var25 = var21 + 0.5F * (var23 - var21);
                        if (var5 && DebugOptions.instance.CollideWithObstaclesRenderNormals.getValue()) {
                           LineDrawer.addLine(
                              var24, var25, var60.node1.z, var24 + var60.normal.x, var25 + var60.normal.y, var60.node1.z, 0.0F, 0.0F, 1.0F, nullptr, true
                           );
                        }

    double var26 = (var23 - var21) * (var8 - var6) - (var22 - var61) * (var9 - var7);
                        if (var26 != 0.0) {
    double var28 = ((var22 - var61) * (var7 - var21) - (var23 - var21) * (var6 - var61)) / var26;
    double var30 = ((var8 - var6) * (var7 - var21) - (var9 - var7) * (var6 - var61)) / var26;
    float var32 = var60.normal.dot(this.move);
                           if (!(var32 >= 0.0F) && var28 >= 0.0 && var28 <= 1.0 && var30 >= 0.0 && var30 <= 1.0) {
                              if (var30 < 0.01 || var30 > 0.99) {
    CCNode var33 = var30 < 0.01 ? var60.node1 : var60.node2;
                                 if (var33.getNormalAndEdgeVectors(this.nodeNormal, this.edgeVec)) {
                                    if (!(this.nodeNormal.dot(this.move) + 0.05F >= this.nodeNormal.dot(this.edgeVec))) {
                                       var40 = var60;
                                       var42 = var33;
                                       break;
                                    }
                                    continue;
                                 }
                              }

    float var62 = (float)(var6 + var28 * (var8 - var6));
    float var34 = (float)(var7 + var28 * (var9 - var7));
    double var35 = IsoUtils.DistanceToSquared(var6, var7, var62, var34);
                              if (var35 < var46) {
                                 var46 = var35;
                                 var40 = var60;
                              }
                           }
                        }
                     }
                  }
               }
            }

            if (var42 != nullptr) {
    CCEdge var47 = var40;
    CCEdge var49 = nullptr;

               for (int var52 = 0; var52 < var42.edges.size(); var52++) {
    CCEdge var57 = (CCEdge)var42.edges.get(var52);
                  if (var57.node1.visible.contains(var57.node2)
                     && var57 != var40
                     && (var47.node1.x != var57.node1.x || var47.node1.y != var57.node1.y || var47.node2.x != var57.node2.x || var47.node2.y != var57.node2.y)
                     && (var47.node1.x != var57.node2.x || var47.node1.y != var57.node2.y || var47.node2.x != var57.node1.x || var47.node2.y != var57.node1.y)
                     && (!var47.hasNode(var57.node1) || !var47.hasNode(var57.node2))) {
                     var49 = var57;
                  }
               }

               if (var47 != nullptr && var49 != nullptr) {
                  if (var40 == var47) {
    CCNode var53 = var42 == var49.node1 ? var49.node2 : var49.node1;
                     this.edgeVec.set(var53.x - var42.x, var53.y - var42.y);
                     this.edgeVec.normalize();
                     if (this.move.dot(this.edgeVec) >= 0.0F) {
                        var40 = var49;
                     }
                  } else if (var40 == var49) {
    CCNode var54 = var42 == var47.node1 ? var47.node2 : var47.node1;
                     this.edgeVec.set(var54.x - var42.x, var54.y - var42.y);
                     this.edgeVec.normalize();
                     if (this.move.dot(this.edgeVec) >= 0.0F) {
                        var40 = var47;
                     }
                  }
               }
            }

            if (var40 != nullptr) {
    float var48 = var40.node1.x;
    float var50 = var40.node1.y;
    float var55 = var40.node2.x;
    float var58 = var40.node2.y;
               if (var5) {
                  LineDrawer.addLine(var48, var50, var40.node1.z, var55, var58, var40.node1.z, 0.0F, 1.0F, 1.0F, nullptr, true);
               }

               var40.closestPoint(var2, var3, this.closest);
               var4.set(this.closest.x, this.closest.y);
            }

    return var4;
         }
      }
   }
}
} // namespace vehicles
} // namespace zombie
