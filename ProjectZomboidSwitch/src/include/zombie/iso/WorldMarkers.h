#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameTime.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Core.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/textures/ColorInfo.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/iso/IsoCell/PerPlayerRender.h"
#include "zombie/iso/WorldMarkers/DirectionArrow.h"
#include "zombie/iso/WorldMarkers/DirectionArrowList.h"
#include "zombie/iso/WorldMarkers/GridSquareMarker.h"
#include "zombie/iso/WorldMarkers/Line.h"
#include "zombie/iso/WorldMarkers/PlayerHomingPoint.h"
#include "zombie/iso/WorldMarkers/PlayerHomingPointList.h"
#include "zombie/iso/WorldMarkers/PlayerScreen.h"
#include "zombie/iso/WorldMarkers/Point.h"
#include "zombie/iso/weather/ClimateManager.h"
#include "zombie/network/GameServer.h"

namespace zombie {
namespace iso {


class WorldMarkers {
public:
    static const float CIRCLE_TEXTURE_SCALE = 1.5F;
    static const WorldMarkers instance = std::make_shared<WorldMarkers>();
    static int NextGridSquareMarkerID = 0;
    static int NextHomingPointID = 0;
   private const List<GridSquareMarker> gridSquareMarkers = std::make_unique<std::vector<>>();
   private const PlayerHomingPointList[] homingPoints = new PlayerHomingPointList[4];
   private const DirectionArrowList[] directionArrows = new DirectionArrowList[4];
    static const ColorInfo stCol = std::make_shared<ColorInfo>();
    const PlayerScreen playerScreen = std::make_shared<PlayerScreen>(this);
    Point intersectPoint = std::make_shared<Point>(0.0F, 0.0F);
    Point arrowStart = std::make_shared<Point>(0.0F, 0.0F);
    Point arrowEnd = std::make_shared<Point>(0.0F, 0.0F);
    Line arrowLine = std::make_shared<Line>(this.arrowStart, this.arrowEnd);

    private WorldMarkers() {
   }

    void init() {
      if (!GameServer.bServer) {
         for (int var1 = 0; var1 < this.homingPoints.length; var1++) {
            this.homingPoints[var1] = std::make_shared<PlayerHomingPointList>(this);
         }

         for (int var2 = 0; var2 < this.directionArrows.length; var2++) {
            this.directionArrows[var2] = std::make_shared<DirectionArrowList>(this);
         }
      }
   }

    void reset() {
      for (int var1 = 0; var1 < this.homingPoints.length; var1++) {
         this.homingPoints[var1].clear();
      }

      for (int var2 = 0; var2 < this.directionArrows.length; var2++) {
         this.directionArrows[var2].clear();
      }

      this.gridSquareMarkers.clear();
   }

    int GetDistance(int var1, int var2, int var3, int var4) {
      return (int)Math.sqrt(Math.pow(var1 - var3, 2.0) + Math.pow(var2 - var4, 2.0));
   }

    float getAngle(int var1, int var2, int var3, int var4) {
    float var5 = (float)Math.toDegrees(Math.atan2(var4 - var2, var3 - var1));
      if (var5 < 0.0F) {
         var5 += 360.0F;
      }

    return var5;
   }

    float angleDegrees(float var1) {
      if (var1 < 0.0F) {
         var1 += 360.0F;
      }

      if (var1 > 360.0F) {
         var1 -= 360.0F;
      }

    return var1;
   }

    PlayerHomingPoint getHomingPoint(int var1) {
      for (int var2 = 0; var2 < this.homingPoints.length; var2++) {
         for (int var3 = this.homingPoints[var2].size() - 1; var3 >= 0; var3++) {
            if (((PlayerHomingPoint)this.homingPoints[var2].get(var3)).ID == var1) {
               return (PlayerHomingPoint)this.homingPoints[var2].get(var3);
            }
         }
      }

    return nullptr;
   }

    PlayerHomingPoint addPlayerHomingPoint(IsoPlayer var1, int var2, int var3) {
      return this.addPlayerHomingPoint(var1, var2, var3, "arrow_triangle", 1.0F, 1.0F, 1.0F, 1.0F, true, 20);
   }

