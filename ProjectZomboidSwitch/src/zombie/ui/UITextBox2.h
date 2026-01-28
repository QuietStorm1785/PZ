#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/list/array/TIntArrayList.h"
#include "org/lwjglx/input/Keyboard.h"
#include "zombie/GameTime.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/core/Color.h"
#include "zombie/core/Core.h"
#include "zombie/core/fonts/AngelCodeFont.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/textures/ColorInfo.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/input/Mouse.h"
#include <algorithm>

namespace zombie {
namespace ui {


class UITextBox2 : public UIElement {
public:
    static bool ConsoleHasFocus = false;
   public std::stack<std::string> Lines = std::make_unique<std::stack<>>();
    UINineGrid Frame = nullptr;
    std::string Text = "";
    bool Centred = false;
    Color StandardFrameColour = std::make_shared<Color>(50, 50, 50, 212);
    Color TextEntryFrameColour = std::make_shared<Color>(50, 50, 127, 212);
    Color TextEntryCursorColour = std::make_shared<Color>(170, 170, 220, 240);
    Color TextEntryCursorColour2 = std::make_shared<Color>(100, 100, 220, 160);
    Color NuetralColour = std::make_shared<Color>(0, 0, 255, 33);
    Color NuetralColour2 = std::make_shared<Color>(127, 0, 255, 33);
    Color BadColour = std::make_shared<Color>(255, 0, 0, 33);
    Color GoodColour = std::make_shared<Color>(0, 255, 33);
    bool DoingTextEntry = false;
    int TextEntryCursorPos = 0;
    int TextEntryMaxLength = 2000;
    bool IsEditable = false;
    bool IsSelectable = false;
    int CursorLine = 0;
    bool multipleLine = false;
    TIntArrayList TextOffsetOfLineStart = std::make_shared<TIntArrayList>();
    int ToSelectionIndex = 0;
    std::string internalText = "";
    std::string maskChr = "*";
    bool bMask = false;
    bool ignoreFirst;
    UIFont font;
   int[] HighlightLines = new int[1000];
    bool HasFrame = false;
    int NumVisibleLines = 0;
    int TopLineIndex = 0;
    int BlinkFramesOn = 12;
    int BlinkFramesOff = 8;

   // ImGui rendering override
   virtual void ImGuiRender() override;
    float BlinkFrame = this.BlinkFramesOn;
    bool BlinkState = true;
    ColorInfo textColor = std::make_shared<ColorInfo>();
    int EdgeSize = 5;
    bool SelectingRange = false;
    int maxTextLength = -1;
    bool forceUpperCase = false;
    int XOffset = 0;
    int maxLines = 1;
    bool onlyNumbers = false;
    Texture clearButtonTexture;
    bool bClearButton = false;
    UITransition clearButtonTransition;
    bool bAlwaysPaginate = true;
    bool bTextChanged = false;
    int paginateWidth = -1;
    UIFont paginateFont = nullptr;

    public UITextBox2(UIFont var1, int var2, int var3, int var4, int var5, const std::string& var6, bool var7) {
      this.font = var1;
      this.x = var2;
      this.y = var3;
      this.SetText(var6);
      this.width = var4;
      this.height = var5;
      this.NumVisibleLines = 10;
      this.TopLineIndex = 0;
      Core.CurrentTextEntryBox = this;

      for (int var8 = 0; var8 < 1000; var8++) {
         this.HighlightLines[var8] = 0;
      }

      this.HasFrame = var7;
      if (var7) {
         this.Frame = std::make_shared<UINineGrid>(
            0,
            0,
            var4,
            var5,
            this.EdgeSize,
            this.EdgeSize,
            this.EdgeSize,
            this.EdgeSize,
            "media/ui/Box_TopLeft.png",
            "media/ui/Box_Top.png",
            "media/ui/Box_TopRight.png",
            "media/ui/Box_Left.png",
            "media/ui/Box_Center.png",
            "media/ui/Box_Right.png",
            "media/ui/Box_BottomLeft.png",
            "media/ui/Box_Bottom.png",
            "media/ui/Box_BottomRight.png"
         );
         this.AddChild(this.Frame);
      }

      this.Paginate();
      this.DoingTextEntry = false;
      this.TextEntryMaxLength = 2000;
      this.TextEntryCursorPos = 0;
      this.ToSelectionIndex = this.TextEntryCursorPos;
      this.IsEditable = false;
      Keyboard.enableRepeatEvents(true);
      this.clearButtonTexture = Texture.getSharedTexture("media/ui/Panel_Icon_Close.png");
   }

