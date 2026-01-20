#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/list/array/TShortArrayList.h"
#include "gnu/trove/map/hash/TShortObjectHashMap.h"
#include "org/lwjgl/opengl/GL11.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/asset/Asset.h"
#include "zombie/asset/Asset/State.h"
#include "zombie/asset/AssetStateObserver.h"
#include "zombie/core/Color.h"
#include "zombie/core/fonts/AngelCodeFont/1.h"
#include "zombie/core/fonts/AngelCodeFont/2.h"
#include "zombie/core/fonts/AngelCodeFont/CharDef.h"
#include "zombie/core/fonts/AngelCodeFont/DisplayList.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/core/textures/TextureID.h"
#include "zombie/util/StringUtils.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace zombie {
namespace core {
namespace fonts {


class AngelCodeFont {
public:
    static const int DISPLAY_LIST_CACHE_SIZE = 200;
    static const int MAX_CHAR = 255;
    int baseDisplayListID = -1;
   public CharDef[] chars;
    bool displayListCaching = false;
    DisplayList eldestDisplayList;
    int eldestDisplayListID;
    const LinkedHashMap displayLists = std::make_shared<1>(this, 200, 1.0F, true);
    Texture fontImage;
    int lineHeight;
   private std::unordered_map<int16_t, Texture> pages = std::make_unique<std::unordered_map<>>();
    File fntFile;
    static int xoff = 0;
    static int yoff = 0;
    static Color curCol = nullptr;
    static float curR = 0.0F;
    static float curG = 0.0F;
    static float curB = 0.0F;
    static float curA = 0.0F;
    static float s_scale = 0.0F;
   private static char[] data = new char[256];

    public AngelCodeFont(const std::string& var1, Texture var2) {
      this.fontImage = var2;
    std::string var3 = var1;
    FileInputStream var4 = std::make_shared<FileInputStream>(std::make_shared<File>(var1));
      if (var1.startsWith("/")) {
         var3 = var1.substr(1);
      }

    int var5;
      while ((var5 = var3.indexOf("\\")) != -1) {
         var3 = var3.substr(0, var5) + "/" + var3.substr(var5 + 1);
      }

      this.parseFnt(var4);
   }

    public AngelCodeFont(const std::string& var1, const std::string& var2) {
      if (!StringUtils.isNullOrWhitespace(var2)) {
    int var3 = 0;
         var3 |= TextureID.bUseCompression ? 4 : 0;
         this.fontImage = Texture.getSharedTexture(var2, var3);
         if (this.fontImage != nullptr && !this.fontImage.isReady()) {
            this.fontImage.getObserverCb().push_back(this);
         }
      }

    std::string var7 = var1;
    void* var4 = nullptr;
      if (var1.startsWith("/")) {
         var7 = var1.substr(1);
      }

    int var5;
      while ((var5 = var7.indexOf("\\")) != -1) {
         var7 = var7.substr(0, var5) + "/" + var7.substr(var5 + 1);
      }

      this.fntFile = std::make_shared<File>(ZomboidFileSystem.instance.getString(var7));
      var4 = std::make_shared<FileInputStream>(ZomboidFileSystem.instance.getString(var7));
      this.parseFnt((InputStream)var4);
   }

    void drawString(float var1, float var2, const std::string& var3) {
      this.drawString(var1, var2, var3, Color.white);
   }

    void drawString(float var1, float var2, const std::string& var3, Color var4) {
      this.drawString(var1, var2, var3, var4, 0, var3.length() - 1);
   }

    void drawString(float var1, float var2, const std::string& var3, float var4, float var5, float var6, float var7) {
      this.drawString(var1, var2, var3, var4, var5, var6, var7, 0, var3.length() - 1);
   }

    void drawString(float var1, float var2, float var3, const std::string& var4, float var5, float var6, float var7, float var8) {
      this.drawString(var1, var2, var3, var4, var5, var6, var7, var8, 0, var4.length() - 1);
   }

