#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/ZomboidFileSystem.h"
#include "zombie/core/Core.h"
#include "zombie/core/Translator.h"
#include "zombie/core/fonts/AngelCodeFont.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/ServerGUI.h"
#include "zombie/ui/TextManager/DeferedTextDraw.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace zombie {
namespace ui {


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
   public const AngelCodeFont[] normal = new AngelCodeFont[14];
    AngelCodeFont zombienew3;
   public const AngelCodeFont[] enumToFont = new AngelCodeFont[UIFont.values().length];
    static const TextManager instance = std::make_shared<TextManager>();
   public std::vector<DeferedTextDraw> todoTextList = std::make_unique<std::vector<>>();

    void DrawString(double var1, double var3, const std::string& var5) {
      this.font.drawString((float)var1, (float)var3, var5, 1.0F, 1.0F, 1.0F, 1.0F);
   }

    void DrawString(double var1, double var3, const std::string& var5, double var6, double var8, double var10, double var12) {
      this.font.drawString((float)var1, (float)var3, var5, (float)var6, (float)var8, (float)var10, (float)var12);
   }

    void DrawString(UIFont var1, double var2, double var4, double var6, const std::string& var8, double var9, double var11, double var13, double var15) {
    AngelCodeFont var17 = this.getFontFromEnum(var1);
      var17.drawString((float)var2, (float)var4, (float)var6, var8, (float)var9, (float)var11, (float)var13, (float)var15);
   }

    void DrawString(UIFont var1, double var2, double var4, const std::string& var6, double var7, double var9, double var11, double var13) {
    AngelCodeFont var15 = this.getFontFromEnum(var1);
      var15.drawString((float)var2, (float)var4, var6, (float)var7, (float)var9, (float)var11, (float)var13);
   }

    void DrawStringUntrimmed(UIFont var1, double var2, double var4, const std::string& var6, double var7, double var9, double var11, double var13) {
    AngelCodeFont var15 = this.getFontFromEnum(var1);
      var15.drawString((float)var2, (float)var4, var6, (float)var7, (float)var9, (float)var11, (float)var13);
   }

    void DrawStringCentre(double var1, double var3, const std::string& var5, double var6, double var8, double var10, double var12) {
      var1 -= this.font.getWidth(var5) / 2;
      this.font.drawString((float)var1, (float)var3, var5, (float)var6, (float)var8, (float)var10, (float)var12);
   }

    void DrawStringCentre(UIFont var1, double var2, double var4, const std::string& var6, double var7, double var9, double var11, double var13) {
    AngelCodeFont var15 = this.getFontFromEnum(var1);
      var2 -= var15.getWidth(var6) / 2;
      var15.drawString((float)var2, (float)var4, var6, (float)var7, (float)var9, (float)var11, (float)var13);
   }

    void DrawStringCentreDefered(UIFont var1, double var2, double var4, const std::string& var6, double var7, double var9, double var11, double var13) {
      this.todoTextList.push_back(std::make_shared<DeferedTextDraw>(var1, var2, var4, var6, var7, var9, var11, var13));
   }

    void DrawTextFromGameWorld() {
      for (int var1 = 0; var1 < this.todoTextList.size(); var1++) {
    DeferedTextDraw var2 = this.todoTextList.get(var1);
         this.DrawStringCentre(var2.font, var2.x, var2.y, var2.str, var2.r, var2.g, var2.b, var2.a);
      }

      this.todoTextList.clear();
   }

    void DrawStringRight(double var1, double var3, const std::string& var5, double var6, double var8, double var10, double var12) {
      var1 -= this.font.getWidth(var5);
      this.font.drawString((float)var1, (float)var3, var5, (float)var6, (float)var8, (float)var10, (float)var12);
   }

    TextDrawObject GetDrawTextObject(const std::string& var1, int var2, bool var3) {
      return std::make_unique<TextDrawObject>();
   }

    void DrawTextObject(double var1, double var3, TextDrawObject var5) {
   }

    void DrawStringBBcode(UIFont var1, double var2, double var4, const std::string& var6, double var7, double var9, double var11, double var13) {
   }

