#include "TextureAtlas.h"
#include <SDL2/SDL_image.h>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <limits>

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

SDL_Texture* TextureAtlas::getMipTexture(int level) const {
    if (level <= 0) return atlasTexture;
    if (level - 1 < static_cast<int>(atlasMipTextures.size())) {
        return atlasMipTextures[level - 1];
    }
    return nullptr;
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
    data.rotated = false;
    data.x = 0;
    data.y = 0;
    data.packedWidth = width;
    data.packedHeight = height;
    
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
    data.rotated = false;
    data.x = 0;
    data.y = 0;
    data.packedWidth = surface->w;
    data.packedHeight = surface->h;
    
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

    destroyAtlasTexture();
    destroyMipmaps();
    resetPlacement();

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

    if (config.generateMipmaps) {
        generateMipmaps();
    }

    // Build region map
    regions.clear();
    for (const auto& sprite : sprites) {
        if (!sprite.placed) continue;

        AtlasRegion region;
        region.name = sprite.name;
        region.rect = {sprite.x, sprite.y, sprite.packedWidth, sprite.packedHeight};
        region.originalWidth = sprite.width;
        region.originalHeight = sprite.height;
        region.rotated = sprite.rotated;

        // Calculate normalized UV coordinates
        region.u1 = static_cast<float>(sprite.x) / atlasWidth;
        region.v1 = static_cast<float>(sprite.y) / atlasHeight;
        region.u2 = static_cast<float>(sprite.x + sprite.packedWidth) / atlasWidth;
        region.v2 = static_cast<float>(sprite.y + sprite.packedHeight) / atlasHeight;

        regions[sprite.name] = region;
    }

    // Optionally release surfaces to save memory
    if (!config.keepSpriteSurfaces) {
        freeSurfaces();
    }

    std::cout << "Atlas built: " << atlasWidth << "x" << atlasHeight
              << " (" << sprites.size() << " sprites, "
              << (getUsedSpace() * 100.0f) << "% filled)" << std::endl;

    return true;
}

bool TextureAtlas::rebuild() {
    if (!config.keepSpriteSurfaces) {
        std::cerr << "Rebuild requested but keepSpriteSurfaces is disabled" << std::endl;
        return false;
    }
    return build();
}

bool TextureAtlas::addSpriteAndRebuild(const std::string& name, SDL_Surface* surface) {
    if (!config.keepSpriteSurfaces) {
        std::cerr << "addSpriteAndRebuild requires keepSpriteSurfaces=true" << std::endl;
        return false;
    }
    if (!addSprite(name, surface)) {
        return false;
    }
    return rebuild();
}

bool TextureAtlas::addSpriteAndRebuild(const std::string& name, const std::string& filePath) {
    if (!config.keepSpriteSurfaces) {
        std::cerr << "addSpriteAndRebuild requires keepSpriteSurfaces=true" << std::endl;
        return false;
    }
    if (!addSprite(name, filePath)) {
        return false;
    }
    return rebuild();
}

bool TextureAtlas::packSprites() {
    if (sprites.empty()) return false;

    bool packed = false;
    switch (config.method) {
        case TextureAtlas::Config::PackingMethod::Shelf:
            packed = packSpritesShelf();
            break;
        case TextureAtlas::Config::PackingMethod::MaxRects:
            packed = packSpritesMaxRects();
            break;
        default:
            packed = packSpritesShelf();
            break;
    }

    if (packed && config.powerOfTwo) {
        atlasWidth = nextPowerOfTwo(atlasWidth);
        atlasHeight = nextPowerOfTwo(atlasHeight);
    }

    return packed;
}