    void drawString(float var1, float var2, const std::string& var3, Color var4, int var5, int var6) {
      xoff = (int)var1;
      yoff = (int)var2;
      curR = var4.r;
      curG = var4.g;
      curB = var4.b;
      curA = var4.a;
      s_scale = 0.0F;
      Texture.lr = var4.r;
      Texture.lg = var4.g;
      Texture.lb = var4.b;
      Texture.la = var4.a;
      if (this.displayListCaching && var5 == 0 && var6 == var3.length() - 1) {
    DisplayList var7 = (DisplayList)this.displayLists.get(var3);
         if (var7 != nullptr) {
            GL11.glCallList(var7.id);
         } else {
            var7 = std::make_unique<DisplayList>();
            var7.text = var3;
    int var8 = this.displayLists.size();
            if (var8 < 200) {
               var7.id = this.baseDisplayListID + var8;
            } else {
               var7.id = this.eldestDisplayListID;
               this.displayLists.remove(this.eldestDisplayList.text);
            }

            this.displayLists.put(var3, var7);
            GL11.glNewList(var7.id, 4865);
            this.render(var3, var5, var6);
            GL11.glEndList();
         }
      } else {
         this.render(var3, var5, var6);
      }
   }

    void drawString(float var1, float var2, const std::string& var3, float var4, float var5, float var6, float var7, int var8, int var9) {
      this.drawString(var1, var2, 0.0F, var3, var4, var5, var6, var7, var8, var9);
   }

    void drawString(float var1, float var2, float var3, const std::string& var4, float var5, float var6, float var7, float var8, int var9, int var10) {
      xoff = (int)var1;
      yoff = (int)var2;
      curR = var5;
      curG = var6;
      curB = var7;
      curA = var8;
      s_scale = var3;
      Texture.lr = var5;
      Texture.lg = var6;
      Texture.lb = var7;
      Texture.la = var8;
      if (this.displayListCaching && var9 == 0 && var10 == var4.length() - 1) {
    DisplayList var11 = (DisplayList)this.displayLists.get(var4);
         if (var11 != nullptr) {
            GL11.glCallList(var11.id);
         } else {
            var11 = std::make_unique<DisplayList>();
            var11.text = var4;
    int var12 = this.displayLists.size();
            if (var12 < 200) {
               var11.id = this.baseDisplayListID + var12;
            } else {
               var11.id = this.eldestDisplayListID;
               this.displayLists.remove(this.eldestDisplayList.text);
            }

            this.displayLists.put(var4, var11);
            GL11.glNewList(var11.id, 4865);
            this.render(var4, var9, var10);
            GL11.glEndList();
         }
      } else {
         this.render(var4, var9, var10);
      }
   }

    int getHeight(const std::string& var1) {
    DisplayList var2 = nullptr;
      if (this.displayListCaching) {
         var2 = (DisplayList)this.displayLists.get(var1);
         if (var2 != nullptr && var2.height != nullptr) {
            return var2.height.intValue();
         }
      }

    int var3 = 1;
    int var4 = 0;

      for (int var5 = 0; var5 < var1.length(); var5++) {
    char var6 = var1.charAt(var5);
         if (var6 == '\n') {
            var3++;
            var4 = 0;
         } else if (var6 != ' ' && var6 < this.chars.length) {
    CharDef var7 = this.chars[var6];
            if (var7 != nullptr) {
               var4 = Math.max(var7.height + var7.yoffset, var4);
            }
         }
      }

      var4 = var3 * this.getLineHeight();
      if (var2 != nullptr) {
         var2.height = std::make_shared<int16_t>((short)var4);
      }

    return var4;
   }

    int getLineHeight() {
      return this.lineHeight;
   }

    int getWidth(const std::string& var1) {
      return this.getWidth(var1, 0, var1.length() - 1, false);
   }

    int getWidth(const std::string& var1, bool var2) {
      return this.getWidth(var1, 0, var1.length() - 1, var2);
   }

    int getWidth(const std::string& var1, int var2, int var3) {
      return this.getWidth(var1, var2, var3, false);
   }

