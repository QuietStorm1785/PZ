#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameTime.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/chat/ChatElement.h"
#include "zombie/core/Core.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/fonts/AngelCodeFont.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/network/GameServer.h"
#include "zombie/ui/TextDrawObject/DrawElement.h"
#include "zombie/ui/TextDrawObject/DrawLine.h"
#include "zombie/ui/TextDrawObject/RenderBatch.h"
#include <algorithm>

namespace zombie {
namespace ui {


class TextDrawObject {
public:
   private std::string[] validImages = new std::string[]{"Icon_music_notes", "media/ui/CarKey.png", "media/ui/ArrowUp.png", "media/ui/ArrowDown.png"};
   private std::string[] validFonts = new std::string[]{"Small", "Dialogue", "Medium", "Code", "Large", "Massive"};
   private const std::vector<DrawLine> lines = std::make_unique<std::vector<>>();
    int width = 0;
    int height = 0;
    int maxCharsLine = -1;
    UIFont defaultFontEnum = UIFont.Dialogue;
    AngelCodeFont defaultFont = nullptr;
    std::string original = "";
    std::string unformatted = "";
    DrawLine currentLine;
    DrawElement currentElement;
    bool hasOpened = false;
    bool drawBackground = false;
    bool allowImages = true;
    bool allowChatIcons = true;
    bool allowColors = true;
    bool allowFonts = true;
    bool allowBBcode = true;
    bool allowAnyImage = false;
    bool allowLineBreaks = true;
    bool equalizeLineHeights = false;
    bool enabled = true;
    int visibleRadius = -1;
    float scrambleVal = 0.0F;
    float outlineR = 0.0F;
    float outlineG = 0.0F;
    float outlineB = 0.0F;
    float outlineA = 1.0F;
    float defaultR = 1.0F;
    float defaultG = 1.0F;
    float defaultB = 1.0F;
    float defaultA = 1.0F;
    int hearRange = -1;
    float internalClock = 0.0F;
    std::string customTag = "default";
    int customImageMaxDim = 18;
    TextDrawHorizontal defaultHorz = TextDrawHorizontal.Center;
    int drawMode = 0;
   private static std::vector<RenderBatch> renderBatch = std::make_unique<std::vector<>>();
   private static ArrayDeque<RenderBatch> renderBatchPool = std::make_unique<ArrayDeque<>>();
    std::string elemText;

    public TextDrawObject() {
      this(255, 255, 255, true, true, true, true, true, false);
   }

    public TextDrawObject(int var1, int var2, int var3, bool var4) {
      this(var1, var2, var3, var4, true, true, true, true, false);
   }

    public TextDrawObject(int var1, int var2, int var3, bool var4, bool var5, bool var6, bool var7, bool var8, bool var9) {
      this.setSettings(var4, var5, var6, var7, var8, var9);
      this.setDefaultColors(var1, var2, var3);
   }

    void setEnabled(bool var1) {
      this.enabled = var1;
   }

    bool getEnabled() {
      return this.enabled;
   }

    void setVisibleRadius(int var1) {
      this.visibleRadius = var1;
   }

    int getVisibleRadius() {
      return this.visibleRadius;
   }

    void setDrawBackground(bool var1) {
      this.drawBackground = var1;
   }

    void setAllowImages(bool var1) {
      this.allowImages = var1;
   }

    void setAllowChatIcons(bool var1) {
      this.allowChatIcons = var1;
   }

    void setAllowColors(bool var1) {
      this.allowColors = var1;
   }

    void setAllowFonts(bool var1) {
      this.allowFonts = var1;
   }

    void setAllowBBcode(bool var1) {
      this.allowBBcode = var1;
   }

    void setAllowAnyImage(bool var1) {
      this.allowAnyImage = var1;
   }

    void setAllowLineBreaks(bool var1) {
      this.allowLineBreaks = var1;
   }

    void setEqualizeLineHeights(bool var1) {
      this.equalizeLineHeights = var1;
      this.calculateDimensions();
   }

    void setSettings(bool var1, bool var2, bool var3, bool var4, bool var5, bool var6) {
      this.allowImages = var2;
      this.allowChatIcons = var3;
      this.allowColors = var4;
      this.allowFonts = var5;
      this.allowBBcode = var1;
      this.equalizeLineHeights = var6;
   }

