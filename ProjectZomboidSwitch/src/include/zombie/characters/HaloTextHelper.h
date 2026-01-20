#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameTime.h"
#include "zombie/characters/HaloTextHelper/ColorRGB.h"

namespace zombie {
namespace characters {


class HaloTextHelper {
public:
    static const ColorRGB COLOR_WHITE = std::make_shared<ColorRGB>(255, 255, 255);
    static const ColorRGB COLOR_GREEN = std::make_shared<ColorRGB>(137, 232, 148);
    static const ColorRGB COLOR_RED = std::make_shared<ColorRGB>(255, 105, 97);
   private static std::string[] queuedLines = new std::string[4];
   private static std::string[] currentLines = new std::string[4];
    static bool ignoreOverheadCheckOnce = false;

    static ColorRGB getColorWhite() {
    return COLOR_WHITE;
   }

    static ColorRGB getColorGreen() {
    return COLOR_GREEN;
   }

    static ColorRGB getColorRed() {
    return COLOR_RED;
   }

    static void forceNextAddText() {
      ignoreOverheadCheckOnce = true;
   }

    static void addTextWithArrow(IsoPlayer var0, const std::string& var1, bool var2, ColorRGB var3) {
      addTextWithArrow(var0, var1, var2, var3.r, var3.g, var3.b, var3.r, var3.g, var3.b);
   }

    static void addTextWithArrow(IsoPlayer var0, const std::string& var1, bool var2, int var3, int var4, int var5) {
      addTextWithArrow(var0, var1, var2, var3, var4, var5, var3, var4, var5);
   }

    static void addTextWithArrow(IsoPlayer var0, const std::string& var1, bool var2, ColorRGB var3, ColorRGB var4) {
      addTextWithArrow(var0, var1, var2, var3.r, var3.g, var3.b, var4.r, var4.g, var4.b);
   }

    static void addTextWithArrow(IsoPlayer var0, const std::string& var1, bool var2, int var3, int var4, int var5, int var6, int var7, int var8) {
      addText(
         var0,
         "[col="
            + var3
            + ","
            + var4
            + ","
            + var5
            + "]"
            + var1
            + "[/] [img=media/ui/"
            + (var2 ? "ArrowUp.png" : "ArrowDown.png")
            + ","
            + var6
            + ","
            + var7
            + ","
            + var8
            + "]"
      );
   }

    static void addText(IsoPlayer var0, const std::string& var1, ColorRGB var2) {
      addText(var0, var1, var2.r, var2.g, var2.b);
   }

    static void addText(IsoPlayer var0, const std::string& var1, int var2, int var3, int var4) {
      addText(var0, "[col=" + var2 + "," + var3 + "," + var4 + "]" + var1 + "[/]");
   }

    static void addText(IsoPlayer var0, const std::string& var1) {
    int var2 = var0.getPlayerNum();
      if (!overheadContains(var2, var1)) {
    std::string var3 = queuedLines[var2];
         if (var3 == nullptr) {
            var3 = var1;
         } else {
            if (var3.contains(var1)) {
               return;
            }

            var3 = var3 + "[col=175,175,175], [/]" + var1;
         }

         queuedLines[var2] = var3;
      }
   }

    static bool overheadContains(int var0, const std::string& var1) {
      if (ignoreOverheadCheckOnce) {
         ignoreOverheadCheckOnce = false;
    return false;
      } else {
         return currentLines[var0] != nullptr && currentLines[var0].contains(var1);
      }
   }

    static void update() {
      for (int var0 = 0; var0 < 4; var0++) {
    IsoPlayer var1 = IsoPlayer.players[var0];
         if (var1 != nullptr) {
            if (currentLines[var0] != nullptr && var1.getHaloTimerCount() <= 0.2F * GameTime.getInstance().getMultiplier()) {
               currentLines[var0] = nullptr;
            }

            if (queuedLines[var0] != nullptr && var1.getHaloTimerCount() <= 0.2F * GameTime.getInstance().getMultiplier()) {
               var1.setHaloNote(queuedLines[var0]);
               currentLines[var0] = queuedLines[var0];
               queuedLines[var0] = nullptr;
            }
         } else {
            if (queuedLines[var0] != nullptr) {
               queuedLines[var0] = nullptr;
            }

            if (currentLines[var0] != nullptr) {
               currentLines[var0] = nullptr;
            }
         }
      }
   }
}
} // namespace characters
} // namespace zombie
