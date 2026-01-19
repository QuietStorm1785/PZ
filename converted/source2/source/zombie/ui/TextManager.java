package zombie.ui;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import zombie.ZomboidFileSystem;
import zombie.core.Core;
import zombie.core.Translator;
import zombie.core.fonts.AngelCodeFont;
import zombie.debug.DebugLog;
import zombie.network.GameServer;
import zombie.network.ServerGUI;
import zombie.ui.TextManager.DeferedTextDraw;

public final class TextManager {
   public AngelCodeFont font;
   public AngelCodeFont font2;
   public AngelCodeFont font3;
   public AngelCodeFont font4;
   public AngelCodeFont main1;
   public AngelCodeFont main2;
   public AngelCodeFont zombiefontcredits1;
   public AngelCodeFont zombiefontcredits2;
   public AngelCodeFont zombienew1;
   public AngelCodeFont zombienew2;
   public AngelCodeFont zomboidDialogue;
   public AngelCodeFont codetext;
   public AngelCodeFont debugConsole;
   public AngelCodeFont intro;
   public AngelCodeFont handwritten;
   public final AngelCodeFont[] normal = new AngelCodeFont[14];
   public AngelCodeFont zombienew3;
   public final AngelCodeFont[] enumToFont = new AngelCodeFont[UIFont.values().length];
   public static final TextManager instance = new TextManager();
   public ArrayList<DeferedTextDraw> todoTextList = new ArrayList<>();

   public void DrawString(double var1, double var3, String var5) {
      this.font.drawString((float)var1, (float)var3, var5, 1.0F, 1.0F, 1.0F, 1.0F);
   }

   public void DrawString(double var1, double var3, String var5, double var6, double var8, double var10, double var12) {
      this.font.drawString((float)var1, (float)var3, var5, (float)var6, (float)var8, (float)var10, (float)var12);
   }

   public void DrawString(UIFont var1, double var2, double var4, double var6, String var8, double var9, double var11, double var13, double var15) {
      AngelCodeFont var17 = this.getFontFromEnum(var1);
      var17.drawString((float)var2, (float)var4, (float)var6, var8, (float)var9, (float)var11, (float)var13, (float)var15);
   }

   public void DrawString(UIFont var1, double var2, double var4, String var6, double var7, double var9, double var11, double var13) {
      AngelCodeFont var15 = this.getFontFromEnum(var1);
      var15.drawString((float)var2, (float)var4, var6, (float)var7, (float)var9, (float)var11, (float)var13);
   }

   public void DrawStringUntrimmed(UIFont var1, double var2, double var4, String var6, double var7, double var9, double var11, double var13) {
      AngelCodeFont var15 = this.getFontFromEnum(var1);
      var15.drawString((float)var2, (float)var4, var6, (float)var7, (float)var9, (float)var11, (float)var13);
   }

   public void DrawStringCentre(double var1, double var3, String var5, double var6, double var8, double var10, double var12) {
      var1 -= this.font.getWidth(var5) / 2;
      this.font.drawString((float)var1, (float)var3, var5, (float)var6, (float)var8, (float)var10, (float)var12);
   }

   public void DrawStringCentre(UIFont var1, double var2, double var4, String var6, double var7, double var9, double var11, double var13) {
      AngelCodeFont var15 = this.getFontFromEnum(var1);
      var2 -= var15.getWidth(var6) / 2;
      var15.drawString((float)var2, (float)var4, var6, (float)var7, (float)var9, (float)var11, (float)var13);
   }

   public void DrawStringCentreDefered(UIFont var1, double var2, double var4, String var6, double var7, double var9, double var11, double var13) {
      this.todoTextList.add(new DeferedTextDraw(var1, var2, var4, var6, var7, var9, var11, var13));
   }

   public void DrawTextFromGameWorld() {
      for (int var1 = 0; var1 < this.todoTextList.size(); var1++) {
         DeferedTextDraw var2 = this.todoTextList.get(var1);
         this.DrawStringCentre(var2.font, var2.x, var2.y, var2.str, var2.r, var2.g, var2.b, var2.a);
      }

      this.todoTextList.clear();
   }

   public void DrawStringRight(double var1, double var3, String var5, double var6, double var8, double var10, double var12) {
      var1 -= this.font.getWidth(var5);
      this.font.drawString((float)var1, (float)var3, var5, (float)var6, (float)var8, (float)var10, (float)var12);
   }

   public TextDrawObject GetDrawTextObject(String var1, int var2, boolean var3) {
      return new TextDrawObject();
   }

   public void DrawTextObject(double var1, double var3, TextDrawObject var5) {
   }

   public void DrawStringBBcode(UIFont var1, double var2, double var4, String var6, double var7, double var9, double var11, double var13) {
   }

   public AngelCodeFont getNormalFromFontSize(int var1) {
      return this.normal[var1 - 11];
   }

   public AngelCodeFont getFontFromEnum(UIFont var1) {
      if (var1 == null) {
         return this.font;
      } else {
         AngelCodeFont var2 = this.enumToFont[var1.ordinal()];
         return var2 == null ? this.font : var2;
      }
   }

