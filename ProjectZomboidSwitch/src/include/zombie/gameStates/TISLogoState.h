#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameTime.h"
#include "zombie/core/Core.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/gameStates/GameStateMachine/StateAction.h"
#include "zombie/gameStates/TISLogoState/LogoElement.h"
#include "zombie/input/GameKeyboard.h"
#include "zombie/input/Mouse.h"
#include "zombie/ui/TextManager.h"
#include "zombie/ui/UIFont.h"
#include "zombie/ui/UIManager.h"

namespace zombie {
namespace gameStates {


class TISLogoState : public GameState {
public:
    float alpha = 0.0F;
    float alphaStep = 0.02F;
    float logoDisplayTime = 20.0F;
    int screenNumber = 1;
    int stage = 0;
    float targetAlpha = 0.0F;
    bool bNoRender = false;
    const LogoElement logoTIS = std::make_shared<LogoElement>("media/ui/TheIndieStoneLogo_Lineart_White.png");
    const LogoElement logoFMOD = std::make_shared<LogoElement>("media/ui/FMODLogo.png");
    const LogoElement logoGA = std::make_shared<LogoElement>("media/ui/GA-1280-white.png");
    const LogoElement logoNW = std::make_shared<LogoElement>("media/ui/NW_Logo_Combined.png");
    static const int SCREEN_TIS = 1;
    static const int SCREEN_OTHER = 2;
    static const int STAGE_FADING_IN_LOGO = 0;
    static const int STAGE_HOLDING_LOGO = 1;
    static const int STAGE_FADING_OUT_LOGO = 2;
    static const int STAGE_EXIT = 3;

    void enter() {
      UIManager.bSuspend = true;
      this.alpha = 0.0F;
      this.targetAlpha = 1.0F;
   }

    void exit() {
      UIManager.bSuspend = false;
   }

    void render() {
      if (this.bNoRender) {
         Core.getInstance().StartFrame();
         SpriteRenderer.instance
            .renderi(nullptr, 0, 0, Core.getInstance().getOffscreenWidth(0), Core.getInstance().getOffscreenHeight(0), 0.0F, 0.0F, 0.0F, 1.0F, nullptr);
         Core.getInstance().EndFrame();
      } else {
         Core.getInstance().StartFrame();
         Core.getInstance().EndFrame();
    bool var1 = UIManager.useUIFBO;
         UIManager.useUIFBO = false;
         Core.getInstance().StartFrameUI();
         SpriteRenderer.instance
            .renderi(nullptr, 0, 0, Core.getInstance().getOffscreenWidth(0), Core.getInstance().getOffscreenHeight(0), 0.0F, 0.0F, 0.0F, 1.0F, nullptr);
         if (this.screenNumber == 1) {
            this.logoTIS.centerOnScreen();
            this.logoTIS.render(this.alpha);
         }

         if (this.screenNumber == 2) {
            this.renderAttribution();
         }

         Core.getInstance().EndFrameUI();
         UIManager.useUIFBO = var1;
      }
   }

    void renderAttribution() {
    int var1 = Core.getInstance().getScreenWidth();
    int var2 = Core.getInstance().getScreenHeight();
    uint8_t var3 = 50;
    uint8_t var4 = 3;
    int var5 = (var2 - (var4 + 1) * var3) / 3;
    Texture var7 = this.logoGA.m_texture;
      if (var7 != nullptr && var7.isReady()) {
    int var8 = (int)((float)(var7.getWidth() * var5) / var7.getHeight());
    int var9 = (var1 - var8) / 2;
         this.logoGA.setPos(var9, var3);
         this.logoGA.setSize(var8, var5);
         this.logoGA.render(this.alpha);
      }

    int var6 = var3 + var5 + var3;
      var6 = (int)(var6 + var5 * 0.15F);
      var7 = this.logoNW.m_texture;
      if (var7 != nullptr && var7.isReady()) {
    float var20 = 0.5F;
    int var22 = (int)(var7.getWidth() * var20 * var5 / var7.getHeight());
    int var10 = (int)(var5 * var20);
    int var11 = (var1 - var22) / 2;
    int var12 = (var5 - var10) / 2;
         this.logoNW.setPos(var11, var6 + var12);
         this.logoNW.setSize(var22, var10);
         this.logoNW.render(this.alpha);
      }

      var6 += var5 + var3;
      var7 = this.logoFMOD.m_texture;
      if (var7 != nullptr && var7.isReady()) {
    float var21 = 0.35F;
    int var23 = TextManager.instance.getFontHeight(UIFont.Small);
    int var24 = (int)(var5 * var21 - 16.0F - var23);
    int var25 = (int)(var7.getWidth() * ((float)var24 / var7.getHeight()));
    int var26 = (var1 - var25) / 2;
    int var13 = (var5 - var24) / 2;
    int var14 = var6 + var13 + var24 + 16;
         this.logoFMOD.setPos(var26, var6 + var13);
         this.logoFMOD.setSize(var25, var24);
         this.logoFMOD.render(this.alpha);
    std::string var15 = "Made with FMOD Studio by Firelight Technologies Pty Ltd.";
         TextManager.instance.DrawStringCentre(var1 / 2.0, var14, var15, 1.0, 1.0, 1.0, this.alpha);
      }
   }

    StateAction update() {
      if (Mouse.isLeftDown() || GameKeyboard.isKeyDown(28) || GameKeyboard.isKeyDown(57) || GameKeyboard.isKeyDown(1)) {
         this.stage = 3;
      }

      if (this.stage == 0) {
         this.targetAlpha = 1.0F;
         if (this.alpha == 1.0F) {
            this.stage = 1;
            this.logoDisplayTime = 20.0F;
         }
      }

      if (this.stage == 1) {
         this.logoDisplayTime = this.logoDisplayTime - GameTime.getInstance().getMultiplier() / 1.6F;
         if (this.logoDisplayTime <= 0.0F) {
            this.stage = 2;
         }
      }

      if (this.stage == 2) {
         this.targetAlpha = 0.0F;
         if (this.alpha == 0.0F) {
            if (this.screenNumber == 1) {
               this.screenNumber = 2;
               this.stage = 0;
            } else {
               this.stage = 3;
            }
         }
      }

      if (this.stage == 3) {
         this.targetAlpha = 0.0F;
         if (this.alpha == 0.0F) {
            this.bNoRender = true;
            return StateAction.Continue;
         }
      }

      if (this.alpha < this.targetAlpha) {
         this.alpha = this.alpha + this.alphaStep * GameTime.getInstance().getMultiplier();
         if (this.alpha > this.targetAlpha) {
            this.alpha = this.targetAlpha;
         }
      } else if (this.alpha > this.targetAlpha) {
         this.alpha = this.alpha - this.alphaStep * GameTime.getInstance().getMultiplier();
         if (this.stage == 3) {
            this.alpha = this.alpha - this.alphaStep * GameTime.getInstance().getMultiplier();
         }

         if (this.alpha < this.targetAlpha) {
            this.alpha = this.targetAlpha;
         }
      }

      return StateAction.Remain;
   }
}
} // namespace gameStates
} // namespace zombie
