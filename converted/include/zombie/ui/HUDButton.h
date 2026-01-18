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
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


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

 public HUDButton(const std::string& _name, double x, double y, const std::string& _texture, const std::string& _highlight, UIElement _display) {
 if (!GameServer.bServer) {
 this->display = _display;
 this->name = _name;
 if (this->texture.empty()) {
 this->texture = Texture.getSharedTexture(_texture);
 this->highlight = Texture.getSharedTexture(_highlight);
 }

 this->x = x;
 this->y = y;
 this->width = this->texture.getWidth();
 this->height = this->texture.getHeight();
 }
 }

 public HUDButton(const std::string& _name, float x, float y, const std::string& _texture, const std::string& _highlight, UIEventHandler _handler) {
 if (!GameServer.bServer) {
 this->texture = Texture.getSharedTexture(_texture);
 this->highlight = Texture.getSharedTexture(_highlight);
 this->handler = _handler;
 this->name = _name;
 if (this->texture.empty()) {
 this->texture = Texture.getSharedTexture(_texture);
 this->highlight = Texture.getSharedTexture(_highlight);
 }

 this->x = x;
 this->y = y;
 this->width = this->texture.getWidth();
 this->height = this->texture.getHeight();
 }
 }

 public HUDButton(const std::string& _name, float x, float y, const std::string& _texture, const std::string& _highlight, const std::string& _overicon, UIElement _display) {
 if (!GameServer.bServer) {
 this->overicon = Texture.getSharedTexture(_overicon);
 this->display = _display;
 this->texture = Texture.getSharedTexture(_texture);
 this->highlight = Texture.getSharedTexture(_highlight);
 this->name = _name;
 if (this->texture.empty()) {
 this->texture = Texture.getSharedTexture(_texture);
 this->highlight = Texture.getSharedTexture(_highlight);
 }

 this->x = x;
 this->y = y;
 this->width = this->texture.getWidth();
 this->height = this->texture.getHeight();
 }
 }

 public HUDButton(const std::string& _name, float x, float y, const std::string& _texture, const std::string& _highlight, const std::string& _overicon, UIEventHandler _handler) {
 if (!GameServer.bServer) {
 this->texture = Texture.getSharedTexture(_texture);
 this->highlight = Texture.getSharedTexture(_highlight);
 this->overicon = Texture.getSharedTexture(_overicon);
 this->handler = _handler;
 this->name = _name;
 if (this->texture.empty()) {
 this->texture = Texture.getSharedTexture(_texture);
 this->highlight = Texture.getSharedTexture(_highlight);
 }

 this->x = x;
 this->y = y;
 this->width = this->texture.getWidth();
 this->height = this->texture.getHeight();
 }
 }

 bool onMouseDown(double x, double y) {
 this->clicked = true;
 return Boolean.TRUE;
 }

 bool onMouseMove(double dx, double dy) {
 this->mouseOver = true;
 return Boolean.TRUE;
 }

 void onMouseMoveOutside(double dx, double dy) {
 this->clicked = false;
 if (this->display != nullptr) {
 if (!this->name == this->display.getClickedValue())) {
 this->mouseOver = false;
 }
 }
 }

 bool onMouseUp(double x, double y) {
 if (this->clicked) {
 if (this->display != nullptr) {
 this->display.ButtonClicked(this->name);
 } else if (this->handler != nullptr) {
 this->handler.Selected(this->name, 0, 0);
 }
 }

 this->clicked = false;
 return Boolean.TRUE;
 }

 void render() {
 int int0 = 0;
 if (this->clicked) {
 int0++;
 }

 if (!this->mouseOver && !this->name == this->display.getClickedValue())) {
 this->DrawTextureScaled(this->texture, 0.0, int0, this->getWidth(), this->getHeight(), this->notclickedAlpha);
 } else {
 this->DrawTextureScaled(this->highlight, 0.0, int0, this->getWidth(), this->getHeight(), this->clickedalpha);
 }

 if (this->overicon != nullptr) {
 this->DrawTextureScaled(this->overicon, 0.0, int0, this->overicon.getWidth(), this->overicon.getHeight(), 1.0);
 }

 super.render();
 }

 void update() {
 super.update();
 }
}
} // namespace ui
} // namespace zombie
