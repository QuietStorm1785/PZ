#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/IndieGL.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/core/BoxedStaticValues.h"
#include "zombie/core/Color.h"
#include "zombie/core/Core.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/input/Mouse.h"

namespace zombie {
namespace ui {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class UIElement {
public:
 static const Color tempcol = new Color(0, 0, 0, 0);
 static ArrayList<UIElement> toAdd = new ArrayList<>(0);
 static Texture white;
 static int StencilLevel = 0;
 bool capture = false;
 bool IgnoreLossControl = false;
 std::string clickedValue = nullptr;
 public ArrayList<UIElement> Controls = std::make_unique<ArrayList<>>();
 bool defaultDraw = true;
 bool followGameWorld = false;
 int renderThisPlayerOnly = -1;
 float height = 256.0F;
 UIElement Parent = nullptr;
 bool visible = true;
 float width = 256.0F;
 double x = 0.0;
 double y = 0.0;
 KahluaTable table;
 bool alwaysBack;
 bool bScrollChildren = false;
 bool bScrollWithParent = true;
 bool bRenderClippedChildren = true;
 bool anchorTop = true;
 bool anchorLeft = true;
 bool anchorRight = false;
 bool anchorBottom = false;
 int playerContext = -1;
 bool alwaysOnTop = false;
 int maxDrawHeight = -1;
 double yScroll = 0.0;
 double xScroll = 0.0;
 int scrollHeight = 0;
 double lastheight = -1.0;
 double lastwidth = -1.0;
 bool bResizeDirty = false;
 bool enabled = true;
 private ArrayList<UIElement> toTop = new ArrayList<>(0);
 bool bConsumeMouseEvents = true;
 long leftDownTime = 0L;
 bool clicked;
 double clickX;
 double clickY;
 std::string uiname = "";
 bool bWantKeyEvents = false;
 bool bForceCursorVisible = false;

 public UIElement() {
 }

 public UIElement(KahluaTable _table) {
 this->table = _table;
 }

 double getMaxDrawHeight() {
 return BoxedStaticValues.toDouble(this->maxDrawHeight);
 }

 void setMaxDrawHeight(double _height) {
 this->maxDrawHeight = (int)_height;
 }

 void clearMaxDrawHeight() {
 this->maxDrawHeight = -1;
 }

 double getXScroll() {
 return this->xScroll;
 }

 void setXScroll(double _x) {
 this->xScroll = _x;
 }

 double getYScroll() {
 return this->yScroll;
 }

 void setYScroll(double _y) {
 this->yScroll = _y;
 }

 void setAlwaysOnTop(bool b) {
 this->alwaysOnTop = b;
 }

 void backMost() {
 this->alwaysBack = true;
 }

 void AddChild(UIElement el) {
 this->getControls().add(el);
 el.setParent(this);
 }

 void RemoveChild(UIElement el) {
 this->getControls().remove(el);
 el.setParent(nullptr);
 }

 double getScrollHeight() {
 return BoxedStaticValues.toDouble(this->scrollHeight);
 }

 void setScrollHeight(double h) {
 this->scrollHeight = (int)h;
 }

 bool isConsumeMouseEvents() {
 return this->bConsumeMouseEvents;
 }

 void setConsumeMouseEvents(bool bConsume) {
 this->bConsumeMouseEvents = bConsume;
 }

 void ClearChildren() {
 this->getControls().clear();
 }

 void ButtonClicked(const std::string& name) {
 this->setClickedValue(name);
 }

 void DrawText(UIFont font, const std::string& text, double _x, double _y, double zoom, double r, double g, double b, double alpha) {
 TextManager.instance
 .DrawString(font, _x + this->getAbsoluteX() + this->xScroll, _y + this->getAbsoluteY() + this->yScroll, (float)zoom, text, r, g, b, alpha);
 }

 void DrawText(const std::string& text, double _x, double _y, double r, double g, double b, double alpha) {
 TextManager.instance.DrawString(_x + this->getAbsoluteX() + this->xScroll, _y + this->getAbsoluteY() + this->yScroll, text, r, g, b, alpha);
 }

 void DrawText(const std::string& text, double _x, double _y, double _width, double _height, double r, double g, double b, double alpha) {
 TextManager.instance.DrawString(_x + this->getAbsoluteX() + this->xScroll, _y + this->getAbsoluteY() + this->yScroll, text, r, g, b, alpha);
 }

 void DrawText(UIFont font, const std::string& text, double _x, double _y, double r, double g, double b, double alpha) {
 if (text != nullptr) {
 int int0 = (int)(_y + this->getAbsoluteY() + this->yScroll);
 if (int0 + 100 >= 0 && int0 <= 4096) {
 TextManager.instance.DrawString(font, _x + this->getAbsoluteX() + this->xScroll, _y + this->getAbsoluteY() + this->yScroll, text, r, g, b, alpha);
 }
 }
 }

 void DrawTextUntrimmed(UIFont font, const std::string& text, double _x, double _y, double r, double g, double b, double alpha) {
 if (text != nullptr) {
 TextManager.instance
 .DrawStringUntrimmed(font, _x + this->getAbsoluteX() + this->xScroll, _y + this->getAbsoluteY() + this->yScroll, text, r, g, b, alpha);
 }
 }

 void DrawTextCentre(const std::string& text, double _x, double _y, double r, double g, double b, double alpha) {
 TextManager.instance.DrawStringCentre(_x + this->getAbsoluteX() + this->xScroll, _y + this->getAbsoluteY() + this->yScroll, text, r, g, b, alpha);
 }

 void DrawTextCentre(UIFont font, const std::string& text, double _x, double _y, double r, double g, double b, double alpha) {
 TextManager.instance.DrawStringCentre(font, _x + this->getAbsoluteX() + this->xScroll, _y + this->getAbsoluteY() + this->yScroll, text, r, g, b, alpha);
 }

 void DrawTextRight(const std::string& text, double _x, double _y, double r, double g, double b, double alpha) {
 TextManager.instance.DrawStringRight(_x + this->getAbsoluteX() + this->xScroll, _y + this->getAbsoluteY() + this->yScroll, text, r, g, b, alpha);
 }

 void DrawTextRight(UIFont font, const std::string& text, double _x, double _y, double r, double g, double b, double alpha) {
 TextManager.instance.DrawStringRight(font, _x + this->getAbsoluteX() + this->xScroll, _y + this->getAbsoluteY() + this->yScroll, text, r, g, b, alpha);
 }

 void DrawTextureAngle(Texture tex, double centerX, double centerY, double angle, double r, double g, double b, double a) {
 if (this->isVisible()) {
 float float0 = tex.getWidth() / 2;
 float float1 = tex.getHeight() / 2;
 double double0 = Math.toRadians(180.0 + angle);
 double double1 = Math.cos(double0) * float0;
 double double2 = Math.sin(double0) * float0;
 double double3 = Math.cos(double0) * float1;
 double double4 = Math.sin(double0) * float1;
 double double5 = double1 - double4;
 double double6 = double3 + double2;
 double double7 = -double1 - double4;
 double double8 = double3 - double2;
 double double9 = -double1 + double4;
 double double10 = -double3 - double2;
 double double11 = double1 + double4;
 double double12 = -double3 + double2;
 double5 += this->getAbsoluteX() + centerX;
 double6 += this->getAbsoluteY() + centerY;
 double7 += this->getAbsoluteX() + centerX;
 double8 += this->getAbsoluteY() + centerY;
 double9 += this->getAbsoluteX() + centerX;
 double10 += this->getAbsoluteY() + centerY;
 double11 += this->getAbsoluteX() + centerX;
 double12 += this->getAbsoluteY() + centerY;
 SpriteRenderer.instance
 .render(
 tex,
 double5,
 double6,
 double7,
 double8,
 double9,
 double10,
 double11,
 double12,
 (float)r,
 (float)g,
 (float)b,
 (float)a,
 (float)r,
 (float)g,
 (float)b,
 (float)a,
 (float)r,
 (float)g,
 (float)b,
 (float)a,
 (float)r,
 (float)g,
 (float)b,
 (float)a,
 nullptr
 );
 }
 }

