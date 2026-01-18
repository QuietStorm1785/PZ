#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameTime.h"

namespace zombie {
namespace characters {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


/**
 * TurboTuTone.
 */
class HaloTextHelper {
public:
 public static HaloTextHelper.ColorRGB COLOR_WHITE = new HaloTextHelper.ColorRGB(255, 255, 255);
 public static HaloTextHelper.ColorRGB COLOR_GREEN = new HaloTextHelper.ColorRGB(137, 232, 148);
 public static HaloTextHelper.ColorRGB COLOR_RED = new HaloTextHelper.ColorRGB(255, 105, 97);
 private static String[] queuedLines = new String[4];
 private static String[] currentLines = new String[4];
 static bool ignoreOverheadCheckOnce = false;

 public static HaloTextHelper.ColorRGB getColorWhite() {
 return COLOR_WHITE;
 }

 public static HaloTextHelper.ColorRGB getColorGreen() {
 return COLOR_GREEN;
 }

 public static HaloTextHelper.ColorRGB getColorRed() {
 return COLOR_RED;
 }

 static void forceNextAddText() {
 ignoreOverheadCheckOnce = true;
 }

 static void addTextWithArrow(IsoPlayer player, const std::string& text, bool arrowIsUp, HaloTextHelper.ColorRGB color) {
 addTextWithArrow(player, text, arrowIsUp, color.r, color.g, color.b, color.r, color.g, color.b);
 }

 static void addTextWithArrow(IsoPlayer player, const std::string& text, bool arrowIsUp, int r, int g, int b) {
 addTextWithArrow(player, text, arrowIsUp, r, g, b, r, g, b);
 }

 static void addTextWithArrow(IsoPlayer player, const std::string& text, bool arrowIsUp, HaloTextHelper.ColorRGB color, HaloTextHelper.ColorRGB arrowColor) {
 addTextWithArrow(player, text, arrowIsUp, color.r, color.g, color.b, arrowColor.r, arrowColor.g, arrowColor.b);
 }

 static void addTextWithArrow(IsoPlayer player, const std::string& text, bool arrowIsUp, int r, int g, int b, int aR, int aG, int aB) {
 addText(
 player,
 "[col="
 + r
 + ","
 + g
 + ","
 + b
 + "]"
 + text
 + "[/] [img=media/ui/"
 + (arrowIsUp ? "ArrowUp.png" : "ArrowDown.png")
 + ","
 + aR
 + ","
 + aG
 + ","
 + aB
 + "]"
 );
 }

 static void addText(IsoPlayer player, const std::string& text, HaloTextHelper.ColorRGB color) {
 addText(player, text, color.r, color.g, color.b);
 }

 static void addText(IsoPlayer player, const std::string& text, int r, int g, int b) {
 addText(player, "[col=" + r + "," + g + "," + b + "]" + text + "[/]");
 }

 static void addText(IsoPlayer player, const std::string& text) {
 int int0 = player.getPlayerNum();
 if (!overheadContains(int0, text) {
 std::string string = queuedLines[int0];
 if (string == nullptr) {
 string = text;
 } else {
 if (string.contains(text) {
 return;
 }

 string = string + "[col=175,175,175], [/]" + text;
 }

 queuedLines[int0] = string;
 }
 }

 static bool overheadContains(int int0, const std::string& string) {
 if (ignoreOverheadCheckOnce) {
 ignoreOverheadCheckOnce = false;
 return false;
 } else {
 return currentLines[int0] != nullptr && currentLines[int0].contains(string);
 }
 }

 static void update() {
 for (int int0 = 0; int0 < 4; int0++) {
 IsoPlayer player = IsoPlayer.players[int0];
 if (player != nullptr) {
 if (currentLines[int0] != nullptr && player.getHaloTimerCount() <= 0.2F * GameTime.getInstance().getMultiplier()) {
 currentLines[int0] = nullptr;
 }

 if (queuedLines[int0] != nullptr && player.getHaloTimerCount() <= 0.2F * GameTime.getInstance().getMultiplier()) {
 player.setHaloNote(queuedLines[int0]);
 currentLines[int0] = queuedLines[int0];
 queuedLines[int0] = nullptr;
 }
 } else {
 if (queuedLines[int0] != nullptr) {
 queuedLines[int0] = nullptr;
 }

 if (currentLines[int0] != nullptr) {
 currentLines[int0] = nullptr;
 }
 }
 }
 }

 public static class ColorRGB {
 int r;
 int g;
 int b;
 int a = 255;

 public ColorRGB(int _r, int _g, int _b) {
 this->r = _r;
 this->g = _g;
 this->b = _b;
 }
 }
}
} // namespace characters
} // namespace zombie
