#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameTime.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Color.h"
#include "zombie/core/Core.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/iso/IsoCamera.h"
#include "zombie/iso/IsoUtils.h"

namespace zombie {
namespace ui {


class ActionProgressBar : public UIElement {
public:
    Texture background;
    Texture foreground;
    float deltaValue = 1.0F;
    float animationProgress = 0.0F;
    int delayHide = 0;
    const int offsetX;
    const int offsetY;

   // ImGui rendering override
   virtual void ImGuiRender() override;

    public ActionProgressBar(int var1, int var2) {
      this.background = Texture.getSharedTexture("BuildBar_Bkg");
      this.foreground = Texture.getSharedTexture("BuildBar_Bar");
      this.offsetX = var1;
      this.offsetY = var2;
      this.width = this.background.getWidth();
      this.height = this.background.getHeight();
      this.followGameWorld = true;
   }

    void render() {
      if (this.isVisible() && UIManager.VisibleAllUI) {
         this.DrawUVSliceTexture(this.background, 0.0, 0.0, this.background.getWidth(), this.background.getHeight(), Color.white, 0.0, 0.0, 1.0, 1.0);
         if (this.deltaValue == float.POSITIVE_INFINITY) {
            if (this.animationProgress < 0.5F) {
               this.DrawUVSliceTexture(
                  this.foreground, 3.0, 0.0, this.foreground.getWidth(), this.foreground.getHeight(), Color.white, 0.0, 0.0, this.animationProgress * 2.0F, 1.0
               );
            } else {
               this.DrawUVSliceTexture(
                  this.foreground,
                  3.0,
                  0.0,
                  this.foreground.getWidth(),
                  this.foreground.getHeight(),
                  Color.white,
                  (this.animationProgress - 0.5F) * 2.0F,
                  0.0,
                  1.0,
                  1.0
               );
            }
         } else {
            this.DrawUVSliceTexture(
               this.foreground, 3.0, 0.0, this.foreground.getWidth(), this.foreground.getHeight(), Color.white, 0.0, 0.0, this.deltaValue, 1.0
            );
         }
      }
   }

    void setValue(float var1) {
      this.deltaValue = var1;
   }

    float getValue() {
      return this.deltaValue;
   }

    void update(int var1) {
      if (this.deltaValue == float.POSITIVE_INFINITY) {
         this.animationProgress = this.animationProgress + 0.02F * (GameTime.getInstance().getRealworldSecondsSinceLastUpdate() * 60.0F);
         if (this.animationProgress > 1.0F) {
            this.animationProgress = 0.0F;
         }

         this.setVisible(true);
         this.updateScreenPos(var1);
         this.delayHide = 2;
      } else {
         if (this.getValue() > 0.0F && this.getValue() < 1.0F) {
            this.setVisible(true);
            this.delayHide = 2;
         } else if (this.isVisible() && this.delayHide > 0 && --this.delayHide == 0) {
            this.setVisible(false);
         }

         if (!UIManager.VisibleAllUI) {
            this.setVisible(false);
         }

         if (this.isVisible()) {
            this.updateScreenPos(var1);
         }
      }
   }

    void updateScreenPos(int var1) {
    IsoPlayer var2 = IsoPlayer.players[var1];
      if (var2 != nullptr) {
    float var3 = IsoUtils.XToScreen(var2.getX(), var2.getY(), var2.getZ(), 0);
    float var4 = IsoUtils.YToScreen(var2.getX(), var2.getY(), var2.getZ(), 0);
         var3 = var3 - IsoCamera.getOffX() - var2.offsetX;
         var4 = var4 - IsoCamera.getOffY() - var2.offsetY;
         var4 -= 128 / (2 / Core.TileScale);
         var3 /= Core.getInstance().getZoom(var1);
         var4 /= Core.getInstance().getZoom(var1);
         var3 -= this.width / 2.0F;
         var4 -= this.height;
         if (var2.getUserNameHeight() > 0) {
            var4 -= var2.getUserNameHeight() + 2;
         }

         this.setX(var3 + this.offsetX);
         this.setY(var4 + this.offsetY);
      }
   }
}
} // namespace ui
} // namespace zombie