    void setCustomTag(const std::string& var1) {
      this.customTag = var1;
   }

    std::string getCustomTag() {
      return this.customTag;
   }

    void setValidImages(std::string[] var1) {
      this.validImages = var1;
   }

    void setValidFonts(std::string[] var1) {
      this.validFonts = var1;
   }

    void setMaxCharsPerLine(int var1) {
      if (var1 > 0) {
         this.ReadString(this.original, var1);
      }
   }

    void setCustomImageMaxDimensions(int var1) {
      if (var1 >= 1) {
         this.customImageMaxDim = var1;
         this.calculateDimensions();
      }
   }

    void setOutlineColors(int var1, int var2, int var3) {
      this.setOutlineColors(var1 / 255.0F, var2 / 255.0F, var3 / 255.0F, 1.0F);
   }

    void setOutlineColors(int var1, int var2, int var3, int var4) {
      this.setOutlineColors(var1 / 255.0F, var2 / 255.0F, var3 / 255.0F, var4 / 255.0F);
   }

    void setOutlineColors(float var1, float var2, float var3) {
      this.setOutlineColors(var1, var2, var3, 1.0F);
   }

    void setOutlineColors(float var1, float var2, float var3, float var4) {
      this.outlineR = var1;
      this.outlineG = var2;
      this.outlineB = var3;
      this.outlineA = var4;
   }

    void setDefaultColors(int var1, int var2, int var3) {
      this.setDefaultColors(var1 / 255.0F, var2 / 255.0F, var3 / 255.0F, 1.0F);
   }

    void setDefaultColors(int var1, int var2, int var3, int var4) {
      this.setDefaultColors(var1 / 255.0F, var2 / 255.0F, var3 / 255.0F, var4 / 255.0F);
   }

    void setDefaultColors(float var1, float var2, float var3) {
      this.setDefaultColors(var1, var2, var3, 1.0F);
   }

    void setDefaultColors(float var1, float var2, float var3, float var4) {
      this.defaultR = var1;
      this.defaultG = var2;
      this.defaultB = var3;
      this.defaultA = var4;
   }

    void setHorizontalAlign(const std::string& var1) {
      if (var1 == "left")) {
         this.defaultHorz = TextDrawHorizontal.Left;
      } else if (var1 == "center")) {
         this.defaultHorz = TextDrawHorizontal.Center;
      }

