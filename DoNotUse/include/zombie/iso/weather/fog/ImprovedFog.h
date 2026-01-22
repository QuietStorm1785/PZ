#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
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
#include "zombie/iso/weather/fog/ImprovedFog/FogRectangle.h"
#include "zombie/iso/weather/fog/ImprovedFog/RectangleIterator.h"
#include "zombie/iso/weather/fx/SteppedUpdateFloat.h"

namespace zombie {
namespace iso {
namespace weather {
namespace fog {


class ImprovedFog {
public:
    static const RectangleIterator rectangleIter = std::make_shared<RectangleIterator>();
    static const Vector2i rectangleMatrixPos = std::make_shared<Vector2i>();
    static IsoChunkMap chunkMap;
    static int minY;
    static int maxY;
    static int minX;
    static int maxX;
    static int zLayer;
    static Vector2i lastIterPos = std::make_shared<Vector2i>();
    static FogRectangle fogRectangle = std::make_shared<FogRectangle>();
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
    static const SteppedUpdateFloat fogIntensity = std::make_shared<SteppedUpdateFloat>(0.0F, 0.005F, 0.0F, 1.0F);
    static int keyPause = 0;
   private static const float[] offsets = new float[]{
      0.3F,
      0.8F,
      0.0F,
      0.6F,
      0.3F,
      0.1F,
      0.5F,
      0.9F,
      0.2F,
      0.0F,
      0.7F,
      0.1F,
      0.4F,
      0.2F,
      0.5F,
      0.3F,
      0.8F,
      0.4F,
      0.9F,
      0.5F,
      0.8F,
      0.4F,
      0.7F,
      0.2F,
      0.0F,
      0.6F,
      0.1F,
      0.6F,
      0.9F,
      0.7F
   };

    static int getMinXOffset() {
    return minXOffset;
   }

    static void setMinXOffset(int var0) {
      minXOffset = var0;
   }

    static int getMaxXOffset() {
    return maxXOffset;
   }

    static void setMaxXOffset(int var0) {
      maxXOffset = var0;
   }

    static int getMaxYOffset() {
    return maxYOffset;
   }

    static void setMaxYOffset(int var0) {
      maxYOffset = var0;
   }

    static bool isRenderEndOnly() {
    return renderEndOnly;
   }

    static void setRenderEndOnly(bool var0) {
      renderEndOnly = var0;
   }

    static float getAlphaCircleAlpha() {
    return alphaCircleAlpha;
   }

    static void setAlphaCircleAlpha(float var0) {
      alphaCircleAlpha = var0;
   }

    static float getAlphaCircleRad() {
    return alphaCircleRad;
   }

    static void setAlphaCircleRad(float var0) {
      alphaCircleRad = var0;
   }

    static bool isHighQuality() {
    return highQuality;
   }

    static void setHighQuality(bool var0) {
      highQuality = var0;
   }

    static bool isEnableEditing() {
    return enableEditing;
   }

    static void setEnableEditing(bool var0) {
      enableEditing = var0;
   }

    static float getTopAlphaHeight() {
    return topAlphaHeight;
   }

    static void setTopAlphaHeight(float var0) {
      topAlphaHeight = var0;
   }

    static float getBottomAlphaHeight() {
    return bottomAlphaHeight;
   }

    static void setBottomAlphaHeight(float var0) {
      bottomAlphaHeight = var0;
   }

    static bool isDrawDebugColors() {
    return drawDebugColors;
   }

    static void setDrawDebugColors(bool var0) {
      drawDebugColors = var0;
   }

    static float getOctaves() {
    return octaves;
   }

    static void setOctaves(float var0) {
      octaves = var0;
   }

    static float getColorR() {
    return colorR;
   }

    static void setColorR(float var0) {
      colorR = var0;
   }

    static float getColorG() {
    return colorG;
   }

    static void setColorG(float var0) {
      colorG = var0;
   }

    static float getColorB() {
    return colorB;
   }

    static void setColorB(float var0) {
      colorB = var0;
   }

    static float getSecondLayerAlpha() {
    return secondLayerAlpha;
   }

    static void setSecondLayerAlpha(float var0) {
      secondLayerAlpha = var0;
   }

    static float getScalingX() {
    return scalingX;
   }

    static void setScalingX(float var0) {
      scalingX = var0;
   }