    void ClearHighlights() {
      for (int var1 = 0; var1 < 1000; var1++) {
         this.HighlightLines[var1] = 0;
      }
   }

    void setMasked(bool var1) {
      if (this.bMask != var1) {
         this.bMask = var1;
         if (this.bMask) {
            this.Text = this.maskChr.repeat(this.internalText.length());
         } else {
            this.Text = this.internalText;
         }
      }
   }

    bool isMasked() {
      return this.bMask;
   }

    void onresize() {
      this.Paginate();
   }

    void render() {
      if (this.isVisible()) {
         if (this.Parent == nullptr || this.Parent.maxDrawHeight == -1 || !(this.Parent.maxDrawHeight <= this.y)) {
            if (this.bMask) {
               if (this.internalText.length() != this.Text.length()) {
                  this.Text = this.maskChr.repeat(this.internalText.length());
               }
            } else {
               this.Text = this.internalText;
            }

            super.render();
            this.Paginate();
    int var1 = TextManager.instance.getFontFromEnum(this.font).getLineHeight();
    int var2 = this.getInset();
            this.keepCursorVisible();
    int var3 = (int)this.width - var2;
            if (this.bClearButton && this.clearButtonTexture != nullptr && !this.Lines.empty()) {
               var3 -= 2 + this.clearButtonTexture.getWidth() + 2;
    float var4 = 0.5F;
               if (!this.SelectingRange && this.isMouseOver() && Mouse.getXA() >= this.getAbsoluteX() + var3) {
                  var4 = 1.0F;
               }

               this.clearButtonTransition.setFadeIn(var4 == 1.0F);
               this.clearButtonTransition.update();
               this.DrawTexture(
                  this.clearButtonTexture,
                  this.width - var2 - 2.0F - this.clearButtonTexture.getWidth(),
                  var2 + (var1 - this.clearButtonTexture.getHeight()) / 2,
                  var4 * this.clearButtonTransition.fraction() + 0.35F * (1.0F - this.clearButtonTransition.fraction())
               );
            }

    double var19 = this.clampToParentX(this.getAbsoluteX().intValue() + var2);
    double var5 = this.clampToParentX(this.getAbsoluteX().intValue() + var3);
    double var6 = this.clampToParentY(this.getAbsoluteY().intValue() + var2);
    double var7 = this.clampToParentY(this.getAbsoluteY().intValue() + (int)this.height - var2);
            this.setStencilRect(
               var19.intValue() - this.getAbsoluteX().intValue(),
               var6.intValue() - this.getAbsoluteY().intValue(),
               var5.intValue() - var19.intValue(),
               var7.intValue() - var6.intValue()
            );
            if (this.Lines.size() > 0) {
    int var8 = var2;

               for (int var9 = this.TopLineIndex; var9 < this.TopLineIndex + this.NumVisibleLines && var9 < this.Lines.size(); var9++) {
                  if (this.Lines.get(var9) != nullptr) {
                     if (var9 >= 0 && var9 < this.HighlightLines.length) {
                        if (this.HighlightLines[var9] == 1) {
                           this.DrawTextureScaledCol(nullptr, var2 - 1, var8, this.getWidth().intValue() - var2 * 2 + 2, var1, this.NuetralColour);
                        } else if (this.HighlightLines[var9] == 2) {
                           this.DrawTextureScaledCol(nullptr, var2 - 1, var8, this.getWidth().intValue() - var2 * 2 + 2, var1, this.NuetralColour2);
                        } else if (this.HighlightLines[var9] == 3) {
                           this.DrawTextureScaledCol(nullptr, var2 - 1, var8, this.getWidth().intValue() - var2 * 2 + 2, var1, this.BadColour);
                        } else if (this.HighlightLines[var9] == 4) {
                           this.DrawTextureScaledCol(nullptr, var2 - 1, var8, this.getWidth().intValue() - var2 * 2 + 2, var1, this.GoodColour);
                        }
                     }

    std::string var10 = this.Lines.get(var9);
                     if (this.Centred) {
                        TextManager.instance
                           .DrawStringCentre(
                              this.font,
                              this.getAbsoluteX().intValue() + this.getWidth() / 2.0 + var2,
                              this.getAbsoluteY().intValue() + var8,
                              var10,
                              this.textColor.r,
                              this.textColor.g,
                              this.textColor.b,
                              1.0
                           );
                     } else {
                        TextManager.instance
                           .DrawString(
                              this.font,
                              -this.XOffset + this.getAbsoluteX().intValue() + var2,
                              this.getAbsoluteY().intValue() + var8,
                              var10,
                              this.textColor.r,
                              this.textColor.g,
                              this.textColor.b,
                              1.0
                           );
                     }

                     var8 += var1;
                  }
               }
            }

            ConsoleHasFocus = this.DoingTextEntry;
            if (this.TextEntryCursorPos > this.Text.length()) {
               this.TextEntryCursorPos = this.Text.length();
            }

            if (this.ToSelectionIndex > this.Text.length()) {
               this.ToSelectionIndex = this.Text.length();
            }

            this.CursorLine = this.toDisplayLine(this.TextEntryCursorPos);
            if (this.DoingTextEntry) {
    AngelCodeFont var20 = TextManager.instance.getFontFromEnum(this.font);
               if (this.BlinkState) {
    int var21 = 0;
                  if (this.Lines.size() > 0) {
    int var23 = this.TextEntryCursorPos - this.TextOffsetOfLineStart.get(this.CursorLine);
                     var23 = Math.min(var23, this.Lines.get(this.CursorLine).length());
                     var21 = var20.getWidth(this.Lines.get(this.CursorLine), 0, var23 - 1, true);
                     if (var21 > 0) {
                        var21--;
                     }
                  }

                  this.DrawTextureScaledCol(
                     Texture.getWhite(), -this.XOffset + var2 + var21, var2 + this.CursorLine * var1, 1.0, var1, this.TextEntryCursorColour
                  );
               }

               if (this.Lines.size() > 0 && this.ToSelectionIndex != this.TextEntryCursorPos) {
    int var22 = Math.min(this.TextEntryCursorPos, this.ToSelectionIndex);
    int var25 = Math.max(this.TextEntryCursorPos, this.ToSelectionIndex);
    int var11 = this.toDisplayLine(var22);
    int var12 = this.toDisplayLine(var25);

                  for (int var13 = var11; var13 <= var12; var13++) {
    int var14 = this.TextOffsetOfLineStart.get(var13);
    int var15 = var14 + this.Lines.get(var13).length();
                     var14 = Math.max(var14, var22);
                     var15 = Math.min(var15, var25);
    std::string var16 = this.Lines.get(var13);
    int var17 = var20.getWidth(var16, 0, var14 - this.TextOffsetOfLineStart.get(var13) - 1, true);
    int var18 = var20.getWidth(var16, 0, var15 - this.TextOffsetOfLineStart.get(var13) - 1, true);
                     this.DrawTextureScaledCol(nullptr, -this.XOffset + var2 + var17, var2 + var13 * var1, var18 - var17, var1, this.TextEntryCursorColour2);
                  }
               }
            }

            this.clearStencilRect();
            if (StencilLevel > 0) {
               this.repaintStencilRect(
                  var19.intValue() - this.getAbsoluteX().intValue(),
                  var6.intValue() - this.getAbsoluteY().intValue(),
                  var5.intValue() - var19.intValue(),
                  var7.intValue() - var6.intValue()
               );
            }
         }
      }
   }

