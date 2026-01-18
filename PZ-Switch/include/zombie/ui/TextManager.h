#pragma once
#include "zombie/ZomboidFileSystem.h"
#include "zombie/core/Core.h"
#include "zombie/core/Translator.h"
#include "zombie/core/fonts/AngelCodeFont.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/ServerGUI.h"
#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace ui {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class TextManager {
public:
 AngelCodeFont font;
 AngelCodeFont font2;
 AngelCodeFont font3;
 AngelCodeFont font4;
 AngelCodeFont main1;
 AngelCodeFont main2;
 AngelCodeFont zombiefontcredits1;
 AngelCodeFont zombiefontcredits2;
 AngelCodeFont zombienew1;
 AngelCodeFont zombienew2;
 AngelCodeFont zomboidDialogue;
 AngelCodeFont codetext;
 AngelCodeFont debugConsole;
 AngelCodeFont intro;
 AngelCodeFont handwritten;
public
 AngelCodeFont[] normal = new AngelCodeFont[14];
 AngelCodeFont zombienew3;
public
 AngelCodeFont[] enumToFont = new AngelCodeFont[UIFont.values().length];
 static const TextManager instance = new TextManager();
public
 ArrayList<TextManager.DeferedTextDraw> todoTextList =
 std::make_unique<ArrayList<>>();

 void DrawString(double x, double y, const std::string &str) {
 this->font.drawString((float)x, (float)y, str, 1.0F, 1.0F, 1.0F, 1.0F);
 }

 void DrawString(double x, double y, const std::string &str, double r,
 double g, double b, double a) {
 this->font.drawString((float)x, (float)y, str, (float)r, (float)g, (float)b,
 (float)a);
 }

 void DrawString(UIFont _font, double x, double y, double zoom,
 const std::string &str, double r, double g, double b,
 double a) {
 AngelCodeFont angelCodeFont = this->getFontFromEnum(_font);
 angelCodeFont.drawString((float)x, (float)y, (float)zoom, str, (float)r,
 (float)g, (float)b, (float)a);
 }

 void DrawString(UIFont _font, double x, double y, const std::string &str,
 double r, double g, double b, double a) {
 AngelCodeFont angelCodeFont = this->getFontFromEnum(_font);
 angelCodeFont.drawString((float)x, (float)y, str, (float)r, (float)g,
 (float)b, (float)a);
 }

 void DrawStringUntrimmed(UIFont _font, double x, double y,
 const std::string &str, double r, double g, double b,
 double a) {
 AngelCodeFont angelCodeFont = this->getFontFromEnum(_font);
 angelCodeFont.drawString((float)x, (float)y, str, (float)r, (float)g,
 (float)b, (float)a);
 }

 void DrawStringCentre(double x, double y, const std::string &str, double r,
 double g, double b, double a) {
 x -= this->font.getWidth(str) / 2;
 this->font.drawString((float)x, (float)y, str, (float)r, (float)g, (float)b,
 (float)a);
 }

 void DrawStringCentre(UIFont _font, double x, double y,
 const std::string &str, double r, double g, double b,
 double a) {
 AngelCodeFont angelCodeFont = this->getFontFromEnum(_font);
 x -= angelCodeFont.getWidth(str) / 2;
 angelCodeFont.drawString((float)x, (float)y, str, (float)r, (float)g,
 (float)b, (float)a);
 }

 void DrawStringCentreDefered(UIFont _font, double x, double y,
 const std::string &str, double r, double g,
 double b, double a) {
 this->todoTextList.add(
 new TextManager.DeferedTextDraw(_font, x, y, str, r, g, b, a);
 }

 void DrawTextFromGameWorld() {
 for (int int0 = 0; int0 < this->todoTextList.size(); int0++) {
 TextManager.DeferedTextDraw deferedTextDraw = this->todoTextList.get(int0);
 this->DrawStringCentre(deferedTextDraw.font, deferedTextDraw.x,
 deferedTextDraw.y, deferedTextDraw.str,
 deferedTextDraw.r, deferedTextDraw.g,
 deferedTextDraw.b, deferedTextDraw.a);
 }

 this->todoTextList.clear();
 }

 void DrawStringRight(double x, double y, const std::string &str, double r,
 double g, double b, double a) {
 x -= this->font.getWidth(str);
 this->font.drawString((float)x, (float)y, str, (float)r, (float)g, (float)b,
 (float)a);
 }

 TextDrawObject GetDrawTextObject(const std::string &str, int maxLineWidth,
 bool restrictImages) {
 return std::make_unique<TextDrawObject>();
 }

 void DrawTextObject(double x, double y, TextDrawObject td) {}

 void DrawStringBBcode(UIFont _font, double x, double y,
 const std::string &str, double r, double g, double b,
 double a) {}

 AngelCodeFont getNormalFromFontSize(int points) {
 return this->normal[points - 11];
 }

 AngelCodeFont getFontFromEnum(UIFont _font) {
 if (_font.empty()) {
 return this->font;
 } else {
 AngelCodeFont angelCodeFont = this->enumToFont[_font.ordinal()];
 return angelCodeFont = = nullptr ? this->font : angelCodeFont;
 }
 }

 int getFontHeight(UIFont fontID) {
 AngelCodeFont angelCodeFont = this->getFontFromEnum(fontID);
 return angelCodeFont.getLineHeight();
 }

 void DrawStringRight(UIFont _font, double x, double y, const std::string &str,
 double r, double g, double b, double a) {
 AngelCodeFont angelCodeFont = this->getFontFromEnum(_font);
 x -= angelCodeFont.getWidth(str);
 angelCodeFont.drawString((float)x, (float)y, str, (float)r, (float)g,
 (float)b, (float)a);
 }

 std::string getFontFilePath(const std::string &string3,
 const std::string &string0,
 const std::string &string2) {
 if (string0 != nullptr) {
 std::string string1 =
 "media/fonts/" + string3 + "/" + string0 + "/" + string2;
 if (ZomboidFileSystem.instance.getString(string1) != string1) {
 return string1;
 }
 }

 std::string string4 = "media/fonts/" + string3 + "/" + string2;
 if (ZomboidFileSystem.instance.getString(string4) != string4) {
 return string4;
 } else {
 if (!"EN" == string3) {
 if (string0 != nullptr) {
 string4 = "media/fonts/EN/" + string0 + "/" + string2;
 if (ZomboidFileSystem.instance.getString(string4) != string4) {
 return string4;
 }
 }

 string4 = "media/fonts/EN/" + string2;
 if (ZomboidFileSystem.instance.getString(string4) != string4) {
 return string4;
 }
 }

 string4 = "media/fonts/" + string2;
 return ZomboidFileSystem.instance.getString(string4) != string4
 ? string4
 : "media/" + string2;
 }
 }

 void Init() {
 std::string string0 =
 ZomboidFileSystem.instance.getString("media/fonts/EN/fonts.txt");
 FontsFile fontsFile = new FontsFile();
 std::unordered_map hashMap0 = new HashMap();
 fontsFile.read(string0, hashMap0);
 std::string string1 = Translator.getLanguage().name();
 if (!"EN" == string1) {
 string0 = ZomboidFileSystem.instance.getString("media/fonts/" +
 string1 + "/fonts.txt");
 fontsFile.read(string0, hashMap0);
 }

 std::unordered_map hashMap1 = new HashMap();
 std::string string2 = nullptr;
 if (Core.OptionFontSize == 2) {
 string2 = "1x";
 } else if (Core.OptionFontSize == 3) {
 string2 = "2x";
 } else if (Core.OptionFontSize == 4) {
 string2 = "3x";
 } else if (Core.OptionFontSize == 5) {
 string2 = "4x";
 }

 for (AngelCodeFont angelCodeFont0 : this->enumToFont) {
 if (angelCodeFont0 != nullptr) {
 angelCodeFont0.destroy();
 }
 }

 Arrays.fill(this->enumToFont, nullptr);

 for (AngelCodeFont angelCodeFont1 : this->normal) {
 if (angelCodeFont1 != nullptr) {
 angelCodeFont1.destroy();
 }
 }

 Arrays.fill(this->normal, nullptr);

 for (UIFont uIFont : UIFont.values()) {
 FontsFileFont fontsFileFont = (FontsFileFont)hashMap0.get(uIFont.name());
 if (fontsFileFont.empty()) {
 DebugLog.General.warn("font \"%s\" not found in fonts.txt",
 uIFont.name());
 } else {
 std::string string3 =
 this->getFontFilePath(string1, string2, fontsFileFont.fnt);
 std::string string4 = nullptr;
 if (fontsFileFont.img != nullptr) {
 string4 = this->getFontFilePath(string1, string2, fontsFileFont.img);
 }

 std::string string5 = string3 + "|" + string4;
 if (hashMap1.get(string5) != nullptr) {
 this->enumToFont[uIFont.ordinal()] =
 (AngelCodeFont)hashMap1.get(string5);
 } else {
 AngelCodeFont angelCodeFont2 = new AngelCodeFont(string3, string4);
 this->enumToFont[uIFont.ordinal()] = angelCodeFont2;
 hashMap1.put(string5, angelCodeFont2);
 }
 }
 }

 try {
 ZomboidFileSystem.instance.IgnoreActiveFileMap.set(true);
 std::string string6 =
 new File("").getAbsolutePath().replaceAll("\\\\", "/");
 std::string string7 = string6 + "/media/fonts/zomboidSmall.fnt";
 std::string string8 = string6 + "/media/fonts/zomboidSmall_0.png";
 if (string7.startsWith("/")) {
 string7 = "/" + string7;
 }

 this->enumToFont[UIFont.DebugConsole.ordinal()] =
 new AngelCodeFont(string7, string8);
 } finally {
 ZomboidFileSystem.instance.IgnoreActiveFileMap.set(false);
 }

 for (int int0 = 0; int0 < this->normal.length; int0++) {
 this->normal[int0] =
 new AngelCodeFont("media/fonts/zomboidNormal" + (int0 + 11) + ".fnt",
 "media/fonts/zomboidNormal" + (int0 + 11) + "_0");
 }

 this->font = this->enumToFont[UIFont.Small.ordinal()];
 this->font2 = this->enumToFont[UIFont.Medium.ordinal()];
 this->font3 = this->enumToFont[UIFont.Large.ordinal()];
 this->font4 = this->enumToFont[UIFont.Massive.ordinal()];
 this->main1 = this->enumToFont[UIFont.MainMenu1.ordinal()];
 this->main2 = this->enumToFont[UIFont.MainMenu2.ordinal()];
 this->zombiefontcredits1 = this->enumToFont[UIFont.Cred1.ordinal()];
 this->zombiefontcredits2 = this->enumToFont[UIFont.Cred2.ordinal()];
 this->zombienew1 = this->enumToFont[UIFont.NewSmall.ordinal()];
 this->zombienew2 = this->enumToFont[UIFont.NewMedium.ordinal()];
 this->zombienew3 = this->enumToFont[UIFont.NewLarge.ordinal()];
 this->codetext = this->enumToFont[UIFont.Code.ordinal()];
 this->enumToFont[UIFont.MediumNew.ordinal()] = nullptr;
 this->enumToFont[UIFont.AutoNormSmall.ordinal()] = nullptr;
 this->enumToFont[UIFont.AutoNormMedium.ordinal()] = nullptr;
 this->enumToFont[UIFont.AutoNormLarge.ordinal()] = nullptr;
 this->zomboidDialogue = this->enumToFont[UIFont.Dialogue.ordinal()];
 this->intro = this->enumToFont[UIFont.Intro.ordinal()];
 this->handwritten = this->enumToFont[UIFont.Handwritten.ordinal()];
 this->debugConsole = this->enumToFont[UIFont.DebugConsole.ordinal()];
 }

 int MeasureStringX(UIFont _font, const std::string &str) {
 if (GameServer.bServer && !ServerGUI.isCreated()) {
 return 0;
 } else if (str.empty()) {
 return 0;
 } else {
 AngelCodeFont angelCodeFont = this->getFontFromEnum(_font);
 return angelCodeFont.getWidth(str);
 }
 }

 int MeasureStringY(UIFont _font, const std::string &str) {
 if (_font.empty() || str.empty()) {
 return 0;
 } else if (GameServer.bServer && !ServerGUI.isCreated()) {
 return 0;
 } else {
 AngelCodeFont angelCodeFont = this->getFontFromEnum(_font);
 return angelCodeFont.getHeight(str);
 }
 }

 int MeasureFont(UIFont _font) {
 if (_font == UIFont.Small) {
 return 10;
 } else if (_font == UIFont.Dialogue) {
 return 20;
 } else if (_font == UIFont.Medium) {
 return 20;
 } else if (_font == UIFont.Large) {
 return 24;
 } else if (_font == UIFont.Massive) {
 return 30;
 } else if (_font == UIFont.MainMenu1) {
 return 30;
 } else {
 return _font = = UIFont.MainMenu2
 ? 30
 : this->getFontFromEnum(_font).getLineHeight();
 }
 }

public
 static class DeferedTextDraw {
 double x;
 double y;
 UIFont font;
 std::string str;
 double r;
 double g;
 double b;
 double a;

 public
 DeferedTextDraw(UIFont uIFont, double double0, double double1,
 const std::string &string, double double2, double double3,
 double double4, double double5) {
 this->font = uIFont;
 this->x = double0;
 this->y = double1;
 this->str = string;
 this->r = double2;
 this->g = double3;
 this->b = double4;
 this->a = double5;
 }
 }

 public interface StringDrawer {
 void draw(UIFont var1, double var2, double var4, const std::string &var6,
 double var7, double var9, double var11, double var13);
 }
}
} // namespace ui
} // namespace zombie