bool TextureAtlas::packSpritesShelf() {
    // Sort sprites by height (descending) for better packing
    std::sort(sprites.begin(), sprites.end(), 
              [](const SpriteData& a, const SpriteData& b) {
                  return a.height > b.height;
              });

    int currentX = config.padding;
    int currentY = config.padding;
    int rowHeight = 0;
    int maxWidth = 0;

    for (auto& sprite : sprites) {
        sprite.packedWidth = sprite.width;
        sprite.packedHeight = sprite.height;
        sprite.rotated = false;

        int spriteWidth = sprite.packedWidth + config.padding;
        int spriteHeight = sprite.packedHeight + config.padding;

        if (currentX + spriteWidth > config.maxWidth) {
            currentX = config.padding;
            currentY += rowHeight + config.padding;
            rowHeight = 0;
        }

        if (currentY + spriteHeight > config.maxHeight) {
            std::cerr << "Atlas full! Cannot fit sprite: " << sprite.name << std::endl;
            return false;
        }

        sprite.x = currentX;
        sprite.y = currentY;
        sprite.placed = true;

        currentX += spriteWidth;
        rowHeight = std::max(rowHeight, sprite.packedHeight);
        maxWidth = std::max(maxWidth, currentX);
    }

    atlasWidth = maxWidth + config.padding;
    atlasHeight = currentY + rowHeight + config.padding;
    return true;
}

namespace {
struct RectNode {
    int x;
    int y;
    int w;
    int h;
};
}

bool TextureAtlas::packSpritesMaxRects() {
    // Best-short-side-fit MaxRects with optional 90-degree rotation
    std::vector<RectNode> freeRects;
    freeRects.push_back({config.padding, config.padding, config.maxWidth - config.padding * 2, config.maxHeight - config.padding * 2});

    // Sort largest to smallest area to improve success rate
    std::sort(sprites.begin(), sprites.end(), [](const SpriteData& a, const SpriteData& b) {
        return (a.width * a.height) > (b.width * b.height);
    });

    atlasWidth = 0;
    atlasHeight = 0;

    for (auto& sprite : sprites) {
        int bestIndex = -1;
        int bestShortSide = std::numeric_limits<int>::max();
        int bestLongSide = std::numeric_limits<int>::max();
        bool bestRotated = false;
        RectNode bestNode{};

        auto tryFit = [&](const RectNode& rect, int sw, int sh, bool rotatedFlag) {
            if (sw > rect.w || sh > rect.h) return;
            int leftoverHoriz = rect.w - sw;
            int leftoverVert = rect.h - sh;
            int shortSideFit = std::min(leftoverHoriz, leftoverVert);
            int longSideFit = std::max(leftoverHoriz, leftoverVert);
            if (shortSideFit < bestShortSide || (shortSideFit == bestShortSide && longSideFit < bestLongSide)) {
                bestShortSide = shortSideFit;
                bestLongSide = longSideFit;
                bestIndex = static_cast<int>(&rect - &freeRects[0]);
                bestNode = {rect.x, rect.y, sw, sh};
                bestRotated = rotatedFlag;
            }
        };

        for (size_t i = 0; i < freeRects.size(); ++i) {
            const auto& free = freeRects[i];
            tryFit(free, sprite.width + config.padding, sprite.height + config.padding, false);
            if (config.allowRotation) {
                tryFit(free, sprite.height + config.padding, sprite.width + config.padding, true);
            }
        }

        if (bestIndex == -1) {
            std::cerr << "Atlas full! Cannot fit sprite: " << sprite.name << std::endl;
            return false;
        }

        sprite.x = bestNode.x;
        sprite.y = bestNode.y;
        sprite.placed = true;
        sprite.rotated = bestRotated;
        sprite.packedWidth = bestNode.w - config.padding;
        sprite.packedHeight = bestNode.h - config.padding;

        atlasWidth = std::max(atlasWidth, sprite.x + sprite.packedWidth + config.padding);
        atlasHeight = std::max(atlasHeight, sprite.y + sprite.packedHeight + config.padding);

        // Split free rectangle using Guillotine split
        RectNode free = freeRects[bestIndex];
        freeRects.erase(freeRects.begin() + bestIndex);

        RectNode bottom = {free.x, free.y + bestNode.h, free.w, free.h - bestNode.h};
        RectNode right = {free.x + bestNode.w, free.y, free.w - bestNode.w, bestNode.h};

        auto insertRect = [&](const RectNode& node) {
            if (node.w <= 0 || node.h <= 0) return;
            freeRects.push_back(node);
        };

        insertRect(bottom);
        insertRect(right);

        // Prune redundant rectangles
        for (size_t i = 0; i < freeRects.size(); ++i) {
            for (size_t j = i + 1; j < freeRects.size();) {
                const auto& a = freeRects[i];
                const auto& b = freeRects[j];
                bool bInsideA = (b.x >= a.x && b.y >= a.y && b.x + b.w <= a.x + a.w && b.y + b.h <= a.y + a.h);
                bool aInsideB = (a.x >= b.x && a.y >= b.y && a.x + a.w <= b.x + b.w && a.y + a.h <= b.y + b.h);
                if (bInsideA) {
                    freeRects.erase(freeRects.begin() + j);
                } else if (aInsideB) {
                    freeRects.erase(freeRects.begin() + i);
                    --i;
                    break;
                } else {
                    ++j;
                }
            }
        }
    }

    return true;
}