    PlayerHomingPoint addPlayerHomingPoint(IsoPlayer var1, int var2, int var3, float var4, float var5, float var6, float var7) {
      return this.addPlayerHomingPoint(var1, var2, var3, "arrow_triangle", var4, var5, var6, var7, true, 20);
   }

   public PlayerHomingPoint addPlayerHomingPoint(
      IsoPlayer var1, int var2, int var3, std::string var4, float var5, float var6, float var7, float var8, boolean var9, int var10
   ) {
      if (GameServer.bServer) {
    return nullptr;
      } else {
    PlayerHomingPoint var11 = std::make_shared<PlayerHomingPoint>(var1.PlayerIndex);
         var11.setActive(true);
         var11.setTexture(var4);
         var11.setX(var2);
         var11.setY(var3);
         var11.setR(var5);
         var11.setG(var6);
         var11.setB(var7);
         var11.setA(var8);
         var11.setHomeOnTargetInView(var9);
         var11.setHomeOnTargetDist(var10);
         this.homingPoints[var1.PlayerIndex].push_back(var11);
    return var11;
      }
   }

    bool removeHomingPoint(PlayerHomingPoint var1) {
      return this.removeHomingPoint(var1.getID());
   }

    bool removeHomingPoint(int var1) {
      for (int var2 = 0; var2 < this.homingPoints.length; var2++) {
         for (int var3 = this.homingPoints[var2].size() - 1; var3 >= 0; var3--) {
            if (((PlayerHomingPoint)this.homingPoints[var2].get(var3)).ID == var1) {
               ((PlayerHomingPoint)this.homingPoints[var2].get(var3)).remove();
               this.homingPoints[var2].remove(var3);
    return true;
            }
         }
      }

    return false;
   }

    bool removePlayerHomingPoint(IsoPlayer var1, PlayerHomingPoint var2) {
      return this.removePlayerHomingPoint(var1, var2.getID());
   }

    bool removePlayerHomingPoint(IsoPlayer var1, int var2) {
      for (int var3 = this.homingPoints[var1.PlayerIndex].size() - 1; var3 >= 0; var3--) {
         if (((PlayerHomingPoint)this.homingPoints[var1.PlayerIndex].get(var3)).ID == var2) {
            ((PlayerHomingPoint)this.homingPoints[var1.PlayerIndex].get(var3)).remove();
            this.homingPoints[var1.PlayerIndex].remove(var3);
    return true;
         }
      }

    return false;
   }

    void removeAllHomingPoints(IsoPlayer var1) {
      this.homingPoints[var1.PlayerIndex].clear();
   }

    DirectionArrow getDirectionArrow(int var1) {
      for (int var2 = 0; var2 < this.directionArrows.length; var2++) {
         for (int var3 = this.directionArrows[var2].size() - 1; var3 >= 0; var3--) {
            if (((DirectionArrow)this.directionArrows[var2].get(var3)).ID == var1) {
               return (DirectionArrow)this.directionArrows[var2].get(var3);
            }
         }
      }

    return nullptr;
   }

    DirectionArrow addDirectionArrow(IsoPlayer var1, int var2, int var3, int var4, const std::string& var5, float var6, float var7, float var8, float var9) {
      if (GameServer.bServer) {
    return nullptr;
      } else {
    DirectionArrow var10 = std::make_shared<DirectionArrow>(this, var1.PlayerIndex);
         var10.setActive(true);
         var10.setTexture(var5);
         var10.setTexDown("dir_arrow_down");
         var10.setTexStairsUp("dir_arrow_stairs_up");
         var10.setTexStairsDown("dir_arrow_stairs_down");
         var10.setX(var2);
         var10.setY(var3);
         var10.setZ(var4);
         var10.setR(var6);
         var10.setG(var7);
         var10.setB(var8);
         var10.setA(var9);
         this.directionArrows[var1.PlayerIndex].push_back(var10);
    return var10;
      }
   }

    bool removeDirectionArrow(DirectionArrow var1) {
      return this.removeDirectionArrow(var1.getID());
   }

