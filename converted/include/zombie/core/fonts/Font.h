#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Color.h"

namespace zombie {
namespace core {
namespace fonts {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class Font {
public:
 virtual ~Font() = default;
 /**
 * Draw a string to the screen
 * 
 * @param x The x location at which to draw the string
 * @param y The y location at which to draw the string
 * @param text The text to be displayed
 */
 void drawString(float x, float y, const std::string& text);

 /**
 * Draw a string to the screen
 * 
 * @param x The x location at which to draw the string
 * @param y The y location at which to draw the string
 * @param text The text to be displayed
 * @param col The colour to draw with
 */
 void drawString(float x, float y, const std::string& text, Color col);

 /**
 * Draw part of a string to the screen. Note that this will still position the text as though it's part of the bigger string.
 * 
 * @param x The x location at which to draw the string
 * @param y The y location at which to draw the string
 * @param text The text to be displayed
 * @param col The colour to draw with
 * @param startIndex The index of the first character to draw
 * @param endIndex The index of the last character from the string to draw
 */
 void drawString(float x, float y, const std::string& text, Color col, int startIndex, int endIndex);

 /**
 * get the height of the given string
 * 
 * @param str The string to obtain the rendered with of
 * @return The width of the given string
 */
 int getHeight(const std::string& str);

 /**
 * get the width of the given string
 * 
 * @param str The string to obtain the rendered with of
 * @return The width of the given string
 */
 int getWidth(const std::string& str);

 int getWidth(const std::string& str, bool xAdvance);

 int getWidth(const std::string& str, int startIndex, int endIndex);

 int getWidth(const std::string& str, int startIndex, int endIndex, bool xAdvance);

 /**
 * get the maximum height of any line drawn by this font
 * @return The maxium height of any line drawn by this font
 */
 int getLineHeight();
}
} // namespace fonts
} // namespace core
} // namespace zombie
