#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameTime.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/chat/ChatElement.h"
#include "zombie/core/Core.h"
#include "zombie/core/Rand.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/fonts/AngelCodeFont.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/network/GameServer.h"
#include <algorithm>

namespace zombie {
namespace ui {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class TextDrawObject {
public:
 private String[] validImages = new String[]{"Icon_music_notes", "media/ui/CarKey.png", "media/ui/ArrowUp.png", "media/ui/ArrowDown.png"};
 private String[] validFonts = new String[]{"Small", "Dialogue", "Medium", "Code", "Large", "Massive"};
 private ArrayList<TextDrawObject.DrawLine> lines = std::make_unique<ArrayList<>>();
 int width = 0;
 int height = 0;
 int maxCharsLine = -1;
 UIFont defaultFontEnum = UIFont.Dialogue;
 AngelCodeFont defaultFont = nullptr;
 std::string original = "";
 std::string unformatted = "";
 private TextDrawObject.DrawLine currentLine;
 private TextDrawObject.DrawElement currentElement;
 bool hasOpened = false;
 bool drawBackground = false;
 bool allowImages = true;
 bool allowChatIcons = true;
 bool allowColors = true;
 bool allowFonts = true;
 bool allowBBcode = true;
 bool allowAnyImage = false;
 bool allowLineBreaks = true;
 bool equalizeLineHeights = false;
 bool enabled = true;
 int visibleRadius = -1;
 float scrambleVal = 0.0F;
 float outlineR = 0.0F;
 float outlineG = 0.0F;
 float outlineB = 0.0F;
 float outlineA = 1.0F;
 float defaultR = 1.0F;
 float defaultG = 1.0F;
 float defaultB = 1.0F;
 float defaultA = 1.0F;
 int hearRange = -1;
 float internalClock = 0.0F;
 std::string customTag = "default";
 int customImageMaxDim = 18;
 TextDrawHorizontal defaultHorz = TextDrawHorizontal.Center;
 int drawMode = 0;
 private static ArrayList<TextDrawObject.RenderBatch> renderBatch = std::make_unique<ArrayList<>>();
 private static ArrayDeque<TextDrawObject.RenderBatch> renderBatchPool = std::make_unique<ArrayDeque<>>();
 std::string elemText;

 public TextDrawObject() {
 this(255, 255, 255, true, true, true, true, true, false);
 }

 public TextDrawObject(int r, int g, int b, bool _allowBBcode) {
 this(r, g, b, _allowBBcode, true, true, true, true, false);
 }

 public TextDrawObject(
 int r,
 int g,
 int b,
 boolean _allowBBcode,
 boolean _allowImages,
 boolean _allowChatIcons,
 boolean _allowColors,
 boolean _allowFonts,
 boolean _equalizeLineHeights
 ) {
 this->setSettings(_allowBBcode, _allowImages, _allowChatIcons, _allowColors, _allowFonts, _equalizeLineHeights);
 this->setDefaultColors(r, g, b);
 }

 void setEnabled(bool _enabled) {
 this->enabled = _enabled;
 }

 bool getEnabled() {
 return this->enabled;
 }

 void setVisibleRadius(int radius) {
 this->visibleRadius = radius;
 }

 int getVisibleRadius() {
 return this->visibleRadius;
 }

 void setDrawBackground(bool draw) {
 this->drawBackground = draw;
 }

 void setAllowImages(bool _allowImages) {
 this->allowImages = _allowImages;
 }

 void setAllowChatIcons(bool _allowChatIcons) {
 this->allowChatIcons = _allowChatIcons;
 }

 void setAllowColors(bool _allowColors) {
 this->allowColors = _allowColors;
 }

 void setAllowFonts(bool _allowFonts) {
 this->allowFonts = _allowFonts;
 }

 void setAllowBBcode(bool _allowBBcode) {
 this->allowBBcode = _allowBBcode;
 }

 void setAllowAnyImage(bool _allowAnyImage) {
 this->allowAnyImage = _allowAnyImage;
 }

 void setAllowLineBreaks(bool _allowLineBreaks) {
 this->allowLineBreaks = _allowLineBreaks;
 }

 void setEqualizeLineHeights(bool _equalizeLineHeights) {
 this->equalizeLineHeights = _equalizeLineHeights;
 this->calculateDimensions();
 }