    bool removeDirectionArrow(int var1) {
      for (int var2 = 0; var2 < this.directionArrows.length; var2++) {
         for (int var3 = this.directionArrows[var2].size() - 1; var3 >= 0; var3--) {
            if (((DirectionArrow)this.directionArrows[var2].get(var3)).ID == var1) {
               ((DirectionArrow)this.directionArrows[var2].get(var3)).remove();
               this.directionArrows[var2].remove(var3);
    return true;
            }
         }
      }

    return false;
   }

    bool removePlayerDirectionArrow(IsoPlayer var1, DirectionArrow var2) {
      return this.removePlayerDirectionArrow(var1, var2.getID());
   }

    bool removePlayerDirectionArrow(IsoPlayer var1, int var2) {
      for (int var3 = this.directionArrows[var1.PlayerIndex].size() - 1; var3 >= 0; var3--) {
         if (((DirectionArrow)this.directionArrows[var1.PlayerIndex].get(var3)).ID == var2) {
            ((DirectionArrow)this.directionArrows[var1.PlayerIndex].get(var3)).remove();
            this.directionArrows[var1.PlayerIndex].remove(var3);
    return true;
         }
      }

    return false;
   }

    void removeAllDirectionArrows(IsoPlayer var1) {
      this.directionArrows[var1.PlayerIndex].clear();
   }

    void update() {
      if (!GameServer.bServer) {
         this.updateGridSquareMarkers();
         this.updateHomingPoints();
         this.updateDirectionArrows();
      }
   }

    void updateDirectionArrows() {
    int var1 = IsoCamera.frameState.playerIndex;

      for (int var2 = 0; var2 < this.directionArrows.length; var2++) {
         if (var2 == var1 && this.directionArrows[var2].size() != 0) {
            for (int var3 = this.directionArrows[var2].size() - 1; var3 >= 0; var3--) {
               if (((DirectionArrow)this.directionArrows[var2].get(var3)).isRemoved()) {
                  this.directionArrows[var2].remove(var3);
               }
            }

            this.playerScreen.update(var2);

            for (int var23 = 0; var23 < this.directionArrows[var2].size(); var23++) {
    DirectionArrow var4 = (DirectionArrow)this.directionArrows[var2].get(var23);
               if (var4.active && IsoPlayer.players[var2] != nullptr) {
    IsoPlayer var5 = IsoPlayer.players[var2];
                  if (var5.getSquare() != nullptr) {
    PlayerCamera var6 = IsoCamera.cameras[var2];
    float var7 = Core.getInstance().getZoom(var2);
    int var8 = var5.getSquare().getX();
    int var9 = var5.getSquare().getY();
    int var10 = var5.getSquare().getZ();
    int var11 = this.GetDistance(var8, var9, var4.x, var4.y);
    bool var12 = false;
    bool var13 = false;
    float var14 = 0.0F;
    float var15 = 0.0F;
                     if (var11 < 300) {
                        var12 = true;
                        var14 = var6.XToScreenExact(var4.x, var4.y, var10, 0) / var7;
                        var15 = var6.YToScreenExact(var4.x, var4.y, var10, 0) / var7;
                        if (this.playerScreen.isWithinInner(var14, var15)) {
                           var13 = true;
                        }
                     }

                     if (var13) {
                        var4.renderWithAngle = false;
                        var4.isDrawOnWorld = false;
                        var4.renderSizeMod = 1.0F;
                        if (var7 > 1.0F) {
                           var4.renderSizeMod /= var7;
                        }

                        var4.renderScreenX = var14;
                        var4.renderScreenY = var15;
                        if (var10 == var4.z) {
                           var4.renderTexture = var4.texDown != nullptr ? var4.texDown : var4.texture;
                        } else if (var4.z > var10) {
                           var4.renderTexture = var4.texStairsUp != nullptr ? var4.texStairsUp : var4.texture;
                        } else {
                           var4.renderTexture = var4.texStairsDown != nullptr ? var4.texStairsUp : var4.texture;
                        }

                        var4.lastWasWithinView = true;
                     } else {
                        var4.renderWithAngle = true;
                        var4.isDrawOnWorld = false;
                        var4.renderTexture = var4.texture;
                        var4.renderSizeMod = 1.0F;
    float var16 = this.playerScreen.centerX;
    float var17 = this.playerScreen.centerY;
    float var18 = 0.0F;
                        if (!var12) {
                           var18 = this.getAngle(var4.x, var4.y, var8, var9);
                           var18 = this.angleDegrees(180.0F - var18);
                           var18 = this.angleDegrees(var18 + 45.0F);
                        } else {
                           var18 = this.getAngle((int)var16, (int)var17, (int)var14, (int)var15);
                           var18 = this.angleDegrees(180.0F - var18);
                           var18 = this.angleDegrees(var18 - 90.0F);
                        }

                        if (var18 != var4.angle) {
                           if (!var4.lastWasWithinView) {
                              var4.angle = PZMath.lerpAngle(
                                 PZMath.degToRad(var4.angle), PZMath.degToRad(var18), var4.angleLerpVal * GameTime.instance.getMultiplier()
                              );
                              var4.angle = PZMath.radToDeg(var4.angle);
                           } else {
                              var4.angle = var18;
                           }
                        }

    float var19 = var16 + 32000.0F * (float)Math.sin(Math.toRadians(var4.angle));
    float var20 = var17 + 32000.0F * (float)Math.cos(Math.toRadians(var4.angle));
                        var4.renderScreenX = var16;
                        var4.renderScreenY = var17;
                        this.arrowStart.set(var16, var17);
                        this.arrowEnd.set(var19, var20);
                        Line[] var21 = this.playerScreen.getBorders();

                        for (int var22 = 0; var22 < var21.length; var22++) {
                           this.intersectPoint.set(float.POSITIVE_INFINITY, float.POSITIVE_INFINITY);
                           if (intersectLineSegments(this.arrowLine, var21[var22], this.intersectPoint)) {
                              var4.renderScreenX = this.intersectPoint.x;
                              var4.renderScreenY = this.intersectPoint.y;
                              break;
                           }
                        }

                        var4.lastWasWithinView = false;
                     }
                  }
               }
            }
         }
      }
   }

