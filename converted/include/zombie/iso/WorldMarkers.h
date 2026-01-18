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
#include "zombie/iso/sprite/IsoSpriteInstance.h"
#include "zombie/iso/sprite/IsoSpriteManager.h"
#include "zombie/iso/weather/ClimateManager.h"
#include "zombie/network/GameServer.h"

namespace zombie {
namespace iso {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


/**
 * TurboTuTone.
 */
class WorldMarkers {
public:
 static const float CIRCLE_TEXTURE_SCALE = 1.5F;
 static const WorldMarkers instance = new WorldMarkers();
 static int NextGridSquareMarkerID = 0;
 static int NextHomingPointID = 0;
 private List<WorldMarkers.GridSquareMarker> gridSquareMarkers = std::make_unique<ArrayList<>>();
 private WorldMarkers.PlayerHomingPointList[] homingPoints = new WorldMarkers.PlayerHomingPointList[4];
 private WorldMarkers.DirectionArrowList[] directionArrows = new WorldMarkers.DirectionArrowList[4];
 static const ColorInfo stCol = new ColorInfo();
 private WorldMarkers.PlayerScreen playerScreen = new WorldMarkers.PlayerScreen();
 private WorldMarkers.Point intersectPoint = new WorldMarkers.Point(0.0F, 0.0F);
 private WorldMarkers.Point arrowStart = new WorldMarkers.Point(0.0F, 0.0F);
 private WorldMarkers.Point arrowEnd = new WorldMarkers.Point(0.0F, 0.0F);
 private WorldMarkers.Line arrowLine = new WorldMarkers.Line(this->arrowStart, this->arrowEnd);

 private WorldMarkers() {
 }

 void init() {
 if (!GameServer.bServer) {
 for (int int0 = 0; int0 < this->homingPoints.length; int0++) {
 this->homingPoints[int0] = new WorldMarkers.PlayerHomingPointList();
 }

 for (int int1 = 0; int1 < this->directionArrows.length; int1++) {
 this->directionArrows[int1] = new WorldMarkers.DirectionArrowList();
 }
 }
 }

 void reset() {
 for (int int0 = 0; int0 < this->homingPoints.length; int0++) {
 this->homingPoints[int0].clear();
 }

 for (int int1 = 0; int1 < this->directionArrows.length; int1++) {
 this->directionArrows[int1].clear();
 }

 this->gridSquareMarkers.clear();
 }

