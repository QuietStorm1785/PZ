#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Core.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/debug/LineDrawer/DrawableLine.h"
#include "zombie/iso/IsoCamera.h"
#include "zombie/iso/IsoUtils.h"
#include "zombie/iso/PlayerCamera.h"
#include "zombie/iso/Vector2.h"
#include <algorithm>

namespace zombie {
namespace debug {


class LineDrawer {
public:
    static const long serialVersionUID = -8792265397633463907L;
    static int red = 0;
    static int green = 255;
    static int blue = 0;
    static int alpha = 255;
    static int idLayer = -1;
   static const std::vector<DrawableLine> lines = std::make_unique<std::vector<>>();
   static const ArrayDeque<DrawableLine> pool = std::make_unique<ArrayDeque<>>();
    static int layer;
    static const Vector2 tempo = std::make_shared<Vector2>();
    static const Vector2 tempo2 = std::make_shared<Vector2>();

    static void DrawTexturedRect(Texture var0, float var1, float var2, float var3, float var4, int var5, float var6, float var7, float var8) {
      var1 = (int)var1;
      var2 = (int)var2;
    Vector2 var9 = std::make_shared<Vector2>(var1, var2);
    Vector2 var10 = std::make_shared<Vector2>(var1 + var3, var2);
    Vector2 var11 = std::make_shared<Vector2>(var1 + var3, var2 + var4);
    Vector2 var12 = std::make_shared<Vector2>(var1, var2 + var4);
    Vector2 var13 = std::make_shared<Vector2>(IsoUtils.XToScreen(var9.x, var9.y, var5, 0), IsoUtils.YToScreen(var9.x, var9.y, var5, 0));
    Vector2 var14 = std::make_shared<Vector2>(IsoUtils.XToScreen(var10.x, var10.y, var5, 0), IsoUtils.YToScreen(var10.x, var10.y, var5, 0));
    Vector2 var15 = std::make_shared<Vector2>(IsoUtils.XToScreen(var11.x, var11.y, var5, 0), IsoUtils.YToScreen(var11.x, var11.y, var5, 0));
    Vector2 var16 = std::make_shared<Vector2>(IsoUtils.XToScreen(var12.x, var12.y, var5, 0), IsoUtils.YToScreen(var12.x, var12.y, var5, 0));
    PlayerCamera var17 = IsoCamera.cameras[IsoPlayer.getPlayerIndex()];
      var13.x = var13.x - var17.OffX;
      var14.x = var14.x - var17.OffX;
      var15.x = var15.x - var17.OffX;
      var16.x = var16.x - var17.OffX;
      var13.y = var13.y - var17.OffY;
      var14.y = var14.y - var17.OffY;
      var15.y = var15.y - var17.OffY;
      var16.y = var16.y - var17.OffY;
    float var18 = -240.0F;
      var18 -= 128.0F;
    float var19 = -32.0F;
      var13.y -= var18;
      var14.y -= var18;
      var15.y -= var18;
      var16.y -= var18;
      var13.x -= var19;
      var14.x -= var19;
      var15.x -= var19;
      var16.x -= var19;
      SpriteRenderer.instance
         .renderdebug(
            var0,
            var13.x,
            var13.y,
            var14.x,
            var14.y,
            var15.x,
            var15.y,
            var16.x,
            var16.y,
            var6,
            var7,
            var8,
            1.0F,
            var6,
            var7,
            var8,
            1.0F,
            var6,
            var7,
            var8,
            1.0F,
            var6,
            var7,
            var8,
            1.0F,
            nullptr
         );
   }

    static void DrawIsoLine(float var0, float var1, float var2, float var3, float var4, float var5, float var6, float var7, int var8) {
      tempo.set(var0, var1);
      tempo2.set(var2, var3);
    Vector2 var9 = std::make_shared<Vector2>(IsoUtils.XToScreen(tempo.x, tempo.y, 0.0F, 0), IsoUtils.YToScreen(tempo.x, tempo.y, 0.0F, 0));
    Vector2 var10 = std::make_shared<Vector2>(IsoUtils.XToScreen(tempo2.x, tempo2.y, 0.0F, 0), IsoUtils.YToScreen(tempo2.x, tempo2.y, 0.0F, 0));
      var9.x = var9.x - IsoCamera.getOffX();
      var10.x = var10.x - IsoCamera.getOffX();
      var9.y = var9.y - IsoCamera.getOffY();
      var10.y = var10.y - IsoCamera.getOffY();
      drawLine(var9.x, var9.y, var10.x, var10.y, var4, var5, var6, var7, var8);
   }