 void DrawTextureAngle(Texture tex, double centerX, double centerY, double angle) {
 this->DrawTextureAngle(tex, centerX, centerY, angle, 1.0, 1.0, 1.0, 1.0);
 }

 public void DrawTexture(
 Texture tex, double tlx, double tly, double trx, double try2, double brx, double bry, double blx, double bly, double r, double g, double b, double a
 ) {
 SpriteRenderer.instance
 .render(
 tex,
 tlx,
 tly,
 trx,
 try2,
 brx,
 bry,
 blx,
 bly,
 (float)r,
 (float)g,
 (float)b,
 (float)a,
 (float)r,
 (float)g,
 (float)b,
 (float)a,
 (float)r,
 (float)g,
 (float)b,
 (float)a,
 (float)r,
 (float)g,
 (float)b,
 (float)a,
 nullptr
 );
 }

 void DrawTexture(Texture tex, double _x, double _y, double alpha) {
 if (this->isVisible()) {
 double double0 = _x + this->getAbsoluteX();
 double double1 = _y + this->getAbsoluteY();
 double0 += tex.offsetX;
 double1 += tex.offsetY;
 int int0 = (int)(double1 + this->yScroll);
 if (int0 + tex.getHeight() >= 0 && int0 <= 4096) {
 SpriteRenderer.instance
 .renderi(
 tex,
 (int)(double0 + this->xScroll),
 (int)(double1 + this->yScroll),
 tex.getWidth(),
 tex.getHeight(),
 1.0F,
 1.0F,
 1.0F,
 (float)alpha,
 nullptr
 );
 }
 }
 }

 void DrawTextureCol(Texture tex, double _x, double _y, Color col) {
 if (this->isVisible()) {
 double double0 = _x + this->getAbsoluteX();
 double double1 = _y + this->getAbsoluteY();
 int int0 = 0;
 int int1 = 0;
 if (tex != nullptr) {
 double0 += tex.offsetX;
 double1 += tex.offsetY;
 int0 = tex.getWidth();
 int1 = tex.getHeight();
 }

 int int2 = (int)(double1 + this->yScroll);
 if (int2 + int1 >= 0 && int2 <= 4096) {
 SpriteRenderer.instance
 .renderi(tex, (int)(double0 + this->xScroll), (int)(double1 + this->yScroll), int0, int1, col.r, col.g, col.b, col.a, nullptr);
 }
 }
 }

 void DrawTextureScaled(Texture tex, double _x, double _y, double _width, double _height, double alpha) {
 if (this->isVisible()) {
 double double0 = _x + this->getAbsoluteX();
 double double1 = _y + this->getAbsoluteY();
 SpriteRenderer.instance
 .renderi(tex, (int)(double0 + this->xScroll), (int)(double1 + this->yScroll), (int)_width, (int)_height, 1.0F, 1.0F, 1.0F, (float)alpha, nullptr);
 }
 }

 void DrawTextureScaledUniform(Texture tex, double _x, double _y, double scale, double r, double g, double b, double alpha) {
 if (this->isVisible() && tex != nullptr) {
 double double0 = _x + this->getAbsoluteX();
 double double1 = _y + this->getAbsoluteY();
 double0 += tex.offsetX * scale;
 double1 += tex.offsetY * scale;
 SpriteRenderer.instance
 .renderi(
 tex,
 (int)(double0 + this->xScroll),
 (int)(double1 + this->yScroll),
 (int)(tex.getWidth() * scale),
 (int)(tex.getHeight() * scale),
 (float)r,
 (float)g,
 (float)b,
 (float)alpha,
 nullptr
 );
 }
 }

 void DrawTextureScaledAspect(Texture tex, double _x, double _y, double _width, double _height, double r, double g, double b, double alpha) {
 if (this->isVisible() && tex != nullptr) {
 double double0 = _x + this->getAbsoluteX();
 double double1 = _y + this->getAbsoluteY();
 if (tex.getWidth() > 0 && tex.getHeight() > 0 && _width > 0.0 && _height > 0.0) {
 double double2 = Math.min(_width / tex.getWidthOrig(), _height / tex.getHeightOrig());
 double double3 = _width;
 double double4 = _height;
 _width = tex.getWidth() * double2;
 _height = tex.getHeight() * double2;
 double0 -= (_width - double3) / 2.0;
 double1 -= (_height - double4) / 2.0;
 }

 SpriteRenderer.instance
 .renderi(
 tex,
 (int)(double0 + this->xScroll),
 (int)(double1 + this->yScroll),
 (int)_width,
 (int)_height,
 (float)r,
 (float)g,
 (float)b,
 (float)alpha,
 nullptr
 );
 }
 }

 void DrawTextureScaledAspect2(Texture tex, double _x, double _y, double _width, double _height, double r, double g, double b, double alpha) {
 if (this->isVisible() && tex != nullptr) {
 double double0 = _x + this->getAbsoluteX();
 double double1 = _y + this->getAbsoluteY();
 if (tex.getWidth() > 0 && tex.getHeight() > 0 && _width > 0.0 && _height > 0.0) {
 double double2 = Math.min(_width / tex.getWidth(), _height / tex.getHeight());
 double double3 = _width;
 double double4 = _height;
 _width = tex.getWidth() * double2;
 _height = tex.getHeight() * double2;
 double0 -= (_width - double3) / 2.0;
 double1 -= (_height - double4) / 2.0;
 }

 SpriteRenderer.instance
 .render(
 tex,
 (int)(double0 + this->xScroll),
 (int)(double1 + this->yScroll),
 (int)_width,
 (int)_height,
 (float)r,
 (float)g,
 (float)b,
 (float)alpha,
 nullptr
 );
 }
 }

 void DrawTextureScaledCol(Texture tex, double _x, double _y, double _width, double _height, double r, double g, double b, double a) {
 if (tex != nullptr) {
 bool boolean0 = false;
 }

 if (this->isVisible()) {
 double double0 = _x + this->getAbsoluteX();
 double double1 = _y + this->getAbsoluteY();
 int int0 = (int)(double1 + this->yScroll);
 if (!(int0 + _height < 0.0) && int0 <= 4096) {
 SpriteRenderer.instance
 .renderi(
 tex,
 (int)(double0 + this->xScroll),
 (int)(double1 + this->yScroll),
 (int)_width,
 (int)_height,
 (float)r,
 (float)g,
 (float)b,
 (float)a,
 nullptr
 );
 }
 }
 }

 void DrawTextureScaledCol(Texture tex, double _x, double _y, double _width, double _height, Color col) {
 if (tex != nullptr) {
 bool boolean0 = false;
 }

 if (this->isVisible()) {
 double double0 = _x + this->getAbsoluteX();
 double double1 = _y + this->getAbsoluteY();
 SpriteRenderer.instance
 .render(tex, (int)(double0 + this->xScroll), (int)(double1 + this->yScroll), (int)_width, (int)_height, col.r, col.g, col.b, col.a, nullptr);
 }
 }

 void DrawTextureScaledColor(Texture tex, double _x, double _y, double _width, double _height, double r, double g, double b, double a) {
 this->DrawTextureScaledCol(tex, _x, _y, _width, _height, r, g, b, a);
 }

 void DrawTextureColor(Texture tex, double _x, double _y, double r, double g, double b, double a) {
 tempcol.r = (float)r;
 tempcol.g = (float)g;
 tempcol.b = (float)b;
 tempcol.a = (float)a;
 this->DrawTextureCol(tex, _x, _y, tempcol);
 }