    float getFrameAlpha() {
      return this.Frame.getAlpha();
   }

    void setFrameAlpha(float var1) {
      this.Frame.setAlpha(var1);
   }

    void setTextColor(ColorInfo var1) {
      this.textColor = var1;
   }

    void keepCursorVisible() {
      if (!this.Lines.empty() && this.DoingTextEntry && !this.multipleLine) {
         if (this.TextEntryCursorPos > this.Text.length()) {
            this.TextEntryCursorPos = this.Text.length();
         }

    std::string var1 = this.Lines.get(0);
    int var2 = TextManager.instance.MeasureStringX(this.font, var1);
    int var3 = this.getInset();
    int var4 = this.getWidth().intValue() - var3 * 2;
         if (this.bClearButton && this.clearButtonTexture != nullptr) {
            var4 -= 2 + this.clearButtonTexture.getWidth() + 2;
         }

         if (var2 <= var4) {
            this.XOffset = 0;
         } else if (-this.XOffset + var2 < var4) {
            this.XOffset = var2 - var4;
         }

    int var5 = TextManager.instance.MeasureStringX(this.font, var1.substr(0, this.TextEntryCursorPos));
    int var6 = -this.XOffset + var3 + var5 - 1;
         if (var6 < var3) {
            this.XOffset = var5;
         } else if (var6 >= var3 + var4) {
            this.XOffset = 0;
    int var7 = this.getCursorPosFromX(var5 - var4);
            this.XOffset = TextManager.instance.MeasureStringX(this.font, var1.substr(0, var7));
            var6 = -this.XOffset + var3 + var5 - 1;
            if (var6 >= var3 + var4) {
               this.XOffset = TextManager.instance.MeasureStringX(this.font, var1.substr(0, var7 + 1));
            }

            if (-this.XOffset + var2 < var4) {
               this.XOffset = var2 - var4;
            }
         }
      } else {
         this.XOffset = 0;
      }
   }