    int getWidth(const std::string& var1, int var2, int var3, bool var4) {
    DisplayList var5 = nullptr;
      if (this.displayListCaching && var2 == 0 && var3 == var1.length() - 1) {
         var5 = (DisplayList)this.displayLists.get(var1);
         if (var5 != nullptr && var5.width != nullptr) {
            return var5.width.intValue();
         }
      }

    int var6 = var3 - var2 + 1;
    int var7 = 0;
    int var8 = 0;
    CharDef var9 = nullptr;

      for (int var10 = 0; var10 < var6; var10++) {
    char var11 = var1.charAt(var2 + var10);
         if (var11 == '\n') {
            var8 = 0;
         } else if (var11 < this.chars.length) {
    CharDef var12 = this.chars[var11];
            if (var12 != nullptr) {
               if (var9 != nullptr) {
                  var8 += var9.getKerning(var11);
               }

               var9 = var12;
               if (!var4 && var10 >= var6 - 1) {
                  var8 += var12.width;
               } else {
                  var8 += var12.xadvance;
               }

               var7 = Math.max(var7, var8);
            }
         }
      }

      if (var5 != nullptr) {
         var5.width = std::make_shared<int16_t>((short)var7);
      }

    return var7;
   }

    int getYOffset(const std::string& var1) {
    DisplayList var2 = nullptr;
      if (this.displayListCaching) {
         var2 = (DisplayList)this.displayLists.get(var1);
         if (var2 != nullptr && var2.yOffset != nullptr) {
            return var2.yOffset.intValue();
         }
      }

    int var3 = var1.indexOf(10);
      if (var3 == -1) {
         var3 = var1.length();
      }

    int var4 = 10000;

      for (int var5 = 0; var5 < var3; var5++) {
    char var6 = var1.charAt(var5);
    CharDef var7 = this.chars[var6];
         if (var7 != nullptr) {
            var4 = Math.min(var7.yoffset, var4);
         }
      }

      if (var2 != nullptr) {
         var2.yOffset = std::make_shared<int16_t>((short)var4);
      }

    return var4;
   }

    CharDef parseChar(const std::string& var1) {
    CharDef var2 = std::make_shared<CharDef>(this);
    StringTokenizer var3 = std::make_shared<StringTokenizer>(var1, " =");
      var3.nextToken();
      var3.nextToken();
      var2.id = int.parseInt(var3.nextToken());
      if (var2.id < 0) {
    return nullptr;
      } else {
         if (var2.id > 255) {
         }

         var3.nextToken();
         var2.x = int16_t.parseShort(var3.nextToken());
         var3.nextToken();
         var2.y = int16_t.parseShort(var3.nextToken());
         var3.nextToken();
         var2.width = int16_t.parseShort(var3.nextToken());
         var3.nextToken();
         var2.height = int16_t.parseShort(var3.nextToken());
         var3.nextToken();
         var2.xoffset = int16_t.parseShort(var3.nextToken());
         var3.nextToken();
         var2.yoffset = int16_t.parseShort(var3.nextToken());
         var3.nextToken();
         var2.xadvance = int16_t.parseShort(var3.nextToken());
         var3.nextToken();
         var2.page = int16_t.parseShort(var3.nextToken());
    Texture var4 = this.fontImage;
         if (this.pages.containsKey(var2.page)) {
            var4 = this.pages.get(var2.page);
         }

         if (var4 != nullptr && var4.isReady()) {
            var2.init();
         }

         if (var2.id != 32) {
            this.lineHeight = Math.max(var2.height + var2.yoffset, this.lineHeight);
         }

    return var2;
      }
   }

