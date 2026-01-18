#pragma once
#include "org/joml/Vector2i.h"
#include "zombie/GameTime.h"
#include "zombie/IndieGL.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Core.h"
#include "zombie/core/PerformanceSettings.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/input/GameKeyboard.h"
#include "zombie/iso/IsoCamera.h"
#include "zombie/iso/IsoChunkMap.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoUtils.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/PlayerCamera.h"
#include "zombie/iso/weather/ClimateManager.h"
#include "zombie/iso/weather/fx/SteppedUpdateFloat.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace iso {
namespace weather {
namespace fog {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

/**
 * TurboTuTone.
 */
class ImprovedFog {
public:
private
 static ImprovedFog.RectangleIterator rectangleIter =
 new ImprovedFog.RectangleIterator();
 static const Vector2i rectangleMatrixPos = new Vector2i();
 static IsoChunkMap chunkMap;
 static int minY;
 static int maxY;
 static int minX;
 static int maxX;
 static int zLayer;
 static Vector2i lastIterPos = new Vector2i();
private
 static ImprovedFog.FogRectangle fogRectangle = new ImprovedFog.FogRectangle();
 static bool drawingThisLayer = false;
 static float ZOOM = 1.0F;
 static int PlayerIndex;
 static int playerRow;
 static float screenWidth;
 static float screenHeight;
 static float worldOffsetX;
 static float worldOffsetY;
 static float topAlphaHeight = 0.38F;
 static float bottomAlphaHeight = 0.24F;
 static float secondLayerAlpha = 0.5F;
 static float scalingX = 1.0F;
 static float scalingY = 1.0F;
 static float colorR = 1.0F;
 static float colorG = 1.0F;
 static float colorB = 1.0F;
 static bool drawDebugColors = false;
 static float octaves = 6.0F;
 static bool highQuality = true;
 static bool enableEditing = false;
 static float alphaCircleAlpha = 0.3F;
 static float alphaCircleRad = 2.25F;
 static int lastRow = -1;
 static ClimateManager climateManager;
 static Texture noiseTexture;
 static bool renderOnlyOneRow = false;
 static float baseAlpha = 0.0F;
 static int renderEveryXRow = 1;
 static int renderXRowsFromCenter = 0;
 static bool renderCurrentLayerOnly = false;
 static float rightClickOffX = 0.0F;
 static float rightClickOffY = 0.0F;
 static float cameraOffscreenLeft = 0.0F;
 static float cameraOffscreenTop = 0.0F;
 static float cameraZoom = 0.0F;
 static int minXOffset = -2;
 static int maxXOffset = 12;
 static int maxYOffset = -5;
 static bool renderEndOnly = false;
 static const SteppedUpdateFloat fogIntensity =
 new SteppedUpdateFloat(0.0F, 0.005F, 0.0F, 1.0F);
 static int keyPause = 0;
private
 static float[] offsets =
 new float[]{0.3F, 0.8F, 0.0F, 0.6F, 0.3F, 0.1F, 0.5F, 0.9F, 0.2F, 0.0F,
 0.7F, 0.1F, 0.4F, 0.2F, 0.5F, 0.3F, 0.8F, 0.4F, 0.9F, 0.5F,
 0.8F, 0.4F, 0.7F, 0.2F, 0.0F, 0.6F, 0.1F, 0.6F, 0.9F, 0.7F};

 static int getMinXOffset() { return minXOffset; }

 static void setMinXOffset(int _minXOffset) { minXOffset = _minXOffset; }

 static int getMaxXOffset() { return maxXOffset; }

 static void setMaxXOffset(int _maxXOffset) { maxXOffset = _maxXOffset; }

 static int getMaxYOffset() { return maxYOffset; }

 static void setMaxYOffset(int _maxYOffset) { maxYOffset = _maxYOffset; }

 static bool isRenderEndOnly() { return renderEndOnly; }

 static void setRenderEndOnly(bool _renderEndOnly) {
 renderEndOnly = _renderEndOnly;
 }

 static float getAlphaCircleAlpha() { return alphaCircleAlpha; }

 static void setAlphaCircleAlpha(float _alphaCircleAlpha) {
 alphaCircleAlpha = _alphaCircleAlpha;
 }

 static float getAlphaCircleRad() { return alphaCircleRad; }

 static void setAlphaCircleRad(float _alphaCircleRad) {
 alphaCircleRad = _alphaCircleRad;
 }

 static bool isHighQuality() { return highQuality; }

 static void setHighQuality(bool _highQuality) { highQuality = _highQuality; }