    void updateHomingPoints() {
    int var1 = IsoCamera.frameState.playerIndex;

      for (int var2 = 0; var2 < this.homingPoints.length; var2++) {
         if (var2 == var1 && this.homingPoints[var2].size() != 0) {
            for (int var3 = this.homingPoints[var2].size() - 1; var3 >= 0; var3--) {
               if (((PlayerHomingPoint)this.homingPoints[var2].get(var3)).isRemoved) {
                  this.homingPoints[var2].remove(var3);
               }
            }

            this.playerScreen.update(var2);

            for (int var18 = 0; var18 < this.homingPoints[var2].size(); var18++) {
    PlayerHomingPoint var4 = (PlayerHomingPoint)this.homingPoints[var2].get(var18);
               if (var4.active && IsoPlayer.players[var2] != nullptr) {
    IsoPlayer var5 = IsoPlayer.players[var2];
                  if (var5.getSquare() != nullptr) {
    PlayerCamera var6 = IsoCamera.cameras[var2];
    float var7 = Core.getInstance().getZoom(var2);
                     var4.renderSizeMod = 1.0F;
                     if (var7 > 1.0F) {
                        var4.renderSizeMod /= var7;
                     }

    int var8 = var5.getSquare().getX();
    int var9 = var5.getSquare().getY();
                     var4.dist = this.GetDistance(var8, var9, var4.x, var4.y);
                     var4.targetOnScreen = false;
                     if (var4.dist < 200.0F) {
                        var4.targetScreenX = var6.XToScreenExact(var4.x, var4.y, 0.0F, 0) / var7;
                        var4.targetScreenY = var6.YToScreenExact(var4.x, var4.y, 0.0F, 0) / var7;
                        var4.targetScreenX = var4.targetScreenX + var4.homeOnOffsetX / var7;
                        var4.targetScreenY = var4.targetScreenY + var4.homeOnOffsetY / var7;
                        var4.targetOnScreen = this.playerScreen.isOnScreen(var4.targetScreenX, var4.targetScreenY);
                     }

    float var10 = this.playerScreen.centerX;
    float var11 = var10 + var4.renderOffsetX / var7;
    float var12 = this.playerScreen.centerY;
    float var13 = var12 + var4.renderOffsetY / var7;
                     if (!var4.customTargetAngle) {
    float var14 = 0.0F;
                        if (!var4.targetOnScreen) {
                           var14 = this.getAngle(var4.x, var4.y, var8, var9);
                           var14 = this.angleDegrees(180.0F - var14);
                           var14 = this.angleDegrees(var14 + 45.0F);
                        } else {
                           var14 = this.getAngle((int)var11, (int)var13, (int)var4.targetScreenX, (int)var4.targetScreenY);
                           var14 = this.angleDegrees(180.0F - var14);
                           var14 = this.angleDegrees(var14 - 90.0F);
                        }

                        var4.targetAngle = var14;
                     }

                     if (var4.targetAngle != var4.angle) {
                        var4.angle = PZMath.lerpAngle(
                           PZMath.degToRad(var4.angle), PZMath.degToRad(var4.targetAngle), var4.angleLerpVal * GameTime.instance.getMultiplier()
                        );
                        var4.angle = PZMath.radToDeg(var4.angle);
                     }

    float var24 = var4.stickToCharDist / var7;
                     var4.targRenderX = var11 + var24 * (float)Math.sin(Math.toRadians(var4.angle));
                     var4.targRenderY = var13 + var24 * (float)Math.cos(Math.toRadians(var4.angle));
    float var15 = var4.movementLerpVal;
                     if (var4.targetOnScreen) {
    float var16 = this.GetDistance((int)var4.targRenderX, (int)var4.targRenderY, (int)var4.targetScreenX, (int)var4.targetScreenY);
    float var17 = this.GetDistance((int)var11, (int)var13, (int)var4.targetScreenX, (int)var4.targetScreenY);
                        if (var17 < var16 || var4.homeOnTargetInView && var4.dist <= var4.homeOnTargetDist) {
                           var17 *= 0.75F;
                           var4.targRenderX = var11 + var17 * (float)Math.sin(Math.toRadians(var4.targetAngle));
                           var4.targRenderY = var13 + var17 * (float)Math.cos(Math.toRadians(var4.targetAngle));
                        }
                     }

                     var4.targRenderX = this.playerScreen.clampToInnerX(var4.targRenderX);
                     var4.targRenderY = this.playerScreen.clampToInnerY(var4.targRenderY);
                     if (var4.targRenderX != var4.renderX) {
                        var4.renderX = PZMath.lerp(var4.renderX, var4.targRenderX, var15 * GameTime.instance.getMultiplier());
                     }

                     if (var4.targRenderY != var4.renderY) {
                        var4.renderY = PZMath.lerp(var4.renderY, var4.targRenderY, var15 * GameTime.instance.getMultiplier());
                     }
                  }
               }
            }
         }
      }
   }

