#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/textures/Texture.h"
#include "zombie/network/GameServer.h"

namespace zombie {
namespace ui {


class HUDButton : public UIElement {
public:
    bool clicked = false;
    UIElement display;
    Texture highlight;
    Texture overicon = nullptr;
    bool mouseOver = false;
    std::string name;
    Texture texture;
    UIEventHandler handler;
    float notclickedAlpha = 0.85F;
    float clickedalpha = 1.0F;

    public HUDButton(const std::string& var1, double var2, double var4, const std::string& var6, const std::string& var7, UIElement var8) {
      if (!GameServer.bServer) {
         this.display = var8;
         this.name = var1;
         if (this.texture == nullptr) {
            this.texture = Texture.getSharedTexture(var6);
            this.highlight = Texture.getSharedTexture(var7);
         }

         this.x = var2;
         this.y = var4;
         this.width = this.texture.getWidth();
         this.height = this.texture.getHeight();
      }
   }

    public HUDButton(const std::string& var1, float var2, float var3, const std::string& var4, const std::string& var5, UIEventHandler var6) {
      if (!GameServer.bServer) {
         this.texture = Texture.getSharedTexture(var4);
         this.highlight = Texture.getSharedTexture(var5);
         this.handler = var6;
         this.name = var1;
         if (this.texture == nullptr) {
            this.texture = Texture.getSharedTexture(var4);
            this.highlight = Texture.getSharedTexture(var5);
         }

         this.x = var2;
         this.y = var3;
         this.width = this.texture.getWidth();
         this.height = this.texture.getHeight();
      }
   }

    public HUDButton(const std::string& var1, float var2, float var3, const std::string& var4, const std::string& var5, const std::string& var6, UIElement var7) {
      if (!GameServer.bServer) {
         this.overicon = Texture.getSharedTexture(var6);
         this.display = var7;
         this.texture = Texture.getSharedTexture(var4);
         this.highlight = Texture.getSharedTexture(var5);
         this.name = var1;
         if (this.texture == nullptr) {
            this.texture = Texture.getSharedTexture(var4);
            this.highlight = Texture.getSharedTexture(var5);
         }

         this.x = var2;
         this.y = var3;
         this.width = this.texture.getWidth();
         this.height = this.texture.getHeight();
      }
   }

    public HUDButton(const std::string& var1, float var2, float var3, const std::string& var4, const std::string& var5, const std::string& var6, UIEventHandler var7) {
      if (!GameServer.bServer) {
         this.texture = Texture.getSharedTexture(var4);
         this.highlight = Texture.getSharedTexture(var5);
         this.overicon = Texture.getSharedTexture(var6);
         this.handler = var7;
         this.name = var1;
         if (this.texture == nullptr) {
            this.texture = Texture.getSharedTexture(var4);
            this.highlight = Texture.getSharedTexture(var5);
         }

         this.x = var2;
         this.y = var3;
         this.width = this.texture.getWidth();
         this.height = this.texture.getHeight();
      }
   }

    bool onMouseDown(double var1, double var3) {
      this.clicked = true;
      return bool.TRUE;
   }

    bool onMouseMove(double var1, double var3) {
      this.mouseOver = true;
      return bool.TRUE;
   }

    void onMouseMoveOutside(double var1, double var3) {
      this.clicked = false;
      if (this.display != nullptr) {
         if (!this.name == this.display.getClickedValue())) {
            this.mouseOver = false;
         }
      }
   }

    bool onMouseUp(double var1, double var3) {
      if (this.clicked) {
         if (this.display != nullptr) {
            this.display.ButtonClicked(this.name);
         } else if (this.handler != nullptr) {
            this.handler.Selected(this.name, 0, 0);
         }
      }

      this.clicked = false;
      return bool.TRUE;
   }

    void render() {
    int var1 = 0;
      if (this.clicked) {
         var1++;
      }

      if (!this.mouseOver && !this.name == this.display.getClickedValue())) {
         this.DrawTextureScaled(this.texture, 0.0, var1, this.getWidth(), this.getHeight(), this.notclickedAlpha);
      } else {
         this.DrawTextureScaled(this.highlight, 0.0, var1, this.getWidth(), this.getHeight(), this.clickedalpha);
      }

      if (this.overicon != nullptr) {
         this.DrawTextureScaled(this.overicon, 0.0, var1, this.overicon.getWidth(), this.overicon.getHeight(), 1.0);
      }

      super.render();
   }

    void update() {
      super.update();
   }
}
} // namespace ui
} // namespace zombie