 static bool isEnableEditing() { return enableEditing; }

 static void setEnableEditing(bool _enableEditing) {
 enableEditing = _enableEditing;
 }

 static float getTopAlphaHeight() { return topAlphaHeight; }

 static void setTopAlphaHeight(float _topAlphaHeight) {
 topAlphaHeight = _topAlphaHeight;
 }

 static float getBottomAlphaHeight() { return bottomAlphaHeight; }

 static void setBottomAlphaHeight(float _bottomAlphaHeight) {
 bottomAlphaHeight = _bottomAlphaHeight;
 }

 static bool isDrawDebugColors() { return drawDebugColors; }

 static void setDrawDebugColors(bool _drawDebugColors) {
 drawDebugColors = _drawDebugColors;
 }

 static float getOctaves() { return octaves; }

 static void setOctaves(float _octaves) { octaves = _octaves; }

 static float getColorR() { return colorR; }

 static void setColorR(float _colorR) { colorR = _colorR; }

 static float getColorG() { return colorG; }

 static void setColorG(float _colorG) { colorG = _colorG; }

 static float getColorB() { return colorB; }

 static void setColorB(float _colorB) { colorB = _colorB; }

 static float getSecondLayerAlpha() { return secondLayerAlpha; }

 static void setSecondLayerAlpha(float _secondLayerAlpha) {
 secondLayerAlpha = _secondLayerAlpha;
 }

 static float getScalingX() { return scalingX; }

 static void setScalingX(float _scalingX) { scalingX = _scalingX; }

 static float getScalingY() { return scalingY; }

 static void setScalingY(float _scalingY) { scalingY = _scalingY; }

 static bool isRenderOnlyOneRow() { return renderOnlyOneRow; }

 static void setRenderOnlyOneRow(bool _renderOnlyOneRow) {
 renderOnlyOneRow = _renderOnlyOneRow;
 }

 static float getBaseAlpha() { return baseAlpha; }

 static void setBaseAlpha(float _baseAlpha) { baseAlpha = _baseAlpha; }

 static int getRenderEveryXRow() { return renderEveryXRow; }

 static void setRenderEveryXRow(int _renderEveryXRow) {
 renderEveryXRow = _renderEveryXRow;
 }

 static bool isRenderCurrentLayerOnly() { return renderCurrentLayerOnly; }

 static void setRenderCurrentLayerOnly(bool _renderCurrentLayerOnly) {
 renderCurrentLayerOnly = _renderCurrentLayerOnly;
 }

 static int getRenderXRowsFromCenter() { return renderXRowsFromCenter; }

 static void setRenderXRowsFromCenter(int _renderXRowsFromCenter) {
 renderXRowsFromCenter = _renderXRowsFromCenter;
 }

 static void update() {
 updateKeys();
 if (noiseTexture.empty()) {
 noiseTexture = Texture.getSharedTexture(
 "media/textures/weather/fognew/fog_noise.png");
 }

 climateManager = ClimateManager.getInstance();
 if (!enableEditing) {
 highQuality = PerformanceSettings.FogQuality == 0;
 fogIntensity.setTarget(climateManager.getFogIntensity());
 fogIntensity.update(GameTime.getInstance().getMultiplier());
 baseAlpha = fogIntensity.value();
 if (highQuality) {
 renderEveryXRow = 1;
 topAlphaHeight = 0.38F;
 bottomAlphaHeight = 0.24F;
 octaves = 6.0F;
 secondLayerAlpha = 0.5F;
 } else {
 renderEveryXRow = 2;
 topAlphaHeight = 0.32F;
 bottomAlphaHeight = 0.32F;
 octaves = 3.0F;
 secondLayerAlpha = 1.0F;
 }

 colorR = climateManager.getColorNewFog().getExterior().r;
 colorG = climateManager.getColorNewFog().getExterior().g;
 colorB = climateManager.getColorNewFog().getExterior().b;
 }

 if (baseAlpha <= 0.0F) {
 scalingX = 0.0F;
 scalingY = 0.0F;
 } else {
 double double0 = climateManager.getWindAngleRadians();
 double0 -= Math.PI * 3.0 / 4.0;
 double0 = Math.PI - double0;
 float float0 = (float)Math.cos(double0);
 float float1 = (float)Math.sin(double0);
 scalingX = scalingX + float0 * climateManager.getWindIntensity() *
 GameTime.getInstance().getMultiplier();
 scalingY = scalingY + float1 * climateManager.getWindIntensity() *
 GameTime.getInstance().getMultiplier();
 }
 }