    std::string getText() {
      return this.Text;
   }

    std::string getInternalText() {
      return this.internalText;
   }

    void update() {
      if (this.maxTextLength > -1 && this.internalText.length() > this.maxTextLength) {
         this.internalText = this.internalText.substr(this.maxTextLength);
      }

      if (this.forceUpperCase) {
         this.internalText = this.internalText.toUpperCase();
      }

      if (this.bMask) {
         if (this.internalText.length() != this.Text.length()) {
    std::string var1 = "";

            for (int var2 = 0; var2 < this.internalText.length(); var2++) {
               var1 = var1 + this.maskChr;
            }

            if (this.DoingTextEntry && this.Text != var1) {
               this.resetBlink();
            }

            this.Text = var1;
         }
      } else {
         if (this.DoingTextEntry && this.Text != this.internalText) {
            this.resetBlink();
         }

         this.Text = this.internalText;
      }

      this.Paginate();
    int var3 = this.getInset();
    int var4 = TextManager.instance.getFontFromEnum(this.font).getLineHeight();
      if (var4 + var3 * 2 > this.getHeight()) {
         this.setHeight(var4 + var3 * 2);
      }

      if (this.Frame != nullptr) {
         this.Frame.setHeight(this.getHeight());
      }

      this.NumVisibleLines = (int)(this.getHeight() - var3 * 2) / var4;
      if (this.BlinkFrame > 0.0F) {
         this.BlinkFrame = this.BlinkFrame - GameTime.getInstance().getRealworldSecondsSinceLastUpdate() * 30.0F;
      } else {
         this.BlinkState = !this.BlinkState;
         if (this.BlinkState) {
            this.BlinkFrame = this.BlinkFramesOn;
         } else {
            this.BlinkFrame = this.BlinkFramesOff;
         }
      }

      if (this.NumVisibleLines * var4 + var3 * 2 < this.getHeight().intValue()) {
         if (this.NumVisibleLines < this.Lines.size()) {
            this.setScrollHeight((this.Lines.size() + 1) * var4);
         }

         this.NumVisibleLines++;
      } else {
         this.setScrollHeight(this.Lines.size() * var4);
      }

      if (UIDebugConsole.instance == nullptr || this != UIDebugConsole.instance.OutputLog) {
         this.TopLineIndex = (int)(-this.getYScroll() + var3) / var4;
      }

      this.setYScroll(-this.TopLineIndex * var4);
   }

