#include "Sprite.h"
#include <cmath>

namespace zombie {
namespace graphics {

Sprite::Sprite()
    : texture(nullptr)
    , x(0.0f)
    , y(0.0f)
    , width(0.0f)
    , height(0.0f)
    , scaleX(1.0f)
    , scaleY(1.0f)
    , rotation(0.0f)
    , originX(0.0f)
    , originY(0.0f)
    , red(255)
    , green(255)
    , blue(255)
    , alpha(255)
    , useSourceRect(false)
    , flipH(false)
    , flipV(false)
{
}

Sprite::Sprite(SDL_Texture* tex)
    : Sprite()
{
    setTexture(tex);
}

Sprite::~Sprite() {
    // Texture is managed by TextureManager, don't delete here
}

void Sprite::setTexture(SDL_Texture* tex) {
    texture = tex;
    
    // Auto-set size from texture if no size set
    if (texture && width == 0.0f && height == 0.0f) {
        int w, h;
        SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
        width = static_cast<float>(w);
        height = static_cast<float>(h);
    }
}

void Sprite::setPosition(float px, float py) {
    x = px;
    y = py;
}

void Sprite::setSize(float w, float h) {
    width = w;
    height = h;
}

void Sprite::setScale(float sx, float sy) {
    scaleX = sx;
    scaleY = sy;
}

void Sprite::setRotation(float angle) {
    rotation = angle;
}

void Sprite::setColor(Uint8 r, Uint8 g, Uint8 b) {
    red = r;
    green = g;
    blue = b;
}

void Sprite::setAlpha(Uint8 a) {
    alpha = a;
}

void Sprite::getColor(Uint8* r, Uint8* g, Uint8* b) const {
    if (r) *r = red;
    if (g) *g = green;
    if (b) *b = blue;
}

void Sprite::setSourceRect(int sx, int sy, int sw, int sh) {
    useSourceRect = true;
    sourceRect.x = sx;
    sourceRect.y = sy;
    sourceRect.w = sw;
    sourceRect.h = sh;
    
    // Update sprite size to match source rect
    width = static_cast<float>(sw);
    height = static_cast<float>(sh);
}

void Sprite::clearSourceRect() {
    useSourceRect = false;
    
    // Reset size from texture
    if (texture) {
        int w, h;
        SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
        width = static_cast<float>(w);
        height = static_cast<float>(h);
    }
}

void Sprite::setOrigin(float ox, float oy) {
    originX = ox;
    originY = oy;
}

void Sprite::render(SDL_Renderer* renderer) {
    if (!texture || !renderer) {
        return;
    }
    
    // Apply color modulation
    SDL_SetTextureColorMod(texture, red, green, blue);
    SDL_SetTextureAlphaMod(texture, alpha);
    
    // Calculate final width and height with scale
    float finalWidth = width * scaleX;
    float finalHeight = height * scaleY;
    
    // Calculate position with origin offset
    float drawX = x - (originX * finalWidth);
    float drawY = y - (originY * finalHeight);
    
    // Destination rectangle
    SDL_Rect dstRect;
    dstRect.x = static_cast<int>(drawX);
    dstRect.y = static_cast<int>(drawY);
    dstRect.w = static_cast<int>(finalWidth);
    dstRect.h = static_cast<int>(finalHeight);
    
    // Source rectangle (or nullptr for full texture)
    SDL_Rect* srcRect = useSourceRect ? &sourceRect : nullptr;
    
    // Flip flags
    SDL_RendererFlip flipFlags = SDL_FLIP_NONE;
    if (flipH) flipFlags = static_cast<SDL_RendererFlip>(flipFlags | SDL_FLIP_HORIZONTAL);
    if (flipV) flipFlags = static_cast<SDL_RendererFlip>(flipFlags | SDL_FLIP_VERTICAL);
    
    // Render with rotation
    if (rotation != 0.0f) {
        SDL_Point center;
        center.x = static_cast<int>(originX * finalWidth);
        center.y = static_cast<int>(originY * finalHeight);
        SDL_RenderCopyEx(renderer, texture, srcRect, &dstRect, rotation, &center, flipFlags);
    } else {
        SDL_RenderCopyEx(renderer, texture, srcRect, &dstRect, 0.0, nullptr, flipFlags);
    }
}

} // namespace graphics
} // namespace zombie