    void parseFnt(InputStream var1) {
      if (this.displayListCaching) {
         this.baseDisplayListID = GL11.glGenLists(200);
         if (this.baseDisplayListID == 0) {
            this.displayListCaching = false;
         }
      }

      try {
    BufferedReader var2 = std::make_shared<BufferedReader>(std::make_shared<InputStreamReader>(var1));
    std::string var3 = var2.readLine();
    std::string var4 = var2.readLine();
    TShortObjectHashMap var5 = std::make_shared<TShortObjectHashMap>(64);
    std::vector var6 = new std::vector(255);
    int var7 = 0;
    bool var8 = false;

         while (!var8) {
    std::string var9 = var2.readLine();
            if (var9 == nullptr) {
               var8 = true;
            } else {
               if (var9.startsWith("page")) {
    StringTokenizer var10 = std::make_shared<StringTokenizer>(var9, " =");
                  var10.nextToken();
                  var10.nextToken();
    short var11 = int16_t.parseShort(var10.nextToken());
                  var10.nextToken();
    std::string var12 = var10.nextToken().replace("\"", "");
                  var12 = this.fntFile.getParent() + File.separatorChar + var12;
                  var12 = var12.replace("\\", "/");
    int var13 = 0;
                  var13 |= TextureID.bUseCompression ? 4 : 0;
    Texture var14 = Texture.getSharedTexture(var12, var13);
                  if (var14 == nullptr) {
                     System.out.println("AngelCodeFont failed to load page " + var11 + " texture " + var12);
                  } else {
                     this.pages.put(var11, var14);
                     if (!var14.isReady()) {
                        var14.getObserverCb().push_back(this);
                     }
                  }
               }

               if (!var9.startsWith("chars c") && var9.startsWith("char")) {
    CharDef var17 = this.parseChar(var9);
                  if (var17 != nullptr) {
                     var7 = Math.max(var7, var17.id);
                     var6.push_back(var17);
                  }
               }

               if (!var9.startsWith("kernings c") && var9.startsWith("kerning")) {
    StringTokenizer var18 = std::make_shared<StringTokenizer>(var9, " =");
                  var18.nextToken();
                  var18.nextToken();
    short var20 = int16_t.parseShort(var18.nextToken());
                  var18.nextToken();
    int var23 = int.parseInt(var18.nextToken());
                  var18.nextToken();
    int var25 = int.parseInt(var18.nextToken());
    TShortArrayList var26 = (TShortArrayList)var5.get(var20);
                  if (var26 == nullptr) {
                     var26 = std::make_unique<TShortArrayList>();
                     var5.put(var20, var26);
                  }

                  var26.push_back((short)var23);
                  var26.push_back((short)var25);
               }
            }
         }

         this.chars = new CharDef[var7 + 1];

    for (auto& var19 : var6)            this.chars[var19.id] = var19;
         }

         var5.forEachEntry(std::make_shared<2>(this));
         var2.close();
      } catch (IOException var15) {
         var15.printStackTrace();
      }
   }

    void render(const std::string& var1, int var2, int var3) {
      var3++;
    int var4 = var3 - var2;
    float var5 = 0.0F;
    float var6 = 0.0F;
    CharDef var7 = nullptr;
      if (data.length < var4) {
         data = new char[(var4 + 128 - 1) / 128 * 128];
      }

      var1.getChars(var2, var3, data, 0);

      for (int var8 = 0; var8 < var4; var8++) {
    char var9 = data[var8];
         if (var9 == '\n') {
            var5 = 0.0F;
            var6 += this.getLineHeight();
         } else if (var9 < this.chars.length) {
    CharDef var10 = this.chars[var9];
            if (var10 != nullptr) {
               if (var7 != nullptr) {
                  if (s_scale > 0.0F) {
                     var5 += var7.getKerning(var9) * s_scale;
                  } else {
                     var5 += var7.getKerning(var9);
                  }
               }

               var7 = var10;
               var10.draw(var5, var6);
               if (s_scale > 0.0F) {
                  var5 += var10.xadvance * s_scale;
               } else {
                  var5 += var10.xadvance;
               }
            }
         }
      }
   }

    void onStateChanged(State var1, State var2, Asset var3) {
      if (var3 == this.fontImage || this.pages.containsValue(var3)) {
         if (var2 == State.READY) {
            for (CharDef var7 : this.chars) {
               if (var7 != nullptr && var7.image == nullptr) {
    Texture var8 = this.fontImage;
                  if (this.pages.containsKey(var7.page)) {
                     var8 = this.pages.get(var7.page);
                  }

                  if (var3 == var8) {
                     var7.init();
                  }
               }
            }
         }
      }
   }

    bool isEmpty() {
      if (this.fontImage != nullptr && this.fontImage.empty()) {
    return true;
      } else {
         for (Texture var2 : this.pages.values()) {
            if (var2.empty()) {
    return true;
            }
         }

    return false;
      }
   }

    void destroy() {
      for (CharDef var4 : this.chars) {
         if (var4 != nullptr) {
            var4.destroy();
         }
      }

      Arrays.fill(this.chars, nullptr);
      this.pages.clear();
   }
}
} // namespace fonts
} // namespace core
} // namespace zombie
