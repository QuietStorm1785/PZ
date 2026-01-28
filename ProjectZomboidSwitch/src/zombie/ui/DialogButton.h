#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/Lua/LuaManager.h"
#include "zombie/core/Color.h"
#include "zombie/core/textures/Texture.h"

namespace zombie {
namespace ui {


class DialogButton : public UIElement {
public:
    bool clicked = false;
    UIElement MessageTarget;
    bool mouseOver = false;
    std::string name;
    std::string text;
    Texture downLeft;
    Texture downMid;
    Texture downRight;
    float origX;
    Texture upLeft;
    Texture upMid;
    Texture upRight;
    UIEventHandler MessageTarget2 = nullptr;

    public DialogButton(UIElement var1, float var2, float var3, const std::string& var4, const std::string& var5) {
      this.x = var2;
      this.y = var3;
      this.origX = var2;
      this.MessageTarget = var1;
      this.upLeft = Texture.getSharedTexture("ButtonL_Up");
      this.upMid = Texture.getSharedTexture("ButtonM_Up");
      this.upRight = Texture.getSharedTexture("ButtonR_Up");
      this.downLeft = Texture.getSharedTexture("ButtonL_Down");
      this.downMid = Texture.getSharedTexture("ButtonM_Down");
      this.downRight = Texture.getSharedTexture("ButtonR_Down");
      this.name = var5;
      this.text = var4;
      this.width = TextManager.instance.MeasureStringX(UIFont.Small, var4);
      this.width += 8.0F;
      if (this.width < 40.0F) {
         this.width = 40.0F;
      }

      this.height = this.downMid.getHeight();
      this.x = this.x - this.width / 2.0F;
   }

    public DialogButton(UIEventHandler var1, int var2, int var3, const std::string& var4, const std::string& var5) {
      this.x = var2;
      this.y = var3;
      this.origX = var2;
      this.MessageTarget2 = var1;
      this.upLeft = Texture.getSharedTexture("ButtonL_Up");
      this.upMid = Texture.getSharedTexture("ButtonM_Up");
      this.upRight = Texture.getSharedTexture("ButtonR_Up");
      this.downLeft = Texture.getSharedTexture("ButtonL_Down");
      this.downMid = Texture.getSharedTexture("ButtonM_Down");
      this.downRight = Texture.getSharedTexture("ButtonR_Down");
      this.name = var5;
      this.text = var4;
      this.width = TextManager.instance.MeasureStringX(UIFont.Small, var4);
      this.width += 8.0F;
      if (this.width < 40.0F) {
         this.width = 40.0F;
      }

      this.height = this.downMid.getHeight();
      this.x = this.x - this.width / 2.0F;
   }

    bool onMouseDown(double var1, double var3) {
      if (!this.isVisible()) {
    return false;
      } else {
         if (this.getTable() != nullptr && this.getTable().rawget("onMouseDown") != nullptr) {
            Object[] var5 = LuaManager.caller.pcall(LuaManager.thread, this.getTable().rawget("onMouseDown"), new Object[]{this.table, var1, var3});
         }

         this.clicked = true;
         return bool.TRUE;
      }
   }

    bool onMouseMove(double var1, double var3) {
      this.mouseOver = true;
      if (this.getTable() != nullptr && this.getTable().rawget("onMouseMove") != nullptr) {
         Object[] var5 = LuaManager.caller.pcall(LuaManager.thread, this.getTable().rawget("onMouseMove"), new Object[]{this.table, var1, var3});
      }

      return bool.TRUE;
   }

    void onMouseMoveOutside(double var1, double var3) {
      this.clicked = false;
      if (this.getTable() != nullptr && this.getTable().rawget("onMouseMoveOutside") != nullptr) {
         Object[] var5 = LuaManager.caller.pcall(LuaManager.thread, this.getTable().rawget("onMouseMoveOutside"), new Object[]{this.table, var1, var3});
      }

      this.mouseOver = false;
   }

    bool onMouseUp(double var1, double var3) {
      if (this.getTable() != nullptr && this.getTable().rawget("onMouseUp") != nullptr) {
         Object[] var5 = LuaManager.caller.pcall(LuaManager.thread, this.getTable().rawget("onMouseUp"), new Object[]{this.table, var1, var3});
      }

      if (this.clicked) {
         if (this.MessageTarget2 != nullptr) {
            this.MessageTarget2.Selected(this.name, 0, 0);
         } else if (this.MessageTarget != nullptr) {
            this.MessageTarget.ButtonClicked(this.name);
         }
      }

      this.clicked = false;
      return bool.TRUE;
   }

    void ImGuiRender() override;
    void render() override { ImGuiRender(); }
}
} // namespace ui
} // namespace zombie
