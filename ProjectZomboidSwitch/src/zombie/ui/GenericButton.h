#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/Lua/LuaManager.h"
#include "zombie/core/textures/Texture.h"

namespace zombie {
namespace ui {


class GenericButton : public UIElement {
public:
    bool clicked = false;
    UIElement MessageTarget;
    bool mouseOver = false;
    std::string name;
    std::string text;
    Texture UpTexture = nullptr;
    Texture DownTexture = nullptr;
    UIEventHandler MessageTarget2 = nullptr;

    public GenericButton(UIElement var1, float var2, float var3, float var4, float var5, const std::string& var6, const std::string& var7, Texture var8, Texture var9) {
      this.x = var2;
      this.y = var3;
      this.MessageTarget = var1;
      this.name = var6;
      this.text = var7;
      this.width = var4;
      this.height = var5;
      this.UpTexture = var8;
      this.DownTexture = var9;
   }

    public GenericButton(UIEventHandler var1, float var2, float var3, float var4, float var5, const std::string& var6, const std::string& var7, Texture var8, Texture var9) {
      this.x = var2;
      this.y = var3;
      this.MessageTarget2 = var1;
      this.name = var6;
      this.text = var7;
      this.width = var4;
      this.height = var5;
      this.UpTexture = var8;
      this.DownTexture = var9;
   }

    bool onMouseDown(double var1, double var3) {
      if (!this.isVisible()) {
         return bool.FALSE;
      } else {
         if (this.getTable() != nullptr && this.getTable().rawget("onMouseDown") != nullptr) {
            Object[] var5 = LuaManager.caller.pcall(LuaManager.thread, this.getTable().rawget("onMouseDown"), new Object[]{this.table, var1, var3});
         }

         this.clicked = true;
         return bool.TRUE;
      }
   }

    bool onMouseMove(double var1, double var3) {
      if (this.getTable() != nullptr && this.getTable().rawget("onMouseMove") != nullptr) {
         Object[] var5 = LuaManager.caller.pcall(LuaManager.thread, this.getTable().rawget("onMouseMove"), new Object[]{this.table, var1, var3});
      }

      this.mouseOver = true;
      return bool.TRUE;
   }

    void onMouseMoveOutside(double var1, double var3) {
      if (this.getTable() != nullptr && this.getTable().rawget("onMouseMoveOutside") != nullptr) {
         Object[] var5 = LuaManager.caller.pcall(LuaManager.thread, this.getTable().rawget("onMouseMoveOutside"), new Object[]{this.table, var1, var3});
      }

      this.clicked = false;
      this.mouseOver = false;
   }

    bool onMouseUp(double var1, double var3) {
      if (this.getTable() != nullptr && this.getTable().rawget("onMouseUp") != nullptr) {
         Object[] var5 = LuaManager.caller.pcall(LuaManager.thread, this.getTable().rawget("onMouseUp"), new Object[]{this.table, var1, var3});
      }

      if (this.clicked) {
         if (this.MessageTarget2 != nullptr) {
            this.MessageTarget2.Selected(this.name, 0, 0);
         } else {
            this.MessageTarget.ButtonClicked(this.name);
         }
      }

      this.clicked = false;
      return bool.TRUE;
   }

    void render() {
      if (this.isVisible()) {
    bool var1 = false;
         if (this.clicked) {
            this.DrawTextureScaled(this.DownTexture, 0.0, 0.0, this.getWidth(), this.getHeight(), 1.0);
            this.DrawTextCentre(this.text, this.getWidth() / 2.0, 1.0, 1.0, 1.0, 1.0, 1.0);
         } else {
            this.DrawTextureScaled(this.UpTexture, 0.0, 0.0, this.getWidth(), this.getHeight(), 1.0);
            this.DrawTextCentre(this.text, this.getWidth() / 2.0, 1.0, 1.0, 1.0, 1.0, 1.0);
         }

         super.render();
      }
   }
}
} // namespace ui
} // namespace zombie