    static float getScalingY() {
    return scalingY;
   }

    static void setScalingY(float var0) {
      scalingY = var0;
   }

    static bool isRenderOnlyOneRow() {
    return renderOnlyOneRow;
   }

    static void setRenderOnlyOneRow(bool var0) {
      renderOnlyOneRow = var0;
   }

    static float getBaseAlpha() {
    return baseAlpha;
   }

    static void setBaseAlpha(float var0) {
      baseAlpha = var0;
   }

    static int getRenderEveryXRow() {
    return renderEveryXRow;
   }

    static void setRenderEveryXRow(int var0) {
      renderEveryXRow = var0;
   }

    static bool isRenderCurrentLayerOnly() {
    return renderCurrentLayerOnly;
   }

    static void setRenderCurrentLayerOnly(bool var0) {
      renderCurrentLayerOnly = var0;
   }

    static int getRenderXRowsFromCenter() {
    return renderXRowsFromCenter;
   }

    static void setRenderXRowsFromCenter(int var0) {
      renderXRowsFromCenter = var0;
   }

    static void update() {
      updateKeys();
      if (noiseTexture == nullptr) {
         noiseTexture = Texture.getSharedTexture("media/textures/weather/fognew/fog_noise.png");
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
    double var0 = climateManager.getWindAngleRadians();
         var0 -= Math.PI * 3.0 / 4.0;
         var0 = Math.PI - var0;
    float var2 = (float)Math.cos(var0);
    float var3 = (float)Math.sin(var0);
         scalingX = scalingX + var2 * climateManager.getWindIntensity() * GameTime.getInstance().getMultiplier();
         scalingY = scalingY + var3 * climateManager.getWindIntensity() * GameTime.getInstance().getMultiplier();
      }
   }

    static void startRender(int var0, int var1) {
      climateManager = ClimateManager.getInstance();
      if (var1 < 2 && !(baseAlpha <= 0.0F) && PerformanceSettings.FogQuality != 2) {
         drawingThisLayer = true;
    IsoPlayer var2 = IsoPlayer.players[var0];
         if (renderCurrentLayerOnly && var2.getZ() != var1) {
            drawingThisLayer = false;
         } else if (var2.isInARoom() && var1 > 0) {
            drawingThisLayer = false;
         } else {
            playerRow = (int)var2.getX() + (int)var2.getY();
            ZOOM = Core.getInstance().getZoom(var0);
            zLayer = var1;
            PlayerIndex = var0;
    PlayerCamera var3 = IsoCamera.cameras[var0];
            screenWidth = IsoCamera.getOffscreenWidth(var0);
            screenHeight = IsoCamera.getOffscreenHeight(var0);
            worldOffsetX = var3.getOffX() - IsoCamera.getOffscreenLeft(PlayerIndex) * ZOOM;
            worldOffsetY = var3.getOffY() + IsoCamera.getOffscreenTop(PlayerIndex) * ZOOM;
            rightClickOffX = var3.RightClickX;
            rightClickOffY = var3.RightClickY;
            cameraOffscreenLeft = IsoCamera.getOffscreenLeft(var0);
            cameraOffscreenTop = IsoCamera.getOffscreenTop(var0);
            cameraZoom = ZOOM;
            if (!enableEditing) {
               if (var2.getVehicle() != nullptr) {
                  alphaCircleAlpha = 0.0F;
                  alphaCircleRad = highQuality ? 2.0F : 2.6F;
               } else if (var2.isInARoom()) {
                  alphaCircleAlpha = 0.0F;
                  alphaCircleRad = highQuality ? 1.25F : 1.5F;
               } else {
                  alphaCircleAlpha = highQuality ? 0.1F : 0.16F;
                  alphaCircleRad = highQuality ? 2.5F : 3.0F;
                  if (climateManager.getWeatherPeriod().isRunning()
                     && (climateManager.getWeatherPeriod().isTropicalStorm() || climateManager.getWeatherPeriod().isThunderStorm())) {
                     alphaCircleRad *= 0.6F;
                  }
               }
            }

    uint8_t var4 = 0;
    uint8_t var5 = 0;
    int var6 = var4 + IsoCamera.getOffscreenWidth(var0);
    int var7 = var5 + IsoCamera.getOffscreenHeight(var0);
    float var8 = IsoUtils.XToIso(var4, var5, zLayer);
    float var9 = IsoUtils.YToIso(var4, var5, zLayer);
    float var10 = IsoUtils.XToIso(var6, var7, zLayer);
    float var11 = IsoUtils.YToIso(var6, var7, zLayer);
    float var12 = IsoUtils.YToIso(var4, var7, zLayer);
            minY = (int)var9;
            maxY = (int)var11;
            minX = (int)var8;
            maxX = (int)var10;
            if (IsoPlayer.numPlayers > 1) {
               maxX = Math.max(maxX, IsoWorld.instance.CurrentCell.getMaxX());
               maxY = Math.max(maxY, IsoWorld.instance.CurrentCell.getMaxY());
            }

            minX = minX + minXOffset;
            maxX = maxX + maxXOffset;
            maxY = maxY + maxYOffset;
    int var13 = maxX - minX;
    int var14 = var13;
            if (minY != maxY) {
               var14 = (int)(var13 + PZMath.abs(minY - maxY));
            }

            rectangleIter.reset(var13, var14);
            lastRow = -1;
            fogRectangle.hasStarted = false;
            chunkMap = IsoWorld.instance.getCell().getChunkMap(var0);
         }
      } else {
         drawingThisLayer = false;
      }
   }