    static void DrawIsoRect(float var0, float var1, float var2, float var3, int var4, float var5, float var6, float var7) {
      DrawIsoRect(var0, var1, var2, var3, var4, 0, var5, var6, var7);
   }

    static void DrawIsoRect(float var0, float var1, float var2, float var3, int var4, int var5, float var6, float var7, float var8) {
      if (var2 < 0.0F) {
         var2 = -var2;
         var0 -= var2;
      }

      if (var3 < 0.0F) {
         var3 = -var3;
         var1 -= var3;
      }

    float var9 = IsoUtils.XToScreenExact(var0, var1, var4, 0);
    float var10 = IsoUtils.YToScreenExact(var0, var1, var4, 0);
    float var11 = IsoUtils.XToScreenExact(var0 + var2, var1, var4, 0);
    float var12 = IsoUtils.YToScreenExact(var0 + var2, var1, var4, 0);
    float var13 = IsoUtils.XToScreenExact(var0 + var2, var1 + var3, var4, 0);
    float var14 = IsoUtils.YToScreenExact(var0 + var2, var1 + var3, var4, 0);
    float var15 = IsoUtils.XToScreenExact(var0, var1 + var3, var4, 0);
    float var16 = IsoUtils.YToScreenExact(var0, var1 + var3, var4, 0);
    float var17 = -var5 * Core.TileScale;
      var10 += var17;
      var12 += var17;
      var14 += var17;
      var16 += var17;
      drawLine(var9, var10, var11, var12, var6, var7, var8);
      drawLine(var11, var12, var13, var14, var6, var7, var8);
      drawLine(var13, var14, var15, var16, var6, var7, var8);
      drawLine(var15, var16, var9, var10, var6, var7, var8);
   }

    static void DrawIsoRectRotated(float var0, float var1, float var2, float var3, float var4, float var5, float var6, float var7, float var8, float var9) {
    Vector2 var10 = tempo.setLengthAndDirection(var5, 1.0F);
    Vector2 var11 = tempo2.set(var10);
      var11.tangent();
      var10.x *= var4 / 2.0F;
      var10.y *= var4 / 2.0F;
      var11.x *= var3 / 2.0F;
      var11.y *= var3 / 2.0F;
    float var12 = var0 + var10.x;
    float var13 = var1 + var10.y;
    float var14 = var0 - var10.x;
    float var15 = var1 - var10.y;
    float var16 = var12 - var11.x;
    float var17 = var13 - var11.y;
    float var18 = var12 + var11.x;
    float var19 = var13 + var11.y;
    float var20 = var14 - var11.x;
    float var21 = var15 - var11.y;
    float var22 = var14 + var11.x;
    float var23 = var15 + var11.y;
    uint8_t var24 = 1;
      DrawIsoLine(var16, var17, var2, var18, var19, var2, var6, var7, var8, var9, var24);
      DrawIsoLine(var16, var17, var2, var20, var21, var2, var6, var7, var8, var9, var24);
      DrawIsoLine(var18, var19, var2, var22, var23, var2, var6, var7, var8, var9, var24);
      DrawIsoLine(var20, var21, var2, var22, var23, var2, var6, var7, var8, var9, var24);
   }

   public static void DrawIsoLine(
      float var0, float var1, float var2, float var3, float var4, float var5, float var6, float var7, float var8, float var9, int var10
   ) {
    float var11 = IsoUtils.XToScreenExact(var0, var1, var2, 0);
    float var12 = IsoUtils.YToScreenExact(var0, var1, var2, 0);
    float var13 = IsoUtils.XToScreenExact(var3, var4, var5, 0);
    float var14 = IsoUtils.YToScreenExact(var3, var4, var5, 0);
      drawLine(var11, var12, var13, var14, var6, var7, var8, var9, var10);
   }

