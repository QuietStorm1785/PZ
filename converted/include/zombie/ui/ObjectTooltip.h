#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/core/Core.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/iso/IsoObject.h"
#include <algorithm>

namespace zombie {
namespace ui {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class ObjectTooltip : public UIElement {
public:
 static float alphaStep = 0.1F;
 bool bIsItem = false;
 InventoryItem Item = nullptr;
 IsoObject Object;
 float alpha = 0.0F;
 int showDelay = 0;
 float targetAlpha = 0.0F;
 Texture texture;
 int padRight = 5;
 int padBottom = 5;
 IsoGameCharacter character;
 bool measureOnly;
 float weightOfStack = 0.0F;
 static int lineSpacing = 14;
 static std::string fontSize = "Small";
 static UIFont font = UIFont.Small;
 private static Stack<ObjectTooltip.Layout> freeLayouts = std::make_unique<Stack<>>();

 public ObjectTooltip() {
 this->texture = Texture.getSharedTexture("black");
 this->width = 130.0F;
 this->height = 130.0F;
 this->defaultDraw = false;
 lineSpacing = TextManager.instance.getFontFromEnum(font).getLineHeight();
 checkFont();
 }

 static void checkFont() {
 if (!fontSize == Core.getInstance().getOptionTooltipFont())) {
 fontSize = Core.getInstance().getOptionTooltipFont();
 if ("Large" == fontSize) {
 font = UIFont.Large;
 } else if ("Medium" == fontSize) {
 font = UIFont.Medium;
 } else {
 font = UIFont.Small;
 }

 lineSpacing = TextManager.instance.getFontFromEnum(font).getLineHeight();
 }
 }

 UIFont getFont() {
 return font;
 }

 int getLineSpacing() {
 return lineSpacing;
 }

 void DrawText(UIFont _font, const std::string& text, double x, double y, double r, double g, double b, double _alpha) {
 if (!this->measureOnly) {
 super.DrawText(_font, text, x, y, r, g, b, _alpha);
 }
 }

 void DrawTextCentre(UIFont _font, const std::string& text, double x, double y, double r, double g, double b, double _alpha) {
 if (!this->measureOnly) {
 super.DrawTextCentre(_font, text, x, y, r, g, b, _alpha);
 }
 }

 void DrawTextRight(UIFont _font, const std::string& text, double x, double y, double r, double g, double b, double _alpha) {
 if (!this->measureOnly) {
 super.DrawTextRight(_font, text, x, y, r, g, b, _alpha);
 }
 }

 void DrawValueRight(int value, int x, int y, bool highGood) {
 int integer = value;
 std::string string = integer.toString();
 float float0 = 0.3F;
 float float1 = 1.0F;
 float float2 = 0.2F;
 float float3 = 1.0F;
 if (value > 0) {
 string = "+" + string;
 }

 if (value < 0 && highGood || value > 0 && !highGood) {
 float0 = 0.8F;
 float1 = 0.3F;
 float2 = 0.2F;
 }

 this->DrawTextRight(font, string, x, y, float0, float1, float2, float3);
 }

 void DrawValueRightNoPlus(int value, int x, int y) {
 int integer = value;
 std::string string = integer.toString();
 float float0 = 1.0F;
 float float1 = 1.0F;
 float float2 = 1.0F;
 float float3 = 1.0F;
 this->DrawTextRight(font, string, x, y, float0, float1, float2, float3);
 }

 void DrawValueRightNoPlus(float value, int x, int y) {
 float float0 = value;
 float0 = (int)((float0.floatValue() + 0.01) * 10.0) / 10.0F;
 std::string string = float0.toString();
 float float1 = 1.0F;
 float float2 = 1.0F;
 float float3 = 1.0F;
 float float4 = 1.0F;
 this->DrawTextRight(font, string, x, y, float1, float2, float3, float4);
 }

 void DrawTextureScaled(Texture tex, double x, double y, double width, double height, double _alpha) {
 if (!this->measureOnly) {
 super.DrawTextureScaled(tex, x, y, width, height, _alpha);
 }
 }