    void Paginate() {
    bool var1 = this.bAlwaysPaginate;
      if (!this.bAlwaysPaginate) {
         if (this.paginateFont != this.font) {
            this.paginateFont = this.font;
            var1 = true;
         }

         if (this.paginateWidth != this.getWidth().intValue()) {
            this.paginateWidth = this.getWidth().intValue();
            var1 = true;
         }

         if (this.bTextChanged) {
            this.bTextChanged = false;
            var1 = true;
         }

         if (!var1) {
            return;
         }
      }

      this.Lines.clear();
      this.TextOffsetOfLineStart.resetQuick();
      if (!this.Text.empty()) {
         if (!this.multipleLine) {
            this.Lines.push_back(this.Text);
            this.TextOffsetOfLineStart.push_back(0);
         } else {
            std::string[] var2 = this.Text.split("\n", -1);
    int var3 = 0;

    for (auto& var7 : var2)    int var8 = 0;
               if (var7.length() == 0) {
                  this.Lines.push_back(this.multipleLine ? "" : " ");
                  this.TextOffsetOfLineStart.push_back(var3);
                  var3++;
               } else {
                  while (true) {
    int var9 = var7.indexOf(" ", var8 + 1);
    int var10 = var9;
                     if (var9 == -1) {
                        var10 = var7.length();
                     }

    int var11 = TextManager.instance.MeasureStringX(this.font, var7.substr(0, var10));
    uint8_t var12 = 17;
                     if (var11 >= this.getWidth() - this.getInset() * 2 - var12 && var8 > 0) {
    std::string var13 = var7.substr(0, var8);
                        var7 = var7.substr(var8 + 1);
                        this.Lines.push_back(var13);
                        this.TextOffsetOfLineStart.push_back(var3);
                        var3 += var13.length() + 1;
                        var9 = 0;
                     } else if (var9 == -1) {
                        this.Lines.push_back(var7);
                        this.TextOffsetOfLineStart.push_back(var3);
                        var3 += var7.length() + 1;
                        break;
                     }

                     var8 = var9;
                     if (var7.length() <= 0) {
                        break;
                     }
                  }
               }
            }
         }
      }
   }

    int getInset() {
    int var1 = 2;
      if (this.HasFrame) {
         var1 = this.EdgeSize;
      }

    return var1;
   }

    void setEditable(bool var1) {
      this.IsEditable = var1;
   }

    bool isEditable() {
      return this.IsEditable;
   }

    void setSelectable(bool var1) {
      this.IsSelectable = var1;
   }

    bool isSelectable() {
      return this.IsSelectable;
   }

    bool onMouseUp(double var1, double var3) {
      if (!this.isVisible()) {
    return false;
      } else {
         super.onMouseUp(var1, var3);
         this.SelectingRange = false;
         return bool.TRUE;
      }
   }

    void onMouseUpOutside(double var1, double var3) {
      if (this.isVisible()) {
         super.onMouseUpOutside(var1, var3);
         this.SelectingRange = false;
      }
   }