   public static void DrawIsoTransform(
      float var0, float var1, float var2, float var3, float var4, float var5, int var6, float var7, float var8, float var9, float var10, int var11
   ) {
      DrawIsoCircle(var0, var1, var2, var5, var6, var7, var8, var9, var10);
      DrawIsoLine(var0, var1, var2, var0 + var3 + var5 / 2.0F, var1 + var4 + var5 / 2.0F, var2, var7, var8, var9, var10, var11);
   }

    static void DrawIsoCircle(float var0, float var1, float var2, float var3, float var4, float var5, float var6, float var7) {
    uint8_t var8 = 16;
      DrawIsoCircle(var0, var1, var2, var3, var8, var4, var5, var6, var7);
   }

    static void DrawIsoCircle(float var0, float var1, float var2, float var3, int var4, float var5, float var6, float var7, float var8) {
    double var9 = var0 + var3 * Math.cos(Math.toRadians(0.0F / var4));
    double var11 = var1 + var3 * Math.sin(Math.toRadians(0.0F / var4));

      for (int var13 = 1; var13 <= var4; var13++) {
    double var14 = var0 + var3 * Math.cos(Math.toRadians(var13 * 360.0F / var4));
    double var16 = var1 + var3 * Math.sin(Math.toRadians(var13 * 360.0F / var4));
         addLine((float)var9, (float)var11, var2, (float)var14, (float)var16, var2, var5, var6, var7, var8);
         var9 = var14;
         var11 = var16;
      }
   }

    static void drawLine(float var0, float var1, float var2, float var3, float var4, float var5, float var6) {
      SpriteRenderer.instance.renderline(nullptr, (int)var0, (int)var1, (int)var2, (int)var3, var4, var5, var6, 1.0F);
   }

    static void drawLine(float var0, float var1, float var2, float var3, float var4, float var5, float var6, float var7, int var8) {
      SpriteRenderer.instance.renderline(nullptr, (int)var0, (int)var1, (int)var2, (int)var3, var4, var5, var6, var7);
   }

    static void drawRect(float var0, float var1, float var2, float var3, float var4, float var5, float var6, float var7, int var8) {
      SpriteRenderer.instance.render(nullptr, var0, var1 + var8, var8, var3 - var8 * 2, var4, var5, var6, var7, nullptr);
      SpriteRenderer.instance.render(nullptr, var0, var1, var2, var8, var4, var5, var6, var7, nullptr);
      SpriteRenderer.instance.render(nullptr, var0 + var2 - var8, var1 + var8, 1.0F, var3 - var8 * 2, var4, var5, var6, var7, nullptr);
      SpriteRenderer.instance.render(nullptr, var0, var1 + var3 - var8, var2, var8, var4, var5, var6, var7, nullptr);
   }

    static void drawArc(float var0, float var1, float var2, float var3, float var4, float var5, int var6, float var7, float var8, float var9, float var10) {
    float var11 = var4 + (float)Math.acos(var5);
    float var12 = var4 - (float)Math.acos(var5);
    float var13 = var0 + (float)Math.cos(var11) * var3;
    float var14 = var1 + (float)Math.sin(var11) * var3;

      for (int var15 = 1; var15 <= var6; var15++) {
    float var16 = var11 + (var12 - var11) * var15 / var6;
    float var17 = var0 + (float)Math.cos(var16) * var3;
    float var18 = var1 + (float)Math.sin(var16) * var3;
         DrawIsoLine(var13, var14, var2, var17, var18, var2, var7, var8, var9, var10, 1);
         var13 = var17;
         var14 = var18;
      }
   }