 public void setSettings(
 boolean _allowBBcode, boolean _allowImages, boolean _allowChatIcons, boolean _allowColors, boolean _allowFonts, boolean _equalizeLineHeights
 ) {
 this->allowImages = _allowImages;
 this->allowChatIcons = _allowChatIcons;
 this->allowColors = _allowColors;
 this->allowFonts = _allowFonts;
 this->allowBBcode = _allowBBcode;
 this->equalizeLineHeights = _equalizeLineHeights;
 }

 void setCustomTag(const std::string& tag) {
 this->customTag = tag;
 }

 std::string getCustomTag() {
 return this->customTag;
 }

 void setValidImages(String[] strings) {
 this->validImages = strings;
 }

 void setValidFonts(String[] strings) {
 this->validFonts = strings;
 }

 void setMaxCharsPerLine(int charsperline) {
 if (charsperline > 0) {
 this->ReadString(this->original, charsperline);
 }
 }

 void setCustomImageMaxDimensions(int dim) {
 if (dim >= 1) {
 this->customImageMaxDim = dim;
 this->calculateDimensions();
 }
 }

 void setOutlineColors(int r, int g, int b) {
 this->setOutlineColors(r / 255.0F, g / 255.0F, b / 255.0F, 1.0F);
 }

 void setOutlineColors(int r, int g, int b, int a) {
 this->setOutlineColors(r / 255.0F, g / 255.0F, b / 255.0F, a / 255.0F);
 }

 void setOutlineColors(float r, float g, float b) {
 this->setOutlineColors(r, g, b, 1.0F);
 }

 void setOutlineColors(float r, float g, float b, float a) {
 this->outlineR = r;
 this->outlineG = g;
 this->outlineB = b;
 this->outlineA = a;
 }

 void setDefaultColors(int r, int g, int b) {
 this->setDefaultColors(r / 255.0F, g / 255.0F, b / 255.0F, 1.0F);
 }

 void setDefaultColors(int r, int g, int b, int a) {
 this->setDefaultColors(r / 255.0F, g / 255.0F, b / 255.0F, a / 255.0F);
 }

 void setDefaultColors(float r, float g, float b) {
 this->setDefaultColors(r, g, b, 1.0F);
 }

 void setDefaultColors(float r, float g, float b, float a) {
 this->defaultR = r;
 this->defaultG = g;
 this->defaultB = b;
 this->defaultA = a;
 }

 void setHorizontalAlign(const std::string& horz) {
 if (horz == "left")) {
 this->defaultHorz = TextDrawHorizontal.Left;
 } else if (horz == "center")) {
 this->defaultHorz = TextDrawHorizontal.Center;
 }