   public int getFontHeight(UIFont var1) {
      AngelCodeFont var2 = this.getFontFromEnum(var1);
      return var2.getLineHeight();
   }

   public void DrawStringRight(UIFont var1, double var2, double var4, String var6, double var7, double var9, double var11, double var13) {
      AngelCodeFont var15 = this.getFontFromEnum(var1);
      var2 -= var15.getWidth(var6);
      var15.drawString((float)var2, (float)var4, var6, (float)var7, (float)var9, (float)var11, (float)var13);
   }

   private String getFontFilePath(String var1, String var2, String var3) {
      if (var2 != null) {
         String var4 = "media/fonts/" + var1 + "/" + var2 + "/" + var3;
         if (ZomboidFileSystem.instance.getString(var4) != var4) {
            return var4;
         }
      }

      String var5 = "media/fonts/" + var1 + "/" + var3;
      if (ZomboidFileSystem.instance.getString(var5) != var5) {
         return var5;
      } else {
         if (!"EN".equals(var1)) {
            if (var2 != null) {
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

   public void Init() throws FileNotFoundException {
      String var1 = ZomboidFileSystem.instance.getString("media/fonts/EN/fonts.txt");
      FontsFile var2 = new FontsFile();
      HashMap var3 = new HashMap();
      var2.read(var1, var3);
      String var4 = Translator.getLanguage().name();
      if (!"EN".equals(var4)) {
         var1 = ZomboidFileSystem.instance.getString("media/fonts/" + var4 + "/fonts.txt");
         var2.read(var1, var3);
      }

      HashMap var5 = new HashMap();
      String var6 = null;
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
         if (var10 != null) {
            var10.destroy();
         }
      }

      Arrays.fill(this.enumToFont, null);

      for (AngelCodeFont var30 : this.normal) {
         if (var30 != null) {
            var30.destroy();
         }
      }

      Arrays.fill(this.normal, null);

      for (UIFont var31 : UIFont.values()) {
         FontsFileFont var11 = (FontsFileFont)var3.get(var31.name());
         if (var11 == null) {
            DebugLog.General.warn("font \"%s\" not found in fonts.txt", new Object[]{var31.name()});
         } else {
            String var12 = this.getFontFilePath(var4, var6, var11.fnt);
            String var13 = null;
            if (var11.img != null) {
               var13 = this.getFontFilePath(var4, var6, var11.img);
            }

            String var14 = var12 + "|" + var13;
            if (var5.get(var14) != null) {
               this.enumToFont[var31.ordinal()] = (AngelCodeFont)var5.get(var14);
            } else {
               AngelCodeFont var15 = new AngelCodeFont(var12, var13);
               this.enumToFont[var31.ordinal()] = var15;
               var5.put(var14, var15);
            }
         }
      }

      try {
         ZomboidFileSystem.instance.IgnoreActiveFileMap.set(true);
         String var22 = new File("").getAbsolutePath().replaceAll("\\\\", "/");
         String var26 = var22 + "/media/fonts/zomboidSmall.fnt";
         String var29 = var22 + "/media/fonts/zomboidSmall_0.png";
         if (var26.startsWith("/")) {
            var26 = "/" + var26;
         }

         this.enumToFont[UIFont.DebugConsole.ordinal()] = new AngelCodeFont(var26, var29);
      } finally {
         ZomboidFileSystem.instance.IgnoreActiveFileMap.set(false);
      }

      for (int var23 = 0; var23 < this.normal.length; var23++) {
         this.normal[var23] = new AngelCodeFont("media/fonts/zomboidNormal" + (var23 + 11) + ".fnt", "media/fonts/zomboidNormal" + (var23 + 11) + "_0");
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
      this.enumToFont[UIFont.MediumNew.ordinal()] = null;
      this.enumToFont[UIFont.AutoNormSmall.ordinal()] = null;
      this.enumToFont[UIFont.AutoNormMedium.ordinal()] = null;
      this.enumToFont[UIFont.AutoNormLarge.ordinal()] = null;
      this.zomboidDialogue = this.enumToFont[UIFont.Dialogue.ordinal()];
      this.intro = this.enumToFont[UIFont.Intro.ordinal()];
      this.handwritten = this.enumToFont[UIFont.Handwritten.ordinal()];
      this.debugConsole = this.enumToFont[UIFont.DebugConsole.ordinal()];
   }

   public int MeasureStringX(UIFont var1, String var2) {
      if (GameServer.bServer && !ServerGUI.isCreated()) {
         return 0;
      } else if (var2 == null) {
         return 0;
      } else {
         AngelCodeFont var3 = this.getFontFromEnum(var1);
         return var3.getWidth(var2);
      }
   }

   public int MeasureStringY(UIFont var1, String var2) {
      if (var1 == null || var2 == null) {
         return 0;
      } else if (GameServer.bServer && !ServerGUI.isCreated()) {
         return 0;
      } else {
         AngelCodeFont var3 = this.getFontFromEnum(var1);
         return var3.getHeight(var2);
      }
   }

   public int MeasureFont(UIFont var1) {
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
         return var1 == UIFont.MainMenu2 ? 30 : this.getFontFromEnum(var1).getLineHeight();
      }
   }
}