bool TextureAtlas::renderToAtlas() {
    // Create atlas texture (fallback through compressed/packed options)
    destroyMipmaps();
    std::vector<SDL_PixelFormatEnum> candidates = {
        config.textureFormat,
#ifdef SDL_PIXELFORMAT_ETC2_RGBA
        SDL_PIXELFORMAT_ETC2_RGBA,
#endif
#ifdef SDL_PIXELFORMAT_DXT5
        SDL_PIXELFORMAT_DXT5,
#endif
        SDL_PIXELFORMAT_RGBA4444,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_PIXELFORMAT_RGBA32
    };

    atlasTexture = nullptr;
    for (auto fmt : candidates) {
        atlasTexture = tryCreateTexture(fmt, atlasWidth, atlasHeight);
        if (atlasTexture) {
            config.textureFormat = fmt;
            break;
        }
    }

    if (!atlasTexture) {
        std::cerr << "Failed to create atlas texture: " << SDL_GetError() << std::endl;
        return false;
    }

    SDL_SetTextureBlendMode(atlasTexture, SDL_BLENDMODE_BLEND);

    SDL_Texture* oldTarget = SDL_GetRenderTarget(renderer);
    SDL_SetRenderTarget(renderer, atlasTexture);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    // Render each sprite to atlas
    for (const auto& sprite : sprites) {
        if (!sprite.placed) continue;

        SDL_Surface* surfaceToUse = sprite.surface;
        SDL_Surface* rotatedSurface = nullptr;

        if (sprite.rotated) {
            rotatedSurface = SDL_CreateRGBSurfaceWithFormat(0, sprite.packedWidth, sprite.packedHeight, 32, SDL_PIXELFORMAT_RGBA32);
            if (rotatedSurface && sprite.surface) {
                bool srcLocked = false;
                bool dstLocked = false;
                if (SDL_LockSurface(sprite.surface) == 0) {
                    srcLocked = true;
                }
                if (SDL_LockSurface(rotatedSurface) == 0) {
                    dstLocked = true;
                }

                if (srcLocked && dstLocked) {
                    auto* srcPixels = static_cast<Uint32*>(sprite.surface->pixels);
                    auto* dstPixels = static_cast<Uint32*>(rotatedSurface->pixels);
                    int srcPitch = sprite.surface->pitch / 4;
                    int dstPitch = rotatedSurface->pitch / 4;
                    for (int y = 0; y < sprite.height; ++y) {
                        for (int x = 0; x < sprite.width; ++x) {
                            dstPixels[x * dstPitch + (rotatedSurface->h - 1 - y)] = srcPixels[y * srcPitch + x];
                        }
                    }
                    surfaceToUse = rotatedSurface;
                }

                if (dstLocked) {
                    SDL_UnlockSurface(rotatedSurface);
                }
                if (srcLocked) {
                    SDL_UnlockSurface(sprite.surface);
                }

                if (!surfaceToUse && rotatedSurface) {
                    SDL_FreeSurface(rotatedSurface);
                    rotatedSurface = nullptr;
                    surfaceToUse = sprite.surface;
                }
            }
        }

        SDL_Texture* tempTex = SDL_CreateTextureFromSurface(renderer, surfaceToUse);
        if (!tempTex) {
            std::cerr << "Failed to create temp texture for: " << sprite.name << std::endl;
            if (rotatedSurface) {
                SDL_FreeSurface(rotatedSurface);
            }
            continue;
        }

        SDL_Rect dstRect = {sprite.x, sprite.y, sprite.packedWidth, sprite.packedHeight};
        SDL_RenderCopy(renderer, tempTex, nullptr, &dstRect);

        SDL_DestroyTexture(tempTex);
        if (rotatedSurface) {
            SDL_FreeSurface(rotatedSurface);
        }
    }

    SDL_SetRenderTarget(renderer, oldTarget);

    return true;
}