 void DrawTextureScaledAspect(Texture tex, double x, double y, double width, double height, double r, double g, double b, double _alpha) {
 if (!this->measureOnly) {
 super.DrawTextureScaledAspect(tex, x, y, width, height, r, g, b, _alpha);
 }
 }

 void DrawProgressBar(int x, int y, int w, int h, float f, double r, double g, double b, double a) {
 if (!this->measureOnly) {
 if (f < 0.0F) {
 f = 0.0F;
 }

 if (f > 1.0F) {
 f = 1.0F;
 }

 int int0 = (int)Math.floor(w * f);
 if (f > 0.0F && int0 == 0) {
 int0 = 1;
 }

 this->DrawTextureScaledColor(nullptr, (double)x, (double)y, (double)int0, 3.0, r, g, b, a);
 this->DrawTextureScaledColor(nullptr, (double)x + int0, (double)y, (double)w - int0, 3.0, 0.25, 0.25, 0.25, 1.0);
 }
 }

 bool onMouseMove(double dx, double dy) {
 this->setX(this->getX() + dx);
 this->setY(this->getY() + dy);
 return Boolean.FALSE;
 }

 void onMouseMoveOutside(double dx, double dy) {
 this->setX(this->getX() + dx);
 this->setY(this->getY() + dy);
 }

