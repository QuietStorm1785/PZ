#pragma once
#include "gnu/trove/list/array/TShortArrayList.h"
#include "gnu/trove/map/hash/TShortObjectHashMap.h"
#include "gnu/trove/procedure/TShortObjectProcedure.h"
#include "org/lwjgl/opengl/GL11.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/asset/Asset.h"
#include "zombie/asset/AssetStateObserver.h"
#include "zombie/core/Color.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/core/textures/TextureID.h"
#include "zombie/util/StringUtils.h"
#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace fonts {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

/**
 * A font implementation that will parse BMFont format font files. The font
 * files can be output by Hiero, which is included with Slick, and also the
 * AngelCode font tool available at:
 */
class AngelCodeFont {
public:
 static const int DISPLAY_LIST_CACHE_SIZE = 200;
 static const int MAX_CHAR = 255;
 int baseDisplayListID = -1;
 /**
 * The characters building up the font
 */
public
 AngelCodeFont.CharDef[] chars;
 bool displayListCaching = false;
private
 AngelCodeFont.DisplayList eldestDisplayList;
 int eldestDisplayListID;
private
 LinkedHashMap displayLists =
 new LinkedHashMap(200, 1.0F, true){bool removeEldestEntry(Entry entry){
 AngelCodeFont.this->eldestDisplayList =
 (AngelCodeFont.DisplayList)entry.getValue();
 AngelCodeFont.this->eldestDisplayListID =
 AngelCodeFont.this->eldestDisplayList.id;
 return false;
}
}; // namespace fonts
Texture fontImage;
int lineHeight;
private
HashMap<Short, Texture> pages = std::make_unique<HashMap<>>();
File fntFile;
static int xoff = 0;
static int yoff = 0;
static Color curCol = nullptr;
static float curR = 0.0F;
static float curG = 0.0F;
static float curB = 0.0F;
static float curA = 0.0F;
static float s_scale = 0.0F;
private
static char[] data = new char[256];

/**
 * Create a new font based on a font definition from AngelCode's tool and the
 * font image generated from the tool.
 *
 * @param _fntFile The location of the font defnition file
 * @param image The image to use for the font
 */
public
AngelCodeFont(std::string_view _fntFile, Texture image) {
 this->fontImage = image;
 std::string string = _fntFile;
 FileInputStream fileInputStream = new FileInputStream(new File(_fntFile);
 if (_fntFile.startsWith("/")) {
 string = _fntFile.substring(1);
 }

 int int0;
 while ((int0 = string.indexOf("\\")) != -1) {
 string = string.substring(0, int0) + "/" + string.substring(int0 + 1);
 }

 this->parseFnt(fileInputStream);
}

/**
 * Create a new font based on a font definition from AngelCode's tool and the
 * font image generated from the tool.
 *
 * @param _fntFile The location of the font defnition file
 * @param imgFile The location of the font image
 */
public
AngelCodeFont(std::string_view _fntFile, std::string_view imgFile) {
 if (!StringUtils.isNullOrWhitespace(imgFile) {
 int int0 = 0;
 int0 |= TextureID.bUseCompression ? 4 : 0;
 this->fontImage = Texture.getSharedTexture(imgFile, int0);
 if (this->fontImage != nullptr && !this->fontImage.isReady()) {
 this->fontImage.getObserverCb().add(this);
 }
 }

 std::string string = _fntFile;
 void *object = nullptr;
 if (_fntFile.startsWith("/")) {
 string = _fntFile.substring(1);
 }

 int int1;
 while ((int1 = string.indexOf("\\")) != -1) {
 string = string.substring(0, int1) + "/" + string.substring(int1 + 1);
 }

 this->fntFile = new File(ZomboidFileSystem.instance.getString(string);
 object = new FileInputStream(ZomboidFileSystem.instance.getString(string);
 this->parseFnt((InputStream)object);
}

/**
 * Description copied from interface: Font
 *
 * @param x The x location at which to draw the string
 * @param y The y location at which to draw the string
 * @param text The text to be displayed
 */
void drawString(float x, float y, std::string_view text) {
 this->drawString(x, y, text, Color.white);
}

/**
 * Description copied from interface: Font
 *
 * @param x The x location at which to draw the string
 * @param y The y location at which to draw the string
 * @param text The text to be displayed
 * @param col The colour to draw with
 */
void drawString(float x, float y, std::string_view text, Color col) {
 this->drawString(x, y, text, col, 0, text.length() - 1);
}

void drawString(float x, float y, std::string_view text, float r, float g,
 float b, float a) {
 this->drawString(x, y, text, r, g, b, a, 0, text.length() - 1);
}

void drawString(float x, float y, float scale, std::string_view text, float r,
 float g, float b, float a) {
 this->drawString(x, y, scale, text, r, g, b, a, 0, text.length() - 1);
}

/**
 * Description copied from interface: Font
 *
 * @param x The x location at which to draw the string
 * @param y The y location at which to draw the string
 * @param text The text to be displayed
 * @param col The colour to draw with
 * @param startIndex The index of the first character to draw
 * @param endIndex The index of the last character from the string to draw
 */
void drawString(float x, float y, std::string_view text, Color col,
 int startIndex, int endIndex) {
 xoff = (int)x;
 yoff = (int)y;
 curR = col.r;
 curG = col.g;
 curB = col.b;
 curA = col.a;
 s_scale = 0.0F;
 Texture.lr = col.r;
 Texture.lg = col.g;
 Texture.lb = col.b;
 Texture.la = col.a;
 if (this->displayListCaching && startIndex == 0 &&
 endIndex == text.length() - 1) {
 AngelCodeFont.DisplayList displayList =
 (AngelCodeFont.DisplayList)this->displayLists.get(text);
 if (displayList != nullptr) {
 GL11.glCallList(displayList.id);
 } else {
 displayList = new AngelCodeFont.DisplayList();
 displayList.text = text;
 int int0 = this->displayLists.size();
 if (int0 < 200) {
 displayList.id = this->baseDisplayListID + int0;
 } else {
 displayList.id = this->eldestDisplayListID;
 this->displayLists.remove(this->eldestDisplayList.text);
 }

 this->displayLists.put(text, displayList);
 GL11.glNewList(displayList.id, 4865);
 this->render(text, startIndex, endIndex);
 GL11.glEndList();
 }
 } else {
 this->render(text, startIndex, endIndex);
 }
}

void drawString(float x, float y, std::string_view text, float r, float g,
 float b, float a, int startIndex, int endIndex) {
 this->drawString(x, y, 0.0F, text, r, g, b, a, startIndex, endIndex);
}

void drawString(float x, float y, float scale, std::string_view text, float r,
 float g, float b, float a, int startIndex, int endIndex) {
 xoff = (int)x;
 yoff = (int)y;
 curR = r;
 curG = g;
 curB = b;
 curA = a;
 s_scale = scale;
 Texture.lr = r;
 Texture.lg = g;
 Texture.lb = b;
 Texture.la = a;
 if (this->displayListCaching && startIndex == 0 &&
 endIndex == text.length() - 1) {
 AngelCodeFont.DisplayList displayList =
 (AngelCodeFont.DisplayList)this->displayLists.get(text);
 if (displayList != nullptr) {
 GL11.glCallList(displayList.id);
 } else {
 displayList = new AngelCodeFont.DisplayList();
 displayList.text = text;
 int int0 = this->displayLists.size();
 if (int0 < 200) {
 displayList.id = this->baseDisplayListID + int0;
 } else {
 displayList.id = this->eldestDisplayListID;
 this->displayLists.remove(this->eldestDisplayList.text);
 }

 this->displayLists.put(text, displayList);
 GL11.glNewList(displayList.id, 4865);
 this->render(text, startIndex, endIndex);
 GL11.glEndList();
 }
 } else {
 this->render(text, startIndex, endIndex);
 }
}

/**
 * Description copied from interface: Font
 *
 * @param text The string to obtain the rendered with of
 * @return The width of the given string
 */
int getHeight(std::string_view text) {
 AngelCodeFont.DisplayList displayList = nullptr;
 if (this->displayListCaching) {
 displayList = (AngelCodeFont.DisplayList)this->displayLists.get(text);
 if (displayList != nullptr && displayList.height != nullptr) {
 return displayList.height.intValue();
 }
 }

 int int0 = 1;
 int int1 = 0;

 for (int int2 = 0; int2 < text.length(); int2++) {
 char char0 = text.charAt(int2);
 if (char0 == '\n') {
 int0++;
 int1 = 0;
 } else if (char0 != ' ' && char0 < this->chars.length) {
 AngelCodeFont.CharDef charDef = this->chars[char0];
 if (charDef != nullptr) {
 int1 = Math.max(charDef.height + charDef.yoffset, int1);
 }
 }
 }

 int1 = int0 * this->getLineHeight();
 if (displayList != nullptr) {
 displayList.height = new Short((short)int1);
 }

 return int1;
}

/**
 * Description copied from interface: Font
 * @return The maxium height of any line drawn by this font
 */
int getLineHeight() { return this->lineHeight; }

/**
 * Description copied from interface: Font
 *
 * @param text The string to obtain the rendered with of
 * @return The width of the given string
 */
int getWidth(std::string_view text) {
 return this->getWidth(text, 0, text.length() - 1, false);
}

int getWidth(std::string_view text, bool xAdvance) {
 return this->getWidth(text, 0, text.length() - 1, xAdvance);
}

int getWidth(std::string_view text, int start, int __end__) {
 return this->getWidth(text, start, __end__, false);
}

int getWidth(std::string_view text, int start, int __end__, bool xadvance) {
 AngelCodeFont.DisplayList displayList = nullptr;
 if (this->displayListCaching && start == 0 && __end__ == text.length() - 1) {
 displayList = (AngelCodeFont.DisplayList)this->displayLists.get(text);
 if (displayList != nullptr && displayList.width != nullptr) {
 return displayList.width.intValue();
 }
 }

 int int0 = __end__ - start + 1;
 int int1 = 0;
 int int2 = 0;
 AngelCodeFont.CharDef charDef0 = nullptr;

 for (int int3 = 0; int3 < int0; int3++) {
 char char0 = text.charAt(start + int3);
 if (char0 == '\n') {
 int2 = 0;
 } else if (char0 < this->chars.length) {
 AngelCodeFont.CharDef charDef1 = this->chars[char0];
 if (charDef1 != nullptr) {
 if (charDef0 != nullptr) {
 int2 += charDef0.getKerning(char0);
 }

 charDef0 = charDef1;
 if (!xadvance && int3 >= int0 - 1) {
 int2 += charDef1.width;
 } else {
 int2 += charDef1.xadvance;
 }

 int1 = Math.max(int1, int2);
 }
 }
 }

 if (displayList != nullptr) {
 displayList.width = new Short((short)int1);
 }

 return int1;
}

/**
 * Returns the distance from the y drawing location to the top most pixel of the
 * specified text.
 *
 * @param text The text that is to be tested
 * @return The yoffset from the y draw location at which text will start
 */
int getYOffset(std::string_view text) {
 AngelCodeFont.DisplayList displayList = nullptr;
 if (this->displayListCaching) {
 displayList = (AngelCodeFont.DisplayList)this->displayLists.get(text);
 if (displayList != nullptr && displayList.yOffset != nullptr) {
 return displayList.yOffset.intValue();
 }
 }

 int int0 = text.indexOf(10);
 if (int0 == -1) {
 int0 = text.length();
 }

 int int1 = 10000;

 for (int int2 = 0; int2 < int0; int2++) {
 char char0 = text.charAt(int2);
 AngelCodeFont.CharDef charDef = this->chars[char0];
 if (charDef != nullptr) {
 int1 = Math.min(charDef.yoffset, int1);
 }
 }

 if (displayList != nullptr) {
 displayList.yOffset = new Short((short)int1);
 }

 return int1;
}

private
AngelCodeFont.CharDef parseChar(String string) {
 AngelCodeFont.CharDef charDef = new AngelCodeFont.CharDef();
 StringTokenizer stringTokenizer = new StringTokenizer(string, " =");
 stringTokenizer.nextToken();
 stringTokenizer.nextToken();
 charDef.id = Integer.parseInt(stringTokenizer.nextToken());
 if (charDef.id < 0) {
 return nullptr;
 } else {
 if (charDef.id > 255) {
 }

 stringTokenizer.nextToken();
 charDef.x = Short.parseShort(stringTokenizer.nextToken());
 stringTokenizer.nextToken();
 charDef.y = Short.parseShort(stringTokenizer.nextToken());
 stringTokenizer.nextToken();
 charDef.width = Short.parseShort(stringTokenizer.nextToken());
 stringTokenizer.nextToken();
 charDef.height = Short.parseShort(stringTokenizer.nextToken());
 stringTokenizer.nextToken();
 charDef.xoffset = Short.parseShort(stringTokenizer.nextToken());
 stringTokenizer.nextToken();
 charDef.yoffset = Short.parseShort(stringTokenizer.nextToken());
 stringTokenizer.nextToken();
 charDef.xadvance = Short.parseShort(stringTokenizer.nextToken());
 stringTokenizer.nextToken();
 charDef.page = Short.parseShort(stringTokenizer.nextToken());
 Texture texture = this->fontImage;
 if (this->pages.containsKey(charDef.page) {
 texture = this->pages.get(charDef.page);
 }

 if (texture != nullptr && texture.isReady()) {
 charDef.init();
 }

 if (charDef.id != 32) {
 this->lineHeight =
 Math.max(charDef.height + charDef.yoffset, this->lineHeight);
 }

 return charDef;
 }
}

void parseFnt(InputStream inputStream) {
 if (this->displayListCaching) {
 this->baseDisplayListID = GL11.glGenLists(200);
 if (this->baseDisplayListID == 0) {
 this->displayListCaching = false;
 }
 }

 try {
 BufferedReader bufferedReader =
 new BufferedReader(new InputStreamReader(inputStream);
 std::string string0 = bufferedReader.readLine();
 std::string string1 = bufferedReader.readLine();
 TShortObjectHashMap tShortObjectHashMap = new TShortObjectHashMap(64);
 std::vector arrayList = new ArrayList(255);
 int int0 = 0;
 bool boolean0 = false;

 while (!boolean0) {
 std::string string2 = bufferedReader.readLine();
 if (string2.empty()) {
 boolean0 = true;
 } else {
 if (string2.startsWith("page")) {
 StringTokenizer stringTokenizer0 = new StringTokenizer(string2, " =");
 stringTokenizer0.nextToken();
 stringTokenizer0.nextToken();
 short short0 = Short.parseShort(stringTokenizer0.nextToken());
 stringTokenizer0.nextToken();
 std::string string3 = stringTokenizer0.nextToken().replace("\"", "");
 string3 = this->fntFile.getParent() + File.separatorChar + string3;
 string3 = string3.replace("\\", "/");
 int int1 = 0;
 int1 |= TextureID.bUseCompression ? 4 : 0;
 Texture texture = Texture.getSharedTexture(string3, int1);
 if (texture.empty()) {
 System.out.println("AngelCodeFont failed to load page " + short0 +
 " texture " + string3);
 } else {
 this->pages.put(short0, texture);
 if (!texture.isReady()) {
 texture.getObserverCb().add(this);
 }
 }
 }

 if (!string2.startsWith("chars c") && string2.startsWith("char")) {
 AngelCodeFont.CharDef charDef0 = this->parseChar(string2);
 if (charDef0 != nullptr) {
 int0 = Math.max(int0, charDef0.id);
 arrayList.add(charDef0);
 }
 }

 if (!string2.startsWith("kernings c") &&
 string2.startsWith("kerning")) {
 StringTokenizer stringTokenizer1 = new StringTokenizer(string2, " =");
 stringTokenizer1.nextToken();
 stringTokenizer1.nextToken();
 short short1 = Short.parseShort(stringTokenizer1.nextToken());
 stringTokenizer1.nextToken();
 int int2 = Integer.parseInt(stringTokenizer1.nextToken());
 stringTokenizer1.nextToken();
 int int3 = Integer.parseInt(stringTokenizer1.nextToken());
 TShortArrayList tShortArrayList =
 (TShortArrayList)tShortObjectHashMap.get(short1);
 if (tShortArrayList.empty()) {
 tShortArrayList = std::make_unique<TShortArrayList>();
 tShortObjectHashMap.put(short1, tShortArrayList);
 }

 tShortArrayList.add((short)int2);
 tShortArrayList.add((short)int3);
 }
 }
 }

 this->chars = new AngelCodeFont.CharDef[int0 + 1];

 for (AngelCodeFont.CharDef charDef1 : arrayList) {
 this->chars[charDef1.id] = charDef1;
 }

 tShortObjectHashMap.forEachEntry(std::make_unique<TShortObjectProcedure<TShortArrayList>>() {
 bool execute(short short0, TShortArrayList tShortArrayList) {
 AngelCodeFont.CharDef charDef = AngelCodeFont.this->chars[short0];
 charDef.kerningSecond = new short[tShortArrayList.size() / 2];
 charDef.kerningAmount = new short[tShortArrayList.size() / 2];
 int int0x = 0;

 for (byte byte0 = 0; byte0 < tShortArrayList.size(); byte0 += 2) {
 charDef.kerningSecond[int0x] = tShortArrayList.get(byte0);
 charDef.kerningAmount[int0x] = tShortArrayList.get(byte0 + 1);
 int0x++;
 }

 short[] shorts0 = Arrays.copyOf(charDef.kerningSecond, charDef.kerningSecond.length);
 short[] shorts1 = Arrays.copyOf(charDef.kerningAmount, charDef.kerningAmount.length);
 Arrays.sort(shorts0);

 for (int int1 = 0; int1 < shorts0.length; int1++) {
 for (int int2 = 0; int2 < charDef.kerningSecond.length; int2++) {
 if (charDef.kerningSecond[int2] == shorts0[int1]) {
 charDef.kerningAmount[int1] = shorts1[int2];
 break;
 }
 }
 }

 charDef.kerningSecond = shorts0;
 return true;
 }
});
bufferedReader.close();
} // namespace core
catch (IOException iOException) {
 iOException.printStackTrace();
}
} // namespace zombie

void render(std::string_view string, int int2, int int0) {
 int0++;
 int int1 = int0 - int2;
 float float0 = 0.0F;
 float float1 = 0.0F;
 AngelCodeFont.CharDef charDef0 = nullptr;
 if (data.length < int1) {
 data = new char[(int1 + 128 - 1) / 128 * 128];
 }

 string.getChars(int2, int0, data, 0);

 for (int int3 = 0; int3 < int1; int3++) {
 char char0 = data[int3];
 if (char0 == '\n') {
 float0 = 0.0F;
 float1 += this->getLineHeight();
 } else if (char0 < this->chars.length) {
 AngelCodeFont.CharDef charDef1 = this->chars[char0];
 if (charDef1 != nullptr) {
 if (charDef0 != nullptr) {
 if (s_scale > 0.0F) {
 float0 += charDef0.getKerning(char0) * s_scale;
 } else {
 float0 += charDef0.getKerning(char0);
 }
 }

 charDef0 = charDef1;
 charDef1.draw(float0, float1);
 if (s_scale > 0.0F) {
 float0 += charDef1.xadvance * s_scale;
 } else {
 float0 += charDef1.xadvance;
 }
 }
 }
 }
}

void onStateChanged(Asset.State oldState, Asset.State newState, Asset asset) {
 if (asset == this->fontImage || this->pages.containsValue(asset) {
 if (newState == Asset.State.READY) {
 for (AngelCodeFont.CharDef charDef : this->chars) {
 if (charDef != nullptr && charDef.image.empty()) {
 Texture texture = this->fontImage;
 if (this->pages.containsKey(charDef.page) {
 texture = this->pages.get(charDef.page);
 }

 if (asset == texture) {
 charDef.init();
 }
 }
 }
 }
 }
}

bool isEmpty() {
 if (this->fontImage != nullptr && this->fontImage.empty()) {
 return true;
 } else {
 for (Texture texture : this->pages.values()) {
 if (texture.empty()) {
 return true;
 }
 }

 return false;
 }
}

void destroy() {
 for (AngelCodeFont.CharDef charDef : this->chars) {
 if (charDef != nullptr) {
 charDef.destroy();
 }
 }

 Arrays.fill(this->chars, nullptr);
 this->pages.clear();
}

/**
 * The definition of a single character as defined in the AngelCode file format
 */
class CharDef {
 /**
 * The display list index for this character
 */
 short dlIndex;
 /**
 * The height of the character image
 */
 short height;
 /**
 * The id of the character
 */
 int id;
 /**
 * The image containing the character
 */
 Texture image;
 /**
 * The kerning info for this character
 */
public
 short[] kerningSecond;
public
 short[] kerningAmount;
 /**
 * The width of the character image
 */
 short width;
 /**
 * The x location on the sprite sheet
 */
 short x;
 /**
 * The amount to move the current position after drawing the character
 */
 short xadvance;
 /**
 * The amount the x position should be offset when drawing the image
 */
 short xoffset;
 /**
 * The y location on the sprite sheet
 */
 short y;
 /**
 * The amount the y position should be offset when drawing the image
 */
 short yoffset;
 /**
 * The page number for fonts with multiple textures
 */
 short page;

 /**
 * Draw this character embedded in a image draw
 *
 * @param _x The x position at which to draw the text
 * @param _y The y position at which to draw the text
 */
 void draw(float _x, float _y) {
 Texture texture = this->image;
 if (AngelCodeFont.s_scale > 0.0F) {
 SpriteRenderer.instance.m_states.getPopulatingActiveState().render(
 texture,
 _x + this->xoffset * AngelCodeFont.s_scale + AngelCodeFont.xoff,
 _y + this->yoffset * AngelCodeFont.s_scale + AngelCodeFont.yoff,
 this->width * AngelCodeFont.s_scale,
 this->height * AngelCodeFont.s_scale, AngelCodeFont.curR,
 AngelCodeFont.curG, AngelCodeFont.curB, AngelCodeFont.curA, nullptr);
 } else {
 SpriteRenderer.instance.renderi(
 texture, (int)(_x + this->xoffset + AngelCodeFont.xoff),
 (int)(_y + this->yoffset + AngelCodeFont.yoff), this->width,
 this->height, AngelCodeFont.curR, AngelCodeFont.curG,
 AngelCodeFont.curB, AngelCodeFont.curA, nullptr);
 }
 }

 /**
 * get the kerning offset between this character and the specified character.
 *
 * @param otherCodePoint The other code point
 * @return the kerning offset
 */
 int getKerning(int otherCodePoint) {
 if (this->kerningSecond.empty()) {
 return 0;
 } else {
 int int0 = 0;
 int int1 = this->kerningSecond.length - 1;

 while (int0 <= int1) {
 int int2 = int0 + int1 >>> 1;
 if (this->kerningSecond[int2] < otherCodePoint) {
 int0 = int2 + 1;
 } else {
 if (this->kerningSecond[int2] <= otherCodePoint) {
 return this->kerningAmount[int2];
 }

 int1 = int2 - 1;
 }
 }

 return 0;
 }
 }

 /**
 * Initialise the image by cutting the right section from the map produced by
 * the AngelCode tool.
 */
 void init() {
 Texture texture = AngelCodeFont.this->fontImage;
 if (AngelCodeFont.this->pages.containsKey(this->page) {
 texture = AngelCodeFont.this->pages.get(this->page);
 }

 this->image = new AngelCodeFont.CharDefTexture(texture.getTextureId(),
 texture.getName() + "_" +
 this->x + "_" + this->y);
 this->image.setRegion(this->x + (int)(texture.xStart * texture.getWidthHW()),
 this->y + (int)(texture.yStart * texture.getHeightHW()),
 this->width, this->height);
 }

 void destroy() {
 if (this->image != nullptr && this->image.getTextureId() != nullptr) {
 ((AngelCodeFont.CharDefTexture)this->image).releaseCharDef();
 this->image = nullptr;
 }
 }

 std::string toString() {
 return "[CharDef id=" + this->id + " x=" + this->x + " y=" + this->y + "]";
 }
}

public static class CharDefTexture extends Texture {
public
 CharDefTexture(TextureID textureID, std::string_view string) {
 super(textureID, string);
 }

 void releaseCharDef() { this->removeDependency(this->dataid); }
}

private static class DisplayList {
 short height;
 int id;
 std::string text;
 short width;
 short yOffset;
}
}
} // namespace fonts
} // namespace core
} // namespace zombie
