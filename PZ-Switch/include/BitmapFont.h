#pragma once
#include <SDL2/SDL.h>
#include <string>
#include <string_view>
#include <unordered_map>

namespace zombie {
namespace graphics {

/**
 * Character glyph information
 */
struct CharGlyph {
 int id; // Character code
 int x, y; // Position in texture
 int width, height; // Size in texture
 int xoffset, yoffset; // Rendering offset
 int xadvance; // Horizontal advance
 int page; // Texture page
 
 CharGlyph() : id(0), x(0), y(0), width(0), height(0),
 xoffset(0), yoffset(0), xadvance(0), page(0) {}
};

/**
 * BitmapFont - AngelCode BMFont format (.fnt) renderer
 */
class BitmapFont {
public:
 BitmapFont();
 ~BitmapFont();
 
 // Load font from .fnt file
 bool loadFromFile(std::string_view fntPath, SDL_Renderer* renderer);
 
 // Render text
 void drawText(SDL_Renderer* renderer, std::string_view text, 
 int x, int y, SDL_Color color = {255, 255, 255, 255});
 
 // Measure text dimensions
 int getTextWidth(std::string_view text) const;
 int getTextHeight() const { return lineHeight; }
 
 // Font properties
 int getLineHeight() const { return lineHeight; }
 int getBase() const { return base; }
 std::string getFaceName() const { return face; }
 int getSize() const noexcept { return size; }
 
 // Cleanup
 void cleanup();
 
private:
 std::string face;
 int size;
 int lineHeight;
 int base;
 int scaleW, scaleH;
 
 // Texture pages (usually just 1)
 std::unordered_map<int, SDL_Texture*> pageTextures;
 
 // Character glyphs
 std::unordered_map<int, CharGlyph> glyphs;
 
 // Parse .fnt file
 bool parseFntFile(std::string_view path);
 void parseLine(std::string_view line);
 void parseInfo(std::string_view line);
 void parseCommon(std::string_view line);
 void parsePage(std::string_view line, std::string_view basePath, SDL_Renderer* renderer);
 void parseChar(std::string_view line);
 
 // Helper functions
 std::string extractValue(std::string_view line, std::string_view key) const;
 int extractIntValue(std::string_view line, std::string_view key) const;
};

} // namespace graphics
} // namespace zombie
