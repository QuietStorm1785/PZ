#pragma once
#include "zombie/Lua/LuaManager.h"
#include "zombie/core/Color.h"
#include "zombie/core/textures/Texture.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace ui {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

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
  UIEventHandler MessageTarget2 = null;

public
  DialogButton(UIElement uIElement, float float0, float float1,
               const std::string &string1, const std::string &string0) {
    this.x = float0;
    this.y = float1;
    this.origX = float0;
    this.MessageTarget = uIElement;
    this.upLeft = Texture.getSharedTexture("ButtonL_Up");
    this.upMid = Texture.getSharedTexture("ButtonM_Up");
    this.upRight = Texture.getSharedTexture("ButtonR_Up");
    this.downLeft = Texture.getSharedTexture("ButtonL_Down");
    this.downMid = Texture.getSharedTexture("ButtonM_Down");
    this.downRight = Texture.getSharedTexture("ButtonR_Down");
    this.name = string0;
    this.text = string1;
    this.width = TextManager.instance.MeasureStringX(UIFont.Small, string1);
    this.width += 8.0F;
    if (this.width < 40.0F) {
      this.width = 40.0F;
    }

    this.height = this.downMid.getHeight();
    this.x = this.x - this.width / 2.0F;
  }

public
  DialogButton(UIEventHandler uIEventHandler, int int0, int int1,
               const std::string &string1, const std::string &string0) {
    this.x = int0;
    this.y = int1;
    this.origX = int0;
    this.MessageTarget2 = uIEventHandler;
    this.upLeft = Texture.getSharedTexture("ButtonL_Up");
    this.upMid = Texture.getSharedTexture("ButtonM_Up");
    this.upRight = Texture.getSharedTexture("ButtonR_Up");
    this.downLeft = Texture.getSharedTexture("ButtonL_Down");
    this.downMid = Texture.getSharedTexture("ButtonM_Down");
    this.downRight = Texture.getSharedTexture("ButtonR_Down");
    this.name = string0;
    this.text = string1;
    this.width = TextManager.instance.MeasureStringX(UIFont.Small, string1);
    this.width += 8.0F;
    if (this.width < 40.0F) {
      this.width = 40.0F;
    }

    this.height = this.downMid.getHeight();
    this.x = this.x - this.width / 2.0F;
  }

  bool onMouseDown(double double1, double double0) {
    if (!this.isVisible()) {
      return false;
    } else {
      if (this.getTable() != nullptr &&
          this.getTable().rawget("onMouseDown") != nullptr) {
        Object[] objects = LuaManager.caller.pcall(
            LuaManager.thread, this.getTable().rawget("onMouseDown"),
            this.table, double1, double0);
      }

      this.clicked = true;
      return Boolean.TRUE;
    }
  }

  bool onMouseMove(double double1, double double0) {
    this.mouseOver = true;
    if (this.getTable() != nullptr &&
        this.getTable().rawget("onMouseMove") != nullptr) {
      Object[] objects = LuaManager.caller.pcall(
          LuaManager.thread, this.getTable().rawget("onMouseMove"), this.table,
          double1, double0);
    }

    return Boolean.TRUE;
  }

  void onMouseMoveOutside(double double1, double double0) {
    this.clicked = false;
    if (this.getTable() != nullptr &&
        this.getTable().rawget("onMouseMoveOutside") != nullptr) {
      Object[] objects = LuaManager.caller.pcall(
          LuaManager.thread, this.getTable().rawget("onMouseMoveOutside"),
          this.table, double1, double0);
    }

    this.mouseOver = false;
  }

  bool onMouseUp(double double1, double double0) {
    if (this.getTable() != nullptr &&
        this.getTable().rawget("onMouseUp") != nullptr) {
      Object[] objects = LuaManager.caller.pcall(
          LuaManager.thread, this.getTable().rawget("onMouseUp"), this.table,
          double1, double0);
    }

    if (this.clicked) {
      if (this.MessageTarget2 != nullptr) {
        this.MessageTarget2.Selected(this.name, 0, 0);
      } else if (this.MessageTarget != nullptr) {
        this.MessageTarget.ButtonClicked(this.name);
      }
    }

    this.clicked = false;
    return Boolean.TRUE;
  }

  void render() {
    if (this.isVisible()) {
      bool boolean0 = false;
      if (this.clicked) {
        this.DrawTexture(this.downLeft, 0.0, 0.0, 1.0);
        this.DrawTextureScaledCol(
            this.downMid, this.downLeft.getWidth(), 0.0,
            (int)(this.getWidth() - this.downLeft.getWidth() * 2),
            this.downLeft.getHeight(), new Color(););
        this.DrawTexture(this.downRight,
                         (int)(this.getWidth() - this.downRight.getWidth()),
                         0.0, 1.0);
        this.DrawTextCentre(this.text, this.getWidth() / 2.0, 1.0, 1.0, 1.0,
                            1.0, 1.0);
      } else {
        this.DrawTexture(this.upLeft, 0.0, 0.0, 1.0);
        this.DrawTextureScaledCol(
            this.upMid, this.downLeft.getWidth(), 0.0,
            (int)(this.getWidth() - this.downLeft.getWidth() * 2),
            this.downLeft.getHeight(), new Color(););
        this.DrawTexture(this.upRight,
                         (int)(this.getWidth() - this.downRight.getWidth()),
                         0.0, 1.0);
        this.DrawTextCentre(this.text, this.getWidth() / 2.0, 0.0, 1.0, 1.0,
                            1.0, 1.0);
      }

      super.render();
    }
  }
}
} // namespace ui
} // namespace zombie