      if (var1 == "right")) {
         this.defaultHorz = TextDrawHorizontal.Right;
      }
   }

    void setHorizontalAlign(TextDrawHorizontal var1) {
      this.defaultHorz = var1;
   }

    TextDrawHorizontal getHorizontalAlign() {
      return this.defaultHorz;
   }

    std::string getOriginal() {
      return this.original;
   }

    std::string getUnformatted() {
      if (!(this.scrambleVal > 0.0F)) {
         return this.unformatted;
      } else {
    std::string var1 = "";

         for (DrawLine var3 : this.lines) {
            for (DrawElement var5 : var3.elements) {
               if (!var5.isImage) {
                  var1 = var1 + var5.scrambleText;
               }
            }
         }

    return var1;
      }
   }

    int getWidth() {
      return this.width;
   }

    int getHeight() {
      return this.height;
   }

    UIFont getDefaultFontEnum() {
      return this.defaultFontEnum;
   }

    bool isNullOrZeroLength() {
      return this.original == nullptr || this.original.length() == 0;
   }

    float getInternalClock() {
      return this.internalClock;
   }

    void setInternalTickClock(float var1) {
      if (var1 > 0.0F) {
         this.internalClock = var1;
      }
   }

    float updateInternalTickClock() {
      return this.updateInternalTickClock(1.25F * GameTime.getInstance().getMultiplier());
   }

    float updateInternalTickClock(float var1) {
      if (this.internalClock <= 0.0F) {
         return 0.0F;
      } else {
         this.internalClock -= var1;
         if (this.internalClock <= 0.0F) {
            this.internalClock = 0.0F;
         }

         return this.internalClock;
      }
   }

    void setScrambleVal(float var1) {
      if (this.scrambleVal != var1) {
         this.scrambleVal = var1;
         if (this.scrambleVal > 0.0F) {
            for (DrawLine var3 : this.lines) {
               for (DrawElement var5 : var3.elements) {
                  if (!var5.isImage) {
                     var5.scrambleText(this.scrambleVal);
                  }
               }
            }
         }
      }
   }

    float getScrambleVal() {
      return this.scrambleVal;
   }

    void setHearRange(int var1) {
      if (var1 < 0) {
         this.hearRange = 0;
      } else {
         this.hearRange = var1;
      }
   }

    int getHearRange() {
      return this.hearRange;
   }

    bool isValidFont(const std::string& var1) {
      for (std::string var5 : this.validFonts) {
         if (var1 == var5) && UIFont.FromString(var1) != nullptr) {
    return true;
         }
      }

    return false;
   }

    bool isValidImage(const std::string& var1) {
      for (std::string var5 : this.validImages) {
         if (var1 == var5)) {
    return true;
         }
      }

    return false;
   }

    int tryColorInt(const std::string& var1) {
      if (var1.length() > 0 && var1.length() <= 3) {
         try {
    int var2 = int.parseInt(var1);
            return var2 >= 0 && var2 < 256 ? var2 : -1;
         } catch (NumberFormatException var3) {
            return -1;
         }
      } else {
         return -1;
      }
   }

    std::string readTagValue(char[] var1, int var2) {
      if (var1[var2] == '=') {
    std::string var3 = "";

         for (int var4 = var2 + 1; var4 < var1.length; var4++) {
    char var5 = var1[var4];
            if (var5 == ']') {
    return var3;
            }

            var3 = var3 + var5;
         }
      }

    return nullptr;
   }

    void Clear() {
      this.original = "";
      this.unformatted = "";
      this.reset();
   }

    void reset() {
      this.lines.clear();
      this.currentLine = std::make_unique<DrawLine>();
      this.lines.push_back(this.currentLine);
      this.currentElement = std::make_unique<DrawElement>();
      this.currentLine.addElement(this.currentElement);
      this.enabled = true;
      this.scrambleVal = 0.0F;
   }

    void addNewLine() {
      this.currentLine = std::make_unique<DrawLine>();
      this.lines.push_back(this.currentLine);
      this.currentElement = this.currentElement.softclone();
      this.currentLine.addElement(this.currentElement);
   }

    void addText(const std::string& var1) {
      this.currentElement.addText(var1);
      this.currentLine.charW = this.currentLine.charW + var1.length();
   }

    void addWord(const std::string& var1) {
      if (this.maxCharsLine > 0 && this.currentLine.charW + var1.length() >= this.maxCharsLine) {
         for (int var2 = 0; var2 < var1.length() / this.maxCharsLine + 1; var2++) {
    int var3 = var2 * this.maxCharsLine;
    int var4 = var3 + this.maxCharsLine < var1.length() ? var3 + this.maxCharsLine : var1.length();
            if (var1.substr(var3, var4).length() > 0) {
               if (var2 > 0 || this.currentLine.charW != 0) {
                  this.addNewLine();
               }

               this.addText(var1.substr(var3, var4));
            }
         }
      } else {
         this.addText(var1);
      }
   }

    void addNewElement() {
      if (this.currentElement.text.length() == 0) {
         this.currentElement.reset();
      } else {
         this.currentElement = std::make_unique<DrawElement>();
         this.currentLine.addElement(this.currentElement);
      }
   }

    int readTag(char[] var1, int var2, const std::string& var3) {
      if (this.allowFonts && var3 == "fnt")) {
    std::string var13 = this.readTagValue(var1, var2);
         if (var13 != nullptr && this.isValidFont(var13)) {
            this.addNewElement();
            this.currentElement.f = UIFont.FromString(var13);
            this.currentElement.useFont = true;
            this.currentElement.font = TextManager.instance.getFontFromEnum(this.currentElement.f);
            this.hasOpened = true;
            return var2 + var13.length() + 1;
         }
      } else if ((this.allowImages || this.allowChatIcons) && var3 == "img")) {
    std::string var12 = this.readTagValue(var1, var2);
         if (var12 != nullptr && var12.trim().length() > 0) {
            this.addNewElement();
    int var15 = var12.length();
            std::string[] var16 = var12.split(",");
            if (var16.length > 1) {
               var12 = var16[0];
            }

            this.currentElement.isImage = true;
            this.currentElement.text = var12.trim();
            if (this.currentElement.text == "music")) {
               this.currentElement.text = "Icon_music_notes";
            }

            if (this.allowChatIcons && this.isValidImage(this.currentElement.text)) {
               this.currentElement.tex = Texture.getSharedTexture(this.currentElement.text);
               this.currentElement.isTextImage = true;
            } else if (this.allowImages) {
               this.currentElement.tex = Texture.getSharedTexture("Item_" + this.currentElement.text);
               if (this.currentElement.tex == nullptr) {
                  this.currentElement.tex = Texture.getSharedTexture("media/ui/Container_" + this.currentElement.text);
               }

               if (this.currentElement.tex != nullptr) {
                  this.currentElement.isTextImage = false;
                  this.currentElement.text = "Item_" + this.currentElement.text;
               }
            }

            if (this.allowAnyImage && this.currentElement.tex == nullptr) {
               this.currentElement.tex = Texture.getSharedTexture(this.currentElement.text);
               if (this.currentElement.tex != nullptr) {
                  this.currentElement.isTextImage = false;
               }
            }

            if (var16.length == 4) {
    int var17 = this.tryColorInt(var16[1]);
    int var18 = this.tryColorInt(var16[2]);
    int var9 = this.tryColorInt(var16[3]);
               if (var17 != -1 && var18 != -1 && var9 != -1) {
                  this.currentElement.useColor = true;
                  this.currentElement.R = var17 / 255.0F;
                  this.currentElement.G = var18 / 255.0F;
                  this.currentElement.B = var9 / 255.0F;
               }
            }

            this.addNewElement();
            return var2 + var15 + 1;
         }
      } else if (this.allowColors && var3 == "col")) {
    std::string var11 = this.readTagValue(var1, var2);
         if (var11 != nullptr) {
            std::string[] var14 = var11.split(",");
            if (var14.length == 3) {
    int var6 = this.tryColorInt(var14[0]);
    int var7 = this.tryColorInt(var14[1]);
    int var8 = this.tryColorInt(var14[2]);
               if (var6 != -1 && var7 != -1 && var8 != -1) {
                  this.addNewElement();
                  this.currentElement.useColor = true;
                  this.currentElement.R = var6 / 255.0F;
                  this.currentElement.G = var7 / 255.0F;
                  this.currentElement.B = var8 / 255.0F;
                  this.hasOpened = true;
                  return var2 + var11.length() + 1;
               }
            }
         }
      } else if (var3 == "cdt")) {
    std::string var4 = this.readTagValue(var1, var2);
         if (var4 != nullptr) {
    float var5 = this.internalClock;

            try {
               var5 = float.parseFloat(var4);
               var5 *= 60.0F;
            } catch (NumberFormatException var10) {
               var10.printStackTrace();
            }

            this.internalClock = var5;
            return var2 + var4.length() + 1;
         }
      }

      return -1;
   }

    void setDefaultFont(UIFont var1) {
      if (!var1 == this.defaultFontEnum)) {
         this.ReadString(var1, this.original, this.maxCharsLine);
      }
   }

    void setDefaultFontInternal(UIFont var1) {
      if (this.defaultFont == nullptr || !var1 == this.defaultFontEnum)) {
         this.defaultFontEnum = var1;
         this.defaultFont = TextManager.instance.getFontFromEnum(var1);
      }
   }

    void ReadString(const std::string& var1) {
      this.ReadString(this.defaultFontEnum, var1, this.maxCharsLine);
   }

    void ReadString(const std::string& var1, int var2) {
      this.ReadString(this.defaultFontEnum, var1, var2);
   }

    void ReadString(UIFont var1, const std::string& var2, int var3) {
      if (var2 == nullptr) {
         var2 = "";
      }

      this.reset();
      this.setDefaultFontInternal(var1);
      if (this.defaultFont != nullptr) {
         this.maxCharsLine = var3;
         this.original = var2;
         char[] var4 = var2.toCharArray();
         this.hasOpened = false;
    std::string var5 = "";

         for (int var6 = 0; var6 < var4.length; var6++) {
    char var7 = var4[var6];
            if (this.allowBBcode && var7 == '[') {
               if (var5.length() > 0) {
                  this.addWord(var5);
                  var5 = "";
               }

               if (var6 + 4 < var4.length) {
    std::string var8 = ("" + var4[var6 + 1] + var4[var6 + 2] + var4[var6 + 3]).toLowerCase();
                  if (this.allowLineBreaks && var8 == "br/")) {
                     this.addNewLine();
                     var6 += 4;
                     continue;
                  }

                  if (!this.hasOpened) {
    int var9 = this.readTag(var4, var6 + 4, var8);
                     if (var9 >= 0) {
                        var6 = var9;
                        continue;
                     }
                  }
               }

               if (this.hasOpened && var6 + 2 < var4.length && var4[var6 + 1] == '/' && var4[var6 + 2] == ']') {
                  this.hasOpened = false;
                  this.addNewElement();
                  var6 += 2;
                  continue;
               }
            }

            if (char.isWhitespace(var7) && var6 > 0 && !char.isWhitespace(var4[var6 - 1])) {
               this.addWord(var5);
               var5 = "";
            }

            var5 = var5 + var7;
            this.unformatted = this.unformatted + var7;
         }

         if (var5.length() > 0) {
            this.addWord(var5);
         }

         this.calculateDimensions();
      }
   }

    void calculateDimensions() {
      this.width = 0;
      this.height = 0;
    int var1 = 0;

      for (int var2 = 0; var2 < this.lines.size(); var2++) {
    DrawLine var3 = this.lines.get(var2);
         var3.h = 0;
         var3.w = 0;

         for (int var4 = 0; var4 < var3.elements.size(); var4++) {
    DrawElement var5 = (DrawElement)var3.elements.get(var4);
            var5.w = 0;
            var5.h = 0;
            if (var5.isImage && var5.tex != nullptr) {
               if (var5.isTextImage) {
                  var5.w = var5.tex.getWidth();
                  var5.h = var5.tex.getHeight();
               } else {
                  var5.w = (int)(var5.tex.getWidth() * 0.75F);
                  var5.h = (int)(var5.tex.getHeight() * 0.75F);
               }
            } else if (var5.useFont && var5.font != nullptr) {
               var5.w = var5.font.getWidth(var5.text);
               var5.h = var5.font.getHeight(var5.text);
            } else if (this.defaultFont != nullptr) {
               var5.w = this.defaultFont.getWidth(var5.text);
               var5.h = this.defaultFont.getHeight(var5.text);
            }

            var3.w = var3.w + var5.w;
            if (var5.h > var3.h) {
               var3.h = var5.h;
            }
         }

         if (var3.w > this.width) {
            this.width = var3.w;
         }

         this.height = this.height + var3.h;
         if (var3.h > var1) {
            var1 = var3.h;
         }
      }

      if (this.equalizeLineHeights) {
         this.height = 0;

         for (int var6 = 0; var6 < this.lines.size(); var6++) {
    DrawLine var7 = this.lines.get(var6);
            var7.h = var1;
            this.height += var1;
         }
      }
   }

    void Draw(double var1, double var3) {
      this.Draw(this.defaultHorz, var1, var3, this.defaultR, this.defaultG, this.defaultB, this.defaultA, false);
   }

    void Draw(double var1, double var3, bool var5) {
      this.Draw(this.defaultHorz, var1, var3, this.defaultR, this.defaultG, this.defaultB, this.defaultA, var5);
   }

    void Draw(double var1, double var3, bool var5, float var6) {
      this.Draw(this.defaultHorz, var1, var3, this.defaultR, this.defaultG, this.defaultB, var6, var5);
   }

    void Draw(double var1, double var3, double var5, double var7, double var9, double var11, bool var13) {
      this.Draw(this.defaultHorz, var1, var3, var5, var7, var9, var11, var13);
   }

    void Draw(TextDrawHorizontal var1, double var2, double var4, double var6, double var8, double var10, double var12, bool var14) {
      this.DrawRaw(var1, var2, var4, (float)var6, (float)var8, (float)var10, (float)var12, var14);
   }

    void AddBatchedDraw(double var1, double var3) {
      this.AddBatchedDraw(this.defaultHorz, var1, var3, this.defaultR, this.defaultG, this.defaultB, this.defaultA, false);
   }

    void AddBatchedDraw(double var1, double var3, bool var5) {
      this.AddBatchedDraw(this.defaultHorz, var1, var3, this.defaultR, this.defaultG, this.defaultB, this.defaultA, var5);
   }

    void AddBatchedDraw(double var1, double var3, bool var5, float var6) {
      this.AddBatchedDraw(this.defaultHorz, var1, var3, this.defaultR, this.defaultG, this.defaultB, var6, var5);
   }

    void AddBatchedDraw(double var1, double var3, double var5, double var7, double var9, double var11, bool var13) {
      this.AddBatchedDraw(this.defaultHorz, var1, var3, var5, var7, var9, var11, var13);
   }

    void AddBatchedDraw(TextDrawHorizontal var1, double var2, double var4, double var6, double var8, double var10, double var12, bool var14) {
      if (!GameServer.bServer) {
    RenderBatch var15 = renderBatchPool.empty() ? std::make_shared<RenderBatch>() : renderBatchPool.pop();
         var15.playerNum = IsoPlayer.getPlayerIndex();
         var15.element = this;
         var15.horz = var1;
         var15.x = var2;
         var15.y = var4;
         var15.r = (float)var6;
         var15.g = (float)var8;
         var15.b = (float)var10;
         var15.a = (float)var12;
         var15.drawOutlines = var14;
         renderBatch.push_back(var15);
      }
   }

    static void RenderBatch(int var0) {
      if (renderBatch.size() > 0) {
         for (int var1 = 0; var1 < renderBatch.size(); var1++) {
    RenderBatch var2 = renderBatch.get(var1);
            if (var2.playerNum == var0) {
               var2.element.DrawRaw(var2.horz, var2.x, var2.y, var2.r, var2.g, var2.b, var2.a, var2.drawOutlines);
               renderBatchPool.push_back(var2);
               renderBatch.remove(var1--);
            }
         }
      }
   }

    static void NoRender(int var0) {
      for (int var1 = 0; var1 < renderBatch.size(); var1++) {
    RenderBatch var2 = renderBatch.get(var1);
         if (var2.playerNum == var0) {
            renderBatchPool.push_back(var2);
            renderBatch.remove(var1--);
         }
      }
   }

    void DrawRaw(TextDrawHorizontal var1, double var2, double var4, float var6, float var7, float var8, float var9, bool var10) {
    double var11 = var2;
    double var13 = var4;
    double var15 = 0.0;
    int var17 = Core.getInstance().getScreenWidth();
    int var18 = Core.getInstance().getScreenHeight();
    uint8_t var19 = 20;
      if (var1 == TextDrawHorizontal.Center) {
         var11 = var2 - this.getWidth() / 2;
      } else if (var1 == TextDrawHorizontal.Right) {
         var11 = var2 - this.getWidth();
      }

      if (!(var11 - var19 >= var17) && !(var11 + this.getWidth() + var19 <= 0.0) && !(var4 - var19 >= var18) && !(var4 + this.getHeight() + var19 <= 0.0)) {
         if (this.drawBackground && ChatElement.backdropTexture != nullptr) {
            ChatElement.backdropTexture.renderInnerBased((int)var11, (int)var4, this.getWidth(), this.getHeight(), 0.0F, 0.0F, 0.0F, 0.4F * var9);
         }

    float var20 = this.outlineA;
         if (var10 && var9 < 1.0F) {
            var20 = this.outlineA * var9;
         }

         for (int var21 = 0; var21 < this.lines.size(); var21++) {
    DrawLine var22 = this.lines.get(var21);
            var11 = var2;
            if (var1 == TextDrawHorizontal.Center) {
               var11 = var2 - var22.w / 2;
            } else if (var1 == TextDrawHorizontal.Right) {
               var11 = var2 - var22.w;
            }

            for (int var23 = 0; var23 < var22.elements.size(); var23++) {
    DrawElement var24 = (DrawElement)var22.elements.get(var23);
               var15 = var22.h / 2 - var24.h / 2;
               this.elemText = this.scrambleVal > 0.0F ? var24.scrambleText : var24.text;
               if (var24.isImage && var24.tex != nullptr) {
                  if (var10 && var24.isTextImage) {
                     SpriteRenderer.instance
                        .renderi(
                           var24.tex,
                           (int)(var11 - 1.0),
                           (int)(var13 + var15 - 1.0),
                           var24.w,
                           var24.h,
                           this.outlineR,
                           this.outlineG,
                           this.outlineB,
                           var20,
                           nullptr
                        );
                     SpriteRenderer.instance
                        .renderi(
                           var24.tex,
                           (int)(var11 + 1.0),
                           (int)(var13 + var15 + 1.0),
                           var24.w,
                           var24.h,
                           this.outlineR,
                           this.outlineG,
                           this.outlineB,
                           var20,
                           nullptr
                        );
                     SpriteRenderer.instance
                        .renderi(
                           var24.tex,
                           (int)(var11 - 1.0),
                           (int)(var13 + var15 + 1.0),
                           var24.w,
                           var24.h,
                           this.outlineR,
                           this.outlineG,
                           this.outlineB,
                           var20,
                           nullptr
                        );
                     SpriteRenderer.instance
                        .renderi(
                           var24.tex,
                           (int)(var11 + 1.0),
                           (int)(var13 + var15 - 1.0),
                           var24.w,
                           var24.h,
                           this.outlineR,
                           this.outlineG,
                           this.outlineB,
                           var20,
                           nullptr
                        );
                  }

                  if (var24.useColor) {
                     SpriteRenderer.instance.renderi(var24.tex, (int)var11, (int)(var13 + var15), var24.w, var24.h, var24.R, var24.G, var24.B, var9, nullptr);
                  } else if (var24.isTextImage) {
                     SpriteRenderer.instance.renderi(var24.tex, (int)var11, (int)(var13 + var15), var24.w, var24.h, var6, var7, var8, var9, nullptr);
                  } else {
                     SpriteRenderer.instance.renderi(var24.tex, (int)var11, (int)(var13 + var15), var24.w, var24.h, 1.0F, 1.0F, 1.0F, var9, nullptr);
                  }
               } else if (var24.useFont && var24.font != nullptr) {
                  if (var10) {
                     var24.font
                        .drawString((float)(var11 - 1.0), (float)(var13 + var15 - 1.0), this.elemText, this.outlineR, this.outlineG, this.outlineB, var20);
                     var24.font
                        .drawString((float)(var11 + 1.0), (float)(var13 + var15 + 1.0), this.elemText, this.outlineR, this.outlineG, this.outlineB, var20);
                     var24.font
                        .drawString((float)(var11 - 1.0), (float)(var13 + var15 + 1.0), this.elemText, this.outlineR, this.outlineG, this.outlineB, var20);
                     var24.font
                        .drawString((float)(var11 + 1.0), (float)(var13 + var15 - 1.0), this.elemText, this.outlineR, this.outlineG, this.outlineB, var20);
                  }

                  var24.font.drawString((float)var11, (float)(var13 + var15), this.elemText, var6, var7, var8, var9);
               } else if (this.defaultFont != nullptr) {
                  if (var10) {
                     this.defaultFont
                        .drawString((float)(var11 - 1.0), (float)(var13 + var15 - 1.0), this.elemText, this.outlineR, this.outlineG, this.outlineB, var20);
                     this.defaultFont
                        .drawString((float)(var11 + 1.0), (float)(var13 + var15 + 1.0), this.elemText, this.outlineR, this.outlineG, this.outlineB, var20);
                     this.defaultFont
                        .drawString((float)(var11 - 1.0), (float)(var13 + var15 + 1.0), this.elemText, this.outlineR, this.outlineG, this.outlineB, var20);
                     this.defaultFont
                        .drawString((float)(var11 + 1.0), (float)(var13 + var15 - 1.0), this.elemText, this.outlineR, this.outlineG, this.outlineB, var20);
                  }

                  if (var24.useColor) {
                     this.defaultFont.drawString((float)var11, (float)(var13 + var15), this.elemText, var24.R, var24.G, var24.B, var9);
                  } else {
                     this.defaultFont.drawString((float)var11, (float)(var13 + var15), this.elemText, var6, var7, var8, var9);
                  }
               }

               var11 += var24.w;
            }

            var13 += var22.h;
         }
      }
   }
}
} // namespace ui
} // namespace zombie