 void render() {
 if (this->isVisible()) {
 if (!(this->alpha <= 0.0F) {
 if (!this->bIsItem && this->Object != nullptr && this->Object.haveSpecialTooltip()) {
 this->Object.DoSpecialTooltip(this, this->Object.square);
 }

 super.render();
 }
 }
 }

 void show(IsoObject obj, double x, double y) {
 this->bIsItem = false;
 this->Object = obj;
 this->setX(x);
 this->setY(y);
 this->targetAlpha = 0.5F;
 this->showDelay = 15;
 this->alpha = 0.0F;
 }

 void hide() {
 this->Object = nullptr;
 this->showDelay = 0;
 this->setVisible(false);
 }

 void update() {
 if (!(this->alpha <= 0.0F) || this->targetAlpha != 0.0F) {
 if (this->showDelay > 0) {
 if (--this->showDelay == 0) {
 this->setVisible(true);
 }
 } else {
 if (this->alpha < this->targetAlpha) {
 this->alpha = this->alpha + alphaStep;
 if (this->alpha > 0.5F) {
 this->alpha = 0.5F;
 }
 } else if (this->alpha > this->targetAlpha) {
 this->alpha = this->alpha - alphaStep;
 if (this->alpha < this->targetAlpha) {
 this->alpha = this->targetAlpha;
 }
 }
 }
 }
 }

 void show(InventoryItem item, int var2, int var3) {
 this->Object = nullptr;
 this->Item = item;
 this->bIsItem = true;
 this->setX(this->getX());
 this->setY(this->getY());
 this->targetAlpha = 0.5F;
 this->showDelay = 15;
 this->alpha = 0.0F;
 this->setVisible(true);
 }

 void adjustWidth(int textX, const std::string& text) {
 int int0 = TextManager.instance.MeasureStringX(font, text);
 if (textX + int0 + this->padRight > this->width) {
 this->setWidth(textX + int0 + this->padRight);
 }
 }

 public ObjectTooltip.Layout beginLayout() {
 ObjectTooltip.Layout layout = nullptr;
 if (freeLayouts.empty()) {
 layout = new ObjectTooltip.Layout();
 } else {
 layout = freeLayouts.pop();
 }

 return layout;
 }

 void endLayout(ObjectTooltip.Layout layout) {
 while (layout != nullptr) {
 ObjectTooltip.Layout _layout = layout.next;
 layout.free();
 freeLayouts.push(layout);
 layout = _layout;
 }
 }

 Texture getTexture() {
 return this->texture;
 }

 void setCharacter(IsoGameCharacter chr) {
 this->character = chr;
 }

 IsoGameCharacter getCharacter() {
 return this->character;
 }

 void setMeasureOnly(bool b) {
 this->measureOnly = b;
 }

 bool isMeasureOnly() {
 return this->measureOnly;
 }

 float getWeightOfStack() {
 return this->weightOfStack;
 }

 void setWeightOfStack(float weight) {
 this->weightOfStack = weight;
 }

 public static class Layout {
 public ArrayList<ObjectTooltip.LayoutItem> items = std::make_unique<ArrayList<>>();
 int minLabelWidth;
 int minValueWidth;
 public ObjectTooltip.Layout next;
 int nextPadY;
 private static Stack<ObjectTooltip.LayoutItem> freeItems = std::make_unique<Stack<>>();

 public ObjectTooltip.LayoutItem addItem() {
 ObjectTooltip.LayoutItem layoutItem = nullptr;
 if (freeItems.empty()) {
 layoutItem = new ObjectTooltip.LayoutItem();
 } else {
 layoutItem = freeItems.pop();
 }

 layoutItem.reset();
 this->items.add(layoutItem);
 return layoutItem;
 }

 void setMinLabelWidth(int minWidth) {
 this->minLabelWidth = minWidth;
 }

 void setMinValueWidth(int minWidth) {
 this->minValueWidth = minWidth;
 }

 int render(int left, int top, ObjectTooltip ui) {
 int int0 = this->minLabelWidth;
 int int1 = this->minValueWidth;
 int int2 = this->minValueWidth;
 int int3 = 0;
 int int4 = 0;
 uint8_t byte0 = 8;
 int int5 = 0;

 for (int int6 = 0; int6 < this->items.size(); int6++) {
 ObjectTooltip.LayoutItem layoutItem0 = this->items.get(int6);
 layoutItem0.calcSizes();
 if (layoutItem0.hasValue) {
 int0 = Math.max(int0, layoutItem0.labelWidth);
 int1 = Math.max(int1, layoutItem0.valueWidth);
 int2 = Math.max(int2, layoutItem0.valueWidthRight);
 int3 = Math.max(int3, layoutItem0.progressWidth);
 int5 = Math.max(int5, Math.max(layoutItem0.labelWidth, this->minLabelWidth) + byte0);
 int4 = Math.max(int4, int0 + byte0 + Math.max(Math.max(int1, int2), int3);
 } else {
 int0 = Math.max(int0, layoutItem0.labelWidth);
 int4 = Math.max(int4, layoutItem0.labelWidth);
 }
 }

 if (left + int4 + ui.padRight > ui.width) {
 ui.setWidth(left + int4 + ui.padRight);
 }

 for (int int7 = 0; int7 < this->items.size(); int7++) {
 ObjectTooltip.LayoutItem layoutItem1 = this->items.get(int7);
 layoutItem1.render(left, top, int5, int2, ui);
 top += layoutItem1.height;
 }

 return this->next != nullptr ? this->next.render(left, top + this->next.nextPadY, ui) : top;
 }

 void free() {
 freeItems.addAll(this->items);
 this->items.clear();
 this->minLabelWidth = 0;
 this->minValueWidth = 0;
 this->next = nullptr;
 this->nextPadY = 0;
 }
 }

 public static class LayoutItem {
 std::string label;
 float r0;
 float g0;
 float b0;
 float a0;
 bool hasValue = false;
 std::string value;
 bool rightJustify = false;
 float r1;
 float g1;
 float b1;
 float a1;
 float progressFraction = -1.0F;
 int labelWidth;
 int valueWidth;
 int valueWidthRight;
 int progressWidth;
 int height;

 void reset() {
 this->label = nullptr;
 this->value = nullptr;
 this->hasValue = false;
 this->rightJustify = false;
 this->progressFraction = -1.0F;
 }

 void setLabel(const std::string& _label, float r, float g, float b, float a) {
 this->label = _label;
 this->r0 = r;
 this->b0 = b;
 this->g0 = g;
 this->a0 = a;
 }

 void setValue(const std::string& _label, float r, float g, float b, float a) {
 this->value = _label;
 this->r1 = r;
 this->b1 = b;
 this->g1 = g;
 this->a1 = a;
 this->hasValue = true;
 }

 void setValueRight(int _value, bool highGood) {
 this->value = Integer.toString(_value);
 if (_value > 0) {
 this->value = "+" + this->value;
 }

 if ((_value >= 0 || !highGood) && (_value <= 0 || highGood) {
 this->r1 = Core.getInstance().getGoodHighlitedColor().getR();
 this->g1 = Core.getInstance().getGoodHighlitedColor().getG();
 this->b1 = Core.getInstance().getGoodHighlitedColor().getB();
 } else {
 this->r1 = Core.getInstance().getBadHighlitedColor().getR();
 this->g1 = Core.getInstance().getBadHighlitedColor().getG();
 this->b1 = Core.getInstance().getBadHighlitedColor().getB();
 }

 this->a1 = 1.0F;
 this->hasValue = true;
 this->rightJustify = true;
 }

 void setValueRightNoPlus(float _value) {
 _value = (int)((_value + 0.005F) * 100.0F) / 100.0F;
 this->value = Float.toString(_value);
 this->r1 = 1.0F;
 this->g1 = 1.0F;
 this->b1 = 1.0F;
 this->a1 = 1.0F;
 this->hasValue = true;
 this->rightJustify = true;
 }

 void setValueRightNoPlus(int _value) {
 this->value = Integer.toString(_value);
 this->r1 = 1.0F;
 this->g1 = 1.0F;
 this->b1 = 1.0F;
 this->a1 = 1.0F;
 this->hasValue = true;
 this->rightJustify = true;
 }

 void setProgress(float fraction, float r, float g, float b, float a) {
 this->progressFraction = fraction;
 this->r1 = r;
 this->b1 = b;
 this->g1 = g;
 this->a1 = a;
 this->hasValue = true;
 }

 void calcSizes() {
 this->labelWidth = this->valueWidth = this->valueWidthRight = this->progressWidth = 0;
 if (this->label != nullptr) {
 this->labelWidth = TextManager.instance.MeasureStringX(ObjectTooltip.font, this->label);
 }

 if (this->hasValue) {
 if (this->value != nullptr) {
 int int0 = TextManager.instance.MeasureStringX(ObjectTooltip.font, this->value);
 this->valueWidth = this->rightJustify ? 0 : int0;
 this->valueWidthRight = this->rightJustify ? int0 : 0;
 } else if (this->progressFraction != -1.0F) {
 this->progressWidth = 80;
 }
 }

 int int1 = 1;
 if (this->label != nullptr) {
 int int2 = 1;

 for (int int3 = 0; int3 < this->label.length(); int3++) {
 if (this->label.charAt(int3) == '\n') {
 int2++;
 }
 }

 int1 = Math.max(int1, int2);
 }

 if (this->hasValue && this->value != nullptr) {
 int int4 = 1;

 for (int int5 = 0; int5 < this->value.length(); int5++) {
 if (this->value.charAt(int5) == '\n') {
 int4++;
 }
 }

 int1 = Math.max(int1, int4);
 }

 this->height = int1 * ObjectTooltip.lineSpacing;
 }

 void render(int x, int y, int mid, int right, ObjectTooltip ui) {
 if (this->label != nullptr) {
 ui.DrawText(ObjectTooltip.font, this->label, x, y, this->r0, this->g0, this->b0, this->a0);
 }

 if (this->value != nullptr) {
 if (this->rightJustify) {
 ui.DrawTextRight(ObjectTooltip.font, this->value, x + mid + right, y, this->r1, this->g1, this->b1, this->a1);
 } else {
 ui.DrawText(ObjectTooltip.font, this->value, x + mid, y, this->r1, this->g1, this->b1, this->a1);
 }
 }

 if (this->progressFraction != -1.0F) {
 ui.DrawProgressBar(
 x + mid, y + ObjectTooltip.lineSpacing / 2 - 1, this->progressWidth, 2, this->progressFraction, this->r1, this->g1, this->b1, this->a1
 );
 }
 }
 }
}
} // namespace ui
} // namespace zombie
