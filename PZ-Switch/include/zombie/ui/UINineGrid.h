#pragma once
#include "java/awt/Rectangle.h"
#include "zombie/core/Color.h"
#include "zombie/core/textures/Texture.h"
#include <algorithm>
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

class UINineGrid : public UIElement {
public:
 Texture GridTopLeft = nullptr;
 Texture GridTop = nullptr;
 Texture GridTopRight = nullptr;
 Texture GridLeft = nullptr;
 Texture GridCenter = nullptr;
 Texture GridRight = nullptr;
 Texture GridBottomLeft = nullptr;
 Texture GridBottom = nullptr;
 Texture GridBottomRight = nullptr;
 int TopWidth = 10;
 int LeftWidth = 10;
 int RightWidth = 10;
 int BottomWidth = 10;
 int clientH = 0;
 int clientW = 0;
public
 Stack<Rectangle> nestedItems = std::make_unique<Stack<>>();
 Color Colour = new Color(50, 50, 50, 212);

public
 UINineGrid(int x, int y, int width, int height, int _TopWidth, int _LeftWidth,
 int _RightWidth, int _BottomWidth, String TL_Tex, String T_Tex,
 String TR_Tex, String L_Tex, String C_Tex, String R_Tex,
 String BL_Tex, String B_Tex, String BR_Tex) {
 this->x = x;
 this->y = y;
 this->width = width;
 this->height = height;
 this->TopWidth = _TopWidth;
 this->LeftWidth = _LeftWidth;
 this->RightWidth = _RightWidth;
 this->BottomWidth = _BottomWidth;
 this->GridTopLeft = Texture.getSharedTexture(TL_Tex);
 this->GridTop = Texture.getSharedTexture(T_Tex);
 this->GridTopRight = Texture.getSharedTexture(TR_Tex);
 this->GridLeft = Texture.getSharedTexture(L_Tex);
 this->GridCenter = Texture.getSharedTexture(C_Tex);
 this->GridRight = Texture.getSharedTexture(R_Tex);
 this->GridBottomLeft = Texture.getSharedTexture(BL_Tex);
 this->GridBottom = Texture.getSharedTexture(B_Tex);
 this->GridBottomRight = Texture.getSharedTexture(BR_Tex);
 this->clientW = width;
 this->clientH = height;
 }

 void Nest(UIElement el, int t, int r, int b, int l) {
 this->AddChild(el);
 this->nestedItems.add(new Rectangle(l, t, r, b);
 el.setX(l);
 el.setY(t);
 el.update();
 }

 void render() {
 this->DrawTextureScaledCol(this->GridTopLeft, 0.0, 0.0, this->LeftWidth,
 this->TopWidth, this->Colour);
 this->DrawTextureScaledCol(this->GridTop, this->LeftWidth, 0.0,
 this->getWidth() -
 (this->LeftWidth + this->RightWidth),
 this->TopWidth, this->Colour);
 this->DrawTextureScaledCol(this->GridTopRight,
 this->getWidth() - this->RightWidth, 0.0,
 this->RightWidth, this->TopWidth, this->Colour);
 this->DrawTextureScaledCol(
 this->GridLeft, 0.0, this->TopWidth, this->LeftWidth,
 this->getHeight() - (this->TopWidth + this->BottomWidth), this->Colour);
 this->DrawTextureScaledCol(
 this->GridCenter, this->LeftWidth, this->TopWidth,
 this->getWidth() - (this->LeftWidth + this->RightWidth),
 this->getHeight() - (this->TopWidth + this->BottomWidth), this->Colour);
 this->DrawTextureScaledCol(
 this->GridRight, this->getWidth() - this->RightWidth, this->TopWidth,
 this->RightWidth, this->getHeight() - (this->TopWidth + this->BottomWidth),
 this->Colour);
 this->DrawTextureScaledCol(this->GridBottomLeft, 0.0,
 this->getHeight() - this->BottomWidth,
 this->LeftWidth, this->BottomWidth, this->Colour);
 this->DrawTextureScaledCol(
 this->GridBottom, this->LeftWidth, this->getHeight() - this->BottomWidth,
 this->getWidth() - (this->LeftWidth + this->RightWidth), this->BottomWidth,
 this->Colour);
 this->DrawTextureScaledCol(this->GridBottomRight,
 this->getWidth() - this->RightWidth,
 this->getHeight() - this->BottomWidth,
 this->RightWidth, this->BottomWidth, this->Colour);
 super.render();
 }

 void update() {
 super.update();
 int int0 = 0;

 for (Rectangle rectangle : this->nestedItems) {
 UIElement uIElement = this->getControls().get(int0);
 uIElement.setX((float)rectangle.getX());
 uIElement.setY((float)rectangle.getY());
 uIElement.setWidth(
 (int)(this->clientW - (rectangle.getX() + rectangle.getWidth())));
 uIElement.setHeight(
 (int)(this->clientH - (rectangle.getY() + rectangle.getHeight())));
 uIElement.onresize();
 int0++;
 }
 }

 void setAlpha(float alpha) { this->Colour.a = alpha; }

 float getAlpha() { return this->Colour.a; }
}
} // namespace ui
} // namespace zombie