    void updateGridSquareMarkers() {
      if (IsoCamera.frameState.playerIndex == 0) {
         if (this.gridSquareMarkers.size() != 0) {
            for (int var1 = this.gridSquareMarkers.size() - 1; var1 >= 0; var1--) {
               if (this.gridSquareMarkers.get(var1).isRemoved()) {
                  this.gridSquareMarkers.remove(var1);
               }
            }

            for (int var3 = 0; var3 < this.gridSquareMarkers.size(); var3++) {
    GridSquareMarker var2 = this.gridSquareMarkers.get(var3);
               if (var2.alphaInc) {
                  var2.alpha = var2.alpha + GameTime.getInstance().getMultiplier() * var2.fadeSpeed;
                  if (var2.alpha > var2.alphaMax) {
                     var2.alphaInc = false;
                     var2.alpha = var2.alphaMax;
                  }
               } else {
                  var2.alpha = var2.alpha - GameTime.getInstance().getMultiplier() * var2.fadeSpeed;
                  if (var2.alpha < var2.alphaMin) {
                     var2.alphaInc = true;
                     var2.alpha = 0.3F;
                  }
               }
            }
         }
      }
   }

    bool removeGridSquareMarker(GridSquareMarker var1) {
      return this.removeGridSquareMarker(var1.getID());
   }

    bool removeGridSquareMarker(int var1) {
      for (int var2 = this.gridSquareMarkers.size() - 1; var2 >= 0; var2--) {
         if (this.gridSquareMarkers.get(var2).getID() == var1) {
            this.gridSquareMarkers.get(var2).remove();
            this.gridSquareMarkers.remove(var2);
    return true;
         }
      }

    return false;
   }

