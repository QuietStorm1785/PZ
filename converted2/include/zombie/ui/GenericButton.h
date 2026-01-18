#pragma once
#include "zombie/Lua/LuaManager.h"
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

class GenericButton : public UIElement {
public:
  bool clicked = false;
  UIElement MessageTarget;
  bool mouseOver = false;
  std::string name;
  std::string text;
  Texture UpTexture = nullptr;
  Texture DownTexture = nullptr;
  UIEventHandler MessageTarget2 = null;

public
  GenericButton(UIElement uIElement, float float0, float float1, float float2,
                float float3, String string0, String string1, Texture texture0,
                Texture texture1) {
    this.x = float0;
    this.y = float1;
    this.MessageTarget = uIElement;
    this.name = string0;
    this.text = string1;
    this.width = float2;
    this.height = float3;
    this.UpTexture = texture0;
    this.DownTexture = texture1;
  }

public
  GenericButton(UIEventHandler uIEventHandler, float float0, float float1,
                float float2, float float3, String string0, String string1,
                Texture texture0, Texture texture1) {
    this.x = float0;
    this.y = float1;
    this.MessageTarget2 = uIEventHandler;
    this.name = string0;
    this.text = string1;
    this.width = float2;
    this.height = float3;
    this.UpTexture = texture0;
    this.DownTexture = texture1;
  }

  bool onMouseDown(double double1, double double0) {
    if (!this.isVisible()) {
      return Boolean.FALSE;
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
    if (this.getTable() != nullptr &&
        this.getTable().rawget("onMouseMove") != nullptr) {
      Object[] objects = LuaManager.caller.pcall(
          LuaManager.thread, this.getTable().rawget("onMouseMove"), this.table,
          double1, double0);
    }

    this.mouseOver = true;
    return Boolean.TRUE;
  }

  void onMouseMoveOutside(double double1, double double0) {
    if (this.getTable() != nullptr &&
        this.getTable().rawget("onMouseMoveOutside") != nullptr) {
      Object[] objects = LuaManager.caller.pcall(
          LuaManager.thread, this.getTable().rawget("onMouseMoveOutside"),
          this.table, double1, double0);
    }

    this.clicked = false;
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
      } else {
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
        this.DrawTextureScaled(this.DownTexture, 0.0, 0.0, this.getWidth(),
                               this.getHeight(), 1.0);
        this.DrawTextCentre(this.text, this.getWidth() / 2.0, 1.0, 1.0, 1.0,
                            1.0, 1.0);
      } else {
        this.DrawTextureScaled(this.UpTexture, 0.0, 0.0, this.getWidth(),
                               this.getHeight(), 1.0);
        this.DrawTextCentre(this.text, this.getWidth() / 2.0, 1.0, 1.0, 1.0,
                            1.0, 1.0);
      }

      super.render();
    }
  }
}
} // namespace ui
} // namespace zombie