 static void startRender(int nPlayer, int z) {
 climateManager = ClimateManager.getInstance();
 if (z < 2 && !(baseAlpha <= 0.0F) && PerformanceSettings.FogQuality != 2) {
 drawingThisLayer = true;
 IsoPlayer player = IsoPlayer.players[nPlayer];
 if (renderCurrentLayerOnly && player.getZ() != z) {
 drawingThisLayer = false;
 } else if (player.isInARoom() && z > 0) {
 drawingThisLayer = false;
 } else {
 playerRow = (int)player.getX() + (int)player.getY();
 ZOOM = Core.getInstance().getZoom(nPlayer);
 zLayer = z;
 PlayerIndex = nPlayer;
 PlayerCamera playerCamera = IsoCamera.cameras[nPlayer];
 screenWidth = IsoCamera.getOffscreenWidth(nPlayer);
 screenHeight = IsoCamera.getOffscreenHeight(nPlayer);
 worldOffsetX = playerCamera.getOffX() -
 IsoCamera.getOffscreenLeft(PlayerIndex) * ZOOM;
 worldOffsetY = playerCamera.getOffY() +
 IsoCamera.getOffscreenTop(PlayerIndex) * ZOOM;
 rightClickOffX = playerCamera.RightClickX;
 rightClickOffY = playerCamera.RightClickY;
 cameraOffscreenLeft = IsoCamera.getOffscreenLeft(nPlayer);
 cameraOffscreenTop = IsoCamera.getOffscreenTop(nPlayer);
 cameraZoom = ZOOM;
 if (!enableEditing) {
 if (player.getVehicle() != nullptr) {
 alphaCircleAlpha = 0.0F;
 alphaCircleRad = highQuality ? 2.0F : 2.6F;
 } else if (player.isInARoom()) {
 alphaCircleAlpha = 0.0F;
 alphaCircleRad = highQuality ? 1.25F : 1.5F;
 } else {
 alphaCircleAlpha = highQuality ? 0.1F : 0.16F;
 alphaCircleRad = highQuality ? 2.5F : 3.0F;
 if (climateManager.getWeatherPeriod().isRunning() &&
 (climateManager.getWeatherPeriod().isTropicalStorm() ||
 climateManager.getWeatherPeriod().isThunderStorm())) {
 alphaCircleRad *= 0.6F;
 }
 }
 }

 uint8_t byte0 = 0;
 uint8_t byte1 = 0;
 int int0 = byte0 + IsoCamera.getOffscreenWidth(nPlayer);
 int int1 = byte1 + IsoCamera.getOffscreenHeight(nPlayer);
 float float0 = IsoUtils.XToIso(byte0, byte1, zLayer);
 float float1 = IsoUtils.YToIso(byte0, byte1, zLayer);
 float float2 = IsoUtils.XToIso(int0, int1, zLayer);
 float float3 = IsoUtils.YToIso(int0, int1, zLayer);
 float float4 = IsoUtils.YToIso(byte0, int1, zLayer);
 minY = (int)float1;
 maxY = (int)float3;
 minX = (int)float0;
 maxX = (int)float2;
 if (IsoPlayer.numPlayers > 1) {
 maxX = Math.max(maxX, IsoWorld.instance.CurrentCell.getMaxX());
 maxY = Math.max(maxY, IsoWorld.instance.CurrentCell.getMaxY());
 }

 minX = minX + minXOffset;
 maxX = maxX + maxXOffset;
 maxY = maxY + maxYOffset;
 int int2 = maxX - minX;
 int int3 = int2;
 if (minY != maxY) {
 int3 = (int)(int2 + PZMath.abs(minY - maxY);
 }

 rectangleIter.reset(int2, int3);
 lastRow = -1;
 fogRectangle.hasStarted = false;
 chunkMap = IsoWorld.instance.getCell().getChunkMap(nPlayer);
 }
 } else {
 drawingThisLayer = false;
 }
 }

 static void renderRowsBehind(IsoGridSquare squareMax) {
 if (drawingThisLayer) {
 int int0 = -1;
 if (squareMax != nullptr) {
 int0 = squareMax.getX() + squareMax.getY();
 if (int0 < minX + minY) {
 return;
 }
 }

 if (lastRow < 0 || lastRow != int0) {
 Vector2i vector2i = rectangleMatrixPos;

 while (rectangleIter.next(vector2i) {
 if (vector2i != nullptr) {
 int int1 = vector2i.x + minX;
 int int2 = vector2i.y + minY;
 int int3 = int1 + int2;
 if (int3 != lastRow) {
 if (lastRow >= 0 && (!renderEndOnly || squareMax.empty())) {
 endFogRectangle(lastIterPos.x, lastIterPos.y, zLayer);
 }

 lastRow = int3;
 }

 IsoGridSquare square = chunkMap.getGridSquare(int1, int2, zLayer);
 bool boolean0 = true;
 if (square != nullptr &&
 (!square.isExteriorCache || square.isInARoom())) {
 boolean0 = false;
 }

 if (boolean0) {
 if (!renderEndOnly || squareMax.empty()) {
 startFogRectangle(int1, int2, zLayer);
 }
 } else if (!renderEndOnly || squareMax.empty()) {
 endFogRectangle(lastIterPos.x, lastIterPos.y, zLayer);
 }

 lastIterPos.set(int1, int2);
 if (int0 != -1 && int3 == int0) {
 break;
 }
 }
 }
 }
 }
 }

 static void endRender() {
 if (drawingThisLayer) {
 renderRowsBehind(nullptr);
 if (fogRectangle.hasStarted) {
 endFogRectangle(lastIterPos.x, lastIterPos.y, zLayer);
 }
 }
 }

 static void startFogRectangle(int int0, int int1, int int2) {
 if (!fogRectangle.hasStarted) {
 fogRectangle.hasStarted = true;
 fogRectangle.startX = int0;
 fogRectangle.startY = int1;
 fogRectangle.Z = int2;
 }
 }

 static void endFogRectangle(int int0, int int1, int int2) {
 if (fogRectangle.hasStarted) {
 fogRectangle.hasStarted = false;
 fogRectangle.endX = int0;
 fogRectangle.endY = int1;
 fogRectangle.Z = int2;
 renderFogSegment();
 }
 }

 static void renderFogSegment() {
 int int0 = fogRectangle.startX + fogRectangle.startY;
 int int1 = fogRectangle.endX + fogRectangle.endY;
 if (Core.bDebug && int0 != int1) {
 DebugLog.log("ROWS NOT EQUAL");
 }

 if (renderOnlyOneRow) {
 if (int0 != playerRow) {
 return;
 }
 } else if (int0 % renderEveryXRow != 0) {
 return;
 }

 if (!Core.bDebug || renderXRowsFromCenter < 1 ||
 int0 >= playerRow - renderXRowsFromCenter &&
 int0 <= playerRow + renderXRowsFromCenter) {
 float float0 = baseAlpha;
 ImprovedFog.FogRectangle fogRectanglex = fogRectangle;
 float float1 = IsoUtils.XToScreenExact(
 fogRectanglex.startX, fogRectanglex.startY, fogRectanglex.Z, 0);
 float float2 = IsoUtils.YToScreenExact(
 fogRectanglex.startX, fogRectanglex.startY, fogRectanglex.Z, 0);
 float float3 = IsoUtils.XToScreenExact(
 fogRectanglex.endX, fogRectanglex.endY, fogRectanglex.Z, 0);
 float float4 = IsoUtils.YToScreenExact(
 fogRectanglex.endX, fogRectanglex.endY, fogRectanglex.Z, 0);
 float1 -= 32.0F * Core.TileScale;
 float2 -= 80.0F * Core.TileScale;
 float3 += 32.0F * Core.TileScale;
 float float5 = 96.0F * Core.TileScale;
 float float6 = (float3 - float1) / (64.0F * Core.TileScale);
 float float7 = fogRectanglex.startX % 6.0F;
 float float8 = float7 / 6.0F;
 float float9 = float6 / 6.0F;
 float float10 = float9 + float8;
 if (FogShader.instance.StartShader()) {
 FogShader.instance.setScreenInfo(screenWidth, screenHeight, ZOOM,
 zLayer > 0 ? secondLayerAlpha : 1.0F);
 FogShader.instance.setTextureInfo(drawDebugColors ? 1.0F : 0.0F,
 octaves, float0, Core.TileScale);
 FogShader.instance.setRectangleInfo(
 (int)float1, (int)float2, (int)(float3 - float1), (int)float5);
 FogShader.instance.setWorldOffset(worldOffsetX, worldOffsetY,
 rightClickOffX, rightClickOffY);
 FogShader.instance.setScalingInfo(scalingX, scalingY, zLayer,
 highQuality ? 0.0F : 1.0F);
 FogShader.instance.setColorInfo(colorR, colorG, colorB, 1.0F);
 FogShader.instance.setParamInfo(topAlphaHeight, bottomAlphaHeight,
 alphaCircleAlpha, alphaCircleRad);
 FogShader.instance.setCameraInfo(cameraOffscreenLeft,
 cameraOffscreenTop, cameraZoom,
 offsets[int0 % offsets.length]);
 SpriteRenderer.instance.render(
 noiseTexture, (int)float1, (int)float2, (int)(float3 - float1),
 (int)float5, 1.0F, 1.0F, 1.0F, float0, float8, 0.0F, float10, 0.0F,
 float10, 1.0F, float8, 1.0F);
 IndieGL.EndShader();
 }
 }
 }

public
 static void DrawSubTextureRGBA(Texture tex, double subX, double subY,
 double subW, double subH, double x, double y,
 double w, double h, double r, double g,
 double b, double a) {
 if (tex != nullptr && !(subW <= 0.0) && !(subH <= 0.0) && !(w <= 0.0) &&
 !(h <= 0.0) {
 double double0 = x + tex.offsetX;
 double double1 = y + tex.offsetY;
 if (!(double1 + h < 0.0) && !(double1 > 4096.0) {
 float float0 = PZMath.clamp((float)subX, 0.0F, (float)tex.getWidth());
 float float1 = PZMath.clamp((float)subY, 0.0F, (float)tex.getHeight());
 float float2 =
 PZMath.clamp((float)(float0 + subW), 0.0F, (float)tex.getWidth()) -
 float0;
 float float3 =
 PZMath.clamp((float)(float1 + subH), 0.0F, (float)tex.getHeight()) -
 float1;
 float float4 = float0 / tex.getWidth();
 float float5 = float1 / tex.getHeight();
 float float6 = (float0 + float2) / tex.getWidth();
 float float7 = (float1 + float3) / tex.getHeight();
 float float8 = tex.getXEnd() - tex.getXStart();
 float float9 = tex.getYEnd() - tex.getYStart();
 float4 = tex.getXStart() + float4 * float8;
 float6 = tex.getXStart() + float6 * float8;
 float5 = tex.getYStart() + float5 * float9;
 float7 = tex.getYStart() + float7 * float9;
 SpriteRenderer.instance.render(
 tex, (float)double0, (float)double1, (float)w, (float)h, (float)r,
 (float)g, (float)b, (float)a, float4, float5, float6, float5,
 float6, float7, float4, float7);
 }
 }
 }

 static void updateKeys() {
 if (Core.bDebug) {
 if (keyPause > 0) {
 keyPause--;
 }

 if (keyPause <= 0 && GameKeyboard.isKeyDown(72) {
 DebugLog.log("Reloading fog shader...");
 keyPause = 30;
 FogShader.instance.reloadShader();
 }
 }
 }

 static void init() {
 climateManager = ClimateManager.getInstance();
 fogIntensity.setTarget(climateManager.getFogIntensity());
 fogIntensity.overrideCurrentValue(climateManager.getFogIntensity());
 baseAlpha = fogIntensity.value();
 }

private
 static class FogRectangle {
 int startX;
 int startY;
 int endX;
 int endY;
 int Z;
 bool hasStarted = false;
 }

 private static class RectangleIterator {
 int curX = 0;
 int curY = 0;
 int sX;
 int sY;
 int rowLen = 0;
 bool altRow = false;
 int curRow = 0;
 int rowIndex = 0;
 int maxRows = 0;

 void reset(int arg0, int arg1) {
 this->sX = 0;
 this->sY = 0;
 this->curX = 0;
 this->curY = 0;
 this->curRow = 0;
 this->altRow = false;
 this->rowIndex = 0;
 this->rowLen = (int)PZMath.ceil(arg1 / 2.0F);
 this->maxRows = arg0;
 }

 bool next(Vector2i arg0) {
 if (this->rowLen > 0 && this->maxRows > 0 && this->curRow < this->maxRows) {
 arg0.set(this->curX, this->curY);
 this->rowIndex++;
 if (this->rowIndex == this->rowLen) {
 this->rowLen = this->altRow ? this->rowLen - 1 : this->rowLen + 1;
 this->rowIndex = 0;
 this->sX = this->altRow ? this->sX + 1 : this->sX;
 this->sY = this->altRow ? this->sY : this->sY + 1;
 this->altRow = !this->altRow;
 this->curX = this->sX;
 this->curY = this->sY;
 this->curRow++;
 return this->curRow != this->maxRows;
 } else {
 this->curX++;
 this->curY--;
 return true;
 }
 } else {
 arg0.set(0, 0);
 return false;
 }
 }
 }
}
} // namespace fog
} // namespace weather
} // namespace iso
} // namespace zombie