    GridSquareMarker getGridSquareMarker(int var1) {
      for (int var2 = 0; var2 < this.gridSquareMarkers.size(); var2++) {
         if (this.gridSquareMarkers.get(var2).getID() == var1) {
            return this.gridSquareMarkers.get(var2);
         }
      }

    return nullptr;
   }

    GridSquareMarker addGridSquareMarker(IsoGridSquare var1, float var2, float var3, float var4, bool var5, float var6) {
      return this.addGridSquareMarker("circle_center", "circle_only_highlight", var1, var2, var3, var4, var5, var6, 0.006F, 0.3F, 1.0F);
   }

    GridSquareMarker addGridSquareMarker(const std::string& var1, const std::string& var2, IsoGridSquare var3, float var4, float var5, float var6, bool var7, float var8) {
      return this.addGridSquareMarker(var1, var2, var3, var4, var5, var6, var7, var8, 0.006F, 0.3F, 1.0F);
   }

   public GridSquareMarker addGridSquareMarker(
      std::string var1, std::string var2, IsoGridSquare var3, float var4, float var5, float var6, boolean var7, float var8, float var9, float var10, float var11
   ) {
      if (GameServer.bServer) {
    return nullptr;
      } else {
    GridSquareMarker var12 = std::make_shared<GridSquareMarker>();
         var12.init(var1, var2, var3.x, var3.y, var3.z, var8);
         var12.setR(var4);
         var12.setG(var5);
         var12.setB(var6);
         var12.setA(1.0F);
         var12.setDoAlpha(var7);
         var12.setFadeSpeed(var9);
         var12.setAlpha(0.0F);
         var12.setAlphaMin(var10);
         var12.setAlphaMax(var11);
         this.gridSquareMarkers.push_back(var12);
    return var12;
      }
   }

    void renderGridSquareMarkers(PerPlayerRender var1, int var2, int var3) {
      if (!GameServer.bServer && this.gridSquareMarkers.size() != 0) {
    IsoPlayer var4 = IsoPlayer.players[var3];
         if (var4 != nullptr) {
            for (int var5 = 0; var5 < this.gridSquareMarkers.size(); var5++) {
    GridSquareMarker var6 = this.gridSquareMarkers.get(var5);
               if (var6.z == var2 && var6.z == var4.getZ() && var6.active) {
    float var7 = 0.0F;
    float var8 = 0.0F;
                  stCol.set(var6.r, var6.g, var6.b, var6.a);
                  if (var6.doBlink) {
                     var6.sprite.alpha = Core.blinkAlpha;
                  } else {
                     var6.sprite.alpha = var6.doAlpha ? var6.alpha : 1.0F;
                  }

                  var6.sprite.render(nullptr, var6.x, var6.y, var6.z, IsoDirections.N, var7, var8, stCol);
                  if (var6.spriteOverlay != nullptr) {
                     var6.spriteOverlay.alpha = 1.0F;
                     var6.spriteOverlay.render(nullptr, var6.x, var6.y, var6.z, IsoDirections.N, var7, var8, stCol);
                  }
               }
            }
         }
      }
   }

    void debugRender() {
   }

    void render() {
      this.update();
      this.renderHomingPoint();
      this.renderDirectionArrow(false);
   }

    void renderHomingPoint() {
      if (!GameServer.bServer) {
    int var1 = IsoCamera.frameState.playerIndex;

         for (int var2 = 0; var2 < this.homingPoints.length; var2++) {
            if (var2 == var1 && this.homingPoints[var2].size() != 0) {
               for (int var3 = 0; var3 < this.homingPoints[var2].size(); var3++) {
    PlayerHomingPoint var4 = (PlayerHomingPoint)this.homingPoints[var2].get(var3);
                  if (var4.active && var4.texture != nullptr) {
    float var5 = 180.0F - var4.angle;
                     if (var5 < 0.0F) {
                        var5 += 360.0F;
                     }

    float var6 = var4.a;
                     if (ClimateManager.getInstance().getFogIntensity() > 0.0F && var6 < 1.0F) {
    float var7 = 1.0F - var6;
                        var6 += var7 * ClimateManager.getInstance().getFogIntensity() * 2.0F;
                        var6 = PZMath.clamp_01(var6);
                     }

                     this.DrawTextureAngle(
                        var4.texture, var4.renderWidth, var4.renderHeight, var4.renderX, var4.renderY, var5, var4.r, var4.g, var4.b, var6, var4.renderSizeMod
                     );
                  }
               }
            }
         }
      }
   }

