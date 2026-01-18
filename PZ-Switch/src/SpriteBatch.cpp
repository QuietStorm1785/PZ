#include "SpriteBatch.h"
#include <algorithm>

namespace zombie {
namespace graphics {

SpriteBatch::SpriteBatch()
 : renderer(nullptr)
 , isDrawing(false)
 , drawCallCount(0)
 , spriteCount(0)
{
 batch.reserve(1000); // Pre-allocate for efficiency
}

SpriteBatch::~SpriteBatch() {
 if (isDrawing) {
 end();
 }
}

void SpriteBatch::init(SDL_Renderer* r) {
 renderer = r;
}

void SpriteBatch::begin() {
 if (isDrawing) {
 flush();
 }
 
 isDrawing = true;
 batch.clear();
 resetStats();
}

void SpriteBatch::end() {
 if (!isDrawing) {
 return;
 }
 
 flush();
 isDrawing = false;
}

void SpriteBatch::draw(Sprite* sprite) {
 if (!sprite || !sprite->getTexture()) {
 return;
 }
 
 BatchItem item;
 item.texture = sprite->getTexture();
 
 // Get sprite properties
 float x = sprite->getX();
 float y = sprite->getY();
 float width = sprite->getWidth() * sprite->getScaleX();
 float height = sprite->getHeight() * sprite->getScaleY();
 float originX = sprite->getOriginX();
 float originY = sprite->getOriginY();
 
 // Calculate destination rectangle
 item.dstRect.x = static_cast<int>(x - originX * width);
 item.dstRect.y = static_cast<int>(y - originY * height);
 item.dstRect.w = static_cast<int>(width);
 item.dstRect.h = static_cast<int>(height);
 
 // Source rectangle
 item.hasSourceRect = sprite->hasSourceRect();
 if (item.hasSourceRect) {
 item.srcRect = sprite->getSourceRect();
 }
 
 // Rotation
 item.rotation = sprite->getRotation();
 item.center.x = static_cast<int>(originX * width);
 item.center.y = static_cast<int>(originY * height);
 
 // Color modulation
 sprite->getColor(&item.r, &item.g, &item.b);
 item.a = sprite->getAlpha();
 
 // Flip flags
 item.flip = SDL_FLIP_NONE;
 if (sprite->isFlippedHorizontal()) {
 item.flip = static_cast<SDL_RendererFlip>(item.flip | SDL_FLIP_HORIZONTAL);
 }
 if (sprite->isFlippedVertical()) {
 item.flip = static_cast<SDL_RendererFlip>(item.flip | SDL_FLIP_VERTICAL);
 }
 
 batch.push_back(item);
 spriteCount++;
}

void SpriteBatch::draw(SDL_Texture* texture, float x, float y) {
 if (!texture) return;
 
 int w, h;
 SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
 draw(texture, x, y, static_cast<float>(w), static_cast<float>(h));
}

void SpriteBatch::draw(SDL_Texture* texture, float x, float y, float width, float height) {
 if (!texture) return;
 
 BatchItem item;
 item.texture = texture;
 item.dstRect.x = static_cast<int>(x);
 item.dstRect.y = static_cast<int>(y);
 item.dstRect.w = static_cast<int>(width);
 item.dstRect.h = static_cast<int>(height);
 item.hasSourceRect = false;
 item.rotation = 0.0f;
 item.flip = SDL_FLIP_NONE;
 item.r = item.g = item.b = item.a = 255;
 
 batch.push_back(item);
 spriteCount++;
}

void SpriteBatch::draw(SDL_Texture* texture, const SDL_Rect* srcRect, const SDL_Rect* dstRect,
 float rotation, const SDL_Point* center, SDL_RendererFlip flip) {
 if (!texture || !dstRect) return;
 
 BatchItem item;
 item.texture = texture;
 item.dstRect = *dstRect;
 item.hasSourceRect = (srcRect != nullptr);
 if (item.hasSourceRect) {
 item.srcRect = *srcRect;
 }
 item.rotation = rotation;
 if (center) {
 item.center = *center;
 } else {
 item.center = {0, 0};
 }
 item.flip = flip;
 item.r = item.g = item.b = item.a = 255;
 
 batch.push_back(item);
 spriteCount++;
}

void SpriteBatch::flush() {
 if (!renderer || batch.empty()) {
 return;
 }
 
 // Sort by texture to minimize texture switches (optimization)
 std::sort(batch.begin(), batch.end(), 
 [](const BatchItem& a, const BatchItem& b) {
 return a.texture < b.texture;
 });
 
 // Render all batched items
 SDL_Texture* currentTexture = nullptr;
 
 for (const auto& item : batch) {
 // Switch texture if needed
 if (item.texture != currentTexture) {
 currentTexture = item.texture;
 drawCallCount++;
 }
 
 // Apply color modulation
 SDL_SetTextureColorMod(item.texture, item.r, item.g, item.b);
 SDL_SetTextureAlphaMod(item.texture, item.a);
 
 // Render
 const SDL_Rect* src = item.hasSourceRect ? &item.srcRect : nullptr;
 
 if (item.rotation != 0.0f || item.flip != SDL_FLIP_NONE) {
 const SDL_Point* center = (item.rotation != 0.0f) ? &item.center : nullptr;
 SDL_RenderCopyEx(renderer, item.texture, src, &item.dstRect, 
 item.rotation, center, item.flip);
 } else {
 SDL_RenderCopy(renderer, item.texture, src, &item.dstRect);
 }
 }
 
 batch.clear();
}

void SpriteBatch::resetStats() {
 drawCallCount = 0;
 spriteCount = 0;
}

} // namespace graphics
} // namespace zombie
