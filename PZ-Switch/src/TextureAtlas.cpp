#include "TextureAtlas.h"
#include <SDL2/SDL_image.h>
#include <iostream>
#include <algorithm>
#include <cmath>

namespace zombie {
namespace assets {

TextureAtlas::TextureAtlas(SDL_Renderer* r, const Config& cfg)
    : renderer(r)
    , config(cfg)
    , atlasTexture(nullptr)
    , atlasWidth(0)
    , atlasHeight(0)
{
}

TextureAtlas::~TextureAtlas() {
    clear();
}

bool TextureAtlas::addSprite(const std::string& name, SDL_Texture* texture,
                             int width, int height) {
    if (!texture) return false;
    
    // Create surface from texture
    SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormat(
        0, width, height, 32, SDL_PIXELFORMAT_RGBA32);
    
    if (!surface) {
        std::cerr << "Failed to create surface for sprite: " << name << std::endl;
        return false;
    }
    
    // Set texture as render target and read pixels
    SDL_Texture* oldTarget = SDL_GetRenderTarget(renderer);
    SDL_SetRenderTarget(renderer, texture);
    SDL_RenderReadPixels(renderer, nullptr, SDL_PIXELFORMAT_RGBA32,
                        surface->pixels, surface->pitch);
    SDL_SetRenderTarget(renderer, oldTarget);
    
    SpriteData data;
    data.name = name;
    data.surface = surface;
    data.width = width;
    data.height = height;
    data.placed = false;
    data.x = 0;
    data.y = 0;
    
    sprites.push_back(data);
    return true;
}

bool TextureAtlas::addSprite(const std::string& name, SDL_Surface* surface) {
    if (!surface) return false;
    
    // Convert to RGBA32 if needed
    SDL_Surface* rgbaSurface = surface;
    if (surface->format->format != SDL_PIXELFORMAT_RGBA32) {
        rgbaSurface = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_RGBA32, 0);
        if (!rgbaSurface) {
            std::cerr << "Failed to convert surface format for: " << name << std::endl;
            return false;
        }
    }
    
    SpriteData data;
    data.name = name;
    data.surface = (rgbaSurface == surface) ? SDL_DuplicateSurface(surface) : rgbaSurface;
    data.width = surface->w;
    data.height = surface->h;
    data.placed = false;
    data.x = 0;
    data.y = 0;
    