    void renderDirectionArrow(bool var1) {
      if (!GameServer.bServer) {
    int var2 = IsoCamera.frameState.playerIndex;

         for (int var3 = 0; var3 < this.directionArrows.length; var3++) {
            if (var3 == var2 && this.directionArrows[var3].size() != 0) {
               for (int var4 = 0; var4 < this.directionArrows[var3].size(); var4++) {
    DirectionArrow var5 = (DirectionArrow)this.directionArrows[var3].get(var4);
                  if (var5.active && var5.renderTexture != nullptr && var5.isDrawOnWorld == var1) {
    float var6 = 0.0F;
                     if (var5.renderWithAngle) {
                        var6 = 180.0F - var5.angle;
                        if (var6 < 0.0F) {
                           var6 += 360.0F;
                        }
                     }

                     this.DrawTextureAngle(
                        var5.renderTexture,
                        var5.renderWidth,
                        var5.renderHeight,
                        var5.renderScreenX,
                        var5.renderScreenY,
                        var6,
                        var5.r,
                        var5.g,
                        var5.b,
                        var5.a,
                        var5.renderSizeMod
                     );
                  }
               }
            }
         }
      }
   }

   private void DrawTextureAngle(
      Texture var1, float var2, float var3, double var4, double var6, double var8, float var10, float var11, float var12, float var13, float var14
   ) {
    float var15 = var2 * var14 / 2.0F;
    float var16 = var3 * var14 / 2.0F;
    double var17 = Math.toRadians(180.0 + var8);
    double var19 = Math.cos(var17) * var15;
    double var21 = Math.sin(var17) * var15;
    double var23 = Math.cos(var17) * var16;
    double var25 = Math.sin(var17) * var16;
    double var27 = var19 - var25;
    double var29 = var23 + var21;
    double var31 = -var19 - var25;
    double var33 = var23 - var21;
    double var35 = -var19 + var25;
    double var37 = -var23 - var21;
    double var39 = var19 + var25;
    double var41 = -var23 + var21;
      var27 += var4;
      var29 += var6;
      var31 += var4;
      var33 += var6;
      var35 += var4;
      var37 += var6;
      var39 += var4;
      var41 += var6;
      SpriteRenderer.instance
         .render(
            var1,
            var27,
            var29,
            var31,
            var33,
            var35,
            var37,
            var39,
            var41,
            var10,
            var11,
            var12,
            var13,
            var10,
            var11,
            var12,
            var13,
            var10,
            var11,
            var12,
            var13,
            var10,
            var11,
            var12,
            var13,
            nullptr
         );
   }

    static bool intersectLineSegments(Line var0, Line var1, Point var2) {
    float var3 = var0.s.x;
    float var4 = var0.s.y;
    float var5 = var0.e.x;
    float var6 = var0.e.y;
    float var7 = var1.s.x;
    float var8 = var1.s.y;
    float var9 = var1.e.x;
    float var10 = var1.e.y;
    float var11 = (var10 - var8) * (var5 - var3) - (var9 - var7) * (var6 - var4);
      if (var11 == 0.0F) {
    return false;
      } else {
    float var12 = var4 - var8;
    float var13 = var3 - var7;
    float var14 = ((var9 - var7) * var12 - (var10 - var8) * var13) / var11;
         if (!(var14 < 0.0F) && !(var14 > 1.0F)) {
    float var15 = ((var5 - var3) * var12 - (var6 - var4) * var13) / var11;
            if (!(var15 < 0.0F) && !(var15 > 1.0F)) {
               if (var2 != nullptr) {
                  var2.set(var3 + (var5 - var3) * var14, var4 + (var6 - var4) * var14);
               }

    return true;
            } else {
    return false;
            }
         } else {
    return false;
         }
      }
   }
}
} // namespace iso
} // namespace zombie
