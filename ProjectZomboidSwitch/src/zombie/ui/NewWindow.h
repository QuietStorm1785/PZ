#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/lwjgl/util/Rectangle.h"
#include "zombie/core/textures/Texture.h"
#include <algorithm>

namespace zombie {
namespace ui {


class NewWindow : public UIElement {
public:
    int clickX = 0;
    int clickY = 0;
    int clientH = 0;
    int clientW = 0;
    bool Movable = true;
    bool moving = false;
    int ncclientH = 0;
    int ncclientW = 0;
   public std::stack<Rectangle> nestedItems = std::make_unique<std::stack<>>();
    bool ResizeToFitY = true;
    float alpha = 1.0F;
    Texture dialogBottomLeft = nullptr;
    Texture dialogBottomMiddle = nullptr;
    Texture dialogBottomRight = nullptr;
    Texture dialogLeft = nullptr;
    Texture dialogMiddle = nullptr;
    Texture dialogRight = nullptr;
    Texture titleCloseIcon = nullptr;
    Texture titleLeft = nullptr;
    Texture titleMiddle = nullptr;
    Texture titleRight = nullptr;
    HUDButton closeButton = nullptr;

    public NewWindow(int var1, int var2, int var3, int var4, bool var5) {
      this.x = var1;
      this.y = var2;
      if (var3 < 156) {
         var3 = 156;
      }

      if (var4 < 78) {
         var4 = 78;
      }

      this.width = var3;
      this.height = var4;
      this.titleLeft = Texture.getSharedTexture("media/ui/Dialog_Titlebar_Left.png");
      this.titleMiddle = Texture.getSharedTexture("media/ui/Dialog_Titlebar_Middle.png");
      this.titleRight = Texture.getSharedTexture("media/ui/Dialog_Titlebar_Right.png");
      this.dialogLeft = Texture.getSharedTexture("media/ui/Dialog_Left.png");
      this.dialogMiddle = Texture.getSharedTexture("media/ui/Dialog_Middle.png");
      this.dialogRight = Texture.getSharedTexture("media/ui/Dialog_Right.png");
      this.dialogBottomLeft = Texture.getSharedTexture("media/ui/Dialog_Bottom_Left.png");
      this.dialogBottomMiddle = Texture.getSharedTexture("media/ui/Dialog_Bottom_Middle.png");
      this.dialogBottomRight = Texture.getSharedTexture("media/ui/Dialog_Bottom_Right.png");
      if (var5) {
         this.closeButton = std::make_shared<HUDButton>(
            "close",
            var3 - 16,
            2.0F,
            "media/ui/Dialog_Titlebar_CloseIcon.png",
            "media/ui/Dialog_Titlebar_CloseIcon.png",
            "media/ui/Dialog_Titlebar_CloseIcon.png",
            this
         );
         this.AddChild(this.closeButton);
      }

      this.clientW = var3;
      this.clientH = var4;
   }

    void Nest(UIElement var1, int var2, int var3, int var4, int var5) {
      this.AddChild(var1);
      this.nestedItems.push_back(std::make_shared<Rectangle>(var5, var2, var3, var4));
      var1.setX(var5);
      var1.setY(var2);
      var1.update();
   }

    void ButtonClicked(const std::string& var1) {
      super.ButtonClicked(var1);
      if (var1 == "close")) {
         this.setVisible(false);
      }
   }

    bool onMouseDown(double var1, double var3) {
      if (!this.isVisible()) {
         return bool.FALSE;
      } else {
         super.onMouseDown(var1, var3);
         if (var3 < 18.0) {
            this.clickX = (int)var1;
            this.clickY = (int)var3;
            if (this.Movable) {
               this.moving = true;
            }

            this.setCapture(true);
         }

         return bool.TRUE;
      }
   }

    void setMovable(bool var1) {
      this.Movable = var1;
   }

    bool onMouseMove(double var1, double var3) {
      if (!this.isVisible()) {
         return bool.FALSE;
      } else {
         super.onMouseMove(var1, var3);
         if (this.moving) {
            this.setX(this.getX() + var1);
            this.setY(this.getY() + var3);
         }

         return bool.FALSE;
      }
   }