    static void drawCircle(float var0, float var1, float var2, int var3, float var4, float var5, float var6) {
    double var7 = var0 + var2 * Math.cos(Math.toRadians(0.0F / var3));
    double var9 = var1 + var2 * Math.sin(Math.toRadians(0.0F / var3));

      for (int var11 = 1; var11 <= var3; var11++) {
    double var12 = var0 + var2 * Math.cos(Math.toRadians(var11 * 360.0F / var3));
    double var14 = var1 + var2 * Math.sin(Math.toRadians(var11 * 360.0F / var3));
         drawLine((float)var7, (float)var9, (float)var12, (float)var14, var4, var5, var6, 1.0F, 1);
         var7 = var12;
         var9 = var14;
      }
   }

    static void drawDirectionLine(float var0, float var1, float var2, float var3, float var4, float var5, float var6, float var7, float var8, int var9) {
    float var10 = var0 + (float)Math.cos(var4) * var3;
    float var11 = var1 + (float)Math.sin(var4) * var3;
      DrawIsoLine(var0, var1, var2, var10, var11, var2, var5, var6, var7, var8, var9);
   }

   public static void drawDotLines(
      float var0, float var1, float var2, float var3, float var4, float var5, float var6, float var7, float var8, float var9, int var10
   ) {
      drawDirectionLine(var0, var1, var2, var3, var4 + (float)Math.acos(var5), var6, var7, var8, var9, var10);
      drawDirectionLine(var0, var1, var2, var3, var4 - (float)Math.acos(var5), var6, var7, var8, var9, var10);
   }

    static void addLine(float var0, float var1, float var2, float var3, float var4, float var5, float var6, float var7, float var8, float var9) {
    DrawableLine var10 = pool.empty() ? std::make_shared<DrawableLine>() : pool.pop();
      lines.push_back(var10.init(var0, var1, var2, var3, var4, var5, var6, var7, var8, var9));
   }

    static void addLine(float var0, float var1, float var2, float var3, float var4, float var5, int var6, int var7, int var8, const std::string& var9) {
      addLine(var0, var1, var2, var3, var4, var5, var6, var7, var8, var9, true);
   }

   public static void addLine(
      float var0, float var1, float var2, float var3, float var4, float var5, float var6, float var7, float var8, std::string var9, boolean var10
   ) {
    DrawableLine var11 = pool.empty() ? std::make_shared<DrawableLine>() : pool.pop();
      lines.push_back(var11.init(var0, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10));
   }

    static void addRect(float var0, float var1, float var2, float var3, float var4, float var5, float var6, float var7) {
    DrawableLine var8 = pool.empty() ? std::make_shared<DrawableLine>() : pool.pop();
      lines.push_back(var8.init(var0, var1, var2, var0 + var3, var1 + var4, var2, var5, var6, var7, nullptr, false));
   }

    static void addRectYOffset(float var0, float var1, float var2, float var3, float var4, int var5, float var6, float var7, float var8) {
    DrawableLine var9 = pool.empty() ? std::make_shared<DrawableLine>() : pool.pop();
      lines.push_back(var9.init(var0, var1, var2, var0 + var3, var1 + var4, var2, var6, var7, var8, nullptr, false));
      var9.yPixelOffset = var5;
   }

    static void clear() {
      if (!lines.empty()) {
         for (int var0 = 0; var0 < lines.size(); var0++) {
            pool.push(lines.get(var0));
         }

         lines.clear();
      }
   }

    void removeLine(const std::string& var1) {
      for (int var2 = 0; var2 < lines.size(); var2++) {
         if (lines.get(var2).name == var1)) {
            lines.remove(lines.get(var2));
            var2--;
         }
      }
   }

    static void render() {
      for (int var0 = 0; var0 < lines.size(); var0++) {
    DrawableLine var1 = lines.get(var0);
         if (!var1.bLine) {
            DrawIsoRect(
               var1.xstart, var1.ystart, var1.xend - var1.xstart, var1.yend - var1.ystart, (int)var1.zstart, var1.yPixelOffset, var1.red, var1.green, var1.blue
            );
         } else {
            DrawIsoLine(var1.xstart, var1.ystart, var1.zstart, var1.xend, var1.yend, var1.zend, var1.red, var1.green, var1.blue, var1.alpha, 1);
         }
      }
   }

    static void drawLines() {
      clear();
   }
}
} // namespace debug
} // namespace zombie