    sprites.push_back(data);
    return true;
}

bool TextureAtlas::addSprite(const std::string& name, const std::string& filePath) {
    SDL_Surface* surface = IMG_Load(filePath.c_str());
    if (!surface) {
        std::cerr << "Failed to load sprite: " << filePath << " - " << IMG_GetError() << std::endl;
        return false;
    }
    
    bool result = addSprite(name, surface);
    SDL_FreeSurface(surface);
    return result;
}

bool TextureAtlas::build() {
    if (sprites.empty()) {
        std::cerr << "Cannot build empty atlas" << std::endl;
        return false;
    }
    
    // Pack sprites
    if (!packSprites()) {
        std::cerr << "Failed to pack sprites into atlas" << std::endl;
        return false;
    }
    
    // Render to atlas texture
    if (!renderToAtlas()) {
        std::cerr << "Failed to render atlas texture" << std::endl;
        return false;
    }
    
    // Build region map
    for (const auto& sprite : sprites) {
        AtlasRegion region;
        region.name = sprite.name;
        region.rect = {sprite.x, sprite.y, sprite.width, sprite.height};
        region.originalWidth = sprite.width;
        region.originalHeight = sprite.height;
        
        // Calculate normalized UV coordinates
        region.u1 = static_cast<float>(sprite.x) / atlasWidth;
        region.v1 = static_cast<float>(sprite.y) / atlasHeight;
        region.u2 = static_cast<float>(sprite.x + sprite.width) / atlasWidth;
        region.v2 = static_cast<float>(sprite.y + sprite.height) / atlasHeight;
        
        regions[sprite.name] = region;
    }
    
    // Free surfaces (no longer needed)
    freeSurfaces();
    
    std::cout << "Atlas built: " << atlasWidth << "x" << atlasHeight 
              << " (" << sprites.size() << " sprites, "
              << (getUsedSpace() * 100.0f) << "% filled)" << std::endl;
    
    return true;
}

bool TextureAtlas::packSprites() {
    // Sort sprites by height (descending) for better packing
    std::sort(sprites.begin(), sprites.end(), 
              [](const SpriteData& a, const SpriteData& b) {
                  return a.height > b.height;
              });
    
    // Simple shelf packing algorithm
    int currentX = config.padding;
    int currentY = config.padding;
    int rowHeight = 0;
    int maxWidth = 0;
    
    for (auto& sprite : sprites) {
        int spriteWidth = sprite.width + config.padding;
        int spriteHeight = sprite.height + config.padding;
        
        // Check if sprite fits on current row
        if (currentX + spriteWidth > config.maxWidth) {
            // Move to next row
            currentX = config.padding;
            currentY += rowHeight + config.padding;
            rowHeight = 0;
        }
        
        // Check if atlas is full
        if (currentY + spriteHeight > config.maxHeight) {
            std::cerr << "Atlas full! Cannot fit sprite: " << sprite.name << std::endl;
            return false;
        }
        
        // Place sprite
        sprite.x = currentX;
        sprite.y = currentY;
        sprite.placed = true;
        
        // Update tracking
        currentX += spriteWidth;
        rowHeight = std::max(rowHeight, sprite.height);
        maxWidth = std::max(maxWidth, currentX);
    }
    
    // Calculate final atlas dimensions
    atlasWidth = maxWidth + config.padding;
    atlasHeight = currentY + rowHeight + config.padding;
    
    // Round up to power of 2 if requested
    if (config.powerOfTwo) {
        atlasWidth = nextPowerOfTwo(atlasWidth);
        atlasHeight = nextPowerOfTwo(atlasHeight);
    }
    
    return true;
}

bool TextureAtlas::renderToAtlas() {
    // Create atlas texture
    atlasTexture = SDL_CreateTexture(renderer,
                                     SDL_PIXELFORMAT_RGBA32,
                                     SDL_TEXTUREACCESS_TARGET,
                                     atlasWidth, atlasHeight);
    
    if (!atlasTexture) {
        std::cerr << "Failed to create atlas texture: " << SDL_GetError() << std::endl;
        return false;
    }
    
    // Enable alpha blending
    SDL_SetTextureBlendMode(atlasTexture, SDL_BLENDMODE_BLEND);
    
    // Set atlas as render target
    SDL_Texture* oldTarget = SDL_GetRenderTarget(renderer);
    SDL_SetRenderTarget(renderer, atlasTexture);
    
    // Clear atlas with transparent color
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    
    // Render each sprite to atlas
    for (const auto& sprite : sprites) {
        if (!sprite.placed) continue;
        
        // Create temporary texture from surface
        SDL_Texture* tempTex = SDL_CreateTextureFromSurface(renderer, sprite.surface);
        if (!tempTex) {
            std::cerr << "Failed to create temp texture for: " << sprite.name << std::endl;
            continue;
        }
        
        // Copy to atlas
        SDL_Rect dstRect = {sprite.x, sprite.y, sprite.width, sprite.height};
        SDL_RenderCopy(renderer, tempTex, nullptr, &dstRect);
        
        SDL_DestroyTexture(tempTex);
    }
    
    // Restore render target
    SDL_SetRenderTarget(renderer, oldTarget);
    
    return true;
}

const AtlasRegion* TextureAtlas::getRegion(const std::string& name) const {
    auto it = regions.find(name);
    if (it != regions.end()) {
        return &it->second;
    }
    return nullptr;
}

float TextureAtlas::getUsedSpace() const {
    if (atlasWidth == 0 || atlasHeight == 0) return 0.0f;
    
    int usedPixels = 0;
    for (const auto& sprite : sprites) {
        if (sprite.placed) {
            usedPixels += sprite.width * sprite.height;
        }
    }
    
    int totalPixels = atlasWidth * atlasHeight;
    return static_cast<float>(usedPixels) / totalPixels;
}

void TextureAtlas::clear() {
    if (atlasTexture) {
        SDL_DestroyTexture(atlasTexture);
        atlasTexture = nullptr;
    }
    
    freeSurfaces();
    sprites.clear();
    regions.clear();
    atlasWidth = 0;
    atlasHeight = 0;
}

void TextureAtlas::freeSurfaces() {
    for (auto& sprite : sprites) {
        if (sprite.surface) {
            SDL_FreeSurface(sprite.surface);
            sprite.surface = nullptr;
        }
    }
}

int TextureAtlas::nextPowerOfTwo(int n) const {
    if (n <= 0) return 1;
    n--;
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    return n + 1;
}

// ===== AtlasBuilder =====

AtlasBuilder::AtlasBuilder(SDL_Renderer* r)
    : renderer(r)
{
}

bool AtlasBuilder::addSpritesFromDirectory(const std::string& dirPath,
                                          const std::string& pattern) {
    // This would need platform-specific directory iteration
    // For now, just add to the list
    spritePaths.push_back(dirPath);
    return true;
}

bool AtlasBuilder::addSpritesWithPrefix(const std::string& dirPath,
                                       const std::string& prefix) {
    // Similar to above - platform-specific
    spritePaths.push_back(dirPath + "/" + prefix);
    return true;
}

std::shared_ptr<TextureAtlas> AtlasBuilder::build(const TextureAtlas::Config& config) {
    auto atlas = std::make_shared<TextureAtlas>(renderer, config);
    
    // Add all sprites
    for (const auto& path : spritePaths) {
        std::string name = path.substr(path.find_last_of("/\\") + 1);
        atlas->addSprite(name, path);
    }
    
    // Build atlas
    if (atlas->build()) {
        return atlas;
    }
    
    return nullptr;
}

} // namespace assets
} // namespace zombie