    void onMouseMoveOutside(double var1, double var3) {
      if (this.isVisible()) {
         super.onMouseMoveOutside(var1, var3);
         if (this.moving) {
            this.setX(this.getX() + var1);
            this.setY(this.getY() + var3);
         }
      }
   }

    bool onMouseUp(double var1, double var3) {
      if (!this.isVisible()) {
         return bool.FALSE;
      } else {
         super.onMouseUp(var1, var3);
         this.moving = false;
         this.setCapture(false);
         return bool.TRUE;
      }
   }

    void render() {
    float var1 = 0.8F * this.alpha;
    uint8_t var2 = 0;
    int var3 = 0;
      this.DrawTexture(this.titleLeft, var2, var3, var1);
      this.DrawTexture(this.titleRight, this.getWidth() - this.titleRight.getWidth(), var3, var1);
      this.DrawTextureScaled(
         this.titleMiddle, this.titleLeft.getWidth(), var3, this.getWidth() - this.titleLeft.getWidth() * 2, this.titleMiddle.getHeight(), var1
      );
      var3 += this.titleRight.getHeight();
      this.DrawTextureScaled(
         this.dialogLeft, var2, var3, this.dialogLeft.getWidth(), this.getHeight() - this.titleLeft.getHeight() - this.dialogBottomLeft.getHeight(), var1
      );
      this.DrawTextureScaled(
         this.dialogMiddle,
         this.dialogLeft.getWidth(),
         var3,
         this.getWidth() - this.dialogRight.getWidth() * 2,
         this.getHeight() - this.titleLeft.getHeight() - this.dialogBottomLeft.getHeight(),
         var1
      );
      this.DrawTextureScaled(
         this.dialogRight,
         this.getWidth() - this.dialogRight.getWidth(),
         var3,
         this.dialogLeft.getWidth(),
         this.getHeight() - this.titleLeft.getHeight() - this.dialogBottomLeft.getHeight(),
         var1
      );
      var3 = (int)(var3 + (this.getHeight() - this.titleLeft.getHeight() - this.dialogBottomLeft.getHeight()));
      this.DrawTextureScaled(
         this.dialogBottomMiddle,
         this.dialogBottomLeft.getWidth(),
         var3,
         this.getWidth() - this.dialogBottomLeft.getWidth() * 2,
         this.dialogBottomMiddle.getHeight(),
         var1
      );
      this.DrawTexture(this.dialogBottomLeft, var2, var3, var1);
      this.DrawTexture(this.dialogBottomRight, this.getWidth() - this.dialogBottomRight.getWidth(), var3, var1);
      super.render();
   }

    void update() {
      super.update();
      if (this.closeButton != nullptr) {
         this.closeButton.setX(4.0);
         this.closeButton.setY(3.0);
      }

    int var1 = 0;
      if (!this.ResizeToFitY) {
         for (Rectangle var3 : this.nestedItems) {
    UIElement var4 = (UIElement)this.getControls().get(var1);
            if (var4 != this.closeButton) {
               var4.setX(var3.getX());
               var4.setY(var3.getY());
               var4.setWidth(this.clientW - (var3.getX() + var3.getWidth()));
               var4.setHeight(this.clientH - (var3.getY() + var3.getHeight()));
               var4.onresize();
               var1++;
            }
         }
      } else {
    int var9 = 100000;
    int var10 = 100000;
    float var11 = 0.0F;
    float var5 = 0.0F;

         for (Rectangle var7 : this.nestedItems) {
    UIElement var8 = (UIElement)this.getControls().get(var1);
            if (var8 != this.closeButton) {
               if (var9 > var8.getAbsoluteX()) {
                  var9 = var8.getAbsoluteX().intValue();
               }

               if (var10 > var8.getAbsoluteX()) {
                  var10 = var8.getAbsoluteX().intValue();
               }

               if (var11 < var8.getWidth()) {
                  var11 = var8.getWidth().intValue();
               }

               if (var5 < var8.getHeight()) {
                  var5 = var8.getHeight().intValue();
               }

               var1++;
            }
         }

         var5 += 50.0F;
         this.height = var5;
      }
   }
}
} // namespace ui
} // namespace zombie