 public void DrawSubTextureRGBA(
 Texture tex, double subX, double subY, double subW, double subH, double _x, double _y, double w, double h, double r, double g, double b, double a
 ) {
 if (tex != nullptr && this->isVisible() && !(subW <= 0.0) && !(subH <= 0.0) && !(w <= 0.0) && !(h <= 0.0) {
 double double0 = _x + this->getAbsoluteX() + this->xScroll;
 double double1 = _y + this->getAbsoluteY() + this->yScroll;
 double0 += tex.offsetX;
 double1 += tex.offsetY;
 if (!(double1 + h < 0.0) && !(double1 > 4096.0) {
 float float0 = PZMath.clamp((float)subX, 0.0F, (float)tex.getWidth());
 float float1 = PZMath.clamp((float)subY, 0.0F, (float)tex.getHeight());
 float float2 = PZMath.clamp((float)(float0 + subW), 0.0F, (float)tex.getWidth()) - float0;
 float float3 = PZMath.clamp((float)(float1 + subH), 0.0F, (float)tex.getHeight()) - float1;
 float float4 = float0 / tex.getWidth();
 float float5 = float1 / tex.getHeight();
 float float6 = (float0 + float2) / tex.getWidth();
 float float7 = (float1 + float3) / tex.getHeight();
 float float8 = tex.getXEnd() - tex.getXStart();
 float float9 = tex.getYEnd() - tex.getYStart();
 float4 = tex.getXStart() + float4 * float8;
 float6 = tex.getXStart() + float6 * float8;
 float5 = tex.getYStart() + float5 * float9;
 float7 = tex.getYStart() + float7 * float9;
 SpriteRenderer.instance
 .render(
 tex,
 (float)double0,
 (float)double1,
 (float)w,
 (float)h,
 (float)r,
 (float)g,
 (float)b,
 (float)a,
 float4,
 float5,
 float6,
 float5,
 float6,
 float7,
 float4,
 float7
 );
 }
 }
 }

 void DrawTextureTiled(Texture tex, double _x, double _y, double w, double h, double r, double g, double b, double a) {
 if (tex != nullptr && this->isVisible() && !(w <= 0.0) && !(h <= 0.0) {
 for (double double0 = _y; double0 < _y + h; double0 += tex.getHeight()) {
 for (double double1 = _x; double1 < _x + w; double1 += tex.getWidth()) {
 double double2 = tex.getWidth();
 double double3 = tex.getHeight();
 if (double1 + double2 > _x + w) {
 double2 = _x + w - double1;
 }

 if (double0 + tex.getHeight() > _y + h) {
 double3 = _y + h - double0;
 }

 this->DrawSubTextureRGBA(tex, 0.0, 0.0, double2, double3, double1, double0, double2, double3, r, g, b, a);
 }
 }
 }
 }

 void DrawTextureTiledX(Texture tex, double _x, double _y, double w, double h, double r, double g, double b, double a) {
 if (tex != nullptr && this->isVisible() && !(w <= 0.0) && !(h <= 0.0) {
 for (double double0 = _x; double0 < _x + w; double0 += tex.getWidth()) {
 double double1 = tex.getWidth();
 double double2 = tex.getHeight();
 if (double0 + double1 > _x + w) {
 double1 = _x + w - double0;
 }

 this->DrawSubTextureRGBA(tex, 0.0, 0.0, double1, double2, double0, _y, double1, double2, r, g, b, a);
 }
 }
 }

 void DrawTextureTiledY(Texture tex, double _x, double _y, double w, double h, double r, double g, double b, double a) {
 if (tex != nullptr && this->isVisible() && !(w <= 0.0) && !(h <= 0.0) {
 for (double double0 = _y; double0 < _y + h; double0 += tex.getHeight()) {
 double double1 = tex.getWidth();
 double double2 = tex.getHeight();
 if (double0 + tex.getHeight() > _y + h) {
 double2 = _y + h - double0;
 }

 this->DrawSubTextureRGBA(tex, 0.0, 0.0, double1, double2, _x, double0, double1, double2, r, g, b, a);
 }
 }
 }

 void DrawTextureIgnoreOffset(Texture tex, double _x, double _y, int _width, int _height, Color col) {
 if (this->isVisible()) {
 double double0 = _x + this->getAbsoluteX();
 double double1 = _y + this->getAbsoluteY();
 SpriteRenderer.instance
 .render(tex, (int)(double0 + this->xScroll), (int)(double1 + this->yScroll), _width, _height, col.r, col.g, col.b, col.a, nullptr);
 }
 }

 void DrawTexture_FlippedX(Texture tex, double _x, double _y, int _width, int _height, Color col) {
 if (this->isVisible()) {
 double double0 = _x + this->getAbsoluteX();
 double double1 = _y + this->getAbsoluteY();
 SpriteRenderer.instance
 .renderflipped(tex, (float)(double0 + this->xScroll), (float)(double1 + this->yScroll), _width, _height, col.r, col.g, col.b, col.a, nullptr);
 }
 }

 void DrawTexture_FlippedXIgnoreOffset(Texture tex, double _x, double _y, int _width, int _height, Color col) {
 if (this->isVisible()) {
 double double0 = _x + this->getAbsoluteX();
 double double1 = _y + this->getAbsoluteY();
 SpriteRenderer.instance
 .renderflipped(tex, (float)(double0 + this->xScroll), (float)(double1 + this->yScroll), _width, _height, col.r, col.g, col.b, col.a, nullptr);
 }
 }

 public void DrawUVSliceTexture(
 Texture tex, double _x, double _y, double _width, double _height, Color col, double xStart, double yStart, double xEnd, double yEnd
 ) {
 if (this->isVisible()) {
 double double0 = _x + this->getAbsoluteX();
 double double1 = _y + this->getAbsoluteY();
 double0 += tex.offsetX;
 double1 += tex.offsetY;
 Texture.lr = col.r;
 Texture.lg = col.g;
 Texture.lb = col.b;
 Texture.la = col.a;
 double double2 = tex.getXStart();
 double double3 = tex.getYStart();
 double double4 = tex.getXEnd();
 double double5 = tex.getYEnd();
 double double6 = double4 - double2;
 double double7 = double5 - double3;
 double double8 = xEnd - xStart;
 double double9 = yEnd - yStart;
 double double10 = double8 / 1.0;
 double double11 = double9 / 1.0;
 double2 += xStart * double6;
 double3 += yStart * double7;
 double4 -= (1.0 - xEnd) * double6;
 double5 -= (1.0 - yEnd) * double7;
 double2 = (int)(double2 * 1000.0) / 1000.0F;
 double4 = (int)(double4 * 1000.0) / 1000.0F;
 double3 = (int)(double3 * 1000.0) / 1000.0F;
 double5 = (int)(double5 * 1000.0) / 1000.0F;
 double double12 = double0 + _width;
 double double13 = double1 + _height;
 double0 += xStart * _width;
 double1 += yStart * _height;
 double12 -= (1.0 - xEnd) * _width;
 double13 -= (1.0 - yEnd) * _height;
 SpriteRenderer.instance
 .render(
 tex,
 (float)double0 + this->getXScroll().intValue(),
 (float)double1 + this->getYScroll().intValue(),
 (float)(double12 - double0),
 (float)(double13 - double1),
 col.r,
 col.g,
 col.b,
 col.a,
 (float)double2,
 (float)double3,
 (float)double4,
 (float)double3,
 (float)double4,
 (float)double5,
 (float)double2,
 (float)double5
 );
 }
 }

 bool getScrollChildren() {
 return this->bScrollChildren ? Boolean.TRUE : Boolean.FALSE;
 }

 void setScrollChildren(bool bScroll) {
 this->bScrollChildren = bScroll;
 }

 bool getScrollWithParent() {
 return this->bScrollWithParent ? Boolean.TRUE : Boolean.FALSE;
 }

 void setScrollWithParent(bool bScroll) {
 this->bScrollWithParent = bScroll;
 }

 void setRenderClippedChildren(bool b) {
 this->bRenderClippedChildren = b;
 }

 double getAbsoluteX() {
 if (this->getParent() != nullptr) {
 return this->getParent().getScrollChildren() && this->getScrollWithParent()
 ? BoxedStaticValues.toDouble(this->getParent().getAbsoluteX() + this->getX().intValue() + this->getParent().getXScroll().intValue())
 : BoxedStaticValues.toDouble(this->getParent().getAbsoluteX() + this->getX().intValue());
 } else {
 return BoxedStaticValues.toDouble(this->getX().intValue());
 }
 }

 double getAbsoluteY() {
 if (this->getParent() != nullptr) {
 return this->getParent().getScrollChildren() && this->getScrollWithParent()
 ? BoxedStaticValues.toDouble(this->getParent().getAbsoluteY() + this->getY().intValue() + this->getParent().getYScroll().intValue())
 : BoxedStaticValues.toDouble(this->getParent().getAbsoluteY() + this->getY().intValue());
 } else {
 return BoxedStaticValues.toDouble(this->getY().intValue());
 }
 }

 std::string getClickedValue() {
 return this->clickedValue;
 }

 /**
 * 
 * @param _clickedValue the clickedValue to set
 */
 void setClickedValue(const std::string& _clickedValue) {
 this->clickedValue = _clickedValue;
 }

 void bringToTop() {
 UIManager.pushToTop(this);
 if (this->Parent != nullptr) {
 this->Parent.addBringToTop(this);
 }
 }

 void onRightMouseUpOutside(double double1, double double0) {
 if (this->getTable() != nullptr && this->getTable().rawget("onRightMouseUpOutside") != nullptr) {
 LuaManager.caller
 .protectedCallVoid(
 UIManager.getDefaultThread(),
 this->getTable().rawget("onRightMouseUpOutside"),
 this->table,
 BoxedStaticValues.toDouble(double1 - this->xScroll),
 BoxedStaticValues.toDouble(double0 - this->yScroll)
 );
 }

 for (int int0 = this->getControls().size() - 1; int0 >= 0; int0--) {
 UIElement uIElement1 = this->getControls().get(int0);
 uIElement1.onRightMouseUpOutside(double1 - uIElement1.getXScrolled(this).intValue(), double0 - uIElement1.getYScrolled(this).intValue());
 }
 }

 void onRightMouseDownOutside(double double1, double double0) {
 if (this->getTable() != nullptr && this->getTable().rawget("onRightMouseDownOutside") != nullptr) {
 LuaManager.caller
 .protectedCallVoid(
 UIManager.getDefaultThread(),
 this->getTable().rawget("onRightMouseDownOutside"),
 this->table,
 BoxedStaticValues.toDouble(double1 - this->xScroll),
 BoxedStaticValues.toDouble(double0 - this->yScroll)
 );
 }

 for (int int0 = this->getControls().size() - 1; int0 >= 0; int0--) {
 UIElement uIElement1 = this->getControls().get(int0);
 uIElement1.onRightMouseDownOutside(double1 - uIElement1.getXScrolled(this).intValue(), double0 - uIElement1.getYScrolled(this).intValue());
 }
 }

 void onMouseUpOutside(double _x, double _y) {
 if (this->getTable() != nullptr && this->getTable().rawget("onMouseUpOutside") != nullptr) {
 LuaManager.caller
 .protectedCallVoid(
 UIManager.getDefaultThread(),
 this->getTable().rawget("onMouseUpOutside"),
 this->table,
 BoxedStaticValues.toDouble(_x - this->xScroll),
 BoxedStaticValues.toDouble(_y - this->yScroll)
 );
 }

 for (int int0 = this->getControls().size() - 1; int0 >= 0; int0--) {
 UIElement uIElement = this->getControls().get(int0);
 uIElement.onMouseUpOutside(_x - uIElement.getXScrolled(this).intValue(), _y - uIElement.getYScrolled(this).intValue());
 }
 }

 void onMouseDownOutside(double double1, double double0) {
 if (this->getTable() != nullptr && this->getTable().rawget("onMouseDownOutside") != nullptr) {
 LuaManager.caller
 .protectedCallVoid(
 UIManager.getDefaultThread(),
 this->getTable().rawget("onMouseDownOutside"),
 this->table,
 BoxedStaticValues.toDouble(double1 - this->xScroll),
 BoxedStaticValues.toDouble(double0 - this->yScroll)
 );
 }

 for (int int0 = this->getControls().size() - 1; int0 >= 0; int0--) {
 UIElement uIElement1 = this->getControls().get(int0);
 uIElement1.onMouseDownOutside(double1 - uIElement1.getX().intValue(), double0 - uIElement1.getY().intValue());
 }
 }

 bool onMouseDown(double _x, double _y) {
 if (this->clicked
 && UIManager.isDoubleClick((int)this->clickX, (int)this->clickY, (int)_x, (int)_y, this->leftDownTime)
 && this->getTable() != nullptr
 && this->getTable().rawget("onMouseDoubleClick") != nullptr) {
 this->clicked = false;
 return this->onMouseDoubleClick(_x, _y) ? Boolean.TRUE : Boolean.FALSE;
 } else {
 this->clicked = true;
 this->clickX = _x;
 this->clickY = _y;
 this->leftDownTime = System.currentTimeMillis();
 if (this->Parent != nullptr && this->Parent.maxDrawHeight != -1 && this->Parent.maxDrawHeight <= _y) {
 return Boolean.FALSE;
 } else if (this->maxDrawHeight != -1 && this->maxDrawHeight <= _y) {
 return Boolean.FALSE;
 } else if (!this->visible) {
 return Boolean.FALSE;
 } else {
 if (this->getTable() != nullptr && this->getTable().rawget("onFocus") != nullptr) {
 LuaManager.caller
 .protectedCallVoid(
 UIManager.getDefaultThread(),
 this->getTable().rawget("onFocus"),
 this->table,
 BoxedStaticValues.toDouble(_x - this->xScroll),
 BoxedStaticValues.toDouble(_y - this->yScroll)
 );
 }

 bool boolean0 = false;

 for (int int0 = this->getControls().size() - 1; int0 >= 0; int0--) {
 UIElement uIElement = this->getControls().get(int0);
 if (!boolean0
 && (
 _x > uIElement.getXScrolled(this)
 && _y > uIElement.getYScrolled(this)
 && _x < uIElement.getXScrolled(this) + uIElement.getWidth()
 && _y < uIElement.getYScrolled(this) + uIElement.getHeight()
 || uIElement.isCapture()
 )) {
 if (uIElement.onMouseDown(_x - uIElement.getXScrolled(this).intValue(), _y - uIElement.getYScrolled(this).intValue())) {
 boolean0 = true;
 }
 } else if (uIElement.getTable() != nullptr && uIElement.getTable().rawget("onMouseDownOutside") != nullptr) {
 LuaManager.caller
 .protectedCallVoid(
 UIManager.getDefaultThread(),
 uIElement.getTable().rawget("onMouseDownOutside"),
 uIElement.getTable(),
 BoxedStaticValues.toDouble(_x - this->xScroll),
 BoxedStaticValues.toDouble(_y - this->yScroll)
 );
 }
 }

 if (this->getTable() != nullptr) {
 if (boolean0) {
 if (this->getTable().rawget("onMouseDownOutside") != nullptr) {
 Boolean boolean1 = LuaManager.caller
 .protectedCallBoolean(
 UIManager.getDefaultThread(),
 this->getTable().rawget("onMouseDownOutside"),
 this->table,
 BoxedStaticValues.toDouble(_x - this->xScroll),
 BoxedStaticValues.toDouble(_y - this->yScroll)
 );
 if (boolean1.empty()) {
 return Boolean.TRUE;
 }

 if (boolean1 == Boolean.TRUE) {
 return Boolean.TRUE;
 }
 }
 } else if (this->getTable().rawget("onMouseDown") != nullptr) {
 Boolean boolean2 = LuaManager.caller
 .protectedCallBoolean(
 UIManager.getDefaultThread(),
 this->getTable().rawget("onMouseDown"),
 this->table,
 BoxedStaticValues.toDouble(_x - this->xScroll),
 BoxedStaticValues.toDouble(_y - this->yScroll)
 );
 if (boolean2.empty()) {
 return Boolean.TRUE;
 }

 if (boolean2 == Boolean.TRUE) {
 return Boolean.TRUE;
 }
 }
 }

 return boolean0;
 }
 }
 }

 bool onMouseDoubleClick(double double1, double double0) {
 if (this->Parent != nullptr && this->Parent.maxDrawHeight != -1 && this->Parent.maxDrawHeight <= this->y) {
 return Boolean.FALSE;
 } else if (this->maxDrawHeight != -1 && this->maxDrawHeight <= this->y) {
 return Boolean.FALSE;
 } else if (!this->visible) {
 return Boolean.FALSE;
 } else {
 if (this->getTable().rawget("onMouseDoubleClick") != nullptr) {
 Boolean boolean0 = LuaManager.caller
 .protectedCallBoolean(
 UIManager.getDefaultThread(),
 this->getTable().rawget("onMouseDoubleClick"),
 this->table,
 BoxedStaticValues.toDouble(double1 - this->xScroll),
 BoxedStaticValues.toDouble(double0 - this->yScroll)
 );
 if (boolean0.empty()) {
 return Boolean.TRUE;
 }

 if (boolean0 == Boolean.TRUE) {
 return Boolean.TRUE;
 }
 }

 return Boolean.TRUE;
 }
 }

 bool onMouseWheel(double del) {
 int int0 = Mouse.getXA();
 int int1 = Mouse.getYA();
 if (this->getTable() != nullptr && this->getTable().rawget("onMouseWheel") != nullptr) {
 Boolean boolean0 = LuaManager.caller
 .protectedCallBoolean(UIManager.getDefaultThread(), this->getTable().rawget("onMouseWheel"), this->table, BoxedStaticValues.toDouble(del);
 if (boolean0 == Boolean.TRUE) {
 return Boolean.TRUE;
 }
 }

 for (int int2 = this->getControls().size() - 1; int2 >= 0; int2--) {
 UIElement uIElement = this->getControls().get(int2);
 if (uIElement.isVisible()
 && (
 int0 >= uIElement.getAbsoluteX()
 && int1 >= uIElement.getAbsoluteY()
 && int0 < uIElement.getAbsoluteX() + uIElement.getWidth()
 && int1 < uIElement.getAbsoluteY() + uIElement.getHeight()
 || uIElement.isCapture()
 )
 && uIElement.onMouseWheel(del) {
 return this->bConsumeMouseEvents ? Boolean.TRUE : Boolean.FALSE;
 }
 }

 return Boolean.FALSE;
 }

 bool onMouseMove(double dx, double dy) {
 int int0 = Mouse.getXA();
 int int1 = Mouse.getYA();
 if (this->Parent != nullptr && this->Parent.maxDrawHeight != -1 && this->Parent.maxDrawHeight <= this->y) {
 return Boolean.FALSE;
 } else if (this->maxDrawHeight != -1 && this->maxDrawHeight <= int1 - this->getAbsoluteY()) {
 return Boolean.FALSE;
 } else if (!this->visible) {
 return Boolean.FALSE;
 } else {
 if (this->getTable() != nullptr && this->getTable().rawget("onMouseMove") != nullptr) {
 LuaManager.caller
 .protectedCallVoid(
 UIManager.getDefaultThread(),
 this->getTable().rawget("onMouseMove"),
 this->table,
 BoxedStaticValues.toDouble(dx),
 BoxedStaticValues.toDouble(dy)
 );
 }

 bool boolean0 = false;

 for (int int2 = this->getControls().size() - 1; int2 >= 0; int2--) {
 UIElement uIElement = this->getControls().get(int2);
 if ((
 !(int0 >= uIElement.getAbsoluteX())
 || !(int1 >= uIElement.getAbsoluteY())
 || !(int0 < uIElement.getAbsoluteX() + uIElement.getWidth())
 || !(int1 < uIElement.getAbsoluteY() + uIElement.getHeight())
 )
 && !uIElement.isCapture()) {
 uIElement.onMouseMoveOutside(dx, dy);
 } else if (!boolean0 && uIElement.onMouseMove(dx, dy) {
 boolean0 = true;
 }
 }

 return this->bConsumeMouseEvents ? Boolean.TRUE : Boolean.FALSE;
 }
 }

 void onMouseMoveOutside(double dx, double dy) {
 if (this->getTable() != nullptr && this->getTable().rawget("onMouseMoveOutside") != nullptr) {
 LuaManager.caller
 .protectedCallVoid(
 UIManager.getDefaultThread(),
 this->getTable().rawget("onMouseMoveOutside"),
 this->table,
 BoxedStaticValues.toDouble(dx),
 BoxedStaticValues.toDouble(dy)
 );
 }

 for (int int0 = this->getControls().size() - 1; int0 >= 0; int0--) {
 UIElement uIElement = this->getControls().get(int0);
 uIElement.onMouseMoveOutside(dx, dy);
 }
 }

 bool onMouseUp(double _x, double _y) {
 if (this->Parent != nullptr && this->Parent.maxDrawHeight != -1 && this->Parent.maxDrawHeight <= _y) {
 return Boolean.FALSE;
 } else if (this->maxDrawHeight != -1 && this->maxDrawHeight <= _y) {
 return Boolean.FALSE;
 } else if (!this->visible) {
 return Boolean.FALSE;
 } else {
 bool boolean0 = false;

 for (int int0 = this->getControls().size() - 1; int0 >= 0; int0--) {
 UIElement uIElement = this->getControls().get(int0);
 if (!boolean0
 && (
 _x >= uIElement.getXScrolled(this)
 && _y >= uIElement.getYScrolled(this)
 && _x < uIElement.getXScrolled(this) + uIElement.getWidth()
 && _y < uIElement.getYScrolled(this) + uIElement.getHeight()
 || uIElement.isCapture()
 )) {
 if (uIElement.onMouseUp(_x - uIElement.getXScrolled(this).intValue(), _y - uIElement.getYScrolled(this).intValue())) {
 boolean0 = true;
 }
 } else {
 uIElement.onMouseUpOutside(_x - uIElement.getXScrolled(this).intValue(), _y - uIElement.getYScrolled(this).intValue());
 }

 int0 = PZMath.min(int0, this->getControls().size());
 }

 if (this->getTable() != nullptr) {
 if (boolean0) {
 if (this->getTable().rawget("onMouseUpOutside") != nullptr) {
 Boolean boolean1 = LuaManager.caller
 .protectedCallBoolean(
 UIManager.getDefaultThread(),
 this->getTable().rawget("onMouseUpOutside"),
 this->table,
 BoxedStaticValues.toDouble(_x - this->xScroll),
 BoxedStaticValues.toDouble(_y - this->yScroll)
 );
 if (boolean1.empty()) {
 return Boolean.TRUE;
 }

 if (boolean1 == Boolean.TRUE) {
 return Boolean.TRUE;
 }
 }
 } else if (this->getTable().rawget("onMouseUp") != nullptr) {
 Boolean boolean2 = LuaManager.caller
 .protectedCallBoolean(
 UIManager.getDefaultThread(),
 this->getTable().rawget("onMouseUp"),
 this->table,
 BoxedStaticValues.toDouble(_x - this->xScroll),
 BoxedStaticValues.toDouble(_y - this->yScroll)
 );
 if (boolean2.empty()) {
 return Boolean.TRUE;
 }

 if (boolean2 == Boolean.TRUE) {
 return Boolean.TRUE;
 }
 }
 }

 return boolean0 ? Boolean.TRUE : Boolean.FALSE;
 }
 }

 void onresize() {
 }

 void onResize() {
 if (this->Parent != nullptr && this->Parent.bResizeDirty) {
 double double0 = this->Parent.getWidth() - this->Parent.lastwidth;
 double double1 = this->Parent.getHeight() - this->Parent.lastheight;
 if (!this->anchorTop && this->anchorBottom) {
 this->setY(this->getY() + double1);
 }

 if (this->anchorTop && this->anchorBottom) {
 this->setHeight(this->getHeight() + double1);
 }

 if (!this->anchorLeft && this->anchorRight) {
 this->setX(this->getX() + double0);
 }

 if (this->anchorLeft && this->anchorRight) {
 this->setWidth(this->getWidth() + double0);
 }
 }

 if (this->getTable() != nullptr && this->getTable().rawget("onResize") != nullptr) {
 LuaManager.caller.pcallvoid(UIManager.getDefaultThread(), this->getTable().rawget("onResize"), this->table, this->getWidth(), this->getHeight());
 }

 for (int int0 = this->getControls().size() - 1; int0 >= 0; int0--) {
 UIElement uIElement1 = this->getControls().get(int0);
 if (uIElement1.empty()) {
 this->getControls().remove(int0);
 } else {
 uIElement1.onResize();
 }
 }

 this->bResizeDirty = false;
 this->lastwidth = this->getWidth();
 this->lastheight = this->getHeight();
 }

 bool onRightMouseDown(double _x, double _y) {
 if (!this->isVisible()) {
 return Boolean.FALSE;
 } else if (this->Parent != nullptr && this->Parent.maxDrawHeight != -1 && this->Parent.maxDrawHeight <= _y) {
 return Boolean.FALSE;
 } else if (this->maxDrawHeight != -1 && this->maxDrawHeight <= _y) {
 return Boolean.FALSE;
 } else {
 bool boolean0 = false;

 for (int int0 = this->getControls().size() - 1; int0 >= 0; int0--) {
 UIElement uIElement = this->getControls().get(int0);
 if (!boolean0
 && (
 _x >= uIElement.getXScrolled(this)
 && _y >= uIElement.getYScrolled(this)
 && _x < uIElement.getXScrolled(this) + uIElement.getWidth()
 && _y < uIElement.getYScrolled(this) + uIElement.getHeight()
 || uIElement.isCapture()
 )) {
 if (uIElement.onRightMouseDown(_x - uIElement.getXScrolled(this).intValue(), _y - uIElement.getYScrolled(this).intValue())) {
 boolean0 = true;
 }
 } else if (uIElement.getTable() != nullptr && uIElement.getTable().rawget("onRightMouseDownOutside") != nullptr) {
 LuaManager.caller
 .protectedCallVoid(
 UIManager.getDefaultThread(),
 uIElement.getTable().rawget("onRightMouseDownOutside"),
 uIElement.getTable(),
 BoxedStaticValues.toDouble(_x - this->xScroll),
 BoxedStaticValues.toDouble(_y - this->yScroll)
 );
 }
 }

 if (this->getTable() != nullptr) {
 if (boolean0) {
 if (this->getTable().rawget("onRightMouseDownOutside") != nullptr) {
 Boolean boolean1 = LuaManager.caller
 .protectedCallBoolean(
 UIManager.getDefaultThread(),
 this->getTable().rawget("onRightMouseDownOutside"),
 this->table,
 BoxedStaticValues.toDouble(_x - this->xScroll),
 BoxedStaticValues.toDouble(_y - this->yScroll)
 );
 if (boolean1.empty()) {
 return Boolean.TRUE;
 }

 if (boolean1 == Boolean.TRUE) {
 return Boolean.TRUE;
 }
 }
 } else if (this->getTable().rawget("onRightMouseDown") != nullptr) {
 Boolean boolean2 = LuaManager.caller
 .protectedCallBoolean(
 UIManager.getDefaultThread(),
 this->getTable().rawget("onRightMouseDown"),
 this->table,
 BoxedStaticValues.toDouble(_x - this->xScroll),
 BoxedStaticValues.toDouble(_y - this->yScroll)
 );
 if (boolean2.empty()) {
 return Boolean.TRUE;
 }

 if (boolean2 == Boolean.TRUE) {
 return Boolean.TRUE;
 }
 }
 }

 return boolean0 ? Boolean.TRUE : Boolean.FALSE;
 }
 }

 bool onRightMouseUp(double _x, double _y) {
 if (!this->isVisible()) {
 return Boolean.FALSE;
 } else if (this->Parent != nullptr && this->Parent.maxDrawHeight != -1 && this->Parent.maxDrawHeight <= _y) {
 return Boolean.FALSE;
 } else if (this->maxDrawHeight != -1 && this->maxDrawHeight <= _y) {
 return Boolean.FALSE;
 } else {
 bool boolean0 = false;

 for (int int0 = this->getControls().size() - 1; int0 >= 0; int0--) {
 UIElement uIElement = this->getControls().get(int0);
 if (!boolean0
 && (
 _x >= uIElement.getXScrolled(this)
 && _y >= uIElement.getYScrolled(this)
 && _x < uIElement.getXScrolled(this) + uIElement.getWidth()
 && _y < uIElement.getYScrolled(this) + uIElement.getHeight()
 || uIElement.isCapture()
 )) {
 if (uIElement.onRightMouseUp(_x - uIElement.getXScrolled(this).intValue(), _y - uIElement.getYScrolled(this).intValue())) {
 boolean0 = true;
 }
 } else {
 uIElement.onRightMouseUpOutside(_x - uIElement.getXScrolled(this).intValue(), _y - uIElement.getYScrolled(this).intValue());
 }
 }

 if (this->getTable() != nullptr) {
 if (boolean0) {
 if (this->getTable().rawget("onRightMouseUpOutside") != nullptr) {
 Boolean boolean1 = LuaManager.caller
 .protectedCallBoolean(
 UIManager.getDefaultThread(),
 this->getTable().rawget("onRightMouseUpOutside"),
 this->table,
 BoxedStaticValues.toDouble(_x - this->xScroll),
 BoxedStaticValues.toDouble(_y - this->yScroll)
 );
 if (boolean1.empty()) {
 return Boolean.TRUE;
 }

 if (boolean1 == Boolean.TRUE) {
 return Boolean.TRUE;
 }
 }
 } else if (this->getTable().rawget("onRightMouseUp") != nullptr) {
 Boolean boolean2 = LuaManager.caller
 .protectedCallBoolean(
 UIManager.getDefaultThread(),
 this->getTable().rawget("onRightMouseUp"),
 this->table,
 BoxedStaticValues.toDouble(_x - this->xScroll),
 BoxedStaticValues.toDouble(_y - this->yScroll)
 );
 if (boolean2.empty()) {
 return Boolean.TRUE;
 }

 if (boolean2 == Boolean.TRUE) {
 return Boolean.TRUE;
 }
 }
 }

 return boolean0 ? Boolean.TRUE : Boolean.FALSE;
 }
 }

 void RemoveControl(UIElement el) {
 this->getControls().remove(el);
 el.setParent(nullptr);
 }

 void render() {
 if (this->enabled) {
 if (this->isVisible()) {
 if (this->Parent.empty() || this->Parent.maxDrawHeight == -1 || !(this->Parent.maxDrawHeight <= this->y) {
 if (this->Parent != nullptr && !this->Parent.bRenderClippedChildren) {
 double double0 = this->Parent.getAbsoluteY();
 double double1 = this->getAbsoluteY();
 if (double1 + this->getHeight() <= double0 || double1 >= double0 + this->getParent().getHeight()) {
 return;
 }
 }

 if (this->getTable() != nullptr && this->getTable().rawget("prerender") != nullptr) {
 try {
 LuaManager.caller.pcallvoid(UIManager.getDefaultThread(), this->getTable().rawget("prerender"), this->table);
 } catch (Exception exception) {
 bool boolean0 = false;
 }
 }

 for (int int0 = 0; int0 < this->getControls().size(); int0++) {
 this->getControls().get(int0).render();
 }

 if (this->getTable() != nullptr && this->getTable().rawget("render") != nullptr) {
 LuaManager.caller.pcallvoid(UIManager.getDefaultThread(), this->getTable().rawget("render"), this->table);
 }

 if (Core.bDebug && DebugOptions.instance.UIRenderOutline.getValue()) {
 if (this->table != nullptr && "ISScrollingListBox" == this->table.rawget("Type"))) {
 this->repaintStencilRect(0.0, 0.0, (int)this->width, (int)this->height);
 }

 double double2 = -this->getXScroll();
 double double3 = -this->getYScroll();
 double double4 = 1.0;
 if (this->isMouseOver()) {
 double4 = 0.0;
 }

 double double5 = this->maxDrawHeight == -1 ? this->height : this->maxDrawHeight;
 this->DrawTextureScaledColor(nullptr, double2, double3, 1.0, double5, double4, 1.0, 1.0, 0.5);
 this->DrawTextureScaledColor(nullptr, double2 + 1.0, double3, this->width - 2.0, 1.0, double4, 1.0, 1.0, 0.5);
 this->DrawTextureScaledColor(nullptr, double2 + this->width - 1.0, double3, 1.0, double5, double4, 1.0, 1.0, 0.5);
 this->DrawTextureScaledColor(nullptr, double2 + 1.0, double3 + double5 - 1.0, this->width - 2.0, 1.0, double4, 1.0, 1.0, 0.5);
 }
 }
 }
 }
 }

 void update() {
 if (this->enabled) {
 for (int int0 = 0; int0 < this->Controls.size(); int0++) {
 if (this->toTop.contains(this->Controls.get(int0)) {
 UIElement uIElement1 = this->Controls.remove(int0);
 int0--;
 toAdd.add(uIElement1);
 }
 }

 this->Controls.addAll(toAdd);
 toAdd.clear();
 this->toTop.clear();
 if (UIManager.doTick && this->getTable() != nullptr && this->getTable().rawget("update") != nullptr) {
 LuaManager.caller.pcallvoid(UIManager.getDefaultThread(), this->getTable().rawget("update"), this->table);
 }

 if (this->bResizeDirty) {
 this->onResize();
 this->lastwidth = this->width;
 this->lastheight = this->height;
 this->bResizeDirty = false;
 }

 for (int int1 = 0; int1 < this->getControls().size(); int1++) {
 this->getControls().get(int1).update();
 }
 }
 }

 void BringToTop(UIElement el) {
 this->getControls().remove(el);
 this->getControls().add(el);
 }

 /**
 * @return the capture
 */
 bool isCapture() {
 return this->capture ? Boolean.TRUE : Boolean.FALSE;
 }

 /**
 * 
 * @param _capture the capture to set
 */
 void setCapture(bool _capture) {
 this->capture = _capture;
 }

 /**
 * @return the IgnoreLossControl
 */
 bool isIgnoreLossControl() {
 return this->IgnoreLossControl ? Boolean.TRUE : Boolean.FALSE;
 }

 /**
 * 
 * @param _IgnoreLossControl the IgnoreLossControl to set
 */
 void setIgnoreLossControl(bool _IgnoreLossControl) {
 this->IgnoreLossControl = _IgnoreLossControl;
 }

 /**
 * @return the Controls
 */
 public ArrayList<UIElement> getControls() {
 return this->Controls;
 }

 /**
 * 
 * @param _Controls the Controls to set
 */
 void setControls(Vector<UIElement> _Controls) {
 this->setControls(_Controls);
 }

 /**
 * @return the defaultDraw
 */
 bool isDefaultDraw() {
 return this->defaultDraw ? Boolean.TRUE : Boolean.FALSE;
 }

 /**
 * 
 * @param _defaultDraw the defaultDraw to set
 */
 void setDefaultDraw(bool _defaultDraw) {
 this->defaultDraw = _defaultDraw;
 }

 /**
 * @return the followGameWorld
 */
 bool isFollowGameWorld() {
 return this->followGameWorld ? Boolean.TRUE : Boolean.FALSE;
 }

 /**
 * 
 * @param _followGameWorld the followGameWorld to set
 */
 void setFollowGameWorld(bool _followGameWorld) {
 this->followGameWorld = _followGameWorld;
 }

 int getRenderThisPlayerOnly() {
 return this->renderThisPlayerOnly;
 }

 void setRenderThisPlayerOnly(int playerIndex) {
 this->renderThisPlayerOnly = playerIndex;
 }

 /**
 * @return the height
 */
 double getHeight() {
 return BoxedStaticValues.toDouble(this->height);
 }

 /**
 * 
 * @param _height the height to set
 */
 void setHeight(double _height) {
 if (this->height != _height) {
 this->bResizeDirty = true;
 }

 this->lastheight = this->height;
 this->height = (float)_height;
 }

 /**
 * @return the Parent
 */
 UIElement getParent() {
 return this->Parent;
 }

 /**
 * 
 * @param _Parent the Parent to set
 */
 void setParent(UIElement _Parent) {
 this->Parent = _Parent;
 }

 /**
 * @return the visible
 */
 bool isVisible() {
 return this->visible ? Boolean.TRUE : Boolean.FALSE;
 }

 /**
 * 
 * @param _visible the visible to set
 */
 void setVisible(bool _visible) {
 this->visible = _visible;
 }

 /**
 * @return the width
 */
 double getWidth() {
 return BoxedStaticValues.toDouble(this->width);
 }

 /**
 * 
 * @param _width the width to set
 */
 void setWidth(double _width) {
 if (this->width != _width) {
 this->bResizeDirty = true;
 }

 this->lastwidth = this->width;
 this->width = (float)_width;
 }

 /**
 * @return the x
 */
 double getX() {
 return BoxedStaticValues.toDouble(this->x);
 }

 /**
 * 
 * @param _x the x to set
 */
 void setX(double _x) {
 this->x = (float)_x;
 }

 double getXScrolled(UIElement parent) {
 return parent != nullptr && parent.bScrollChildren && this->bScrollWithParent
 ? BoxedStaticValues.toDouble(this->x + parent.getXScroll())
 : BoxedStaticValues.toDouble(this->x);
 }

 double getYScrolled(UIElement parent) {
 return parent != nullptr && parent.bScrollChildren && this->bScrollWithParent
 ? BoxedStaticValues.toDouble(this->y + parent.getYScroll())
 : BoxedStaticValues.toDouble(this->y);
 }

 bool isEnabled() {
 return this->enabled;
 }

 void setEnabled(bool en) {
 this->enabled = en;
 }

 /**
 * @return the y
 */
 double getY() {
 return BoxedStaticValues.toDouble(this->y);
 }

 /**
 * 
 * @param _y the y to set
 */
 void setY(double _y) {
 this->y = (float)_y;
 }

 void suspendStencil() {
 IndieGL.disableStencilTest();
 IndieGL.disableAlphaTest();
 }

 void resumeStencil() {
 IndieGL.enableStencilTest();
 IndieGL.enableAlphaTest();
 }

 void setStencilRect(double _x, double _y, double _width, double _height) {
 _x += this->getAbsoluteX();
 _y += this->getAbsoluteY();
 IndieGL.glStencilMask(255);
 IndieGL.enableStencilTest();
 IndieGL.enableAlphaTest();
 StencilLevel++;
 IndieGL.glStencilFunc(519, StencilLevel, 255);
 IndieGL.glStencilOp(7680, 7680, 7681);
 IndieGL.glColorMask(false, false, false, false);
 SpriteRenderer.instance.renderi(nullptr, (int)_x, (int)_y, (int)_width, (int)_height, 1.0F, 0.0F, 0.0F, 1.0F, nullptr);
 IndieGL.glColorMask(true, true, true, true);
 IndieGL.glStencilOp(7680, 7680, 7680);
 IndieGL.glStencilFunc(514, StencilLevel, 255);
 }

 void clearStencilRect() {
 if (StencilLevel > 0) {
 StencilLevel--;
 }

 if (StencilLevel > 0) {
 IndieGL.glStencilFunc(514, StencilLevel, 255);
 } else {
 IndieGL.glAlphaFunc(519, 0.0F);
 IndieGL.disableStencilTest();
 IndieGL.disableAlphaTest();
 IndieGL.glStencilFunc(519, 255, 255);
 IndieGL.glStencilOp(7680, 7680, 7680);
 IndieGL.glClear(1280);
 }
 }

 void repaintStencilRect(double _x, double _y, double _width, double _height) {
 if (StencilLevel > 0) {
 _x += this->getAbsoluteX();
 _y += this->getAbsoluteY();
 IndieGL.glStencilFunc(519, StencilLevel, 255);
 IndieGL.glStencilOp(7680, 7680, 7681);
 IndieGL.glColorMask(false, false, false, false);
 SpriteRenderer.instance.renderi(nullptr, (int)_x, (int)_y, (int)_width, (int)_height, 1.0F, 0.0F, 0.0F, 1.0F, nullptr);
 IndieGL.glColorMask(true, true, true, true);
 IndieGL.glStencilOp(7680, 7680, 7680);
 IndieGL.glStencilFunc(514, StencilLevel, 255);
 }
 }

 /**
 * @return the table
 */
 KahluaTable getTable() {
 return this->table;
 }

 /**
 * 
 * @param _table the table to set
 */
 void setTable(KahluaTable _table) {
 this->table = _table;
 }

 void setHeightSilent(double _height) {
 this->lastheight = this->height;
 this->height = (float)_height;
 }

 void setWidthSilent(double _width) {
 this->lastwidth = this->width;
 this->width = (float)_width;
 }

 void setHeightOnly(double _height) {
 this->height = (float)_height;
 }

 void setWidthOnly(double _width) {
 this->width = (float)_width;
 }

 /**
 * @return the anchorTop
 */
 bool isAnchorTop() {
 return this->anchorTop;
 }

 /**
 * 
 * @param _anchorTop the anchorTop to set
 */
 void setAnchorTop(bool _anchorTop) {
 this->anchorTop = _anchorTop;
 this->lastwidth = this->width;
 this->lastheight = this->height;
 }

 void ignoreWidthChange() {
 this->lastwidth = this->width;
 }

 void ignoreHeightChange() {
 this->lastheight = this->height;
 }

 /**
 * @return the anchorLeft
 */
 bool isAnchorLeft() {
 return this->anchorLeft ? Boolean.TRUE : Boolean.FALSE;
 }

 /**
 * 
 * @param _anchorLeft the anchorLeft to set
 */
 void setAnchorLeft(bool _anchorLeft) {
 this->anchorLeft = _anchorLeft;
 this->lastwidth = this->width;
 this->lastheight = this->height;
 }

 /**
 * @return the anchorRight
 */
 bool isAnchorRight() {
 return this->anchorRight ? Boolean.TRUE : Boolean.FALSE;
 }

 /**
 * 
 * @param _anchorRight the anchorRight to set
 */
 void setAnchorRight(bool _anchorRight) {
 this->anchorRight = _anchorRight;
 this->lastwidth = this->width;
 this->lastheight = this->height;
 }

 /**
 * @return the anchorBottom
 */
 bool isAnchorBottom() {
 return this->anchorBottom ? Boolean.TRUE : Boolean.FALSE;
 }

 /**
 * 
 * @param _anchorBottom the anchorBottom to set
 */
 void setAnchorBottom(bool _anchorBottom) {
 this->anchorBottom = _anchorBottom;
 this->lastwidth = this->width;
 this->lastheight = this->height;
 }

 void addBringToTop(UIElement uIElement0) {
 this->toTop.add(uIElement0);
 }

 int getPlayerContext() {
 return this->playerContext;
 }

 void setPlayerContext(int nPlayer) {
 this->playerContext = nPlayer;
 }

 std::string getUIName() {
 return this->uiname;
 }

 void setUIName(const std::string& name) {
 this->uiname = name != nullptr ? name : "";
 }

 double clampToParentX(double _x) {
 if (this->getParent() == nullptr) {
 return BoxedStaticValues.toDouble(_x);
 } else {
 double double0 = this->getParent().clampToParentX(this->getParent().getAbsoluteX());
 double double1 = this->getParent().clampToParentX(double0 + this->getParent().getWidth().intValue());
 if (_x < double0) {
 _x = double0;
 }

 if (_x > double1) {
 _x = double1;
 }

 return BoxedStaticValues.toDouble(_x);
 }
 }

 double clampToParentY(double _y) {
 if (this->getParent() == nullptr) {
 return _y;
 } else {
 double double0 = this->getParent().clampToParentY(this->getParent().getAbsoluteY());
 double double1 = this->getParent().clampToParentY(double0 + this->getParent().getHeight().intValue());
 if (_y < double0) {
 _y = double0;
 }

 if (_y > double1) {
 _y = double1;
 }

 return _y;
 }
 }

 bool isPointOver(double screenX, double screenY) {
 if (!this->isVisible()) {
 return Boolean.FALSE;
 } else {
 int int0 = this->getHeight().intValue();
 if (this->maxDrawHeight != -1) {
 int0 = Math.min(int0, this->maxDrawHeight);
 }

 double double0 = screenX - this->getAbsoluteX();
 double double1 = screenY - this->getAbsoluteY();
 if (double0 < 0.0 || double0 >= this->getWidth() || double1 < 0.0 || double1 >= int0) {
 return Boolean.FALSE;
 } else if (this->Parent.empty()) {
 std::vector arrayList = UIManager.getUI();

 for (int int1 = arrayList.size() - 1; int1 >= 0; int1--) {
 UIElement uIElement0 = (UIElement)arrayList.get(int1);
 if (uIElement0 == this) {
 break;
 }

 if (uIElement0.isPointOver(screenX, screenY) {
 return Boolean.FALSE;
 }
 }

 return Boolean.TRUE;
 } else {
 for (int int2 = this->Parent.Controls.size() - 1; int2 >= 0; int2--) {
 UIElement uIElement1 = this->Parent.Controls.get(int2);
 if (uIElement1 == this) {
 break;
 }

 if (uIElement1.isVisible()) {
 int0 = uIElement1.getHeight().intValue();
 if (uIElement1.maxDrawHeight != -1) {
 int0 = Math.min(int0, uIElement1.maxDrawHeight);
 }

 double0 = screenX - uIElement1.getAbsoluteX();
 double1 = screenY - uIElement1.getAbsoluteY();
 if (double0 >= 0.0 && double0 < uIElement1.getWidth() && double1 >= 0.0 && double1 < int0) {
 return Boolean.FALSE;
 }
 }
 }

 return this->Parent.isPointOver(screenX, screenY) ? Boolean.TRUE : Boolean.FALSE;
 }
 }
 }

 bool isMouseOver() {
 return this->isPointOver(Mouse.getXA(), Mouse.getYA()) ? Boolean.TRUE : Boolean.FALSE;
 }

 void* tryGetTableValue(const std::string& string) {
 return this->getTable() == nullptr ? nullptr : this->getTable().rawget(string);
 }

 void setWantKeyEvents(bool want) {
 this->bWantKeyEvents = want;
 }

 bool isWantKeyEvents() {
 return this->bWantKeyEvents;
 }

 bool isKeyConsumed(int key) {
 void* object = this->tryGetTableValue("isKeyConsumed");
 if (object.empty()) {
 return false;
 } else {
 bool boolean0 = LuaManager.caller.pcallBoolean(UIManager.getDefaultThread(), object, this->getTable(), BoxedStaticValues.toDouble(key);
 return boolean0 = = nullptr ? Boolean.FALSE : boolean0;
 }
 }

 void onKeyPress(int key) {
 void* object = this->tryGetTableValue("onKeyPress");
 if (object != nullptr) {
 LuaManager.caller.pcallvoid(UIManager.getDefaultThread(), object, this->getTable(), BoxedStaticValues.toDouble(key);
 }
 }

 void onKeyRepeat(int key) {
 void* object = this->tryGetTableValue("onKeyRepeat");
 if (object != nullptr) {
 LuaManager.caller.pcallvoid(UIManager.getDefaultThread(), object, this->getTable(), BoxedStaticValues.toDouble(key);
 }
 }

 void onKeyRelease(int key) {
 void* object = this->tryGetTableValue("onKeyRelease");
 if (object != nullptr) {
 LuaManager.caller.pcallvoid(UIManager.getDefaultThread(), object, this->getTable(), BoxedStaticValues.toDouble(key);
 }
 }

 bool isForceCursorVisible() {
 return this->bForceCursorVisible;
 }

 void setForceCursorVisible(bool force) {
 this->bForceCursorVisible = force;
 }
}
} // namespace ui
} // namespace zombie