 int GetDistance(int int2, int int0, int int3, int int1) {
 return (int)Math.sqrt(Math.pow(int2 - int3, 2.0) + Math.pow(int0 - int1, 2.0);
 }

 float getAngle(int int1, int int3, int int0, int int2) {
 float float0 = (float)Math.toDegrees(Math.atan2(int2 - int3, int0 - int1);
 if (float0 < 0.0F) {
 float0 += 360.0F;
 }

 return float0;
 }

 float angleDegrees(float float0) {
 if (float0 < 0.0F) {
 float0 += 360.0F;
 }

 if (float0 > 360.0F) {
 float0 -= 360.0F;
 }

 return float0;
 }

 public WorldMarkers.PlayerHomingPoint getHomingPoint(int id) {
 for (int int0 = 0; int0 < this->homingPoints.length; int0++) {
 for (int int1 = this->homingPoints[int0].size() - 1; int1 >= 0; int1++) {
 if (this->homingPoints[int0].get(int1).ID == id) {
 return this->homingPoints[int0].get(int1);
 }
 }
 }

 return nullptr;
 }

 public WorldMarkers.PlayerHomingPoint addPlayerHomingPoint(IsoPlayer player, int x, int y) {
 return this->addPlayerHomingPoint(player, x, y, "arrow_triangle", 1.0F, 1.0F, 1.0F, 1.0F, true, 20);
 }

 public WorldMarkers.PlayerHomingPoint addPlayerHomingPoint(IsoPlayer player, int x, int y, float r, float g, float b, float a) {
 return this->addPlayerHomingPoint(player, x, y, "arrow_triangle", r, g, b, a, true, 20);
 }

 public WorldMarkers.PlayerHomingPoint addPlayerHomingPoint(
 IsoPlayer player, int x, int y, String texname, float r, float g, float b, float a, boolean homeOnTarget, int homeOnDist
 ) {
 if (GameServer.bServer) {
 return nullptr;
 } else {
 WorldMarkers.PlayerHomingPoint playerHomingPoint = new WorldMarkers.PlayerHomingPoint(player.PlayerIndex);
 playerHomingPoint.setActive(true);
 playerHomingPoint.setTexture(texname);
 playerHomingPoint.setX(x);
 playerHomingPoint.setY(y);
 playerHomingPoint.setR(r);
 playerHomingPoint.setG(g);
 playerHomingPoint.setB(b);
 playerHomingPoint.setA(a);
 playerHomingPoint.setHomeOnTargetInView(homeOnTarget);
 playerHomingPoint.setHomeOnTargetDist(homeOnDist);
 this->homingPoints[player.PlayerIndex].add(playerHomingPoint);
 return playerHomingPoint;
 }
 }

 bool removeHomingPoint(WorldMarkers.PlayerHomingPoint point) {
 return this->removeHomingPoint(point.getID());
 }

 bool removeHomingPoint(int id) {
 for (int int0 = 0; int0 < this->homingPoints.length; int0++) {
 for (int int1 = this->homingPoints[int0].size() - 1; int1 >= 0; int1--) {
 if (this->homingPoints[int0].get(int1).ID == id) {
 this->homingPoints[int0].get(int1).remove();
 this->homingPoints[int0].remove(int1);
 return true;
 }
 }
 }

 return false;
 }

 bool removePlayerHomingPoint(IsoPlayer player, WorldMarkers.PlayerHomingPoint point) {
 return this->removePlayerHomingPoint(player, point.getID());
 }

 bool removePlayerHomingPoint(IsoPlayer player, int id) {
 for (int int0 = this->homingPoints[player.PlayerIndex].size() - 1; int0 >= 0; int0--) {
 if (this->homingPoints[player.PlayerIndex].get(int0).ID == id) {
 this->homingPoints[player.PlayerIndex].get(int0).remove();
 this->homingPoints[player.PlayerIndex].remove(int0);
 return true;
 }
 }

 return false;
 }

 void removeAllHomingPoints(IsoPlayer player) {
 this->homingPoints[player.PlayerIndex].clear();
 }

 public WorldMarkers.DirectionArrow getDirectionArrow(int id) {
 for (int int0 = 0; int0 < this->directionArrows.length; int0++) {
 for (int int1 = this->directionArrows[int0].size() - 1; int1 >= 0; int1--) {
 if (this->directionArrows[int0].get(int1).ID == id) {
 return this->directionArrows[int0].get(int1);
 }
 }
 }

 return nullptr;
 }

 public WorldMarkers.DirectionArrow addDirectionArrow(IsoPlayer player, int x, int y, int z, String texname, float r, float g, float b, float a) {
 if (GameServer.bServer) {
 return nullptr;
 } else {
 WorldMarkers.DirectionArrow directionArrow = new WorldMarkers.DirectionArrow(player.PlayerIndex);
 directionArrow.setActive(true);
 directionArrow.setTexture(texname);
 directionArrow.setTexDown("dir_arrow_down");
 directionArrow.setTexStairsUp("dir_arrow_stairs_up");
 directionArrow.setTexStairsDown("dir_arrow_stairs_down");
 directionArrow.setX(x);
 directionArrow.setY(y);
 directionArrow.setZ(z);
 directionArrow.setR(r);
 directionArrow.setG(g);
 directionArrow.setB(b);
 directionArrow.setA(a);
 this->directionArrows[player.PlayerIndex].add(directionArrow);
 return directionArrow;
 }
 }

 bool removeDirectionArrow(WorldMarkers.DirectionArrow arrow) {
 return this->removeDirectionArrow(arrow.getID());
 }

 bool removeDirectionArrow(int id) {
 for (int int0 = 0; int0 < this->directionArrows.length; int0++) {
 for (int int1 = this->directionArrows[int0].size() - 1; int1 >= 0; int1--) {
 if (this->directionArrows[int0].get(int1).ID == id) {
 this->directionArrows[int0].get(int1).remove();
 this->directionArrows[int0].remove(int1);
 return true;
 }
 }
 }

 return false;
 }

 bool removePlayerDirectionArrow(IsoPlayer player, WorldMarkers.DirectionArrow arrow) {
 return this->removePlayerDirectionArrow(player, arrow.getID());
 }

 bool removePlayerDirectionArrow(IsoPlayer player, int id) {
 for (int int0 = this->directionArrows[player.PlayerIndex].size() - 1; int0 >= 0; int0--) {
 if (this->directionArrows[player.PlayerIndex].get(int0).ID == id) {
 this->directionArrows[player.PlayerIndex].get(int0).remove();
 this->directionArrows[player.PlayerIndex].remove(int0);
 return true;
 }
 }

 return false;
 }

 void removeAllDirectionArrows(IsoPlayer player) {
 this->directionArrows[player.PlayerIndex].clear();
 }

 void update() {
 if (!GameServer.bServer) {
 this->updateGridSquareMarkers();
 this->updateHomingPoints();
 this->updateDirectionArrows();
 }
 }

 void updateDirectionArrows() {
 int int0 = IsoCamera.frameState.playerIndex;

 for (int int1 = 0; int1 < this->directionArrows.length; int1++) {
 if (int1 == int0 && this->directionArrows[int1].size() != 0) {
 for (int int2 = this->directionArrows[int1].size() - 1; int2 >= 0; int2--) {
 if (this->directionArrows[int1].get(int2).isRemoved()) {
 this->directionArrows[int1].remove(int2);
 }
 }

 this->playerScreen.update(int1);

 for (int int3 = 0; int3 < this->directionArrows[int1].size(); int3++) {
 WorldMarkers.DirectionArrow directionArrow = this->directionArrows[int1].get(int3);
 if (directionArrow.active && IsoPlayer.players[int1] != nullptr) {
 IsoPlayer player = IsoPlayer.players[int1];
 if (player.getSquare() != nullptr) {
 PlayerCamera playerCamera = IsoCamera.cameras[int1];
 float float0 = Core.getInstance().getZoom(int1);
 int int4 = player.getSquare().getX();
 int int5 = player.getSquare().getY();
 int int6 = player.getSquare().getZ();
 int int7 = this->GetDistance(int4, int5, directionArrow.x, directionArrow.y);
 bool boolean0 = false;
 bool boolean1 = false;
 float float1 = 0.0F;
 float float2 = 0.0F;
 if (int7 < 300) {
 boolean0 = true;
 float1 = playerCamera.XToScreenExact(directionArrow.x, directionArrow.y, int6, 0) / float0;
 float2 = playerCamera.YToScreenExact(directionArrow.x, directionArrow.y, int6, 0) / float0;
 if (this->playerScreen.isWithinInner(float1, float2) {
 boolean1 = true;
 }
 }

 if (boolean1) {
 directionArrow.renderWithAngle = false;
 directionArrow.isDrawOnWorld = false;
 directionArrow.renderSizeMod = 1.0F;
 if (float0 > 1.0F) {
 directionArrow.renderSizeMod /= float0;
 }

 directionArrow.renderScreenX = float1;
 directionArrow.renderScreenY = float2;
 if (int6 == directionArrow.z) {
 directionArrow.renderTexture = directionArrow.texDown != nullptr ? directionArrow.texDown : directionArrow.texture;
 } else if (directionArrow.z > int6) {
 directionArrow.renderTexture = directionArrow.texStairsUp != nullptr ? directionArrow.texStairsUp : directionArrow.texture;
 } else {
 directionArrow.renderTexture = directionArrow.texStairsDown != nullptr ? directionArrow.texStairsUp : directionArrow.texture;
 }

 directionArrow.lastWasWithinView = true;
 } else {
 directionArrow.renderWithAngle = true;
 directionArrow.isDrawOnWorld = false;
 directionArrow.renderTexture = directionArrow.texture;
 directionArrow.renderSizeMod = 1.0F;
 float float3 = this->playerScreen.centerX;
 float float4 = this->playerScreen.centerY;
 float float5 = 0.0F;
 if (!boolean0) {
 float5 = this->getAngle(directionArrow.x, directionArrow.y, int4, int5);
 float5 = this->angleDegrees(180.0F - float5);
 float5 = this->angleDegrees(float5 + 45.0F);
 } else {
 float5 = this->getAngle((int)float3, (int)float4, (int)float1, (int)float2);
 float5 = this->angleDegrees(180.0F - float5);
 float5 = this->angleDegrees(float5 - 90.0F);
 }

 if (float5 != directionArrow.angle) {
 if (!directionArrow.lastWasWithinView) {
 directionArrow.angle = PZMath.lerpAngle(
 PZMath.degToRad(directionArrow.angle),
 PZMath.degToRad(float5),
 directionArrow.angleLerpVal * GameTime.instance.getMultiplier()
 );
 directionArrow.angle = PZMath.radToDeg(directionArrow.angle);
 } else {
 directionArrow.angle = float5;
 }
 }

 float float6 = float3 + 32000.0F * (float)Math.sin(Math.toRadians(directionArrow.angle);
 float float7 = float4 + 32000.0F * (float)Math.cos(Math.toRadians(directionArrow.angle);
 directionArrow.renderScreenX = float3;
 directionArrow.renderScreenY = float4;
 this->arrowStart.set(float3, float4);
 this->arrowEnd.set(float6, float7);
 WorldMarkers.Line[] lines = this->playerScreen.getBorders();

 for (int int8 = 0; int8 < lines.length; int8++) {
 this->intersectPoint.set(Float.POSITIVE_INFINITY, Float.POSITIVE_INFINITY);
 if (intersectLineSegments(this->arrowLine, lines[int8], this->intersectPoint) {
 directionArrow.renderScreenX = this->intersectPoint.x;
 directionArrow.renderScreenY = this->intersectPoint.y;
 break;
 }
 }

 directionArrow.lastWasWithinView = false;
 }
 }
 }
 }
 }
 }
 }

 void updateHomingPoints() {
 int int0 = IsoCamera.frameState.playerIndex;

 for (int int1 = 0; int1 < this->homingPoints.length; int1++) {
 if (int1 == int0 && this->homingPoints[int1].size() != 0) {
 for (int int2 = this->homingPoints[int1].size() - 1; int2 >= 0; int2--) {
 if (this->homingPoints[int1].get(int2).isRemoved) {
 this->homingPoints[int1].remove(int2);
 }
 }

 this->playerScreen.update(int1);

 for (int int3 = 0; int3 < this->homingPoints[int1].size(); int3++) {
 WorldMarkers.PlayerHomingPoint playerHomingPoint = this->homingPoints[int1].get(int3);
 if (playerHomingPoint.active && IsoPlayer.players[int1] != nullptr) {
 IsoPlayer player = IsoPlayer.players[int1];
 if (player.getSquare() != nullptr) {
 PlayerCamera playerCamera = IsoCamera.cameras[int1];
 float float0 = Core.getInstance().getZoom(int1);
 playerHomingPoint.renderSizeMod = 1.0F;
 if (float0 > 1.0F) {
 playerHomingPoint.renderSizeMod /= float0;
 }

 int int4 = player.getSquare().getX();
 int int5 = player.getSquare().getY();
 playerHomingPoint.dist = this->GetDistance(int4, int5, playerHomingPoint.x, playerHomingPoint.y);
 playerHomingPoint.targetOnScreen = false;
 if (playerHomingPoint.dist < 200.0F) {
 playerHomingPoint.targetScreenX = playerCamera.XToScreenExact(playerHomingPoint.x, playerHomingPoint.y, 0.0F, 0) / float0;
 playerHomingPoint.targetScreenY = playerCamera.YToScreenExact(playerHomingPoint.x, playerHomingPoint.y, 0.0F, 0) / float0;
 playerHomingPoint.targetScreenX = playerHomingPoint.targetScreenX + playerHomingPoint.homeOnOffsetX / float0;
 playerHomingPoint.targetScreenY = playerHomingPoint.targetScreenY + playerHomingPoint.homeOnOffsetY / float0;
 playerHomingPoint.targetOnScreen = this->playerScreen
 .isOnScreen(playerHomingPoint.targetScreenX, playerHomingPoint.targetScreenY);
 }

 float float1 = this->playerScreen.centerX;
 float float2 = float1 + playerHomingPoint.renderOffsetX / float0;
 float float3 = this->playerScreen.centerY;
 float float4 = float3 + playerHomingPoint.renderOffsetY / float0;
 if (!playerHomingPoint.customTargetAngle) {
 float float5 = 0.0F;
 if (!playerHomingPoint.targetOnScreen) {
 float5 = this->getAngle(playerHomingPoint.x, playerHomingPoint.y, int4, int5);
 float5 = this->angleDegrees(180.0F - float5);
 float5 = this->angleDegrees(float5 + 45.0F);
 } else {
 float5 = this->getAngle((int)float2, (int)float4, (int)playerHomingPoint.targetScreenX, (int)playerHomingPoint.targetScreenY);
 float5 = this->angleDegrees(180.0F - float5);
 float5 = this->angleDegrees(float5 - 90.0F);
 }

 playerHomingPoint.targetAngle = float5;
 }

 if (playerHomingPoint.targetAngle != playerHomingPoint.angle) {
 playerHomingPoint.angle = PZMath.lerpAngle(
 PZMath.degToRad(playerHomingPoint.angle),
 PZMath.degToRad(playerHomingPoint.targetAngle),
 playerHomingPoint.angleLerpVal * GameTime.instance.getMultiplier()
 );
 playerHomingPoint.angle = PZMath.radToDeg(playerHomingPoint.angle);
 }

 float float6 = playerHomingPoint.stickToCharDist / float0;
 playerHomingPoint.targRenderX = float2 + float6 * (float)Math.sin(Math.toRadians(playerHomingPoint.angle);
 playerHomingPoint.targRenderY = float4 + float6 * (float)Math.cos(Math.toRadians(playerHomingPoint.angle);
 float float7 = playerHomingPoint.movementLerpVal;
 if (playerHomingPoint.targetOnScreen) {
 float float8 = this->GetDistance(
 (int)playerHomingPoint.targRenderX,
 (int)playerHomingPoint.targRenderY,
 (int)playerHomingPoint.targetScreenX,
 (int)playerHomingPoint.targetScreenY
 );
 float float9 = this->GetDistance(
 (int)float2, (int)float4, (int)playerHomingPoint.targetScreenX, (int)playerHomingPoint.targetScreenY
 );
 if (float9 < float8 || playerHomingPoint.homeOnTargetInView && playerHomingPoint.dist <= playerHomingPoint.homeOnTargetDist) {
 float9 *= 0.75F;
 playerHomingPoint.targRenderX = float2 + float9 * (float)Math.sin(Math.toRadians(playerHomingPoint.targetAngle);
 playerHomingPoint.targRenderY = float4 + float9 * (float)Math.cos(Math.toRadians(playerHomingPoint.targetAngle);
 }
 }

 playerHomingPoint.targRenderX = this->playerScreen.clampToInnerX(playerHomingPoint.targRenderX);
 playerHomingPoint.targRenderY = this->playerScreen.clampToInnerY(playerHomingPoint.targRenderY);
 if (playerHomingPoint.targRenderX != playerHomingPoint.renderX) {
 playerHomingPoint.renderX = PZMath.lerp(
 playerHomingPoint.renderX, playerHomingPoint.targRenderX, float7 * GameTime.instance.getMultiplier()
 );
 }

 if (playerHomingPoint.targRenderY != playerHomingPoint.renderY) {
 playerHomingPoint.renderY = PZMath.lerp(
 playerHomingPoint.renderY, playerHomingPoint.targRenderY, float7 * GameTime.instance.getMultiplier()
 );
 }
 }
 }
 }
 }
 }
 }

 void updateGridSquareMarkers() {
 if (IsoCamera.frameState.playerIndex == 0) {
 if (this->gridSquareMarkers.size() != 0) {
 for (int int0 = this->gridSquareMarkers.size() - 1; int0 >= 0; int0--) {
 if (this->gridSquareMarkers.get(int0).isRemoved()) {
 this->gridSquareMarkers.remove(int0);
 }
 }

 for (int int1 = 0; int1 < this->gridSquareMarkers.size(); int1++) {
 WorldMarkers.GridSquareMarker gridSquareMarker = this->gridSquareMarkers.get(int1);
 if (gridSquareMarker.alphaInc) {
 gridSquareMarker.alpha = gridSquareMarker.alpha + GameTime.getInstance().getMultiplier() * gridSquareMarker.fadeSpeed;
 if (gridSquareMarker.alpha > gridSquareMarker.alphaMax) {
 gridSquareMarker.alphaInc = false;
 gridSquareMarker.alpha = gridSquareMarker.alphaMax;
 }
 } else {
 gridSquareMarker.alpha = gridSquareMarker.alpha - GameTime.getInstance().getMultiplier() * gridSquareMarker.fadeSpeed;
 if (gridSquareMarker.alpha < gridSquareMarker.alphaMin) {
 gridSquareMarker.alphaInc = true;
 gridSquareMarker.alpha = 0.3F;
 }
 }
 }
 }
 }
 }

 bool removeGridSquareMarker(WorldMarkers.GridSquareMarker marker) {
 return this->removeGridSquareMarker(marker.getID());
 }

 bool removeGridSquareMarker(int id) {
 for (int int0 = this->gridSquareMarkers.size() - 1; int0 >= 0; int0--) {
 if (this->gridSquareMarkers.get(int0).getID() == id) {
 this->gridSquareMarkers.get(int0).remove();
 this->gridSquareMarkers.remove(int0);
 return true;
 }
 }

 return false;
 }

 public WorldMarkers.GridSquareMarker getGridSquareMarker(int id) {
 for (int int0 = 0; int0 < this->gridSquareMarkers.size(); int0++) {
 if (this->gridSquareMarkers.get(int0).getID() == id) {
 return this->gridSquareMarkers.get(int0);
 }
 }

 return nullptr;
 }

 public WorldMarkers.GridSquareMarker addGridSquareMarker(IsoGridSquare gs, float r, float g, float b, boolean doAlpha, float size) {
 return this->addGridSquareMarker("circle_center", "circle_only_highlight", gs, r, g, b, doAlpha, size, 0.006F, 0.3F, 1.0F);
 }

 public WorldMarkers.GridSquareMarker addGridSquareMarker(
 String texid, String overlay, IsoGridSquare gs, float r, float g, float b, boolean doAlpha, float size
 ) {
 return this->addGridSquareMarker(texid, overlay, gs, r, g, b, doAlpha, size, 0.006F, 0.3F, 1.0F);
 }

 public WorldMarkers.GridSquareMarker addGridSquareMarker(
 String texid, String overlay, IsoGridSquare gs, float r, float g, float b, boolean doAlpha, float size, float fadeSpeed, float fadeMin, float fadeMax
 ) {
 if (GameServer.bServer) {
 return nullptr;
 } else {
 WorldMarkers.GridSquareMarker gridSquareMarker = new WorldMarkers.GridSquareMarker();
 gridSquareMarker.init(texid, overlay, gs.x, gs.y, gs.z, size);
 gridSquareMarker.setR(r);
 gridSquareMarker.setG(g);
 gridSquareMarker.setB(b);
 gridSquareMarker.setA(1.0F);
 gridSquareMarker.setDoAlpha(doAlpha);
 gridSquareMarker.setFadeSpeed(fadeSpeed);
 gridSquareMarker.setAlpha(0.0F);
 gridSquareMarker.setAlphaMin(fadeMin);
 gridSquareMarker.setAlphaMax(fadeMax);
 this->gridSquareMarkers.add(gridSquareMarker);
 return gridSquareMarker;
 }
 }

 void renderGridSquareMarkers(IsoCell.PerPlayerRender perPlayerRender, int zLayer, int playerIndex) {
 if (!GameServer.bServer && this->gridSquareMarkers.size() != 0) {
 IsoPlayer player = IsoPlayer.players[playerIndex];
 if (player != nullptr) {
 for (int int0 = 0; int0 < this->gridSquareMarkers.size(); int0++) {
 WorldMarkers.GridSquareMarker gridSquareMarker = this->gridSquareMarkers.get(int0);
 if (gridSquareMarker.z == zLayer && gridSquareMarker.z == player.getZ() && gridSquareMarker.active) {
 float float0 = 0.0F;
 float float1 = 0.0F;
 stCol.set(gridSquareMarker.r, gridSquareMarker.g, gridSquareMarker.b, gridSquareMarker.a);
 if (gridSquareMarker.doBlink) {
 gridSquareMarker.sprite.alpha = Core.blinkAlpha;
 } else {
 gridSquareMarker.sprite.alpha = gridSquareMarker.doAlpha ? gridSquareMarker.alpha : 1.0F;
 }

 gridSquareMarker.sprite
 .render(nullptr, gridSquareMarker.x, gridSquareMarker.y, gridSquareMarker.z, IsoDirections.N, float0, float1, stCol);
 if (gridSquareMarker.spriteOverlay != nullptr) {
 gridSquareMarker.spriteOverlay.alpha = 1.0F;
 gridSquareMarker.spriteOverlay
 .render(nullptr, gridSquareMarker.x, gridSquareMarker.y, gridSquareMarker.z, IsoDirections.N, float0, float1, stCol);
 }
 }
 }
 }
 }
 }

 void debugRender() {
 }

 void render() {
 this->update();
 this->renderHomingPoint();
 this->renderDirectionArrow(false);
 }

 void renderHomingPoint() {
 if (!GameServer.bServer) {
 int int0 = IsoCamera.frameState.playerIndex;

 for (int int1 = 0; int1 < this->homingPoints.length; int1++) {
 if (int1 == int0 && this->homingPoints[int1].size() != 0) {
 for (int int2 = 0; int2 < this->homingPoints[int1].size(); int2++) {
 WorldMarkers.PlayerHomingPoint playerHomingPoint = this->homingPoints[int1].get(int2);
 if (playerHomingPoint.active && playerHomingPoint.texture != nullptr) {
 float float0 = 180.0F - playerHomingPoint.angle;
 if (float0 < 0.0F) {
 float0 += 360.0F;
 }

 float float1 = playerHomingPoint.a;
 if (ClimateManager.getInstance().getFogIntensity() > 0.0F && float1 < 1.0F) {
 float float2 = 1.0F - float1;
 float1 += float2 * ClimateManager.getInstance().getFogIntensity() * 2.0F;
 float1 = PZMath.clamp_01(float1);
 }

 this->DrawTextureAngle(
 playerHomingPoint.texture,
 playerHomingPoint.renderWidth,
 playerHomingPoint.renderHeight,
 playerHomingPoint.renderX,
 playerHomingPoint.renderY,
 float0,
 playerHomingPoint.r,
 playerHomingPoint.g,
 playerHomingPoint.b,
 float1,
 playerHomingPoint.renderSizeMod
 );
 }
 }
 }
 }
 }
 }

 void renderDirectionArrow(bool worldDraw) {
 if (!GameServer.bServer) {
 int int0 = IsoCamera.frameState.playerIndex;

 for (int int1 = 0; int1 < this->directionArrows.length; int1++) {
 if (int1 == int0 && this->directionArrows[int1].size() != 0) {
 for (int int2 = 0; int2 < this->directionArrows[int1].size(); int2++) {
 WorldMarkers.DirectionArrow directionArrow = this->directionArrows[int1].get(int2);
 if (directionArrow.active && directionArrow.renderTexture != nullptr && directionArrow.isDrawOnWorld == worldDraw) {
 float float0 = 0.0F;
 if (directionArrow.renderWithAngle) {
 float0 = 180.0F - directionArrow.angle;
 if (float0 < 0.0F) {
 float0 += 360.0F;
 }
 }

 this->DrawTextureAngle(
 directionArrow.renderTexture,
 directionArrow.renderWidth,
 directionArrow.renderHeight,
 directionArrow.renderScreenX,
 directionArrow.renderScreenY,
 float0,
 directionArrow.r,
 directionArrow.g,
 directionArrow.b,
 directionArrow.a,
 directionArrow.renderSizeMod
 );
 }
 }
 }
 }
 }
 }

 private void DrawTextureAngle(
 Texture texture,
 float float1,
 float float4,
 double double14,
 double double15,
 double double1,
 float float5,
 float float6,
 float float7,
 float float8,
 float float2
 ) {
 float float0 = float1 * float2 / 2.0F;
 float float3 = float4 * float2 / 2.0F;
 double double0 = Math.toRadians(180.0 + double1);
 double double2 = Math.cos(double0) * float0;
 double double3 = Math.sin(double0) * float0;
 double double4 = Math.cos(double0) * float3;
 double double5 = Math.sin(double0) * float3;
 double double6 = double2 - double5;
 double double7 = double4 + double3;
 double double8 = -double2 - double5;
 double double9 = double4 - double3;
 double double10 = -double2 + double5;
 double double11 = -double4 - double3;
 double double12 = double2 + double5;
 double double13 = -double4 + double3;
 double6 += double14;
 double7 += double15;
 double8 += double14;
 double9 += double15;
 double10 += double14;
 double11 += double15;
 double12 += double14;
 double13 += double15;
 SpriteRenderer.instance
 .render(
 texture,
 double6,
 double7,
 double8,
 double9,
 double10,
 double11,
 double12,
 double13,
 float5,
 float6,
 float7,
 float8,
 float5,
 float6,
 float7,
 float8,
 float5,
 float6,
 float7,
 float8,
 float5,
 float6,
 float7,
 float8,
 nullptr
 );
 }

 static bool intersectLineSegments(WorldMarkers.Line l1, WorldMarkers.Line l2, WorldMarkers.Point intersection) {
 float float0 = l1.s.x;
 float float1 = l1.s.y;
 float float2 = l1.e.x;
 float float3 = l1.e.y;
 float float4 = l2.s.x;
 float float5 = l2.s.y;
 float float6 = l2.e.x;
 float float7 = l2.e.y;
 float float8 = (float7 - float5) * (float2 - float0) - (float6 - float4) * (float3 - float1);
 if (float8 == 0.0F) {
 return false;
 } else {
 float float9 = float1 - float5;
 float float10 = float0 - float4;
 float float11 = ((float6 - float4) * float9 - (float7 - float5) * float10) / float8;
 if (!(float11 < 0.0F) && !(float11 > 1.0F) {
 float float12 = ((float2 - float0) * float9 - (float3 - float1) * float10) / float8;
 if (!(float12 < 0.0F) && !(float12 > 1.0F) {
 if (intersection != nullptr) {
 intersection.set(float0 + (float2 - float0) * float11, float1 + (float3 - float1) * float11);
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

 public class DirectionArrow {
 static const bool doDebug = false;
 private WorldMarkers.DirectionArrow.DebugStuff debugStuff;
 int ID;
 bool active = true;
 bool isRemoved = false;
 bool isDrawOnWorld = false;
 Texture renderTexture;
 Texture texture;
 Texture texStairsUp;
 Texture texStairsDown;
 Texture texDown;
 int x;
 int y;
 int z;
 float r;
 float g;
 float b;
 float a;
 float renderWidth = 32.0F;
 float renderHeight = 32.0F;
 float angle;
 float angleLerpVal = 0.25F;
 bool lastWasWithinView = true;
 float renderScreenX;
 float renderScreenY;
 bool renderWithAngle = true;
 float renderSizeMod = 1.0F;

 public DirectionArrow(int var2) {
 if (Core.bDebug) {
 }

 this->ID = WorldMarkers.NextHomingPointID++;
 }

 void setTexture(const std::string& texname) {
 if (texname == nullptr) {
 texname = "dir_arrow_up";
 }

 this->texture = Texture.getSharedTexture("media/textures/highlights/" + texname + ".png");
 }

 void setTexDown(const std::string& texname) {
 this->texDown = Texture.getSharedTexture("media/textures/highlights/" + texname + ".png");
 }

 void setTexStairsDown(const std::string& texname) {
 this->texStairsDown = Texture.getSharedTexture("media/textures/highlights/" + texname + ".png");
 }

 void setTexStairsUp(const std::string& texname) {
 this->texStairsUp = Texture.getSharedTexture("media/textures/highlights/" + texname + ".png");
 }

 /**
 * When called will remove the pointer next tick
 */
 void remove() {
 this->isRemoved = true;
 }

 bool isRemoved() {
 return this->isRemoved;
 }

 /**
 * Active can be set to false, the pointer will remain but wont be drawn.
 */
 bool isActive() {
 return this->active;
 }

 void setActive(bool _active) {
 this->active = _active;
 }

 float getR() {
 return this->r;
 }

 void setR(float _r) {
 this->r = _r;
 }

 float getB() {
 return this->b;
 }

 void setB(float _b) {
 this->b = _b;
 }

 float getG() {
 return this->g;
 }

 void setG(float _g) {
 this->g = _g;
 }

 float getA() {
 return this->a;
 }

 void setA(float _a) {
 this->a = _a;
 }

 void setRGBA(float _r, float _g, float _b, float _a) {
 this->r = _r;
 this->g = _g;
 this->b = _b;
 this->a = _a;
 }

 int getID() {
 return this->ID;
 }

 /**
 * The target position on the map for this pointer.
 */
 int getX() {
 return this->x;
 }

 void setX(int _x) {
 this->x = _x;
 }

 int getY() {
 return this->y;
 }

 void setY(int _y) {
 this->y = _y;
 }

 int getZ() {
 return this->z;
 }

 void setZ(int _z) {
 this->z = _z;
 }

 /**
 * Render width and height for the pointer texture.
 */
 float getRenderWidth() {
 return this->renderWidth;
 }

 void setRenderWidth(float _renderWidth) {
 this->renderWidth = _renderWidth;
 }

 float getRenderHeight() {
 return this->renderHeight;
 }

 void setRenderHeight(float _renderHeight) {
 this->renderHeight = _renderHeight;
 }

 private class DebugStuff {
 float centerX;
 float centerY;
 float endX;
 float endY;
 }
 }

 class DirectionArrowList extends ArrayList<WorldMarkers.DirectionArrow> {
 }

 public static class GridSquareMarker {
 int ID;
 IsoSpriteInstance sprite;
 IsoSpriteInstance spriteOverlay;
 float orig_x;
 float orig_y;
 float orig_z;
 float x;
 float y;
 float z;
 float scaleRatio;
 float r;
 float g;
 float b;
 float a;
 float size;
 bool doBlink = false;
 bool doAlpha;
 bool bScaleCircleTexture = false;
 float fadeSpeed = 0.006F;
 float alpha = 0.0F;
 float alphaMax = 1.0F;
 float alphaMin = 0.3F;
 bool alphaInc = true;
 bool active = true;
 bool isRemoved = false;

 public GridSquareMarker() {
 this->ID = WorldMarkers.NextGridSquareMarkerID++;
 }

 int getID() {
 return this->ID;
 }

 void remove() {
 this->isRemoved = true;
 }

 bool isRemoved() {
 return this->isRemoved;
 }

 void init(const std::string& texid, const std::string& overlay, int _x, int _y, int _z, float _size) {
 if (texid == nullptr) {
 texid = "circle_center";
 }

 Texture texture = Texture.getSharedTexture("media/textures/highlights/" + texid + ".png");
 float float0 = texture.getWidth();
 float float1 = 64.0F * Core.TileScale;
 this->scaleRatio = 1.0F / (float0 / float1);
 this->sprite = new IsoSpriteInstance(IsoSpriteManager.instance.getSprite("media/textures/highlights/" + texid + ".png"));
 if (overlay != nullptr) {
 this->spriteOverlay = new IsoSpriteInstance(IsoSpriteManager.instance.getSprite("media/textures/highlights/" + overlay + ".png"));
 }

 this->setPosAndSize(_x, _y, _z, _size);
 }

 void setPosAndSize(int _x, int _y, int _z, float _size) {
 float float0 = _size * (this->bScaleCircleTexture ? 1.5F : 1.0F);
 float float1 = this->scaleRatio * float0;
 this->sprite.setScale(float1, float1);
 if (this->spriteOverlay != nullptr) {
 this->spriteOverlay.setScale(float1, float1);
 }

 this->size = _size;
 this->orig_x = _x;
 this->orig_y = _y;
 this->orig_z = _z;
 this->x = _x - (float0 - 0.5F);
 this->y = _y + 0.5F;
 this->z = _z;
 }

 void setPos(int _x, int _y, int _z) {
 float float0 = this->size * (this->bScaleCircleTexture ? 1.5F : 1.0F);
 this->orig_x = _x;
 this->orig_y = _y;
 this->orig_z = _z;
 this->x = _x - (float0 - 0.5F);
 this->y = _y + 0.5F;
 this->z = _z;
 }

 void setSize(float _size) {
 float float0 = _size * (this->bScaleCircleTexture ? 1.5F : 1.0F);
 float float1 = this->scaleRatio * float0;
 this->sprite.setScale(float1, float1);
 if (this->spriteOverlay != nullptr) {
 this->spriteOverlay.setScale(float1, float1);
 }

 this->size = _size;
 this->x = this->orig_x - (float0 - 0.5F);
 this->y = this->orig_y + 0.5F;
 this->z = this->orig_z;
 }

 bool isActive() {
 return this->active;
 }

 void setActive(bool _active) {
 this->active = _active;
 }

 float getSize() {
 return this->size;
 }

 float getX() {
 return this->x;
 }

 float getY() {
 return this->y;
 }

 float getZ() {
 return this->z;
 }

 float getR() {
 return this->r;
 }

 void setR(float _r) {
 this->r = _r;
 }

 float getG() {
 return this->g;
 }

 void setG(float _g) {
 this->g = _g;
 }

 float getB() {
 return this->b;
 }

 void setB(float _b) {
 this->b = _b;
 }

 float getA() {
 return this->a;
 }

 void setA(float _a) {
 this->a = _a;
 }

 float getAlpha() {
 return this->alpha;
 }

 void setAlpha(float _alpha) {
 this->alpha = _alpha;
 }

 float getAlphaMax() {
 return this->alphaMax;
 }

 void setAlphaMax(float _alphaMax) {
 this->alphaMax = _alphaMax;
 }

 float getAlphaMin() {
 return this->alphaMin;
 }

 void setAlphaMin(float _alphaMin) {
 this->alphaMin = _alphaMin;
 }

 bool isDoAlpha() {
 return this->doAlpha;
 }

 void setDoAlpha(bool _doAlpha) {
 this->doAlpha = _doAlpha;
 }

 float getFadeSpeed() {
 return this->fadeSpeed;
 }

 void setFadeSpeed(float _fadeSpeed) {
 this->fadeSpeed = _fadeSpeed;
 }

 /**
 * If blink set uses Core.blinkAlpha, this takes precedence over other alpha settings.
 */
 bool isDoBlink() {
 return this->doBlink;
 }

 void setDoBlink(bool _doBlink) {
 this->doBlink = _doBlink;
 }

 bool isScaleCircleTexture() {
 return this->bScaleCircleTexture;
 }

 void setScaleCircleTexture(bool bScale) {
 this->bScaleCircleTexture = bScale;
 float float0 = this->size * (this->bScaleCircleTexture ? 1.5F : 1.0F);
 float float1 = this->scaleRatio * float0;
 if (this->sprite != nullptr) {
 this->sprite.setScale(float1, float1);
 }

 if (this->spriteOverlay != nullptr) {
 this->spriteOverlay.setScale(float1, float1);
 }

 this->x = this->orig_x - (float0 - 0.5F);
 }
 }

 private static class Line {
 WorldMarkers.Point s;
 WorldMarkers.Point e;

 Line(WorldMarkers.Point point0, WorldMarkers.Point point1) {
 this->s = point0;
 this->e = point1;
 }

 std::string toString() {
 return String.format("{s: %s, e: %s}", this->s.toString(), this->e.toString());
 }
 }

 public static class PlayerHomingPoint {
 int ID;
 Texture texture;
 int x;
 int y;
 float r;
 float g;
 float b;
 float a;
 float angle = 0.0F;
 float targetAngle = 0.0F;
 bool customTargetAngle = false;
 float angleLerpVal = 0.25F;
 float movementLerpVal = 0.25F;
 int dist = 0;
 float targRenderX = Core.getInstance().getScreenWidth() / 2.0F;
 float targRenderY = Core.getInstance().getScreenHeight() / 2.0F;
 float renderX = this->targRenderX;
 float renderY = this->targRenderY;
 float renderOffsetX = 0.0F;
 float renderOffsetY = 50.0F;
 float renderWidth = 32.0F;
 float renderHeight = 32.0F;
 float renderSizeMod = 1.0F;
 float targetScreenX;
 float targetScreenY;
 bool targetOnScreen = false;
 float stickToCharDist = 130.0F;
 bool active;
 bool homeOnTargetInView = true;
 int homeOnTargetDist = 20;
 float homeOnOffsetX = 0.0F;
 float homeOnOffsetY = 0.0F;
 bool isRemoved = false;

 public PlayerHomingPoint(int plrIndex) {
 this->ID = WorldMarkers.NextHomingPointID++;
 float float0 = IsoCamera.getScreenLeft(plrIndex);
 float float1 = IsoCamera.getScreenTop(plrIndex);
 float float2 = IsoCamera.getScreenWidth(plrIndex);
 float float3 = IsoCamera.getScreenHeight(plrIndex);
 this->targRenderX = float0 + float2 / 2.0F;
 this->targRenderY = float1 + float3 / 2.0F;
 }

 void setTexture(const std::string& texname) {
 if (texname == nullptr) {
 texname = "arrow_triangle";
 }

 this->texture = Texture.getSharedTexture("media/textures/highlights/" + texname + ".png");
 }

 /**
 * When called will remove the pointer next tick
 */
 void remove() {
 this->isRemoved = true;
 }

 bool isRemoved() {
 return this->isRemoved;
 }

 /**
 * Active can be set to false, the pointer will remain but wont be drawn.
 */
 bool isActive() {
 return this->active;
 }

 void setActive(bool _active) {
 this->active = _active;
 }

 float getR() {
 return this->r;
 }

 void setR(float _r) {
 this->r = _r;
 }

 float getB() {
 return this->b;
 }

 void setB(float _b) {
 this->b = _b;
 }

 float getG() {
 return this->g;
 }

 void setG(float _g) {
 this->g = _g;
 }

 float getA() {
 return this->a;
 }

 void setA(float _a) {
 this->a = _a;
 }

 /**
 * The distance in tiles uppon which the pointer will jump to target (if homeOnTarget is enabled, and the target is onScreen)
 */
 int getHomeOnTargetDist() {
 return this->homeOnTargetDist;
 }

 void setHomeOnTargetDist(int _homeOnTargetDist) {
 this->homeOnTargetDist = _homeOnTargetDist;
 }

 int getID() {
 return this->ID;
 }

 float getTargetAngle() {
 return this->targetAngle;
 }

 void setTargetAngle(float _targetAngle) {
 this->targetAngle = _targetAngle;
 }

 /**
 * When enabled will ommit angle calculation, custom angle be set with 'setTargetAngle'.
 */
 bool isCustomTargetAngle() {
 return this->customTargetAngle;
 }

 void setCustomTargetAngle(bool _customTargetAngle) {
 this->customTargetAngle = _customTargetAngle;
 }

 /**
 * The target position on the map for this pointer.
 */
 int getX() {
 return this->x;
 }

 void setX(int _x) {
 this->x = _x;
 }

 int getY() {
 return this->y;
 }

 void setY(int _y) {
 this->y = _y;
 }

 /**
 * The lerp value for angle adjustment, can be tweaked to be more slowly or faster responding.
 */
 float getAngleLerpVal() {
 return this->angleLerpVal;
 }

 void setAngleLerpVal(float _angleLerpVal) {
 this->angleLerpVal = _angleLerpVal;
 }

 /**
 * The lerp value for jumping to target (homeOneTarget), can be tweaked to be more slowly or faster responding.
 */
 float getMovementLerpVal() {
 return this->movementLerpVal;
 }

 void setMovementLerpVal(float _movementLerpVal) {
 this->movementLerpVal = _movementLerpVal;
 }

 /**
 * if enabled the pointer will jump to the target when its in view (and within the 'homeOnTargetDist'.
 */
 bool isHomeOnTargetInView() {
 return this->homeOnTargetInView;
 }

 void setHomeOnTargetInView(bool _homeOnTargetInView) {
 this->homeOnTargetInView = _homeOnTargetInView;
 }

 /**
 * Render width and height for the pointer texture.
 */
 float getRenderWidth() {
 return this->renderWidth;
 }

 void setRenderWidth(float _renderWidth) {
 this->renderWidth = _renderWidth;
 }

 float getRenderHeight() {
 return this->renderHeight;
 }

 void setRenderHeight(float _renderHeight) {
 this->renderHeight = _renderHeight;
 }

 /**
 * The distance in pixels the pointer will hover around the character.
 */
 float getStickToCharDist() {
 return this->stickToCharDist;
 }

 void setStickToCharDist(float _stickToCharDist) {
 this->stickToCharDist = _stickToCharDist;
 }

 /**
 * The base render position for pointers is the center of the screen, adjust this to have it more at feet or head of character for example.
 */
 float getRenderOffsetX() {
 return this->renderOffsetX;
 }

 void setRenderOffsetX(float _renderOffsetX) {
 this->renderOffsetX = _renderOffsetX;
 }

 float getRenderOffsetY() {
 return this->renderOffsetY;
 }

 void setRenderOffsetY(float _renderOffsetY) {
 this->renderOffsetY = _renderOffsetY;
 }

 /**
 * Offset the screen target point, for example to point to top of counter by offsetting Y value
 */
 float getHomeOnOffsetX() {
 return this->homeOnOffsetX;
 }

 void setHomeOnOffsetX(float _homeOnOffsetX) {
 this->homeOnOffsetX = _homeOnOffsetX;
 }

 float getHomeOnOffsetY() {
 return this->homeOnOffsetY;
 }

 void setHomeOnOffsetY(float _homeOnOffsetY) {
 this->homeOnOffsetY = _homeOnOffsetY;
 }

 void setTableSurface() {
 this->homeOnOffsetY = -30.0F * Core.TileScale;
 }

 void setHighCounter() {
 this->homeOnOffsetY = -50.0F * Core.TileScale;
 }

 void setYOffsetScaled(float offset) {
 this->homeOnOffsetY = offset * Core.TileScale;
 }

 void setXOffsetScaled(float offset) {
 this->homeOnOffsetX = offset * Core.TileScale;
 }
 }

 class PlayerHomingPointList extends ArrayList<WorldMarkers.PlayerHomingPoint> {
 }

 class PlayerScreen {
 float centerX;
 float centerY;
 float x;
 float y;
 float width;
 float height;
 float padTop = 100.0F;
 float padLeft = 100.0F;
 float padBot = 100.0F;
 float padRight = 100.0F;
 float innerX;
 float innerY;
 float innerX2;
 float innerY2;
 private WorldMarkers.Line borderTop = new WorldMarkers.Line(new WorldMarkers.Point(0.0F, 0.0F), new WorldMarkers.Point(0.0F, 0.0F);
 private WorldMarkers.Line borderRight = new WorldMarkers.Line(new WorldMarkers.Point(0.0F, 0.0F), new WorldMarkers.Point(0.0F, 0.0F);
 private WorldMarkers.Line borderBot = new WorldMarkers.Line(new WorldMarkers.Point(0.0F, 0.0F), new WorldMarkers.Point(0.0F, 0.0F);
 private WorldMarkers.Line borderLeft = new WorldMarkers.Line(new WorldMarkers.Point(0.0F, 0.0F), new WorldMarkers.Point(0.0F, 0.0F);
 private WorldMarkers.Line[] borders = new WorldMarkers.Line[4];

 void update(int int0) {
 this->x = 0.0F;
 this->y = 0.0F;
 this->width = IsoCamera.getScreenWidth(int0);
 this->height = IsoCamera.getScreenHeight(int0);
 this->centerX = this->x + this->width / 2.0F;
 this->centerY = this->y + this->height / 2.0F;
 this->innerX = this->x + this->padLeft;
 this->innerY = this->y + this->padTop;
 float float0 = this->width - (this->padLeft + this->padRight);
 float float1 = this->height - (this->padTop + this->padBot);
 this->innerX2 = this->innerX + float0;
 this->innerY2 = this->innerY + float1;
 }

 private WorldMarkers.Line[] getBorders() {
 this->borders[0] = this->getBorderTop();
 this->borders[1] = this->getBorderRight();
 this->borders[2] = this->getBorderBot();
 this->borders[3] = this->getBorderLeft();
 return this->borders;
 }

 private WorldMarkers.Line getBorderTop() {
 this->borderTop.s.set(this->innerX, this->innerY);
 this->borderTop.e.set(this->innerX2, this->innerY);
 return this->borderTop;
 }

 private WorldMarkers.Line getBorderRight() {
 this->borderRight.s.set(this->innerX2, this->innerY);
 this->borderRight.e.set(this->innerX2, this->innerY2);
 return this->borderRight;
 }

 private WorldMarkers.Line getBorderBot() {
 this->borderBot.s.set(this->innerX, this->innerY2);
 this->borderBot.e.set(this->innerX2, this->innerY2);
 return this->borderBot;
 }

 private WorldMarkers.Line getBorderLeft() {
 this->borderLeft.s.set(this->innerX, this->innerY);
 this->borderLeft.e.set(this->innerX, this->innerY2);
 return this->borderLeft;
 }

 float clampToInnerX(float float0) {
 return PZMath.clamp(float0, this->innerX, this->innerX2);
 }

 float clampToInnerY(float float0) {
 return PZMath.clamp(float0, this->innerY, this->innerY2);
 }

 bool isOnScreen(float float1, float float0) {
 return float1 >= this->x && float1 < this->x + this->width && float0 >= this->y && float0 < this->y + this->height;
 }

 bool isWithinInner(float float1, float float0) {
 return float1 >= this->innerX && float1 < this->innerX2 && float0 >= this->innerY && float0 < this->innerY2;
 }
 }

 private static class Point {
 float x;
 float y;

 Point(float float0, float float1) {
 this->x = float0;
 this->y = float1;
 }

 public WorldMarkers.Point set(float arg0, float arg1) {
 this->x = arg0;
 this->y = arg1;
 return this;
 }

 bool notInfinite() {
 return !Float.isInfinite(this->x) && !Float.isInfinite(this->y);
 }

 std::string toString() {
 return String.format("{%f, %f}", this->x, this->y);
 }
 }
}
} // namespace iso
} // namespace zombie
