#include "BitmapFont.h"
#include <SDL2/SDL_image.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

namespace zombie {
namespace graphics {

BitmapFont::BitmapFont()
    : face("unknown")
    , size(12)
    , lineHeight(12)
    , base(12)
    , scaleW(512)
    , scaleH(512)
{
}

BitmapFont::~BitmapFont() {
    cleanup();
}

void BitmapFont::cleanup() {
    for (auto& pair : pageTextures) {
        if (pair.second) {
            SDL_DestroyTexture(pair.second);
        }
    }
    pageTextures.clear();
    glyphs.clear();
}

bool BitmapFont::loadFromFile(const std::string& fntPath, SDL_Renderer* renderer) {
    cleanup();
    
    if (!parseFntFile(fntPath)) {
        std::cerr << "Failed to parse font file: " << fntPath << std::endl;
        return false;
    }
    
    std::cout << "Loaded font: " << face << " size=" << size 
              << " glyphs=" << glyphs.size() << std::endl;
    
    return !pageTextures.empty() && !glyphs.empty();
}

bool BitmapFont::parseFntFile(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        return false;
    }
    
    // Extract base path for finding texture files
    size_t lastSlash = path.find_last_of("/\\");
    std::string basePath = (lastSlash != std::string::npos) 
        ? path.substr(0, lastSlash + 1) 
        : "";
    
    std::string line;
    SDL_Renderer* tempRenderer = nullptr; // Will be set on first page
    
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        parseLine(line);
    }
    
    file.close();
    return true;
}

void BitmapFont::parseLine(const std::string& line) {
    if (line.find("info ") == 0) {
        parseInfo(line);
    } else if (line.find("common ") == 0) {
        parseCommon(line);
    } else if (line.find("page ") == 0) {
        // Page parsing will be deferred - we need renderer
    } else if (line.find("char ") == 0) {
        parseChar(line);
    }
}

void BitmapFont::parseInfo(const std::string& line) {
    face = extractValue(line, "face");
    size = extractIntValue(line, "size");
}

void BitmapFont::parseCommon(const std::string& line) {
    lineHeight = extractIntValue(line, "lineHeight");
    base = extractIntValue(line, "base");
    scaleW = extractIntValue(line, "scaleW");
    scaleH = extractIntValue(line, "scaleH");
}

void BitmapFont::parsePage(const std::string& line, const std::string& basePath, SDL_Renderer* renderer) {
    int pageId = extractIntValue(line, "id");
    std::string file = extractValue(line, "file");
    
    // Remove quotes from filename
    file.erase(std::remove(file.begin(), file.end(), '\"'), file.end());
    
    std::string fullPath = basePath + file;
    
    // Load texture
    SDL_Surface* surface = IMG_Load(fullPath.c_str());
    if (!surface) {
        std::cerr << "Failed to load font texture: " << fullPath << std::endl;
        return;
    }
    
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    
    if (!texture) {
        std::cerr << "Failed to create font texture: " << fullPath << std::endl;
        return;
    }
    
    // Enable alpha blending
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    
    pageTextures[pageId] = texture;
    std::cout << "Loaded font page " << pageId << ": " << file << std::endl;
}

void BitmapFont::parseChar(const std::string& line) {
    CharGlyph glyph;
    
    glyph.id = extractIntValue(line, "id");
    glyph.x = extractIntValue(line, "x");
    glyph.y = extractIntValue(line, "y");
    glyph.width = extractIntValue(line, "width");
    glyph.height = extractIntValue(line, "height");
    glyph.xoffset = extractIntValue(line, "xoffset");
    glyph.yoffset = extractIntValue(line, "yoffset");
    glyph.xadvance = extractIntValue(line, "xadvance");
    glyph.page = extractIntValue(line, "page");
    
    glyphs[glyph.id] = glyph;
}

std::string BitmapFont::extractValue(const std::string& line, const std::string& key) const {
    size_t pos = line.find(key + "=");
    if (pos == std::string::npos) return "";
    
    pos += key.length() + 1;
    
    // Handle quoted strings
    if (pos < line.length() && line[pos] == '"') {
        pos++;
        size_t endPos = line.find('"', pos);
        if (endPos != std::string::npos) {
            return line.substr(pos, endPos - pos);
        }
    }
    
    // Handle space-delimited values
    size_t endPos = line.find(' ', pos);
    if (endPos == std::string::npos) {
        return line.substr(pos);
    }
    return line.substr(pos, endPos - pos);
}

int BitmapFont::extractIntValue(const std::string& line, const std::string& key) const {
    std::string value = extractValue(line, key);
    if (value.empty()) return 0;
    
    try {
        return std::stoi(value);
    } catch (...) {
        return 0;
    }
}

void BitmapFont::drawText(SDL_Renderer* renderer, const std::string& text, 
                         int x, int y, SDL_Color color) {
    if (text.empty() || pageTextures.empty()) {
        return;
    }
    
    // Lazy-load page textures if needed
    if (pageTextures.empty()) {
        // Pages weren't loaded during parsing - this shouldn't happen
        // but we'll handle it gracefully
        return;
    }
    
    int currentX = x;
    int currentY = y;
    
    for (char c : text) {
        int charCode = static_cast<int>(static_cast<unsigned char>(c));
        
        // Handle newlines
        if (c == '\n') {
            currentX = x;
            currentY += lineHeight;
            continue;
        }
        
        // Find glyph
        auto it = glyphs.find(charCode);
        if (it == glyphs.end()) {
            // Character not found, skip
            continue;
        }
        
        const CharGlyph& glyph = it->second;
        
        // Get texture for this page
        auto texIt = pageTextures.find(glyph.page);
        if (texIt == pageTextures.end()) {
            continue;
        }
        
        SDL_Texture* texture = texIt->second;
        
        // Apply color modulation
        SDL_SetTextureColorMod(texture, color.r, color.g, color.b);
        SDL_SetTextureAlphaMod(texture, color.a);
        
        // Source rectangle
        SDL_Rect srcRect;
        srcRect.x = glyph.x;
        srcRect.y = glyph.y;
        srcRect.w = glyph.width;
        srcRect.h = glyph.height;
        
        // Destination rectangle
        SDL_Rect dstRect;
        dstRect.x = currentX + glyph.xoffset;
        dstRect.y = currentY + glyph.yoffset;
        dstRect.w = glyph.width;
        dstRect.h = glyph.height;
        
        // Render character
        SDL_RenderCopy(renderer, texture, &srcRect, &dstRect);
        
        // Advance cursor
        currentX += glyph.xadvance;
    }
}

int BitmapFont::getTextWidth(const std::string& text) const {
    int width = 0;
    
    for (char c : text) {
        if (c == '\n') break; // Stop at first newline
        
        int charCode = static_cast<int>(static_cast<unsigned char>(c));
        auto it = glyphs.find(charCode);
        if (it != glyphs.end()) {
            width += it->second.xadvance;
        }
    }
    
    return width;
}

} // namespace graphics
} // namespace zombie