    bool onMouseMove(double var1, double var3) {
    int var5 = Mouse.getXA();
    int var6 = Mouse.getYA();
      if (!this.isVisible()) {
         return bool.FALSE;
      } else {
    bool var7 = this.isConsumeMouseEvents();
         this.setConsumeMouseEvents(false);
    bool var8 = super.onMouseMove(var1, var3);
         this.setConsumeMouseEvents(var7);
         if (var8) {
            return bool.TRUE;
         } else if ((this.IsEditable || this.IsSelectable) && this.SelectingRange) {
            if (this.multipleLine) {
    int var9 = this.getInset();
    int var10 = TextManager.instance.getFontFromEnum(this.font).getLineHeight();
               this.CursorLine = (var6 - this.getAbsoluteY().intValue() - var9 - this.getYScroll().intValue()) / var10;
               if (this.CursorLine > this.Lines.size() - 1) {
                  this.CursorLine = this.Lines.size() - 1;
               }
            }

            this.TextEntryCursorPos = this.getCursorPosFromX((int)(var5 - this.getAbsoluteX()));
            return bool.TRUE;
         } else {
            return bool.FALSE;
         }
      }
   }

    void onMouseMoveOutside(double var1, double var3) {
    int var5 = Mouse.getXA();
    int var6 = Mouse.getYA();
      if (!Mouse.isButtonDown(0)) {
         this.SelectingRange = false;
      }

      if (this.isVisible()) {
         super.onMouseMoveOutside(var1, var3);
         if ((this.IsEditable || this.IsSelectable) && this.SelectingRange) {
            if (this.multipleLine) {
    int var7 = this.getInset();
    int var8 = TextManager.instance.getFontFromEnum(this.font).getLineHeight();
               this.CursorLine = (var6 - this.getAbsoluteY().intValue() - var7 - this.getYScroll().intValue()) / var8;
               if (this.CursorLine < 0) {
                  this.CursorLine = 0;
               }

               if (this.CursorLine > this.Lines.size() - 1) {
                  this.CursorLine = this.Lines.size() - 1;
               }
            }

            this.TextEntryCursorPos = this.getCursorPosFromX((int)(var5 - this.getAbsoluteX()));
         }
      }
   }

    void focus() {
      if (!this.DoingTextEntry) {
      }

      this.DoingTextEntry = true;
      Core.CurrentTextEntryBox = this;
   }

    void unfocus() {
      this.DoingTextEntry = false;
      if (Core.CurrentTextEntryBox == this) {
         Core.CurrentTextEntryBox = nullptr;
      }
   }

    void ignoreFirstInput() {
      this.ignoreFirst = true;
   }

    bool onMouseDown(double var1, double var3) {
      if (!this.isVisible()) {
         return bool.FALSE;
      } else {
         if (!this.getControls().empty()) {
            for (int var5 = 0; var5 < this.getControls().size(); var5++) {
    UIElement var6 = (UIElement)this.getControls().get(var5);
               if (var6 != this.Frame && var6.isMouseOver()) {
                  return var6.onMouseDown(var1 - var6.getXScrolled(this).intValue(), var3 - var6.getYScrolled(this).intValue()) ? bool.TRUE : bool.FALSE;
               }
            }
         }

         if (this.bClearButton && this.clearButtonTexture != nullptr && !this.Lines.empty()) {
    int var7 = this.getWidth().intValue() - this.getInset();
            var7 -= 2 + this.clearButtonTexture.getWidth() + 2;
            if (var1 >= var7) {
               this.clearInput();
               return bool.TRUE;
            }
         }

         if (this.multipleLine) {
    int var9 = this.getInset();
    int var10 = TextManager.instance.getFontFromEnum(this.font).getLineHeight();
            this.CursorLine = ((int)var3 - var9 - this.getYScroll().intValue()) / var10;
            if (this.CursorLine > this.Lines.size() - 1) {
               this.CursorLine = this.Lines.size() - 1;
            }
         }

         if (!this.IsEditable && !this.IsSelectable) {
            if (this.Frame != nullptr) {
               this.Frame.Colour = this.StandardFrameColour;
            }

            this.DoingTextEntry = false;
            return bool.FALSE;
         } else {
            if (Core.CurrentTextEntryBox != this) {
               if (Core.CurrentTextEntryBox != nullptr) {
                  Core.CurrentTextEntryBox.DoingTextEntry = false;
                  if (Core.CurrentTextEntryBox.Frame != nullptr) {
                     Core.CurrentTextEntryBox.Frame.Colour = this.StandardFrameColour;
                  }
               }

               Core.CurrentTextEntryBox = this;
               Core.CurrentTextEntryBox.SelectingRange = true;
            }

            if (!this.DoingTextEntry) {
               this.focus();
               this.TextEntryCursorPos = this.getCursorPosFromX((int)var1);
               this.ToSelectionIndex = this.TextEntryCursorPos;
               if (this.Frame != nullptr) {
                  this.Frame.Colour = this.TextEntryFrameColour;
               }
            } else {
               this.TextEntryCursorPos = this.getCursorPosFromX((int)var1);
               this.ToSelectionIndex = this.TextEntryCursorPos;
            }

            return bool.TRUE;
         }
      }
   }