    static void renderRowsBehind(IsoGridSquare var0) {
      if (drawingThisLayer) {
    int var1 = -1;
         if (var0 != nullptr) {
            var1 = var0.getX() + var0.getY();
            if (var1 < minX + minY) {
               return;
            }
         }

         if (lastRow < 0 || lastRow != var1) {
    Vector2i var3 = rectangleMatrixPos;

            while (rectangleIter.next(var3)) {
               if (var3 != nullptr) {
    int var5 = var3.x + minX;
    int var6 = var3.y + minY;
    int var4 = var5 + var6;
                  if (var4 != lastRow) {
                     if (lastRow >= 0 && (!renderEndOnly || var0 == nullptr)) {
                        endFogRectangle(lastIterPos.x, lastIterPos.y, zLayer);
                     }

                     lastRow = var4;
                  }

    IsoGridSquare var2 = chunkMap.getGridSquare(var5, var6, zLayer);
    bool var7 = true;
                  if (var2 != nullptr && (!var2.isExteriorCache || var2.isInARoom())) {
                     var7 = false;
                  }

                  if (var7) {
                     if (!renderEndOnly || var0 == nullptr) {
                        startFogRectangle(var5, var6, zLayer);
                     }
                  } else if (!renderEndOnly || var0 == nullptr) {
                     endFogRectangle(lastIterPos.x, lastIterPos.y, zLayer);
                  }

                  lastIterPos.set(var5, var6);
                  if (var1 != -1 && var4 == var1) {
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

    static void startFogRectangle(int var0, int var1, int var2) {
      if (!fogRectangle.hasStarted) {
         fogRectangle.hasStarted = true;
         fogRectangle.startX = var0;
         fogRectangle.startY = var1;
         fogRectangle.Z = var2;
      }
   }

    static void endFogRectangle(int var0, int var1, int var2) {
      if (fogRectangle.hasStarted) {
         fogRectangle.hasStarted = false;
         fogRectangle.endX = var0;
         fogRectangle.endY = var1;
         fogRectangle.Z = var2;
         renderFogSegment();
      }
   }

    static void renderFogSegment() {
    int var0 = fogRectangle.startX + fogRectangle.startY;
    int var1 = fogRectangle.endX + fogRectangle.endY;
      if (Core.bDebug && var0 != var1) {
         DebugLog.log("ROWS NOT EQUAL");
      }

      if (renderOnlyOneRow) {
         if (var0 != playerRow) {
            return;
         }
      } else if (var0 % renderEveryXRow != 0) {
         return;
      }

      if (!Core.bDebug || renderXRowsFromCenter < 1 || var0 >= playerRow - renderXRowsFromCenter && var0 <= playerRow + renderXRowsFromCenter) {
    float var2 = baseAlpha;
    FogRectangle var3 = fogRectangle;
    float var4 = IsoUtils.XToScreenExact(var3.startX, var3.startY, var3.Z, 0);
    float var5 = IsoUtils.YToScreenExact(var3.startX, var3.startY, var3.Z, 0);
    float var6 = IsoUtils.XToScreenExact(var3.endX, var3.endY, var3.Z, 0);
    float var7 = IsoUtils.YToScreenExact(var3.endX, var3.endY, var3.Z, 0);
         var4 -= 32.0F * Core.TileScale;
         var5 -= 80.0F * Core.TileScale;
         var6 += 32.0F * Core.TileScale;
    float var8 = 96.0F * Core.TileScale;
    float var9 = (var6 - var4) / (64.0F * Core.TileScale);
    float var10 = var3.startX % 6.0F;
    float var11 = var10 / 6.0F;
    float var12 = var9 / 6.0F;
    float var14 = var12 + var11;
         if (FogShader.instance.StartShader()) {
            FogShader.instance.setScreenInfo(screenWidth, screenHeight, ZOOM, zLayer > 0 ? secondLayerAlpha : 1.0F);
            FogShader.instance.setTextureInfo(drawDebugColors ? 1.0F : 0.0F, octaves, var2, Core.TileScale);
            FogShader.instance.setRectangleInfo((int)var4, (int)var5, (int)(var6 - var4), (int)var8);
            FogShader.instance.setWorldOffset(worldOffsetX, worldOffsetY, rightClickOffX, rightClickOffY);
            FogShader.instance.setScalingInfo(scalingX, scalingY, zLayer, highQuality ? 0.0F : 1.0F);
            FogShader.instance.setColorInfo(colorR, colorG, colorB, 1.0F);
            FogShader.instance.setParamInfo(topAlphaHeight, bottomAlphaHeight, alphaCircleAlpha, alphaCircleRad);
            FogShader.instance.setCameraInfo(cameraOffscreenLeft, cameraOffscreenTop, cameraZoom, offsets[var0 % offsets.length]);
            SpriteRenderer.instance
               .render(
                  noiseTexture, (int)var4, (int)var5, (int)(var6 - var4), (int)var8, 1.0F, 1.0F, 1.0F, var2, var11, 0.0F, var14, 0.0F, var14, 1.0F, var11, 1.0F
               );
            IndieGL.EndShader();
         }
      }
   }

   public static void DrawSubTextureRGBA(
      Texture var0,
      double var1,
      double var3,
      double var5,
      double var7,
      double var9,
      double var11,
      double var13,
      double var15,
      double var17,
      double var19,
      double var21,
      double var23
   ) {
      if (var0 != nullptr && !(var5 <= 0.0) && !(var7 <= 0.0) && !(var13 <= 0.0) && !(var15 <= 0.0)) {
    double var25 = var9 + var0.offsetX;
    double var27 = var11 + var0.offsetY;
         if (!(var27 + var15 < 0.0) && !(var27 > 4096.0)) {
    float var29 = PZMath.clamp((float)var1, 0.0F, var0.getWidth());
    float var30 = PZMath.clamp((float)var3, 0.0F, var0.getHeight());
    float var31 = PZMath.clamp((float)(var29 + var5), 0.0F, var0.getWidth()) - var29;
    float var32 = PZMath.clamp((float)(var30 + var7), 0.0F, var0.getHeight()) - var30;
    float var33 = var29 / var0.getWidth();
    float var34 = var30 / var0.getHeight();
    float var35 = (var29 + var31) / var0.getWidth();
    float var36 = (var30 + var32) / var0.getHeight();
    float var37 = var0.getXEnd() - var0.getXStart();
    float var38 = var0.getYEnd() - var0.getYStart();
            var33 = var0.getXStart() + var33 * var37;
            var35 = var0.getXStart() + var35 * var37;
            var34 = var0.getYStart() + var34 * var38;
            var36 = var0.getYStart() + var36 * var38;
            SpriteRenderer.instance
               .render(
                  var0,
                  (float)var25,
                  (float)var27,
                  (float)var13,
                  (float)var15,
                  (float)var17,
                  (float)var19,
                  (float)var21,
                  (float)var23,
                  var33,
                  var34,
                  var35,
                  var34,
                  var35,
                  var36,
                  var33,
                  var36
               );
         }
      }
   }

    static void updateKeys() {
      if (Core.bDebug) {
         if (keyPause > 0) {
            keyPause--;
         }

         if (keyPause <= 0 && GameKeyboard.isKeyDown(72)) {
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
}
} // namespace fog
} // namespace weather
} // namespace iso
} // namespace zombie