    AngelCodeFont getNormalFromFontSize(int var1) {
      return this.normal[var1 - 11];
   }

    AngelCodeFont getFontFromEnum(UIFont var1) {
      if (var1 == nullptr) {
         return this.font;
      } else {
    AngelCodeFont var2 = this.enumToFont[var1.ordinal()];
    return var2 = = nullptr ? this.font : var2;
      }
   }

    int getFontHeight(UIFont var1) {
    AngelCodeFont var2 = this.getFontFromEnum(var1);
      return var2.getLineHeight();
   }

    void DrawStringRight(UIFont var1, double var2, double var4, const std::string& var6, double var7, double var9, double var11, double var13) {
    AngelCodeFont var15 = this.getFontFromEnum(var1);
      var2 -= var15.getWidth(var6);
      var15.drawString((float)var2, (float)var4, var6, (float)var7, (float)var9, (float)var11, (float)var13);
   }

    std::string getFontFilePath(const std::string& var1, const std::string& var2, const std::string& var3) {
      if (var2 != nullptr) {
    std::string var4 = "media/fonts/" + var1 + "/" + var2 + "/" + var3;
         if (ZomboidFileSystem.instance.getString(var4) != var4) {
    return var4;
         }
      }

    std::string var5 = "media/fonts/" + var1 + "/" + var3;
      if (ZomboidFileSystem.instance.getString(var5) != var5) {
    return var5;
      } else {
         if (!"EN" == var1)) {
            if (var2 != nullptr) {
               var5 = "media/fonts/EN/" + var2 + "/" + var3;
               if (ZomboidFileSystem.instance.getString(var5) != var5) {
    return var5;
               }
            }

            var5 = "media/fonts/EN/" + var3;
            if (ZomboidFileSystem.instance.getString(var5) != var5) {
    return var5;
            }
         }

         var5 = "media/fonts/" + var3;
         return ZomboidFileSystem.instance.getString(var5) != var5 ? var5 : "media/" + var3;
      }
   }

    void Init() {
    std::string var1 = ZomboidFileSystem.instance.getString("media/fonts/EN/fonts.txt");
    FontsFile var2 = std::make_shared<FontsFile>();
    std::unordered_map var3 = new std::unordered_map();
      var2.read(var1, var3);
    std::string var4 = Translator.getLanguage().name();
      if (!"EN" == var4)) {
         var1 = ZomboidFileSystem.instance.getString("media/fonts/" + var4 + "/fonts.txt");
         var2.read(var1, var3);
      }

    std::unordered_map var5 = new std::unordered_map();
    std::string var6 = nullptr;
      if (Core.OptionFontSize == 2) {
         var6 = "1x";
      } else if (Core.OptionFontSize == 3) {
         var6 = "2x";
      } else if (Core.OptionFontSize == 4) {
         var6 = "3x";
      } else if (Core.OptionFontSize == 5) {
         var6 = "4x";
      }

      for (AngelCodeFont var10 : this.enumToFont) {
         if (var10 != nullptr) {
            var10.destroy();
         }
      }

      Arrays.fill(this.enumToFont, nullptr);

      for (AngelCodeFont var30 : this.normal) {
         if (var30 != nullptr) {
            var30.destroy();
         }
      }

      Arrays.fill(this.normal, nullptr);

      for (UIFont var31 : UIFont.values()) {
    FontsFileFont var11 = (FontsFileFont)var3.get(var31.name());
         if (var11 == nullptr) {
            DebugLog.General.warn("font \"%s\" not found in fonts.txt", new Object[]{var31.name()});
         } else {
    std::string var12 = this.getFontFilePath(var4, var6, var11.fnt);
    std::string var13 = nullptr;
            if (var11.img != nullptr) {
               var13 = this.getFontFilePath(var4, var6, var11.img);
            }

    std::string var14 = var12 + "|" + var13;
            if (var5.get(var14) != nullptr) {
               this.enumToFont[var31.ordinal()] = (AngelCodeFont)var5.get(var14);
            } else {
    AngelCodeFont var15 = std::make_shared<AngelCodeFont>(var12, var13);
               this.enumToFont[var31.ordinal()] = var15;
               var5.put(var14, var15);
            }
         }
      }

      try {
         ZomboidFileSystem.instance.IgnoreActiveFileMap.set(true);
    std::string var22 = std::make_shared<File>("").getAbsolutePath().replaceAll("\\\\", "/");
    std::string var26 = var22 + "/media/fonts/zomboidSmall.fnt";
    std::string var29 = var22 + "/media/fonts/zomboidSmall_0.png";
         if (var26.startsWith("/")) {
            var26 = "/" + var26;
         }

         this.enumToFont[UIFont.DebugConsole.ordinal()] = std::make_shared<AngelCodeFont>(var26, var29);
      } finally {
         ZomboidFileSystem.instance.IgnoreActiveFileMap.set(false);
      }

      for (int var23 = 0; var23 < this.normal.length; var23++) {
         this.normal[var23] = std::make_shared<AngelCodeFont>("media/fonts/zomboidNormal" + (var23 + 11) + ".fnt", "media/fonts/zomboidNormal" + (var23 + 11) + "_0");
      }

      this.font = this.enumToFont[UIFont.Small.ordinal()];
      this.font2 = this.enumToFont[UIFont.Medium.ordinal()];
      this.font3 = this.enumToFont[UIFont.Large.ordinal()];
      this.font4 = this.enumToFont[UIFont.Massive.ordinal()];
      this.main1 = this.enumToFont[UIFont.MainMenu1.ordinal()];
      this.main2 = this.enumToFont[UIFont.MainMenu2.ordinal()];
      this.zombiefontcredits1 = this.enumToFont[UIFont.Cred1.ordinal()];
      this.zombiefontcredits2 = this.enumToFont[UIFont.Cred2.ordinal()];
      this.zombienew1 = this.enumToFont[UIFont.NewSmall.ordinal()];
      this.zombienew2 = this.enumToFont[UIFont.NewMedium.ordinal()];
      this.zombienew3 = this.enumToFont[UIFont.NewLarge.ordinal()];
      this.codetext = this.enumToFont[UIFont.Code.ordinal()];
      this.enumToFont[UIFont.MediumNew.ordinal()] = nullptr;
      this.enumToFont[UIFont.AutoNormSmall.ordinal()] = nullptr;
      this.enumToFont[UIFont.AutoNormMedium.ordinal()] = nullptr;
      this.enumToFont[UIFont.AutoNormLarge.ordinal()] = nullptr;
      this.zomboidDialogue = this.enumToFont[UIFont.Dialogue.ordinal()];
      this.intro = this.enumToFont[UIFont.Intro.ordinal()];
      this.handwritten = this.enumToFont[UIFont.Handwritten.ordinal()];
      this.debugConsole = this.enumToFont[UIFont.DebugConsole.ordinal()];
   }

    int MeasureStringX(UIFont var1, const std::string& var2) {
      if (GameServer.bServer && !ServerGUI.isCreated()) {
    return 0;
      } else if (var2 == nullptr) {
    return 0;
      } else {
    AngelCodeFont var3 = this.getFontFromEnum(var1);
         return var3.getWidth(var2);
      }
   }

    int MeasureStringY(UIFont var1, const std::string& var2) {
      if (var1 == nullptr || var2 == nullptr) {
    return 0;
      } else if (GameServer.bServer && !ServerGUI.isCreated()) {
    return 0;
      } else {
    AngelCodeFont var3 = this.getFontFromEnum(var1);
         return var3.getHeight(var2);
      }
   }

    int MeasureFont(UIFont var1) {
      if (var1 == UIFont.Small) {
    return 10;
      } else if (var1 == UIFont.Dialogue) {
    return 20;
      } else if (var1 == UIFont.Medium) {
    return 20;
      } else if (var1 == UIFont.Large) {
    return 24;
      } else if (var1 == UIFont.Massive) {
    return 30;
      } else if (var1 == UIFont.MainMenu1) {
    return 30;
      } else {
    return var1 = = UIFont.MainMenu2 ? 30 : this.getFontFromEnum(var1).getLineHeight();
      }
   }
}
} // namespace ui
} // namespace zombie