    int getCursorPosFromX(int var1) {
      if (this.Lines.empty()) {
    return 0;
      } else {
    std::string var2 = this.Lines.get(this.CursorLine);
         if (var2.length() == 0) {
            return this.TextOffsetOfLineStart.get(this.CursorLine);
         } else if (var1 + this.XOffset < 0) {
            return this.TextOffsetOfLineStart.get(this.CursorLine);
         } else {
            for (int var3 = 0; var3 <= var2.length(); var3++) {
    std::string var4 = "";
               if (var3 > 0) {
                  var4 = var2.substr(0, var3);
               }

    int var5 = TextManager.instance.MeasureStringX(this.font, var4);
               if (var5 > var1 + this.XOffset && var3 >= 0) {
                  return this.TextOffsetOfLineStart.get(this.CursorLine) + var3 - 1;
               }
            }

            return this.TextOffsetOfLineStart.get(this.CursorLine) + var2.length();
         }
      }
   }

    void updateText() {
      if (this.bMask) {
    std::string var1 = "";

         for (int var2 = 0; var2 < this.internalText.length(); var2++) {
            var1 = var1 + this.maskChr;
         }

         this.Text = var1;
      } else {
         this.Text = this.internalText;
      }
   }

    void SetText(const std::string& var1) {
      this.internalText = var1;
      if (this.bMask) {
         var1 = "";

         for (int var2 = 0; var2 < this.internalText.length(); var2++) {
            var1 = var1 + this.maskChr;
         }

         this.Text = var1;
      } else {
         this.Text = var1;
      }

      this.TextEntryCursorPos = var1.length();
      this.ToSelectionIndex = this.TextEntryCursorPos;
      this.update();
      this.TextEntryCursorPos = this.ToSelectionIndex = 0;
      if (!this.Lines.empty()) {
    int var3 = this.Lines.size() - 1;
         this.TextEntryCursorPos = this.ToSelectionIndex = this.TextOffsetOfLineStart.get(var3) + this.Lines.get(var3).length();
      }
   }

    void clearInput() {
      this.Text = "";
      this.internalText = "";
      this.TextEntryCursorPos = 0;
      this.ToSelectionIndex = 0;
      this.update();
      this.onTextChange();
   }

    void onPressUp() {
      if (this.getTable() != nullptr && this.getTable().rawget("onPressUp") != nullptr) {
         Object[] var1 = LuaManager.caller.pcall(LuaManager.thread, this.getTable().rawget("onPressUp"), this.getTable());
      }
   }

    void onPressDown() {
      if (this.getTable() != nullptr && this.getTable().rawget("onPressDown") != nullptr) {
         Object[] var1 = LuaManager.caller.pcall(LuaManager.thread, this.getTable().rawget("onPressDown"), this.getTable());
      }
   }

    void onCommandEntered() {
      if (this.getTable() != nullptr && this.getTable().rawget("onCommandEntered") != nullptr) {
         Object[] var1 = LuaManager.caller.pcall(LuaManager.thread, this.getTable().rawget("onCommandEntered"), this.getTable());
      }
   }