SDL_Texture* TextureAtlas::tryCreateTexture(SDL_PixelFormatEnum fmt, int w, int h) {
    SDL_Texture* tex = SDL_CreateTexture(renderer, fmt, SDL_TEXTUREACCESS_TARGET, w, h);
    if (tex) {
        SDL_SetTextureBlendMode(tex, SDL_BLENDMODE_BLEND);
    }
    return tex;
}

bool TextureAtlas::generateMipmaps() {
    if (!atlasTexture) return false;
    destroyMipmaps();

    int levelWidth = atlasWidth / 2;
    int levelHeight = atlasHeight / 2;
    int levelsCreated = 0;
    SDL_Texture* source = atlasTexture;

    SDL_Texture* oldTarget = SDL_GetRenderTarget(renderer);

    while (levelWidth > 0 && levelHeight > 0 && levelsCreated + 1 < config.maxMipLevels) {
        SDL_Texture* mip = tryCreateTexture(config.textureFormat, levelWidth, levelHeight);
        if (!mip) {
            break;
        }

        SDL_SetRenderTarget(renderer, mip);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);

        SDL_Rect dst{0, 0, levelWidth, levelHeight};
        SDL_RenderCopy(renderer, source, nullptr, &dst);

        atlasMipTextures.push_back(mip);
        source = mip;
        levelsCreated++;
        levelWidth = std::max(1, levelWidth / 2);
        levelHeight = std::max(1, levelHeight / 2);
    }

    SDL_SetRenderTarget(renderer, oldTarget);
    return !atlasMipTextures.empty();
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
            usedPixels += sprite.packedWidth * sprite.packedHeight;
        }
    }
    
    int totalPixels = atlasWidth * atlasHeight;
    return static_cast<float>(usedPixels) / totalPixels;
}

void TextureAtlas::clear() {
    destroyAtlasTexture();
    destroyMipmaps();
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

void TextureAtlas::destroyAtlasTexture() {
    if (atlasTexture) {
        SDL_DestroyTexture(atlasTexture);
        atlasTexture = nullptr;
    }
}

void TextureAtlas::destroyMipmaps() {
    for (auto* tex : atlasMipTextures) {
        if (tex) {
            SDL_DestroyTexture(tex);
        }
    }
    atlasMipTextures.clear();
}

void TextureAtlas::resetPlacement() {
    for (auto& sprite : sprites) {
        sprite.placed = false;
        sprite.rotated = false;
        sprite.x = 0;
        sprite.y = 0;
        sprite.packedWidth = sprite.width;
        sprite.packedHeight = sprite.height;
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
    (void)pattern;
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