 if (horz == "right")) {
 this->defaultHorz = TextDrawHorizontal.Right;
 }
 }

 void setHorizontalAlign(TextDrawHorizontal horz) {
 this->defaultHorz = horz;
 }

 TextDrawHorizontal getHorizontalAlign() {
 return this->defaultHorz;
 }

 std::string getOriginal() {
 return this->original;
 }

 std::string getUnformatted() {
 if (!(this->scrambleVal > 0.0F) {
 return this->unformatted;
 } else {
 std::string string = "";

 for (TextDrawObject.DrawLine drawLine : this->lines) {
 for (TextDrawObject.DrawElement drawElement : drawLine.elements) {
 if (!drawElement.isImage) {
 string = string + drawElement.scrambleText;
 }
 }
 }

 return string;
 }
 }

 int getWidth() {
 return this->width;
 }

 int getHeight() {
 return this->height;
 }

 UIFont getDefaultFontEnum() {
 return this->defaultFontEnum;
 }

 bool isNullOrZeroLength() {
 return this->original == nullptr || this->original.length() == 0;
 }

 float getInternalClock() {
 return this->internalClock;
 }

 void setInternalTickClock(float ticks) {
 if (ticks > 0.0F) {
 this->internalClock = ticks;
 }
 }

 float updateInternalTickClock() {
 return this->updateInternalTickClock(1.25F * GameTime.getInstance().getMultiplier());
 }

 float updateInternalTickClock(float delta) {
 if (this->internalClock <= 0.0F) {
 return 0.0F;
 } else {
 this->internalClock -= delta;
 if (this->internalClock <= 0.0F) {
 this->internalClock = 0.0F;
 }

 return this->internalClock;
 }
 }

 void setScrambleVal(float value) {
 if (this->scrambleVal != value) {
 this->scrambleVal = value;
 if (this->scrambleVal > 0.0F) {
 for (TextDrawObject.DrawLine drawLine : this->lines) {
 for (TextDrawObject.DrawElement drawElement : drawLine.elements) {
 if (!drawElement.isImage) {
 drawElement.scrambleText(this->scrambleVal);
 }
 }
 }
 }
 }
 }

 float getScrambleVal() {
 return this->scrambleVal;
 }

 void setHearRange(int range) {
 if (range < 0) {
 this->hearRange = 0;
 } else {
 this->hearRange = range;
 }
 }

 int getHearRange() {
 return this->hearRange;
 }

 bool isValidFont(const std::string& string1) {
 for (String string0 : this->validFonts) {
 if (string1 == string0) && UIFont.FromString(string1) != nullptr) {
 return true;
 }
 }

 return false;
 }

 bool isValidImage(const std::string& string1) {
 for (String string0 : this->validImages) {
 if (string1 == string0) {
 return true;
 }
 }

 return false;
 }

 int tryColorInt(const std::string& string) {
 if (string.length() > 0 && string.length() <= 3) {
 try {
 int int0 = Integer.parseInt(string);
 return int0 >= 0 && int0 < 256 ? int0 : -1;
 } catch (NumberFormatException numberFormatException) {
 return -1;
 }
 } else {
 return -1;
 }
 }

 std::string readTagValue(char[] chars, int int0) {
 if (chars[int0] == '=') {
 std::string string = "";

 for (int int1 = int0 + 1; int1 < chars.length; int1++) {
 char char0 = chars[int1];
 if (char0 == ']') {
 return string;
 }

 string = string + char0;
 }
 }

 return nullptr;
 }

 void Clear() {
 this->original = "";
 this->unformatted = "";
 this->reset();
 }

 void reset() {
 this->lines.clear();
 this->currentLine = new TextDrawObject.DrawLine();
 this->lines.add(this->currentLine);
 this->currentElement = new TextDrawObject.DrawElement();
 this->currentLine.addElement(this->currentElement);
 this->enabled = true;
 this->scrambleVal = 0.0F;
 }

 void addNewLine() {
 this->currentLine = new TextDrawObject.DrawLine();
 this->lines.add(this->currentLine);
 this->currentElement = this->currentElement.softclone();
 this->currentLine.addElement(this->currentElement);
 }

 void addText(const std::string& string) {
 this->currentElement.addText(string);
 this->currentLine.charW = this->currentLine.charW + string.length();
 }

 void addWord(const std::string& string) {
 if (this->maxCharsLine > 0 && this->currentLine.charW + string.length() >= this->maxCharsLine) {
 for (int int0 = 0; int0 < string.length() / this->maxCharsLine + 1; int0++) {
 int int1 = int0 * this->maxCharsLine;
 int int2 = int1 + this->maxCharsLine < string.length() ? int1 + this->maxCharsLine : string.length();
 if (string.substring(int1, int2).length() > 0) {
 if (int0 > 0 || this->currentLine.charW != 0) {
 this->addNewLine();
 }

 this->addText(string.substring(int1, int2);
 }
 }
 } else {
 this->addText(string);
 }
 }

 void addNewElement() {
 if (this->currentElement.text.length() == 0) {
 this->currentElement.reset();
 } else {
 this->currentElement = new TextDrawObject.DrawElement();
 this->currentLine.addElement(this->currentElement);
 }
 }

 int readTag(char[] chars, int int0, const std::string& string0) {
 if (this->allowFonts && string0 == "fnt")) {
 std::string string1 = this->readTagValue(chars, int0);
 if (string1 != nullptr && this->isValidFont(string1) {
 this->addNewElement();
 this->currentElement.f = UIFont.FromString(string1);
 this->currentElement.useFont = true;
 this->currentElement.font = TextManager.instance.getFontFromEnum(this->currentElement.f);
 this->hasOpened = true;
 return int0 + string1.length() + 1;
 }
 } else if ((this->allowImages || this->allowChatIcons) && string0 == "img")) {
 std::string string2 = this->readTagValue(chars, int0);
 if (string2 != nullptr && string2.trim().length() > 0) {
 this->addNewElement();
 int int1 = string2.length();
 String[] strings0 = string2.split(",");
 if (strings0.length > 1) {
 string2 = strings0[0];
 }

 this->currentElement.isImage = true;
 this->currentElement.text = string2.trim();
 if (this->currentElement.text == "music")) {
 this->currentElement.text = "Icon_music_notes";
 }

 if (this->allowChatIcons && this->isValidImage(this->currentElement.text) {
 this->currentElement.tex = Texture.getSharedTexture(this->currentElement.text);
 this->currentElement.isTextImage = true;
 } else if (this->allowImages) {
 this->currentElement.tex = Texture.getSharedTexture("Item_" + this->currentElement.text);
 if (this->currentElement.tex == nullptr) {
 this->currentElement.tex = Texture.getSharedTexture("media/ui/Container_" + this->currentElement.text);
 }

 if (this->currentElement.tex != nullptr) {
 this->currentElement.isTextImage = false;
 this->currentElement.text = "Item_" + this->currentElement.text;
 }
 }

 if (this->allowAnyImage && this->currentElement.tex == nullptr) {
 this->currentElement.tex = Texture.getSharedTexture(this->currentElement.text);
 if (this->currentElement.tex != nullptr) {
 this->currentElement.isTextImage = false;
 }
 }

 if (strings0.length == 4) {
 int int2 = this->tryColorInt(strings0[1]);
 int int3 = this->tryColorInt(strings0[2]);
 int int4 = this->tryColorInt(strings0[3]);
 if (int2 != -1 && int3 != -1 && int4 != -1) {
 this->currentElement.useColor = true;
 this->currentElement.R = int2 / 255.0F;
 this->currentElement.G = int3 / 255.0F;
 this->currentElement.B = int4 / 255.0F;
 }
 }

 this->addNewElement();
 return int0 + int1 + 1;
 }
 } else if (this->allowColors && string0 == "col")) {
 std::string string3 = this->readTagValue(chars, int0);
 if (string3 != nullptr) {
 String[] strings1 = string3.split(",");
 if (strings1.length == 3) {
 int int5 = this->tryColorInt(strings1[0]);
 int int6 = this->tryColorInt(strings1[1]);
 int int7 = this->tryColorInt(strings1[2]);
 if (int5 != -1 && int6 != -1 && int7 != -1) {
 this->addNewElement();
 this->currentElement.useColor = true;
 this->currentElement.R = int5 / 255.0F;
 this->currentElement.G = int6 / 255.0F;
 this->currentElement.B = int7 / 255.0F;
 this->hasOpened = true;
 return int0 + string3.length() + 1;
 }
 }
 }
 } else if (string0 == "cdt")) {
 std::string string4 = this->readTagValue(chars, int0);
 if (string4 != nullptr) {
 float float0 = this->internalClock;

 try {
 float0 = Float.parseFloat(string4);
 float0 *= 60.0F;
 } catch (NumberFormatException numberFormatException) {
 numberFormatException.printStackTrace();
 }

 this->internalClock = float0;
 return int0 + string4.length() + 1;
 }
 }

 return -1;
 }

 void setDefaultFont(UIFont f) {
 if (!f == this->defaultFontEnum) {
 this->ReadString(f, this->original, this->maxCharsLine);
 }
 }

 void setDefaultFontInternal(UIFont uIFont) {
 if (this->defaultFont == nullptr || !uIFont == this->defaultFontEnum) {
 this->defaultFontEnum = uIFont;
 this->defaultFont = TextManager.instance.getFontFromEnum(uIFont);
 }
 }

 void ReadString(const std::string& str) {
 this->ReadString(this->defaultFontEnum, str, this->maxCharsLine);
 }

 void ReadString(const std::string& str, int maxLineWidth) {
 this->ReadString(this->defaultFontEnum, str, maxLineWidth);
 }

 void ReadString(UIFont font, const std::string& str, int maxLineWidth) {
 if (str == nullptr) {
 str = "";
 }

 this->reset();
 this->setDefaultFontInternal(font);
 if (this->defaultFont != nullptr) {
 this->maxCharsLine = maxLineWidth;
 this->original = str;
 char[] chars = str.toCharArray();
 this->hasOpened = false;
 std::string string0 = "";

 for (int int0 = 0; int0 < chars.length; int0++) {
 char char0 = chars[int0];
 if (this->allowBBcode && char0 == '[') {
 if (string0.length() > 0) {
 this->addWord(string0);
 string0 = "";
 }

 if (int0 + 4 < chars.length) {
 std::string string1 = ("" + chars[int0 + 1] + chars[int0 + 2] + chars[int0 + 3]).toLowerCase();
 if (this->allowLineBreaks && string1 == "br/")) {
 this->addNewLine();
 int0 += 4;
 continue;
 }

 if (!this->hasOpened) {
 int int1 = this->readTag(chars, int0 + 4, string1);
 if (int1 >= 0) {
 int0 = int1;
 continue;
 }
 }
 }

 if (this->hasOpened && int0 + 2 < chars.length && chars[int0 + 1] == '/' && chars[int0 + 2] == ']') {
 this->hasOpened = false;
 this->addNewElement();
 int0 += 2;
 continue;
 }
 }

 if (Character.isWhitespace(char0) && int0 > 0 && !Character.isWhitespace(chars[int0 - 1])) {
 this->addWord(string0);
 string0 = "";
 }

 string0 = string0 + char0;
 this->unformatted = this->unformatted + char0;
 }

 if (string0.length() > 0) {
 this->addWord(string0);
 }

 this->calculateDimensions();
 }
 }

 void calculateDimensions() {
 this->width = 0;
 this->height = 0;
 int int0 = 0;

 for (int int1 = 0; int1 < this->lines.size(); int1++) {
 TextDrawObject.DrawLine drawLine0 = this->lines.get(int1);
 drawLine0.h = 0;
 drawLine0.w = 0;

 for (int int2 = 0; int2 < drawLine0.elements.size(); int2++) {
 TextDrawObject.DrawElement drawElement = drawLine0.elements.get(int2);
 drawElement.w = 0;
 drawElement.h = 0;
 if (drawElement.isImage && drawElement.tex != nullptr) {
 if (drawElement.isTextImage) {
 drawElement.w = drawElement.tex.getWidth();
 drawElement.h = drawElement.tex.getHeight();
 } else {
 drawElement.w = (int)(drawElement.tex.getWidth() * 0.75F);
 drawElement.h = (int)(drawElement.tex.getHeight() * 0.75F);
 }
 } else if (drawElement.useFont && drawElement.font != nullptr) {
 drawElement.w = drawElement.font.getWidth(drawElement.text);
 drawElement.h = drawElement.font.getHeight(drawElement.text);
 } else if (this->defaultFont != nullptr) {
 drawElement.w = this->defaultFont.getWidth(drawElement.text);
 drawElement.h = this->defaultFont.getHeight(drawElement.text);
 }

 drawLine0.w = drawLine0.w + drawElement.w;
 if (drawElement.h > drawLine0.h) {
 drawLine0.h = drawElement.h;
 }
 }

 if (drawLine0.w > this->width) {
 this->width = drawLine0.w;
 }

 this->height = this->height + drawLine0.h;
 if (drawLine0.h > int0) {
 int0 = drawLine0.h;
 }
 }

 if (this->equalizeLineHeights) {
 this->height = 0;

 for (int int3 = 0; int3 < this->lines.size(); int3++) {
 TextDrawObject.DrawLine drawLine1 = this->lines.get(int3);
 drawLine1.h = int0;
 this->height += int0;
 }
 }
 }

 void Draw(double x, double y) {
 this->Draw(this->defaultHorz, x, y, this->defaultR, this->defaultG, this->defaultB, this->defaultA, false);
 }

 void Draw(double x, double y, bool drawOutlines) {
 this->Draw(this->defaultHorz, x, y, this->defaultR, this->defaultG, this->defaultB, this->defaultA, drawOutlines);
 }

 void Draw(double x, double y, bool drawOutlines, float alpha) {
 this->Draw(this->defaultHorz, x, y, this->defaultR, this->defaultG, this->defaultB, alpha, drawOutlines);
 }

 void Draw(double x, double y, double r, double g, double b, double a, bool drawOutlines) {
 this->Draw(this->defaultHorz, x, y, r, g, b, a, drawOutlines);
 }

 void Draw(TextDrawHorizontal horz, double x, double y, double r, double g, double b, double a, bool drawOutlines) {
 this->DrawRaw(horz, x, y, (float)r, (float)g, (float)b, (float)a, drawOutlines);
 }

 void AddBatchedDraw(double x, double y) {
 this->AddBatchedDraw(this->defaultHorz, x, y, this->defaultR, this->defaultG, this->defaultB, this->defaultA, false);
 }

 void AddBatchedDraw(double x, double y, bool drawOutlines) {
 this->AddBatchedDraw(this->defaultHorz, x, y, this->defaultR, this->defaultG, this->defaultB, this->defaultA, drawOutlines);
 }

 void AddBatchedDraw(double x, double y, bool drawOutlines, float alpha) {
 this->AddBatchedDraw(this->defaultHorz, x, y, this->defaultR, this->defaultG, this->defaultB, alpha, drawOutlines);
 }

 void AddBatchedDraw(double x, double y, double r, double g, double b, double a, bool drawOutlines) {
 this->AddBatchedDraw(this->defaultHorz, x, y, r, g, b, a, drawOutlines);
 }

 void AddBatchedDraw(TextDrawHorizontal horz, double x, double y, double r, double g, double b, double a, bool drawOutlines) {
 if (!GameServer.bServer) {
 TextDrawObject.RenderBatch renderBatchx = renderBatchPool.empty() ? new TextDrawObject.RenderBatch() : renderBatchPool.pop();
 renderBatchx.playerNum = IsoPlayer.getPlayerIndex();
 renderBatchx.element = this;
 renderBatchx.horz = horz;
 renderBatchx.x = x;
 renderBatchx.y = y;
 renderBatchx.r = (float)r;
 renderBatchx.g = (float)g;
 renderBatchx.b = (float)b;
 renderBatchx.a = (float)a;
 renderBatchx.drawOutlines = drawOutlines;
 renderBatch.add(renderBatchx);
 }
 }

 static void RenderBatch(int playerNum) {
 if (renderBatch.size() > 0) {
 for (int int0 = 0; int0 < renderBatch.size(); int0++) {
 TextDrawObject.RenderBatch renderBatchx = renderBatch.get(int0);
 if (renderBatchx.playerNum == playerNum) {
 renderBatchx.element
 .DrawRaw(
 renderBatchx.horz,
 renderBatchx.x,
 renderBatchx.y,
 renderBatchx.r,
 renderBatchx.g,
 renderBatchx.b,
 renderBatchx.a,
 renderBatchx.drawOutlines
 );
 renderBatchPool.add(renderBatchx);
 renderBatch.remove(int0--);
 }
 }
 }
 }

 static void NoRender(int playerNum) {
 for (int int0 = 0; int0 < renderBatch.size(); int0++) {
 TextDrawObject.RenderBatch renderBatchx = renderBatch.get(int0);
 if (renderBatchx.playerNum == playerNum) {
 renderBatchPool.add(renderBatchx);
 renderBatch.remove(int0--);
 }
 }
 }

 void DrawRaw(TextDrawHorizontal horz, double x, double y, float r, float g, float b, float a, bool drawOutlines) {
 double double0 = x;
 double double1 = y;
 double double2 = 0.0;
 int int0 = Core.getInstance().getScreenWidth();
 int int1 = Core.getInstance().getScreenHeight();
 uint8_t byte0 = 20;
 if (horz == TextDrawHorizontal.Center) {
 double0 = x - this->getWidth() / 2;
 } else if (horz == TextDrawHorizontal.Right) {
 double0 = x - this->getWidth();
 }

 if (!(double0 - byte0 >= int0) && !(double0 + this->getWidth() + byte0 <= 0.0) && !(y - byte0 >= int1) && !(y + this->getHeight() + byte0 <= 0.0) {
 if (this->drawBackground && ChatElement.backdropTexture != nullptr) {
 ChatElement.backdropTexture.renderInnerBased((int)double0, (int)y, this->getWidth(), this->getHeight(), 0.0F, 0.0F, 0.0F, 0.4F * a);
 }

 float float0 = this->outlineA;
 if (drawOutlines && a < 1.0F) {
 float0 = this->outlineA * a;
 }

 for (int int2 = 0; int2 < this->lines.size(); int2++) {
 TextDrawObject.DrawLine drawLine = this->lines.get(int2);
 double0 = x;
 if (horz == TextDrawHorizontal.Center) {
 double0 = x - drawLine.w / 2;
 } else if (horz == TextDrawHorizontal.Right) {
 double0 = x - drawLine.w;
 }

 for (int int3 = 0; int3 < drawLine.elements.size(); int3++) {
 TextDrawObject.DrawElement drawElement = drawLine.elements.get(int3);
 double2 = drawLine.h / 2 - drawElement.h / 2;
 this->elemText = this->scrambleVal > 0.0F ? drawElement.scrambleText : drawElement.text;
 if (drawElement.isImage && drawElement.tex != nullptr) {
 if (drawOutlines && drawElement.isTextImage) {
 SpriteRenderer.instance
 .renderi(
 drawElement.tex,
 (int)(double0 - 1.0),
 (int)(double1 + double2 - 1.0),
 drawElement.w,
 drawElement.h,
 this->outlineR,
 this->outlineG,
 this->outlineB,
 float0,
 nullptr
 );
 SpriteRenderer.instance
 .renderi(
 drawElement.tex,
 (int)(double0 + 1.0),
 (int)(double1 + double2 + 1.0),
 drawElement.w,
 drawElement.h,
 this->outlineR,
 this->outlineG,
 this->outlineB,
 float0,
 nullptr
 );
 SpriteRenderer.instance
 .renderi(
 drawElement.tex,
 (int)(double0 - 1.0),
 (int)(double1 + double2 + 1.0),
 drawElement.w,
 drawElement.h,
 this->outlineR,
 this->outlineG,
 this->outlineB,
 float0,
 nullptr
 );
 SpriteRenderer.instance
 .renderi(
 drawElement.tex,
 (int)(double0 + 1.0),
 (int)(double1 + double2 - 1.0),
 drawElement.w,
 drawElement.h,
 this->outlineR,
 this->outlineG,
 this->outlineB,
 float0,
 nullptr
 );
 }

 if (drawElement.useColor) {
 SpriteRenderer.instance
 .renderi(
 drawElement.tex,
 (int)double0,
 (int)(double1 + double2),
 drawElement.w,
 drawElement.h,
 drawElement.R,
 drawElement.G,
 drawElement.B,
 a,
 nullptr
 );
 } else if (drawElement.isTextImage) {
 SpriteRenderer.instance
 .renderi(drawElement.tex, (int)double0, (int)(double1 + double2), drawElement.w, drawElement.h, r, g, b, a, nullptr);
 } else {
 SpriteRenderer.instance
 .renderi(drawElement.tex, (int)double0, (int)(double1 + double2), drawElement.w, drawElement.h, 1.0F, 1.0F, 1.0F, a, nullptr);
 }
 } else if (drawElement.useFont && drawElement.font != nullptr) {
 if (drawOutlines) {
 drawElement.font
 .drawString(
 (float)(double0 - 1.0),
 (float)(double1 + double2 - 1.0),
 this->elemText,
 this->outlineR,
 this->outlineG,
 this->outlineB,
 float0
 );
 drawElement.font
 .drawString(
 (float)(double0 + 1.0),
 (float)(double1 + double2 + 1.0),
 this->elemText,
 this->outlineR,
 this->outlineG,
 this->outlineB,
 float0
 );
 drawElement.font
 .drawString(
 (float)(double0 - 1.0),
 (float)(double1 + double2 + 1.0),
 this->elemText,
 this->outlineR,
 this->outlineG,
 this->outlineB,
 float0
 );
 drawElement.font
 .drawString(
 (float)(double0 + 1.0),
 (float)(double1 + double2 - 1.0),
 this->elemText,
 this->outlineR,
 this->outlineG,
 this->outlineB,
 float0
 );
 }

 drawElement.font.drawString((float)double0, (float)(double1 + double2), this->elemText, r, g, b, a);
 } else if (this->defaultFont != nullptr) {
 if (drawOutlines) {
 this->defaultFont
 .drawString(
 (float)(double0 - 1.0),
 (float)(double1 + double2 - 1.0),
 this->elemText,
 this->outlineR,
 this->outlineG,
 this->outlineB,
 float0
 );
 this->defaultFont
 .drawString(
 (float)(double0 + 1.0),
 (float)(double1 + double2 + 1.0),
 this->elemText,
 this->outlineR,
 this->outlineG,
 this->outlineB,
 float0
 );
 this->defaultFont
 .drawString(
 (float)(double0 - 1.0),
 (float)(double1 + double2 + 1.0),
 this->elemText,
 this->outlineR,
 this->outlineG,
 this->outlineB,
 float0
 );
 this->defaultFont
 .drawString(
 (float)(double0 + 1.0),
 (float)(double1 + double2 - 1.0),
 this->elemText,
 this->outlineR,
 this->outlineG,
 this->outlineB,
 float0
 );
 }

 if (drawElement.useColor) {
 this->defaultFont
 .drawString((float)double0, (float)(double1 + double2), this->elemText, drawElement.R, drawElement.G, drawElement.B, a);
 } else {
 this->defaultFont.drawString((float)double0, (float)(double1 + double2), this->elemText, r, g, b, a);
 }
 }

 double0 += drawElement.w;
 }

 double1 += drawLine.h;
 }
 }
 }

 private static class DrawElement {
 std::string text = "";
 std::string scrambleText = "";
 float currentScrambleVal = 0.0F;
 UIFont f = UIFont.AutoNormSmall;
 AngelCodeFont font = nullptr;
 float R = 1.0F;
 float G = 1.0F;
 float B = 1.0F;
 int w = 0;
 int h = 0;
 bool isImage = false;
 bool useFont = false;
 bool useColor = false;
 Texture tex = nullptr;
 bool isTextImage = false;
 int charWidth = 0;

 void reset() {
 this->text = "";
 this->scrambleText = "";
 this->f = UIFont.AutoNormSmall;
 this->font = nullptr;
 this->R = 1.0F;
 this->G = 1.0F;
 this->B = 1.0F;
 this->w = 0;
 this->h = 0;
 this->isImage = false;
 this->useFont = false;
 this->useColor = false;
 this->tex = nullptr;
 this->isTextImage = false;
 this->charWidth = 0;
 }

 void addText(const std::string& string) {
 this->text = this->text + string;
 this->charWidth = this->text.length();
 }

 void scrambleText(float float0) {
 if (float0 != this->currentScrambleVal) {
 this->currentScrambleVal = float0;
 int int0 = (int)(float0 * 100.0F);
 String[] strings = this->text.split("\\s+");
 this->scrambleText = "";

 for (auto& string : strings) int int1 = Rand.Next(100);
 if (int1 > int0) {
 this->scrambleText = this->scrambleText + string + " ";
 } else {
 char[] chars = new char[string.length()];
 Arrays.fill(chars, ".".charAt(0);
 this->scrambleText = this->scrambleText + new String(chars) + " ";
 }
 }
 }
 }

 void trim() {
 this->text = this->text.trim();
 }

 private TextDrawObject.DrawElement softclone() {
 TextDrawObject.DrawElement drawElement0 = new TextDrawObject.DrawElement();
 if (this->useColor) {
 drawElement0.R = this->R;
 drawElement0.G = this->G;
 drawElement0.B = this->B;
 drawElement0.useColor = this->useColor;
 }

 if (this->useFont) {
 drawElement0.f = this->f;
 drawElement0.font = this->font;
 drawElement0.useFont = this->useFont;
 }

 return drawElement0;
 }
 }

 private static class DrawLine {
 private ArrayList<TextDrawObject.DrawElement> elements = std::make_unique<ArrayList<>>();
 int h = 0;
 int w = 0;
 int charW = 0;

 void addElement(TextDrawObject.DrawElement drawElement) {
 this->elements.add(drawElement);
 }
 }

 private static class RenderBatch {
 int playerNum;
 TextDrawObject element;
 TextDrawHorizontal horz;
 double x;
 double y;
 float r;
 float g;
 float b;
 float a;
 bool drawOutlines;
 }
}
} // namespace ui
} // namespace zombie