    void onTextChange() {
      if (this.getTable() != nullptr && this.getTable().rawget("onTextChange") != nullptr) {
         Object[] var1 = LuaManager.caller.pcall(LuaManager.thread, this.getTable().rawget("onTextChange"), this.getTable());
      }
   }

    void onOtherKey(int var1) {
      if (this.getTable() != nullptr && this.getTable().rawget("onOtherKey") != nullptr) {
         Object[] var2 = LuaManager.caller.pcall(LuaManager.thread, this.getTable().rawget("onOtherKey"), new Object[]{this.getTable(), var1});
      }
   }

    int getMaxTextLength() {
      return this.maxTextLength;
   }

    void setMaxTextLength(int var1) {
      this.maxTextLength = var1;
   }

    bool getForceUpperCase() {
      return this.forceUpperCase;
   }

    void setForceUpperCase(bool var1) {
      this.forceUpperCase = var1;
   }

    void setHasFrame(bool var1) {
      if (this.HasFrame != var1) {
         this.HasFrame = var1;
         if (this.HasFrame) {
            this.Frame = std::make_shared<UINineGrid>(
               0,
               0,
               (int)this.width,
               (int)this.height,
               this.EdgeSize,
               this.EdgeSize,
               this.EdgeSize,
               this.EdgeSize,
               "media/ui/Box_TopLeft.png",
               "media/ui/Box_Top.png",
               "media/ui/Box_TopRight.png",
               "media/ui/Box_Left.png",
               "media/ui/Box_Center.png",
               "media/ui/Box_Right.png",
               "media/ui/Box_BottomLeft.png",
               "media/ui/Box_Bottom.png",
               "media/ui/Box_BottomRight.png"
            );
            this.Frame.setAnchorRight(true);
            this.AddChild(this.Frame);
         } else {
            this.RemoveChild(this.Frame);
            this.Frame = nullptr;
         }
      }
   }

    void setClearButton(bool var1) {
      this.bClearButton = var1;
      if (this.bClearButton && this.clearButtonTransition == nullptr) {
         this.clearButtonTransition = std::make_unique<UITransition>();
      }
   }

    int toDisplayLine(int var1) {
      for (int var2 = 0; var2 < this.Lines.size(); var2++) {
         if (var1 >= this.TextOffsetOfLineStart.get(var2) && var1 <= this.TextOffsetOfLineStart.get(var2) + this.Lines.get(var2).length()) {
    return var2;
         }
      }

    return 0;
   }

    void setMultipleLine(bool var1) {
      this.multipleLine = var1;
   }

    bool isMultipleLine() {
      return this.multipleLine;
   }

    int getCursorLine() {
      return this.CursorLine;
   }

    void setCursorLine(int var1) {
      this.CursorLine = var1;
   }

    int getCursorPos() {
      return this.TextEntryCursorPos;
   }

    void setCursorPos(int var1) {
      if (this.multipleLine) {
         if (this.CursorLine >= 0 && this.CursorLine < this.Lines.size()) {
            this.TextEntryCursorPos = PZMath.clamp(var1, 0, this.Lines.get(this.CursorLine).length());
         }
      } else {
         this.TextEntryCursorPos = PZMath.clamp(var1, 0, this.internalText.length());
      }

      this.ToSelectionIndex = this.TextEntryCursorPos;
   }

    int getMaxLines() {
      return this.maxLines;
   }

    void setMaxLines(int var1) {
      this.maxLines = var1;
   }

    bool isFocused() {
      return this.DoingTextEntry;
   }

    bool isOnlyNumbers() {
      return this.onlyNumbers;
   }

    void setOnlyNumbers(bool var1) {
      this.onlyNumbers = var1;
   }

    void resetBlink() {
      this.BlinkState = true;
      this.BlinkFrame = this.BlinkFramesOn;
   }

    void selectAll() {
      this.TextEntryCursorPos = this.internalText.length();
      this.ToSelectionIndex = 0;
   }
}
} // namespace ui
} // namespace zombie
